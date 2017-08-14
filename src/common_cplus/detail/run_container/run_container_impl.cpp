#include "run_container_impl.h"
#include "timer_impl.h"
#include "log.h"

RunContainerImpl::RunContainerImpl(const std::string &id)
    : m_id(id)
    , m_iowork(m_ioservice)
    , m_working(false)
    , m_lock_join(false)
{
}

RunContainerImpl::~RunContainerImpl()
{
    INFO("enter ~RunContainerImpl(), id = {}", m_id);
    stop();
    join();

    if (m_thread.joinable())
    {
        m_thread.detach();
    }

    INFO("leave ~RunContainerImpl(), id = {}", m_id);
}

void RunContainerImpl::join()
{
    if (m_lock_join)
    {
        return;
    }

    m_lock_join = true;

    if (m_thread.joinable() && std::this_thread::get_id() != m_thread.get_id())
    {
        m_thread.join();
        m_thread = std::thread();
    }
}

void RunContainerImpl::run(bool mainloop)
{
    if (m_working == false)
    {
        m_working = true;

        if (mainloop)
        {
            run_func();
        }
        else
        {
            m_thread = std::thread(std::bind(&RunContainerImpl::run_func, shared_from_this()));
        }
    }
}

void RunContainerImpl::run_func()
{
    while (m_working)
    {
#ifndef _DEBUG

        try
        {
#endif
            boost::system::error_code ec;
            m_ioservice.run(ec);

            if (ec)
            {
                ERR("error = {}", ec.message());
            }

#ifndef _DEBUG
        }
        catch (...)
        {
            ERR("unknow err");
        }

#endif
    }
}

void RunContainerImpl::stop()
{
    if (m_working)
    {
        m_working = false;
        m_ioservice.stop();
    }
}

void RunContainerImpl::post(const std::function<void(void)> &func)
{
    m_ioservice.post(func);
}

std::shared_ptr<TimerImpl> RunContainerImpl::timeout(
    unsigned timeout,
    const std::function<void(void)> &func,
    bool loop)
{
    auto timer = std::make_shared<TimerImpl>(m_ioservice);
    timer->init(timeout, func, loop);
    timer->go();
    return timer;
}
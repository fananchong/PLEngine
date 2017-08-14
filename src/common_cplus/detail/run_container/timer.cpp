#include "timer.h"
#include "timer_impl.h"
#include "run_container_main.h"
#include "log.h"

Timer::Timer()
{
}

Timer::Timer(
    unsigned timeout,
    const std::function<void(void)> &func,
    bool loop)
{
    m_impl = std::make_shared<TimerImpl>(g_pmain->get_io_service());
    m_impl->init(timeout, func, loop);
    m_impl->go();
}

Timer::Timer(const Timer &rsh)
    : m_impl(rsh.m_impl)
{
}

Timer::Timer(const std::shared_ptr<TimerImpl> &rsh)
    : m_impl(rsh)
{
}

Timer::~Timer()
{
    INFO("enter ~Timer()");
}

void Timer::cancel()
{
    if (m_impl)
    {
        m_impl->cancel();
        m_impl->clear();
    }
}

static void call_timeout(
    const std::shared_ptr<TimerImpl> &/*impl*/,
    const std::function<void(void)> &func)
{
    if (func)
    {
        func();
    }
}

void timeout(unsigned timeout, const std::function<void(void)> &func)
{
    auto impl = std::make_shared<TimerImpl>(g_pmain->get_io_service());
    impl->init(timeout, std::bind(call_timeout, impl, func), false);
    impl->go();
}
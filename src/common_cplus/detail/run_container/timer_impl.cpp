#include "timer_impl.h"
#include "log.h"


TimerImpl::TimerImpl(boost::asio::io_service &io_service)
    : m_timer(io_service)
    , m_millisecond(0)
    , m_loop(false)
{
}

void TimerImpl::init(
    unsigned millisecond,
    const std::function<void()> &cb,
    bool loop)
{
    m_millisecond = millisecond;
    m_cb = cb;
    m_loop = loop;
}

TimerImpl::~TimerImpl()
{
    INFO("enter ~TimerImpl()");
}

void TimerImpl::go()
{
    m_timer.expires_from_now(boost::posix_time::milliseconds(m_millisecond));
    m_timer.async_wait(std::bind(&TimerImpl::cb_wrip, this, std::placeholders::_1)); // no need shared_from_this()
}

void TimerImpl::cb_wrip(const boost::system::error_code& e)
{
    if (!e)
    {
        if (m_cb)
        {
            m_cb();
        }

        if (m_loop)
        {
            go();
        }
    }
}

void TimerImpl::cancel()
{
    m_loop = false;
    boost::system::error_code ec;
    m_timer.cancel(ec);
}

void TimerImpl::clear()
{
    m_loop = false;
    m_millisecond = 0;

    if (m_cb)
    {
        m_cb = std::function<void()>();
    }
}
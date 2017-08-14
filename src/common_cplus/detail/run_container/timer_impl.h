#ifndef __TIMER_IMPL_H__
#define __TIMER_IMPL_H__

#include <boost/asio.hpp>
#include <memory>
#include <functional>

class TimerImpl
{
public:
    TimerImpl(boost::asio::io_service &io_service);
    void init(
        unsigned millisecond,
        const std::function<void()> &cb,
        bool loop = false);

    virtual ~TimerImpl();

    void go();
    void cancel();
    void clear();

private:
    void cb_wrip(const boost::system::error_code& e);

    boost::asio::deadline_timer m_timer;
    unsigned m_millisecond;
    std::function<void()> m_cb;
    bool m_loop;
};

typedef boost::shared_ptr<TimerImpl> TimerImplPtr;

#endif
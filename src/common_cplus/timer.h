#ifndef __TIMER_H__
#define __TIMER_H__

#include <memory>
#include <functional>

class TimerImpl;
class Timer
{
public:
    Timer(
        unsigned timeout,
        const std::function<void(void)> &func,
        bool loop = true);

    Timer();
    Timer(const Timer &rsh);
    Timer(const std::shared_ptr<TimerImpl> &rsh);

    virtual ~Timer();

    void cancel();

protected:
    std::shared_ptr<TimerImpl> m_impl;
};

void timeout(unsigned timeout, const std::function<void(void)> &func);

#endif
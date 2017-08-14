#ifndef __RUN_CONTAINER_H__
#define __RUN_CONTAINER_H__

#include <functional>
#include <memory>
#include <vector>

class TimerImpl;
class RunContainerImpl;

class RunContainer : public std::enable_shared_from_this<RunContainer>
{
public:
    RunContainer(const std::string &id, int thread_num = 1);
    virtual ~RunContainer();

    virtual bool run(bool mainloop);
    virtual void stop();
    void release_impl();

public:
    void post(const std::function<void(void)> &func);
    void post_special(int special, const std::function<void(void)> &func);

    std::shared_ptr<TimerImpl> timeout(
        unsigned timeout,
        const std::function<void(void)> &func,
        bool loop = true);
    std::shared_ptr<TimerImpl> timeout_special(
        int special,
        unsigned timeout,
        const std::function<void(void)> &func,
        bool loop = true);

public:
    int get_thread_num();

protected:
    std::vector<std::shared_ptr<RunContainerImpl>> m_impl;
    std::string m_id;
};

#endif
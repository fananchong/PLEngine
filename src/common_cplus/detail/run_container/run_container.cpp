#include "run_container.h"
#include "log.h"
#include "run_container_impl.h"
#include "random.h"

RunContainer::RunContainer(const std::string &id, int thread_num)
    : m_id(id)
{
    int num = thread_num <= 0 ? 1 : thread_num;

    for (int i = 0; i < num; i++)
    {
        m_impl.emplace_back(std::make_shared<RunContainerImpl>(id));
    }
}

RunContainer::~RunContainer()
{
    INFO("enter ~RunContainer(), id = {}", m_id);
    stop();
}

bool RunContainer::run(bool mainloop)
{
    int num = (int)m_impl.size();
    int index = 0;

    for (; index < (mainloop ? num - 1 : num); index++)
    {
        m_impl[index]->run(false);
    }

    if (index == num - 1)
    {
        m_impl[index]->run(true);
    }

    return true;
}

void RunContainer::stop()
{
    int num = (int)m_impl.size();

    for (int i = 0; i < num; i++)
    {
        m_impl[i]->stop();
        m_impl[i]->join();
    }
}

void RunContainer::release_impl()
{
    m_impl.clear();
}

void RunContainer::post(const std::function<void(void)> &func)
{
    int num = (int)m_impl.size();
    int index = Random(0, num - 1);
    post_special(index, func);
}

void RunContainer::post_special(int special, const std::function<void(void)> &func)
{
    int num = (int)m_impl.size();
    int index = special % num;
    m_impl[index]->post(func);
}

std::shared_ptr<TimerImpl> RunContainer::timeout(
    unsigned timeout,
    const std::function<void(void)> &func,
    bool loop)
{
    int num = (int)m_impl.size();
    int index = Random(0, num - 1);
    return timeout_special(index, timeout, func, loop);
}

std::shared_ptr<TimerImpl> RunContainer::timeout_special(
    int special,
    unsigned timeout,
    const std::function<void(void)> &func,
    bool loop)
{
    int num = (int)m_impl.size();
    int index = special % num;
    return m_impl[index]->timeout(timeout, func, loop);
}

int RunContainer::get_thread_num()
{
    return (int)m_impl.size();
}
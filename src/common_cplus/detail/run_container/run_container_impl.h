#ifndef __RUN_CONTAINER_IMPL_H__
#define __RUN_CONTAINER_IMPL_H__

#include <boost/asio.hpp>
#include <functional>
#include <thread>

class TimerImpl;
class RunContainerImpl : public std::enable_shared_from_this<RunContainerImpl>
{
public:
    RunContainerImpl(const std::string &id);
    virtual ~RunContainerImpl();

    void run(bool mainloop);
    void stop();
    void post(const std::function<void(void)> &func);

    std::shared_ptr<TimerImpl> timeout(
        unsigned timeout,
        const std::function<void(void)> &func,
        bool loop);

    void join();

    inline bool working()
    {
        return m_working;
    }
    inline boost::asio::io_service &get_io_service()
    {
        return m_ioservice;
    }

    inline std::string &get_id()
    {
        return m_id;
    }

private:
    void run_func();

    std::string m_id;
    boost::asio::io_service m_ioservice;
    boost::asio::io_service::work m_iowork;
    volatile bool m_working;
    std::thread m_thread;
    bool m_lock_join;
};

#endif
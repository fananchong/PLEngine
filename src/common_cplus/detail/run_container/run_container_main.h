#ifndef __RUN_CONTAINER_MAIN_H__
#define __RUN_CONTAINER_MAIN_H__

#include <boost/asio.hpp>
#include <memory>
#include "run_container.h"

class TimerImpl;
class RunContainerMain
    : public RunContainer
{
public:
    RunContainerMain();
    ~RunContainerMain();

    bool run();

    boost::asio::io_service &get_io_service();

private:
    bool run(bool mainloop) override
    {
        assert(false);
        return false;
    }
    void post_special(int special, const std::function<void(void)> &func);
    std::shared_ptr<TimerImpl> timeout_special(
        int special,
        unsigned timeout,
        const std::function<void(void)> &func,
        bool loop = true);
};

extern std::shared_ptr<RunContainerMain> g_pmain;

#endif
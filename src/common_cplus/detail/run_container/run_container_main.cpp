#include "run_container_main.h"
#include "run_container_impl.h"

std::shared_ptr<RunContainerMain> g_pmain;

RunContainerMain::RunContainerMain()
    : RunContainer("main")
{
}

RunContainerMain::~RunContainerMain()
{
}

bool RunContainerMain::run()
{
    return RunContainer::run(true);
}

boost::asio::io_service &RunContainerMain::get_io_service()
{
    return m_impl[0]->get_io_service();
}
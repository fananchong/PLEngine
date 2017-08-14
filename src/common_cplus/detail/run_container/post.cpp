#include "post.h"
#include "run_container_main.h"

void post(const std::function<void(void)> &func)
{
    g_pmain->post(func);
}
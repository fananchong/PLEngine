#include <plengine/setup.h>
#include <plengine/timer.h>
#include <plengine/log.h>

Timer t2;


void on_app_open()
{
    Timer t1(1000, []()
    {
        INFO("[t1] called");
    }, true);
    t2 = Timer(500, []()
    {
        static int i = 0;
        i++;

        if (i > 10)
            t2.cancel();
        else
            INFO("[t2] called");
    });
    timeout(3000, [] {INFO("timeout is called");});
}

void on_app_close() {}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}
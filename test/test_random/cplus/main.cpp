#include <plengine/log.h>
#include <plengine/random.h>
#include <plengine/setup.h>

void on_app_open()
{
    for (int i = 0; i < 50; ++i)
    {
        WARN("{}", Random(1, 100));
    }
}

void on_app_close() {}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}
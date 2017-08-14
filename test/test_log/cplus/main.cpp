#include <plengine/log.h>
#include <plengine/setup.h>

void on_app_open()
{
    INFO("hello {0} {1} {0}", "wolrd", "1");
    WARN("warning into");
    ERR("hahahah {}", std::string("aaaaa"));
}

void on_app_close() {}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}
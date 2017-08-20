#include <plengine/log.h>
#include <plengine/setup.h>

void on_app_open()
{
    TRACE("hello {0}", 111);
    DEBUG("hello {0}", 1.5);
    INFO("hello {0} {1} {0}", std::string("wolrd"), "1");
    WARN("warning into");
    ERR("hahahah {}", std::string("aaaaa"));
    FATAL("hahahah {}", "bbb");
}

void on_app_close() {}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}
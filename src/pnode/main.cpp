#include <plengine/setup.h>
#include <plengine/log.h>
#include <plengine/program_options.h>
#include <plengine/version.h>

static void show_copy_right(const std::string &appname)
{
    SHOW_GREEN("-------------------------------------------------------------");
    SHOW_GREEN("[PLEngine] {}", appname);
    SHOW_YELLOW("");
    SHOW_GREEN("(c) 2017 fananchong. All Rights Reserved.");
    SHOW_GREEN("-------------------------------------------------------------");
    SHOW_YELLOW("Version    : {}", std::string(APP_VERSION, 10));
    SHOW_YELLOW("Build Time : {}", APP_BUILD_TIME);
    SHOW_YELLOW("");
    SHOW_YELLOW("");
}


static void on_app_open()
{
    show_copy_right(ProgramOptions::get_string("name"));

    bool openshell = false;
#ifdef _MSC_VER
    openshell = true;
#endif
#ifdef _DEBUG
    openshell = true;
#endif
    setup_pythonvm(openshell);
}

static void on_app_close()
{
}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close);
}
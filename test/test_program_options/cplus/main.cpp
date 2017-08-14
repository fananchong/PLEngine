#include <plengine/log.h>
#include <plengine/setup.h>
#include <vector>


#define PROGRAM_OPTIONS()                               \
{ "force,f", false, "force desc", true },            \
{ "file", "filename", "this file's name", true },    \
{ "daemon,d", "", "daemon desc", false},                 \



void on_app_open()
{
    WARN("file = {}", ProgramOptions::get_string("file"));
    WARN("force = {}", ProgramOptions::get_bool("force"));

    if (ProgramOptions::has("daemon"))
    {
        WARN("daemon");
    }
    else
    {
        WARN("no daemon");
    }

    ProgramOptions::set("force", true);
    ProgramOptions::set("file", "aaaa");
    WARN("file = {}", ProgramOptions::get_string("file"));
    WARN("force = {}", ProgramOptions::get_bool("force"));
}

void on_app_close() {}

int main(int argc, char *argv[])
{
    return setup(argc, argv, on_app_open, on_app_close, { PROGRAM_OPTIONS() });
}
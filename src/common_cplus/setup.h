#ifndef __SETUP_H__
#define __SETUP_H__

#include <string>
#include <vector>
#include <functional>

#include "program_options.h"

int setup(
    const std::vector<std::string> &args,
    const std::function<void()> &on_app_open,
    const std::function<void()> &on_app_close,
    const std::vector<ProgramOptions::option_t> &options = std::vector<ProgramOptions::option_t>());

int setup(
    int argc, char *argv[],
    const std::function<void()> &on_app_open,
    const std::function<void()> &on_app_close,
    const std::vector<ProgramOptions::option_t> &options = std::vector<ProgramOptions::option_t>());

#ifdef ENABLE_PLENGINE_PYTHON
void setup_pythonvm(bool open_shell, const std::function<void()> &before_app_open = std::function<void()>());
#endif

#endif
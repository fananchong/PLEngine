#include "readline.h"
#include "log.h"
#include <iostream>
#include <thread>

bool Readline::wait(const std::string &prompt, std::string &line)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << prompt;
    char buff[1024] = {0};
    std::cin.getline(buff, sizeof(buff) - 1);
    line = buff;
    return false;
}
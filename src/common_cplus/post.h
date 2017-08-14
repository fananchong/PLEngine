#ifndef __POST_H__
#define __POST_H__

#include <functional>

void post(const std::function<void(void)> &func);

#endif
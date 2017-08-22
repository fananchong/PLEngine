#include "pymain.h"

const char *entrypoint = "PLMain";

std::string pymain = R"(

import pl
import sys

class MyStdOut(object):
    def __init__(self):
        pass
    def write(self, *args, **kwargs):
        buffer = ""
        for arg in args:
            buffer = buffer + str(arg).replace("\n", "")
        pl.info(buffer)

class MyStdErr(object):
    def __init__(self):
        self.flag = 0
        self.buffer = ""
    def write(self, *args, **kwargs):
        for arg in args:
            self.buffer = self.buffer + str(arg)
        if str(arg) == ": ":
            self.flag = 1
        elif self.flag == 1:
            pl.error(self.buffer)
            self.flag = 0
            self.buffer = ""

sys.stdout = MyStdOut()
sys.stderr = MyStdErr()

import PLMain

)";
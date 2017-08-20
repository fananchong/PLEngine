#include <fstream>
#include "log.h"

std::string get_filecontent(const std::string &filename, bool showmsg)
{
    std::string ret;
    std::ifstream in(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (in.is_open() == false && showmsg)
    {
        ERR("open file failed! filename={}", filename);
        return "";
    }

    in.seekg(0, std::ios::end);
    ret.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read((char*)ret.data(), ret.size());
    in.close();
    return std::move(ret);
}
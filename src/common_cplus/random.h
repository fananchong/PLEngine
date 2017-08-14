#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random
{
public:
    Random(int min, int max);   //[min, max]±ÕÇø¼ä

    operator int() const;
    operator int();

private:
    int m_ivalue;
};

#endif
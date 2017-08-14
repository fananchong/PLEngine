#include "random.h"
#include <boost/random.hpp>
#include <time.h>

static boost::mt19937 g_random_gen((uint32_t)time(0));

Random::Random(int min, int max)
    : m_ivalue(0)
{
    boost::uniform_int<> dist(min, max);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<>> g(g_random_gen, dist);
    m_ivalue = g();
}

Random::operator int() const
{
    return m_ivalue;
}

Random::operator int()
{
    return m_ivalue;
}
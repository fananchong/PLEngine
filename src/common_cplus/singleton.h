#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <boost/serialization/singleton.hpp>

template <class T>
class Singleton : public boost::serialization::singleton<T>
{
    static T & get_mutable_instance();
    static const T & get_const_instance();
public:
    inline static T & instance()
    {
        return boost::serialization::singleton<T>::get_mutable_instance();
    }
};

#endif
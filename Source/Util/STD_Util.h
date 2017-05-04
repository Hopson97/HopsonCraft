#ifndef STD_UTIL_H_INCLUDED
#define STD_UTIL_H_INCLUDED


template <template<class, class> class Map, typename T, typename R>
bool existsInMap(const Map<T, R>& m, const T& toFind)
{
    return m.find(toFind) != m.end();
}

#endif // STD_UTIL_H_INCLUDED

#ifndef STD_UTIL_H_INCLUDED
#define STD_UTIL_H_INCLUDED

#include <unordered_map>


template <typename Key, typename Value>
bool existsInMap(const std::unordered_map<Key, Value>& m, const Key& toFind)
{
    return m.find(toFind) != m.end();
}

#endif // STD_UTIL_H_INCLUDED

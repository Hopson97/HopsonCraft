#ifndef BLOCK_POSITION_H
#define BLOCK_POSITION_H


#include <functional>
#include <cmath>

struct Block_Location
{
    Block_Location (int x, int y, int z);

    int x = 0;
    int y = 0;
    int z = 0;

    bool operator== (const Block_Location& other) const;

    bool operator!=  (const Block_Location& other) const;
};

namespace std
{
    template<>
    struct hash<Block_Location>
    {
        template <typename T>
        T hashInt( T key ) const
        {
            key = ~key + (key << 15);
            key = key ^ (key >> 12);
            key = key + (key << 2);
            key = key ^ (key >> 4);
            key = key * 2057;
            key = std::hash<double>{}(key ^ (key >> 16));
            return key;
        }

        size_t operator() ( Block_Location const& v ) const
        {
            size_t h1 = std::hash<double>()(hashInt(v.x >> v.z));
            size_t h2 = std::hash<double>()(hashInt(v.x << v.z));
            size_t h3 = std::hash<double>()(hashInt(v.y << h1));
            return (h1 ^ (h2 << 1) ^ h3);
        }
    };
}

#endif // BLOCK_POSITION_H

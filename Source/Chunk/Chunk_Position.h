#ifndef CHUNK_POSITION_H
#define CHUNK_POSITION_H

#include <unordered_map>

struct Chunk_Position
{
    public:
        Chunk_Position() = default;
        Chunk_Position(int x, int z);

        int x = 0;
        int z = 0;

        bool operator == (const Chunk_Position& other);
        bool operator != (const Chunk_Position& other);

};

namespace std
{
    template<>
    struct hash<Chunk_Position>
    {
        int hashInt(int key) const
        {
            key = ~key + (key << 15);
            key = key ^ (key >> 12);
            key = key + (key << 2);
            key = key ^ (key >> 4);
            key = key * 2057;
            key = std::hash<double>{}(key ^ (key >> 16));
            return key;
        }

        size_t operator () (const Chunk_Position& position)
        {
            auto h1 = std::hash<int>{}(hashInt(position.x));
            auto h2 = std::hash<int>{}(hashInt(position.z));
            return (h1 ^ (h2 << 1));
        }
    };
}

#endif // CHUNK_POSITION_H

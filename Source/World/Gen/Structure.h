#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "../Block/Block_Location.h"

#include <functional>

class Chunk;

typedef std::function<void(Chunk& chunk, const Block_Location& location)> Structure_Function;

class Structure_Base
{
    public:
        Structure_Base(Chunk& chunk, const Block_Location& location, Structure_Function function);
        void create();

    private:
        Chunk* m_p_chunk;
        const Block_Location m_location;
        Structure_Function m_function;
};

namespace Structure
{
    void createOak(Chunk& chunk, const Block_Location& location);

    void createCactus(Chunk& chunk, const Block_Location& location);
}

#endif // STRUCTURE_H

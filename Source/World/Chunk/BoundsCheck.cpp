#include "BoundsCheck.h"

#include "../World_Constants.h"

#include "Section.h"
#include "Map.h"

namespace Chunk
{
    namespace
    {
/*
 *          Checks for the position of block passed in.
 *          If the block position is out of the chunks bounds
 *          (see the if statements)
 *          It will correct the position to be within a neighbouring chunks bounds
 *          It also takes in "change", which says which direction the neighbouring chunk
 *          is located.
 */
        void checkBound(int& pos, int& change)
        {
            if (pos > CHUNK_SIZE - 1)
            {
                change = 1;
                pos -= CHUNK_SIZE;
            }
            else if (pos < 0)
            {
                change = -1;
                pos += CHUNK_SIZE;
            }
        }
    }
/*
 *  Tries to get a get chunk section based on the block position relative to the "default chunk"
 *  This does some bounds checks, and thus will return a neighbouring chunk to the default chunk if the checks fail
 */
    Section* getSection(Block::Position& position,
                        Section* defaultSection,
                        Map& chunkMap)
    {
        static const sf::Vector3<int> noChnage(0, 0, 0);
        auto change = noChnage;

        checkBound(position.x, change.x);
        checkBound(position.y, change.y);
        checkBound(position.z, change.z);

        if (change == noChnage)
        {
            return defaultSection;
        }
        else
        {
            Chunk::Chunklet_Position newPos = defaultSection->getPosition() + change;
            return chunkMap.editableGet({newPos.x, newPos.y, newPos.z});
        }
    }

    //ditto
    const Section* getConstSection(Block::Position& position,
                                   const Section* defaultSection,
                                   Map& chunkMap)
    {
        static const sf::Vector3<int> noChnage(0, 0, 0);
        auto change = noChnage;

        checkBound(position.x, change.x);
        checkBound(position.y, change.y);
        checkBound(position.z, change.z);

        if (change == noChnage)
        {
            return defaultSection;
        }
        else
        {
            Chunk::Chunklet_Position newPos = defaultSection->getPosition() + change;
            return chunkMap.editableGet({newPos.x, newPos.y, newPos.z});
        }
    }
}

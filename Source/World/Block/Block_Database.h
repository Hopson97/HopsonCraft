#ifndef BLOCK_DATABASE_H_INCLUDED
#define BLOCK_DATABASE_H_INCLUDED

#include <memory>
#include <vector>

#include "Block_Types/Block_Type.h"
#include "Block_ID.h"

#include "../../Texture/Texture_Atlas.h"

namespace Block
{
    class Database
    {
        public:
            static Database& get();

            Database();

            const Type& getBlock(uint8_t id);
            const Type& getBlock(ID blockID);

        private:
            std::vector<std::unique_ptr<Type>> blocks;

        public:
            Texture::Atlas textures;
    };
}

#endif // BLOCK_DATABASE_H_INCLUDED

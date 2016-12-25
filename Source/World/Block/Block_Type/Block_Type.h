#ifndef BLOCK_TYPE_H
#define BLOCK_TYPE_H

//Base class for the single-instance blocks

#include <string>
#include <vector>
#include <memory>

#include "../Block_Data.h"
#include "../Updateable/Updatable_Block.h"

//This will be moved eventually
struct Temp_Item_ID {};
struct Empty : Temp_Item_ID {};
class Lootable
{
    public:
        virtual std::vector<Temp_Item_ID> getLoot() const = 0;
};
//But for now, they be here.

namespace Block
{
    class Block_Type : public Lootable
    {
        public:
            Block_Type(const std::string& name);
            virtual ~Block_Type() = default;

            virtual std::vector<Temp_Item_ID>           getLoot             () const;
            virtual std::unique_ptr<Updatable_Block>    getUpdatableBlock   () const;

            const Block_Data& getData() const;

        private:
            Block_Data m_data;
    };
}

#endif // BLOCK_TYPE_H

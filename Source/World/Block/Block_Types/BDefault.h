#ifndef BDEFAULT_H_INCLUDED
#define BDEFAULT_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class Default : public Type
    {
        public:
            Default(const std::string& dataFileName);
    };

    class BSand : public Type
    {
        public:
            BSand();
    };

    class BTall_Grass : public Type
    {
        public:
            BTall_Grass();
            void trigger(World& world, const Position& position) const;
    };
}

#endif // BDEFAULT_H_INCLUDED

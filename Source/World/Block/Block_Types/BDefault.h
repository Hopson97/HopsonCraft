#ifndef BDEFAULT_H_INCLUDED
#define BDEFAULT_H_INCLUDED

#include "Block_Type.h"

namespace Block
{
    class Default : public Type
    {
        public:
            Default(std::string&& dataFileName);
    };

    class BSand : public Type
    {
        public:
            BSand();
    };
}

#endif // BDEFAULT_H_INCLUDED

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
}

#endif // BDEFAULT_H_INCLUDED

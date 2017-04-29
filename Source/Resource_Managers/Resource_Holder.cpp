#include "Resource_Holder.h"

#include <iostream>


Resource_Holder& getResources()
{
    static Resource_Holder h;
    return h;
}

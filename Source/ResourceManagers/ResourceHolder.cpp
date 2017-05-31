#include "ResourceHolder.h"

#include <iostream>


ResourceHolder& getResources()
{
    static ResourceHolder h;
    return h;
}

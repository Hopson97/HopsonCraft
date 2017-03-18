#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "Crosshair.h"
#include "Vignette.h"
#include "Debug.h"

#include "../Renderer/RMaster.h"

struct HUD
{
    void draw(Renderer::Master& renderer)
    {
        vignette.draw   (renderer);
        crosshair.draw  (renderer);

        debug.draw(renderer);
    }

    Vignette    vignette;
    Crosshair   crosshair;
    Debug_HUD   debug;
};

#endif // HUD_H_INCLUDED

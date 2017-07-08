#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include <unordered_map>

#include "Crosshair.h"
#include "Vignette.h"
#include "Debug.h"

#include "../Renderer/RMaster.h"

enum class HUD_Part
{
    Vignette,
    Crosshair,
};

struct HUD
{
    void draw(Renderer::Master& renderer)
    {
        vignette.draw   (renderer);
        crosshair.draw  (renderer);
    }

    Vignette    vignette;
    Crosshair   crosshair;
};

#endif // HUD_H_INCLUDED

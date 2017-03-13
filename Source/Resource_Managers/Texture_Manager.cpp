#include "Texture_Manager.h"

Texture_Manager::Texture_Manager()
{
    std::string path ("Data/Textures/");

    registerResource(Texture_ID::Vignette, path + "vignette.png");
    registerResource(Texture_ID::Crosshair1, path + "Crosshair.png");
}

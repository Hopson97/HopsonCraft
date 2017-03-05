#include "Font_Manager.h"

Font_Manager::Font_Manager()
{
    std::string path ("Data/Fonts/");

    registerResource(Font_ID::RS, path + "rs.ttf");
}

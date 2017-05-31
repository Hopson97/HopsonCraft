#include "Menu.h"

#include "../Resource_Managers/Resource_Holder.h"

#include "../Util/Random.h"
#include "../Util/File_Util.h"

#include "Image.h"

namespace GUI
{
    Menu::Menu()
    :   Panel   (Layout::Center)
    {
        addPadding(100);
        getBackground();
        addComponent(std::make_unique<GUI::Image>("Logo", sf::Vector2f{800, 100}));
    }

    void Menu::getBackground()
    {
        auto backgrounds    = getFileNamesFromFolder("Data/Textures/Menu_BG");
        auto textureName    = backgrounds[Random::intInRange(0, backgrounds.size() - 1)];
        textureName.erase(textureName.length() - 4);
        addBackgroud(getResources().textures.get("Menu_BG/" + textureName));
    }


}

#include "Menu.h"

#include "../ResourceManagers/ResourceHolder.h"

#include "../Util/Random.h"
#include "../Util/FileUtil.h"

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
        auto backgrounds = getFileNamesFromFolder("Data/Textures/Menu_BG");
        if (backgrounds.empty())
            return;
        auto textureName    = backgrounds[Random::intInRange(0, backgrounds.size() - 1)];
        textureName.erase(textureName.length() - 4);
        addBackgroud(ResourceHolder::getTexure("Menu_BG/" + textureName));
    }


}

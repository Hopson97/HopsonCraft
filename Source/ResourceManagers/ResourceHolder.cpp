#include "ResourceHolder.h"

#include "../Util/Log.h"

ResourceHolder::ResourceHolder() noexcept
:   textures        ("Data/Textures/",  "png")
,   fonts           ("Data/Fonts/",     "ttf")
,   soundBuffers    ("Data/Sounds",     "ogg")
{ }

ResourceHolder& ResourceHolder::get()
{
    static ResourceHolder res;
    return res;
}

const sf::Texture& ResourceHolder::getTexure(const std::string& name, bool isFullPath)
{
    LOG("Got Texture: %s\n", name.c_str());
    return get().textures.get(name, isFullPath);
}

const sf::Font& ResourceHolder::getFont(const std::string& name, bool isFullPath)
{
    LOG("Got Font: %s\n", name.c_str());
    return get().fonts.get(name, isFullPath);
}

const sf::SoundBuffer& ResourceHolder::getSoundBuff(const std::string& name, bool isFullPath)
{
    LOG("Got SoundBuffer: %s\n", name.c_str());
    return get().soundBuffers.get(name, isFullPath);
}

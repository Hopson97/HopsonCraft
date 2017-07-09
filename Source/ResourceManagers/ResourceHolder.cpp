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

const sf::Texture& ResourceHolder::getTexure(const std::string& name)
{
    LOG("Got Texture: %s\n", name.c_str());
    return get().textures.get(name);
}

const sf::Font& ResourceHolder::getFont(const std::string& name)
{
    LOG("Got Font: %s\n", name.c_str());
    return get().fonts.get(name);
}

const sf::SoundBuffer& ResourceHolder::getSoundBuff(const std::string& name)
{
    LOG("Got SoundBuffer: %s\n", name.c_str());
    return get().soundBuffers.get(name);
}

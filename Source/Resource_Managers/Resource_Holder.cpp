#include "Resource_Holder.h"

#include <iostream>

const Resource_Holder& getResources()
{
    static Resource_Holder holder;
    return holder;
}

const sf::Texture& Resource_Holder::getTexture(Texture_ID id) const
{
    return textures.get(id);
}

const sf::Font& Resource_Holder::getFont(Font_ID id) const
{
    return fonts.get(id);
}

const sf::SoundBuffer& Resource_Holder::getSound(Sound_ID id) const
{
    return sounds.get(id);
}

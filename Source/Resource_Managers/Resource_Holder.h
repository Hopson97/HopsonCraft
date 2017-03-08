#ifndef RESOURCE_HOLDER_H_INCLUDED
#define RESOURCE_HOLDER_H_INCLUDED

#include "Texture_Manager.h"
#include "Sound_Manager.h"
#include "Font_Manager.h"

class Resource_Holder
{
    public:
        const sf::Texture&      getTexture (Texture_ID id) const;
        const sf::Font&         getFont    (Font_ID    id) const;
        const sf::SoundBuffer&  getSound   (Sound_ID   id) const;

    private:
        Texture_Manager textures;
        Font_Manager    fonts;
        Sound_Manager   sounds;
};

const Resource_Holder& getResources();

#endif // RESOURCE_HOLDER_H_INCLUDED

#ifndef RESOURCEHOLDER_INCLUDED
#define RESOURCEHOLDER_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"

#include "../Util/Singleton.h"

class ResourceHolder : public Singleton
{
    public:
        static ResourceHolder& get();
        static const sf::Texture&       getTexure   (const std::string& name, bool = false);
        static const sf::Font&          getFont     (const std::string& name, bool = false);
        static const sf::SoundBuffer&   getSoundBuff(const std::string& name, bool = false);

        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::SoundBuffer>    soundBuffers;

    private:
        ResourceHolder() noexcept;
};

#endif // RESOURCEHOLDER_INCLUDED

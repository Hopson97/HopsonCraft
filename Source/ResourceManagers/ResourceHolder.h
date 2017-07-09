#ifndef RESOURCEHOLDER_INCLUDED
#define RESOURCEHOLDER_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ResourceManager.h"

class ResourceHolder
{
    public:
        static ResourceHolder& get();
        static const sf::Texture&       getTexure   (const std::string& name);
        static const sf::Font&          getFont     (const std::string& name);
        static const sf::SoundBuffer&   getSoundBuff(const std::string& name);

        ResourceHolder(const ResourceHolder& other) = delete;
        ResourceHolder(ResourceHolder&& other) = delete;

        ResourceHolder& operator=(const ResourceHolder& other) = delete;
        ResourceHolder& operator=(ResourceHolder&& other) = delete;


        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::SoundBuffer>    soundBuffers;

    private:
        ResourceHolder() noexcept;
};

#endif // RESOURCEHOLDER_INCLUDED

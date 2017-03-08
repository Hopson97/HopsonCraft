#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <map>
#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template<typename Resource, typename Enum>
class Resource_Manager
{
    public:
        const Resource& get(Enum e) const
        {
            return m_resources.at(e);
        }

        virtual ~Resource_Manager() = default;

    protected:
        void registerResource(Enum key, const std::string& filename)
        {
            Resource res;
            if (!res.loadFromFile(filename))
            {
                throw std::runtime_error ("Could load resource: " + filename + "!");
            }
            m_resources.insert(std::make_pair(key, res));
        }

    private:
        std::map<Enum, Resource> m_resources;
};

#endif // RESOURCEMANAGER_H_INCLUDED

#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <unordered_map>
#include <string>

template<typename Resource>
class ResourceManager
{
    public:
        ResourceManager(const std::string& folder, const std::string& ext)
        :   m_folder    (folder)
        ,   m_ext       (ext)
        { }

        const Resource& get(const std::string& fileName)
        {
            if(!exists(fileName))
            {
                addResource(fileName);
            }
            return m_resourceMap[fileName];
        }

        void remove(const std::string& fileName)
        {
            m_resourceMap.erase(fileName);
        }

    private:
        void addResource(const std::string& name)
        {
            auto str = buildString(name);
            Resource r;
            r.loadFromFile(str);
            m_resourceMap.emplace(name, r);
        }

        std::string buildString(const std::string& fileName) const
        {
            return m_folder + fileName + "." + m_ext;
        }

        bool exists(const std::string& fileName) const
        {
            return m_resourceMap.find(fileName) != m_resourceMap.end();
        }

        std::unordered_map<std::string, Resource> m_resourceMap;

        std::string m_folder,
                    m_ext;
};

#endif // RESOURCEMANAGER_H_INCLUDED

#include "World_File.h"

#include "World_Settings.h"

World_File::World_File(const World_Settings& settings)
:   m_folderName        ("Worlds/" + settings.name + "/")
,   m_pWorldSettings    (&settings)
{

}

const std::string& World_File::getFolderName() const
{
    return m_folderName;
}

void World_File::saveWorldInfo()
{

}


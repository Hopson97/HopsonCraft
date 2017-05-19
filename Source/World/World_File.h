#ifndef WORLD_FILE_H_INCLUDED
#define WORLD_FILE_H_INCLUDED

#include <string>

class World_Settings;

class World_File
{
    public:
        World_File(const World_Settings& settings);

        const std::string&  getFolderName  () const;
        void                saveWorldInfo  ();

    private:
         std::string m_folderName;

        const World_Settings* m_pWorldSettings = nullptr;
};

#endif // WORLD_FILE_H_INCLUDED

#ifndef BLOCK_DATA_H_INCLUDED
#define BLOCK_DATA_H_INCLUDED

#include <string>
#include <fstream>

#include "Block_ID.h"
#include "../../Glm_Common.h"
#include "../../Util/Loader.h"

namespace Block
{
    enum Mesh_Type
    {
        Solid   = 0,
        Flora   = 1,
        Liquid  = 2,
    };

    enum Mesh_Style
    {
        Block   = 0,
        XStyle  = 1
    };

    enum class State
    {
        Solid   = 0,
        Liquid  = 1,
        Gas     = 2
    };

    struct Data_Holder
    {
        Data_Holder() = default;
        Data_Holder(Data_Holder& other) = delete;

        ID          blockID;
        std::string name;

        bool        isOpaque    = true;
        bool        isObstacle  = true;
        bool        canUpdate   = false;

        Mesh_Type   meshType    = Mesh_Type     ::Solid;
        Mesh_Style  meshStyle   = Mesh_Style    ::Block;
        State       state       = State         ::Solid;

        Vector2     topTextureCoords;
        Vector2     sideTextureCoords;
        Vector2     bottomTextureCoords;
    };

    class Data : public Loader
    {
        public:
            Data(std::string&& fileName);

            const Data_Holder& get() const { return m_holder; }

        private:
            bool parseLine  (const std::string& line, std::ifstream& stream) override;

            template<typename T>
            void loadEnum(std::ifstream& stream, T& data)
            {
                int32_t val;
                stream >> val;
                data = static_cast<T>(val);
            }

            std::string m_fileName;

            Data_Holder m_holder;
    };
}

#endif // BLOCK_DATA_H_INCLUDED

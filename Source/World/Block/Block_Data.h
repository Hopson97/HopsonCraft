#ifndef BLOCK_DATA_H_INCLUDED
#define BLOCK_DATA_H_INCLUDED

#include <string>
#include <fstream>

#include "Block_ID.h"
#include "../../Glm_Common.h"

namespace Block
{
    enum Mesh_Type
    {
        Solid   = 0,
        Flora   = 1,
        Liquid  = 2,
    };

    struct Data_Holder
    {
        Data_Holder() = default;
        Data_Holder(Data_Holder& other) = delete;

        ID          blockID;
        std::string name;
        bool        isOpaque;
        bool        isObstacle;
        Mesh_Type   meshType;
        Vector2     topTextureCoords;
        Vector2     sideTextureCoords;
        Vector2     bottomTextureCoords;
    };

    class Data
    {
        public:
            Data(const std::string& fileName);

            const Data_Holder& get() const { return m_holder; }

        private:
            template<typename T>
            void loadEnum(std::ifstream& stream, T& data)
            {
                int32_t val;
                stream >> val;
                data = static_cast<T>(val);
            }

            Data_Holder m_holder;
    };
}

#endif // BLOCK_DATA_H_INCLUDED

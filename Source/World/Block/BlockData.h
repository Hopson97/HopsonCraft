#ifndef BlockData_H_INCLUDED
#define BlockData_H_INCLUDED

#include <string>
#include <fstream>

#include "BlockID.h"
#include "../../Maths/GLM.h"
#include "../../Util/Loader.h"

namespace Block
{
    enum MeshType
    {
        Solid   = 0,
        Flora   = 1,
        Liquid  = 2,
    };

    enum MeshStyle
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

    struct DataHolder
    {
        DataHolder() = default;
        DataHolder(DataHolder& other) = delete;

        ID          blockID;
        std::string name;

        bool        isOpaque    = true;
        bool        isObstacle  = true;
        bool        canUpdate   = false;

        MeshType   meshType    = MeshType     ::Solid;
        MeshStyle  meshStyle   = MeshStyle    ::Block;
        State       state       = State         ::Solid;

        Vector2     topTextureCoords;
        Vector2     sideTextureCoords;
        Vector2     bottomTextureCoords;
    };

    class Data : public Loader
    {
        public:
            Data(std::string&& fileName);

            const DataHolder& get() const { return m_holder; }

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

            DataHolder m_holder;
    };
}

#endif // BlockData_H_INCLUDED

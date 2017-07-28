#ifndef BlockBlockData_H_INCLUDED
#define BlockBlockData_H_INCLUDED

#include <string>
#include <fstream>

#include "BlockID.h"
#include "../../Maths/GLM.h"
#include "../../Util/Loader.h"

enum class MeshType
{
    Solid   = 0,
    Flora   = 1,
    Liquid  = 2,
};

enum class MeshStyle
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

struct BlockDataHolder
{
    BlockDataHolder() = default;
    BlockDataHolder(BlockDataHolder& other) = delete;

    BlockID     blockID;
    std::string name;

    bool        isOpaque    = true;
    bool        isObstacle  = true;
    bool        canUpdate   = false;

    MeshType   meshType     = MeshType::Solid;
    MeshStyle  meshStyle    = MeshStyle::Block;
    State       state       = State::Solid;

    Vector2     topTextureCoords;
    Vector2     sideTextureCoords;
    Vector2     bottomTextureCoords;
};

class BlockData : public Loader
{
    public:
        BlockData(std::string&& fileName);

        const BlockDataHolder& get() const { return m_holder; }

    private:
        bool parseLine  (const std::string& line, std::ifstream& stream) override;

        template<typename T>
        void loadEnum(std::ifstream& stream, T& BlockData)
        {
            int32_t val;
            stream >> val;
            BlockData = static_cast<T>(val);
        }

        std::string m_fileName;

        BlockDataHolder m_holder;
};


#endif // BlockBlockData_H_INCLUDED

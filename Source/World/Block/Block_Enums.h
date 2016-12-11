#ifndef E_BLOCK_ID_H_INCLUDED
#define E_BLOCK_ID_H_INCLUDED
namespace Block
{
    enum class ID
    {
        Air             =   0,
        Grass           =   1,
        Dirt            =   2,
        Stone           =   3,
        Sand            =   4,
        Water           =   5,
        Oak_Wood        =   6,
        Oak_Leaf        =   7,
        Oak_Plank       =   8,
        Glass           =   9,
        Cobble_Stone    =   10,
        Stone_Brick     =   11,
        Snow            =   12,
        Cactus          =   13,
        Rose            =   14,
        Tall_Grass      =   15,
        Dead_Shrub      =   16,
        Bedrock         =   17,

        NUM_BLOCK_TYPES
    };

    enum class Mesh_Type
    {
        Block   =   0,
        X_Style =   1,
        Special =   2
    };

    enum class Physical_State
    {
        Solid   = 0,
        Liquid  = 1,
        Gas     = 2,
        Flora   = 3
    };
}

#endif // E_BLOCK_ID_H_INCLUDED

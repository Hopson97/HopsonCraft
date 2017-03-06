#ifndef UPDATABLE_BLOCK_H_INCLUDED
#define UPDATABLE_BLOCK_H_INCLUDED

#include "../Block_Location.h"

class Chunk;

class Updatable_Block
{
    public:
        void setChunk   (Chunk& chunk);

        virtual bool update     (const Block_Location& location) = 0;
        void breakBlock ();

        bool isDestroyed    () const;



    protected:
        virtual void onBreak () = 0;

        Chunk*          m_p_chunk       = nullptr;
        bool            m_isDestroyed   = false;
};

#endif // UPDATABLE_BLOCK_H_INCLUDED

#ifndef UPDATABLE_BLOCK_H_INCLUDED
#define UPDATABLE_BLOCK_H_INCLUDED

class Chunk;

class Updatable_Block
{
    public:
        Updatable_Block(Chunk& chunk);

        virtual void update() = 0;

    protected:
        Chunk* m_p_chunk;
};

#endif // UPDATABLE_BLOCK_H_INCLUDED

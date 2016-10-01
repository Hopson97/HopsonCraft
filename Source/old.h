#ifndef OLD_H_INCLUDED
#define OLD_H_INCLUDED
/*
struct Block
{
    float x, y, z;

    Block( float x, float y, float z ): x ( x ), y ( y ), z ( z ) { }

    void thing()
    {
        for ( int i = 0 ; i < 6 ; i ++ )
        {
            if ( x < y ) x = z;
        }
    }
};

constexpr static int totalSize = 16 * 16 * 512;
constexpr static int totalChunks = 16 * 16;

struct Chunk
{
    Chunk ()
    {
        for ( size_t i = 0 ; i < totalSize  ; i++  ) {
            things.emplace_back ( std::make_unique<Block> ( i, i, i ) );
        }
    }

    void generateMesh ()
    {
        for ( int x = 0 ; x < 16 ; x++ )
        {
            for ( int z = 0 ; z < 16 ; z++ )
            {
                for ( int y = 0 ; y < 512 ; y++ )
                {
                    things.at( x * y * z + 16 + 16 )->thing();
                }
            }
        }



    }

    std::vector<std::unique_ptr<Block>> things;
};

int main()
{
    /*
    std::cout << "Chunk size: "     << totalSize                << std::endl;
    std::cout << "Chunks "          << totalChunks              << std::endl;
    std::cout << "Total blocks "    << totalSize * totalChunks  << std::endl;


    sf::Clock clock;
    std::vector<Chunk> m_chunks;
    int totalChunks = 16;


    for ( size_t i = 0 ; i < totalChunks * totalChunks  ; i++  ) {
        m_chunks.emplace_back ( Chunk() );
    }

    for ( auto& chunk : m_chunks )
    {
        chunk.generateMesh();
    }

    std::cout << "Time: " << clock.getElapsedTime().asSeconds() << std::endl;
}
*/

*/
#endif // OLD_H_INCLUDED

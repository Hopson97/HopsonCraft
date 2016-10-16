# MattCraft

A minecraft clone written using C++, SFML, OpenGL and GLEW. (Uses modern C++ and OpenGL)

Linker:

All:

opengl32

Debug:

sfml-graphics-d

sfml-window-d

sfml-system-d

Release

sfml-graphics

sfml-window

sfml-system

Flags:

Please use -O3 in release mode!

## How it works:

The world class contains a hash map (std::unordered_list) of chunks. The key of the hash map is the position of a chunk, stored as custom type "Vector2i", which I also defined a hash function for.

Each chunk contains a std::vector of "blocks". The block, at this moment, just stores an ID for it's type. In the future, it will contain methods for actions with said tile (eg destory)

The chunk also contains a function to generate a vertex array, for OpenGL to render with. 

This is quite simple:

1. It iterates through every block.

2. It checks the ID.

3. If it is an air block, it ignores it and continues the iteration.

4. If it not an air block, it goes and checks each face of the block for a perpendicuar solid block. If it finds one, no face is generated. If it finds an air block, it does generate a face.

5. Sometimes when it checks a block, it might be out of range of the vector itself. If this is the case, it looks at the respective adjecent chunk, and looks at the corrosponding "overlap".

6. A mesh is created! 

And that is all there is to it.

For texturing, a texture atlas is used.

## Screenshots:

![Blocks](http://i.imgur.com/MsdCJbz.png "Blocks")

![Blocks](http://i.imgur.com/imAEdza.png "Blocks")

![Blocks](http://i.imgur.com/KGxWgGw.png "Blocks")

## Future:

I hope to add collison detection, and make it for Minecraft-y, eg the ability to break and place blocks.


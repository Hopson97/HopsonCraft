# MattCraft

A minecraft clone written using C++, SFML, OpenGL and GLEW. (Uses modern C++ and OpenGL).

I am making this for fun and for learning.

Flags:

Please use -O3 in release mode!

## How it works:

####Rendering:
  Only exposed faces are rendered, or actually added to the vertex array for each chunk.
  So far, there is 2 draw calls per chunk; one for the water and one for the "ground/flora". This is so that the water can have a shader indepenant from the ground shader, which allows the water to have "waves".

## Screenshots:

![Blocks](http://i.imgur.com/MsdCJbz.png "Blocks")

![Blocks](http://i.imgur.com/imAEdza.png "Blocks")

![Blocks](http://i.imgur.com/KGxWgGw.png "Blocks")

## Future:

I hope to add collison detection, and make it for Minecraft-y, eg the ability to break and place blocks.


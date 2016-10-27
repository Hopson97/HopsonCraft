# MattCraft

A minecraft clone written using C++, SFML, OpenGL and GLEW. (Uses modern C++ and OpenGL).

I am making this for fun and for learning.

Flags:

Please use -O3 in release mode!

## How it works:

####Rendering:
  Only exposed faces are rendered, or actually added to the vertex array for each chunk.
  So far, there is 2 draw calls per chunk; one for the water and one for the "ground/flora". This is so that the water can have a shader indepenant from the ground shader, which allows the water to have "waves".
  
####World Generation:
As world generation is slowish, it is done on a seperate thread.

On this thread, there are two values used: The loading distance and render distance.

The loading distance starts at a very small value. This will load chunks with "loading distance" distance from the player's current chunk location. Each iteration, the loading distance increases until it reaches the value of the render ditance, which is when it resets back to a small number.

To generate a chunks, a simple value noise algorithim is used to calculate a height map, which is used to work out what type of blocks go where in a chunk.

## Screenshots:

![Blocks](http://i.imgur.com/MsdCJbz.png "Blocks")

![Blocks](http://i.imgur.com/imAEdza.png "Blocks")

![Blocks](http://i.imgur.com/KGxWgGw.png "Blocks")

## Future:

I hope to add collison detection, and make it for Minecraft-y, eg the ability to break and place blocks.


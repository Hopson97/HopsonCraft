# PureCraft

A minecraft clone written using C++, SFML, OpenGL and GLEW. (Uses modern C++ and OpenGL).

I am making this for fun and for learning.

Flags:

Please use -O3 in release mode!

## How it works:

###Rendering:
For rendering, I have a few classes. The main one is the "Chunk_Renderer", which is actually a base class for different parts of the chunks: The solid parts, liqud, and flora. 

The reason behind different renderers for different parts of the mesh is that they do it a bit different. For example, the water and flora shaders each have special shaders, thus need have a differet shader active for their draw calls.

A major optimization in terms of rendering is that when I generate vertex data for a chunk, I only add exposed faces (there are some cases where this isn't 100% true, but it is mostly) to the mesh. This saves memory, and makes draw calls faster than if I were to draw every single block.
	
  
####World Generation:
This is all done on a seperate thread, and is done in a few stages.

The first stage is creating the actual block data for a given chunk. This uses a noise algorithm in two stages. 

Stage one is simply the creation of a height map, which gives each "collumn" of blocks within a chunk an initial maximum height. 

Stage two is a bitome map. This uses a "smoother" input in the noise functions, and is also done for each column of blocks, giving them a "biome value". The biomes value is then used to determine the surface block there, as well as possible flora and structures.

####Breaking blocks

The input for breaking blocks is a simple raycast from the ceneter of the screen, which returns a block at the end of it.
	
## Screenshots:

![Valley](http://i.imgur.com/pDkpGmN.png "Valley")

![Mountain](http://i.imgur.com/HLMnOjZ.png "Mountain")

![View](http://i.imgur.com/Bl5CFdI.png "View")



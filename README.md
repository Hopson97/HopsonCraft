# HopsonCraft

## Versions

This game has gone through major rewrites and refactors overtime.

To see the source code as it was in episodes 1, 2 and 3 of "Creating Minecraft in C++/ OpenGL" videos, look at the "MattCraft Classic" in the releases section of this repository. 

## Dependencies
The project requires these libraries: SFML (minimum 2.4), GLEW (OpenGL 3.3+), and OpenGL Maths Library (GLM).

Compile using compiler flags: ``-std=c++14 -O3 -s``

## Description
Simple Minecraft clone written using C++.

## Screenshots
Coming soon...

## Implementation details

#### Chunks
Chunks are made out of a volume of blocks 16x16x16 in size.

They are stored in a class called "Full_Chunk", which is basically a handler for a vertical-column of these "chunk sections". There can be potentially an infinite number of sections in a full chunk.

The 16x16x16 chunks are then made into a mesh, and drawn.

#### Rendering
The camera class stores an object of a "Frustum" type. This is used to cull out anything (For now, just chunk sections) that is not within the field of view, which increases performance a fair amount.

Each major mesh type has it's own shader and renderer class, each with their own unique responsabilities. 

For example, the solid chunk renderer enables face-culling and disables blending before drawing, and the liquid renderer disables face-culling, enables blending, and also uploads a time variable to the "Liquid Shader" so it can have a wave effect.

#### Meshes
Coming soon...

#### Collisions
Coming soon...

#### Block editing
Coming soon...


## Credits

#### Design 
Matthew Hopson, https://github.com/Hopson97/

#### Programming
Matthew Hopson, https://github.com/Hopson97/

#### Art
Matthew Hopson, https://github.com/Hopson97/


#### Special Thanks
Anton Golov, https://github.com/jesyspa

Zoltan Fazekas, https://github.com/zfazek

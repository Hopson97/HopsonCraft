# HopsonCraft

Note: Game is undergoing redesign at the moment.

To see source as it was in ep 4 "Creating Minecraft", view here:

https://github.com/Hopson97/HopsonCraft/tree/e803ca5fbf51df134cfa7e87c14275c6c73fce8e

# Note

When I made this, I was highly inexperienced at programming (Less than 2 years), and the code is mostly pretty messy and game crashes a lot. 

I have kept it on my GitHub for historical reasons, seeing as I have videos about this on my YouTube channel.


## Versions (As seen in the YouTube videos)

This game has gone through major rewrites and refactors overtime.

To see the source code as it was in episodes 1, 2 and 3 of "Creating Minecraft in C++/ OpenGL" videos, look at an older commit here:

https://github.com/Hopson97/HopsonCraft/tree/90a5d596d07dfe71b5dbf47ec76c0b0802ec9dfa


## Dependencies
The project requires these libraries: SFML (minimum 2.4), GLEW 2.0+ (OpenGL 3.3+), and OpenGL Maths Library (GLM).

Compile using compiler flags:

Windows -> ``-std=c++14 -O3 -s -lglew32s -lglu32 -lopengl32 -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window``

Linux -> ``-std=c++14 -O3 -s -lGLEW -lGLU -lGL -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window``


All the libaries for Linux (At least, on Ubuntu) can be installed with


`` sudo apt-get install libsfml-dev``

`` sudo apt-get install libglew-dev``

`` sudo apt-get install libglm-dev``



## Contributing
An easy way to contribute is to look for the ``///@TODO`` parts in the code. please actually test before doing a pull request.

You can view the code style in [contributing.md](https://github.com/Hopson97/HopsonCraft/blob/master/CODESTYLE.md)

You can view useful implementation details in [implementation.md](https://github.com/Hopson97/HopsonCraft/blob/master/IMPLEMENTATION.md)

Also, checkout the TRELLO! https://trello.com/b/P8ZbobQH/hopsoncraft


## Description
Simple Minecraft clone written using C++.

## Screenshots
![Trees](http://i.imgur.com/4yvLWQE.png "Trees")

![Mountain](http://i.imgur.com/4FKz3it.png "Mountain")

![Cliff](http://i.imgur.com/PGaiYCB.png "Cliff")


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

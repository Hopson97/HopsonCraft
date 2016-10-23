#include "Application.h"

#include "Display.h"
#include "Model.h"
#include "Texture.h"

#include "Shader.h"

#include "Player.h"

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Chunk.h"
#include "Matrix_Math.h"

    std::vector<GLfloat> tempVertexCoords =
    {
     0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f,  0.5f, 0.0f,  // Top Left
    // Second triangle
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left
    };

    std::vector<GLfloat> tempTextureCoords =
    {
        0, 1,
        0, 0,
        1, 0,
        1, 0,
        1, 1,
        0, 1
};


Application::Application()
{
    srand(time(nullptr));
    std::cout << "Starting app!" << std::endl;
}

void checkFps ();
void Application::runMainLoop()
{
    Shader::Shader_Program shader ("Basic_Vertex_Shader", "Basic_Fragment_Shader");

    shader.useProgram();
    Texture_Atlas atlas("Block_Texture_Atlas", 1024, 32);

    Chunk chunk(atlas);
    chunk.setBlockData();
    chunk.bufferMesh();

    Player player;

    sf::Clock dtClock;

    Model rel (tempVertexCoords, tempTextureCoords);
    Texture relT ("cow");

    shader.loadMatrix4(glGetUniformLocation(shader.m_shaderProgram, "projectionMatrix"),
                       Maths::createPerspectiveMatrix());

    while (Display::isOpen()) {
        auto dt = dtClock.restart().asSeconds();
        Display::clear();

        player.update(dt);
        atlas.bind();


        shader.loadMatrix4(glGetUniformLocation(shader.m_shaderProgram, "viewMatrix"),
                           Maths::createViewMatrix(player.getCamera()));

        shader.loadMatrix4(glGetUniformLocation(shader.m_shaderProgram, "modelMatrix"),
                           Maths::createTransforrmationMatrix({0,0,-5},
                                                              {0,0,0},
                                                              {1, 1, 1}));
        chunk.bind();

        chunk.draw();

        relT.bind();
        rel.bind();
        glDrawArrays(GL_TRIANGLES, 0, rel.getVertexCount());


        Display::update();
        checkFps();
        Display::checkForClose();
    }
}

void checkFps ()
{
    static float frameTimes = 0;
    static int   frames = 0;

    static sf::Clock fpsTimer;
    static sf::Clock printFpsTimer;

    frameTimes += (1000000.0f / fpsTimer.restart().asMicroseconds());
    frames++;

    if (printFpsTimer.getElapsedTime().asSeconds() > 1.0f) {
        std::cout << "FPS -> " << frameTimes / frames << "\n";
        printFpsTimer.restart();
    }
}

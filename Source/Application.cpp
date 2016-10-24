#include "Application.h"

#include "Display.h"
#include "OpenGL/GLEW/glew.h"

#include <cstdlib>
#include <iostream>

#include "Playing_State.h"

namespace
{
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

    void checkFps ();
}

Application::Application()
{
    srand(time(nullptr));
    std::cout << "Starting app!" << std::endl;
    m_stateStack.push(std::make_unique<State::Playing_State>(*this));
}


void Application::runMainLoop()
{
    sf::Clock dtClock;

    while (Display::isOpen()) {
        auto dt = dtClock.restart().asSeconds();
        Display::clear();

        m_stateStack.top()->input   (dt);
        m_stateStack.top()->update  (dt);
        m_stateStack.top()->draw    (dt);

        Display::update();
        checkFps();
        Display::checkForClose();
    }
}

void Application::pushState(std::unique_ptr<State::Game_State> state)
{
    m_stateStack.push(std::move(state));
}


/*
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


        Display::update();
        checkFps();
        Display::checkForClose();
    }
}
*/

namespace
{
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
}

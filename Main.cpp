//
// Main.cpp
//
// 2018-05-07
//

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <windows.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Game/TestScene.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window     *g_Window;
SDL_GLContext   g_GLContext;
bool            g_Running = false;

Scene *currentScene = 0;


// sdl, gl, window initialization
void Initialize(std::string windowTitle)
{
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)// | SDL_INIT_GAMECONTROLLER) < 0)
    {
        std::cout << "Could not init sdl: " << SDL_GetError() << std::endl;
        exit(0);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    //g_Window = SDL_CreateWindow("SDL2 Window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0); 
    g_Window = SDL_CreateWindow(windowTitle.c_str(), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if(g_Window==NULL)
    {   
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        exit(0);
    }

    std::cout << "Window created!\n";

    g_GLContext = SDL_GL_CreateContext(g_Window);

    if (g_GLContext == NULL)
    {
        std::cout << "cannot create GL Context." << std::endl;
        exit(0);
    }

    // optional????
    SDL_GL_SetSwapInterval(1);

    GLenum glewError = glewInit();

    if (glewError != GLEW_OK)
    {
        std::cout << "glew error\n";
        exit(0);
    }
}



// resources releasing and sdlquit
void Shutdown()
{
    std::cout << "Quiting..." << std::endl;
    SDL_GL_DeleteContext(g_GLContext);
    SDL_DestroyWindow(g_Window); 
    SDL_Quit();
}


// Handle input(keys and mouse) events
void HandleInput(SDL_Event *event)
{
    switch( event->type )
    {
    case SDL_KEYDOWN:
        std::cout << "Key press detected\n";
        break;

    case SDL_KEYUP:
        if(event->key.keysym.sym == SDLK_ESCAPE)
        {
            g_Running = false;
        }
        std::cout << "Key release detected\n";
        break;

    default:
        break;
    }
}


void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    currentScene->Render();

    SDL_GL_SwapWindow(g_Window);
}


// entry point
int main(int argc, char **argv)
{
    // Initialize window, SDL, GL
    Initialize("Joguin");

    TestScene scene;
    currentScene = &scene;
    std::cout << "aqui?";
    currentScene->LoadResources();

    SDL_Event event;
    g_Running = true;

    // main???
    while(g_Running)
    {
        while( SDL_PollEvent( &event ) )
        {
            HandleInput(&event);
        }

        currentScene->Update();

        Render();
    }

    // realease resources and quit
    Shutdown();

    return 0;
}
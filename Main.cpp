//
// Main.cpp
//
// 2018-05-07
//


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window     *g_Window;
SDL_GLContext  *g_GLContext;
bool            g_Running = false;


// sdl, gl, window initialization
void Initialize(std::string windowTitle)
{
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)// | SDL_INIT_GAMECONTROLLER) < 0)
    {
        std::cout << "Could not init sdl: " << SDL_GetError() << std::endl;
        exit(0);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

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
    SDL_GL_SetSwapInterval(1);
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
    glClearColor ( 0.7, 0.7, 0.7, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(g_Window);
}


// entry point
int main(int argc, char **argv)
{
    // Initialize window, SDL, GL
    Initialize("Joguin");

    SDL_Event event;
    g_Running = true;

    // main???
    while(g_Running)
    {
        while( SDL_PollEvent( &event ) )
        {
            HandleInput(&event);
        }

        Render();
    }

    // realease resources and quit
    Shutdown();

    return 0;
}
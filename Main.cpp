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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window     *g_Window;
SDL_GLContext   g_GLContext;
bool            g_Running = false;

GLuint  g_ShaderProgramID = 0;
GLint   g_VertexPos2DLoc = -1;

#include "Game/Quad.h"

Quad quad;

void InitShaders()
{
    std::cout << "initializing shaders" << std::endl;

    g_ShaderProgramID = glCreateProgram();

    ///
    // VertexShader
    ///

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShaderSource[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };

    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

    glCompileShader(vertexShader);

    GLint vsCompileResult = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vsCompileResult);
    if (vsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't compile vertex shader" << std::endl;
        exit(0);
    }

    // attach

    glAttachShader(g_ShaderProgramID, vertexShader);


    ///
    // Fragment Shader
    ///

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragShaderSource[] =
    {
        "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 0.5, 0.5, 0.5, 1.0 ); }"
    };

    glShaderSource(fragShader, 1, fragShaderSource, NULL);

    glCompileShader(fragShader);

    GLint fsCompileResult = GL_FALSE;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fsCompileResult);
    if (fsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't compile fragment shader" << std::endl;
        exit(0);
    }

    // attach
    glAttachShader(g_ShaderProgramID, fragShader);


    ///
    // Linking
    ///

    glLinkProgram(g_ShaderProgramID);
    GLint linkingResult = GL_FALSE;
    glGetShaderiv(g_ShaderProgramID, GL_LINK_STATUS, &linkingResult);
    if (fsCompileResult != GL_TRUE)
    {
        std::cout << "couldn't link shader" << std::endl;
        exit(0);
    }

    g_VertexPos2DLoc = glGetAttribLocation(g_ShaderProgramID, "LVertexPos2D");
    if (g_VertexPos2DLoc == -1)
    {
        std::cout << "bad variable name" << std::endl;
        exit(0);
    }
}

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

    InitShaders();
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


void LoadResources()
{
    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    quad.LoadResources();
}


void Render()
{
    //glClearColor ( 0.7, 0.7, 0.7, 1.0 );
    glClear(GL_COLOR_BUFFER_BIT);

    //Bind program
    glUseProgram(g_ShaderProgramID);

    //Enable vertex position
    glEnableVertexAttribArray(g_VertexPos2DLoc);

        quad.Render(g_VertexPos2DLoc);

    //Disable vertex position
    glDisableVertexAttribArray(g_VertexPos2DLoc);

    //Unbind program
    glUseProgram(NULL);

    SDL_GL_SwapWindow(g_Window);
}


// entry point
int main(int argc, char **argv)
{
    // Initialize window, SDL, GL
    Initialize("Joguin");

    LoadResources();

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
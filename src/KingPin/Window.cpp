#include "Window.h"
#include "Errors.h"

namespace KingPin
{

Window::Window() {}

Window::~Window() {}

int Window::create(std::string windowName, int &screenWidth, int &screenHeight,
                   unsigned int currentFlags)
{

  Uint32 flags = SDL_WINDOW_OPENGL;

  if (currentFlags & INVISIBLE)
  {
    flags |= SDL_WINDOW_HIDDEN;
  }
  if (currentFlags & FULLSCREEN)
  {
    flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  if (currentFlags & FULLSCREEN)
  {
    flags |= SDL_WINDOW_BORDERLESS;
  }

  // Open a SDL window
  _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screenWidth,
                                screenHeight, flags);///flags);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  if (_sdlWindow == nullptr){
    std::string errorMessage = SDL_GetError();
    fatalError("SDL Window could not be created: " + errorMessage);
  }


  SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
  if (glContext == nullptr)
  {
    std::string errorMessage = SDL_GetError();
    fatalError("SDL_GL context could not be created: " + errorMessage);
  }

  // Checks the OpenGL version
  std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

  GLenum error = glewInit();
  if (error != GLEW_OK)
  {
    // glewInit sometimes gives an unknown error that can safely be ignored,
    // so shouldn't quit program here.
    printf("Error message from glewInit() %s\n", glewGetErrorString(error));
  }

  // Backgroundcolor
  glClearColor(0.4, 0, 0, 1.0);

  // Set VSYNC
  SDL_GL_SetSwapInterval(1);

  // Enable alpha blending
  glEnable(GL_BLEND);
  // Sets the blending settings
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return 0;
}

void Window::swapBuffer() { SDL_GL_SwapWindow(_sdlWindow); }

} // namespace KingPin
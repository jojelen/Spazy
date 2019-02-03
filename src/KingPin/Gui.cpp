#include "Gui.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "GL/glxew.h"

namespace KingPin
{
Gui::Gui(/* args */) {}

Gui::~Gui()
{
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void Gui::init(SDL_Window *window, SDL_GLContext *glContext)
{
  printf("Initializing imGui!\n");
  _window = window;
  _glContext = *glContext; // SDL_GL_CreateContext(_window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard
  // Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(_window, &_glContext);
  ImGui_ImplOpenGL3_Init("#version 130");

  printf("Finished initializing imGui!\n");
}

void Gui::addWindow(std::unique_ptr<GuiWindow> &window)
{
  _guiWindows.push_back(std::move(window));
}

void Gui::show()
{

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(_window);
  ImGui::NewFrame();

  for (auto &window : _guiWindows)
    window->show();

  ImGui::Render();
  SDL_GL_MakeCurrent(_window, _glContext);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::clearGui()
{
  _guiWindows.clear();
}
} // namespace KingPin
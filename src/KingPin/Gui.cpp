#include "Gui.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "GL/glxew.h"

Gui::Gui(/* args */)
{
}

Gui::~Gui()
{
}

void Gui::init(SDL_Window *window, SDL_GLContext *glContext)
{
  printf("Initializing imGui!\n");
  _window = window;
  _glContext = *glContext; //SDL_GL_CreateContext(_window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplSDL2_InitForOpenGL(_window, &_glContext);
  ImGui_ImplOpenGL3_Init("#version 130");

  printf("Finished initializing imGui!\n");
}

void Gui::show()
{

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(_window);
  ImGui::NewFrame();

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)

    if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }


  // printf("Rendering imGui!\n");
  ImGui::Render();
  SDL_GL_MakeCurrent(_window, _glContext);
  // ImGuiIO& io = ImGui::GetIO(); (void)io;
  // glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
  // ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  // glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  // SDL_GL_SwapWindow(_window);

  // printf("Finished showing imGui!\n");
}
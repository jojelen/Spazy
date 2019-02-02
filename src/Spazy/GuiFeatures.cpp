#include "GuiFeatures.h"

Menu::Menu(GameState *gameState) : _gameState(gameState)
{
}
Menu::~Menu()
{
}

void Menu::show()
{
  static bool window = true;
  static ImGuiWindowFlags window_flags = 0;
  window_flags |= ImGuiWindowFlags_NoTitleBar;
  window_flags |= ImGuiWindowFlags_NoScrollbar;
  window_flags |= ImGuiWindowFlags_NoResize;
  window_flags |= ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoCollapse;
  window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::SetNextWindowPos(ImVec2(1280 / 2 - 75, 300));
  ImGui::SetNextWindowSize(ImVec2(150, 150));

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  if (window)
  {
    ImGui::Begin("Menu", &window, window_flags);

    if (ImGui::Button("Single player"))
    {
      *_gameState = GameState::SINGLE_PLAYER;
      window = false;
    }

    if (ImGui::Button("Two players"))
    {
      *_gameState = GameState::TWO_PLAYER;
      window = false;
    }
    ImGui::Button("Options");
    if (ImGui::Button("Quit"))
    {
      *_gameState = GameState::QUIT;
      window = false;
    }
    ImGui::End();
  }
  else
    if (*_gameState == GameState::MENU)
      window = true;
}

FpsCounter::FpsCounter()
{
}
FpsCounter::~FpsCounter()
{
}

void FpsCounter::show()
{
  static bool window = true;
  static ImGuiWindowFlags window_flags = 0;
  window_flags |= ImGuiWindowFlags_NoTitleBar;
  window_flags |= ImGuiWindowFlags_NoScrollbar;
  window_flags |= ImGuiWindowFlags_NoResize;
  window_flags |= ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoCollapse;
  window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::SetNextWindowPos(ImVec2(640, 20), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  if (window)
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("FPS", &window, window_flags);

    ImGui::Text("FPS = %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
  }
}
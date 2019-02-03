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
  else if (*_gameState == GameState::MENU)
    window = true;
}

LevelCounter::LevelCounter(int *level) : _level(level)
{
}
LevelCounter::~LevelCounter()
{
}

void LevelCounter::show()
{
  static bool window = true;
  static ImGuiWindowFlags window_flags = 0;
  window_flags |= ImGuiWindowFlags_NoTitleBar;
  window_flags |= ImGuiWindowFlags_NoScrollbar;
  window_flags |= ImGuiWindowFlags_NoResize;
  window_flags |= ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoCollapse;
  window_flags |= ImGuiWindowFlags_NoBackground;

  ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2.f, 0), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_FirstUseEver);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  if (window)
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Level", &window, window_flags);

    ImGui::Text("Level %i", *_level);
    ImGui::End();
  }
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

  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_FirstUseEver);

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

PlayerInfo::PlayerInfo(Spaceship *player) : _player(player)
{
}
PlayerInfo::~PlayerInfo() {}

void PlayerInfo::show()
{
  if (_player != nullptr)
  {
    static bool window = true;
    static ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoBackground;

    // if (_player->getPlayerNr() == 1)
    ImGui::SetNextWindowPos(ImVec2(0, 0), 0, ImVec2(0.5f, 0.5f));
    // else if (_player->getPlayerNr() == 2)
    // ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x-200, 50));
    // ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x, 0), 0, ImVec2(0.5f,0.5f));
    ImGui::SetNextWindowSize(ImVec2(0, 0)); //, ImGuiCond_FirstUseEver);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    if (window)
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("FPS", &window, window_flags);
      if (_player->getPlayerNr() == 1)
      {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Player %i", _player->getPlayerNr());
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Score %i", _player->getScore());
      }
      else
      {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Player %i", _player->getPlayerNr());
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Score %i", _player->getScore());
      }

      float lifeFraction = _player->getLife() / _player->getMaxLife();
      char text[10];
      sprintf(text, "%.0f %%", 100 * lifeFraction);
      ImGui::ProgressBar(lifeFraction, ImVec2(100, 20), text);
      // ImGui::Text("x = %.1f",ImGui::GetIO().DisplaySize.x);
      // ImGui::Text("y = %.1f",ImGui::GetIO().DisplaySize.y);
      ImGui::End();
    }
  }
}

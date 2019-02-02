#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace KingPin
{
class GuiWindow
{
public:
  GuiWindow();
  virtual ~GuiWindow();

  virtual void show() = 0;

private:
};
} // namespace KingPin
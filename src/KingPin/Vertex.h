#pragma once
#include <GL/glew.h>

namespace KingPin
{
struct Position
{
  float x, y;
};

struct Color
{
  GLubyte r, g, b, a;

  Color() : r(0), g(0), b(0), a(0) {}

  Color(GLubyte R, GLubyte G, GLubyte B, GLubyte A) : r(R), g(G), b(B), a(A) {}
};

struct UV
{
  float u, v;
};
// Each vertex is specified with a position, color and uv.
struct Vertex
{
  Position position;
  Color color;
  UV uv;
  void setPosition(float x, float y)
  {
    position.x = x;
    position.y = y;
  }
  void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
  {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
  }
  void setUV(float u, float v)
  {
    uv.u = u;
    uv.v = v;
  }
};
} // namespace KingPin
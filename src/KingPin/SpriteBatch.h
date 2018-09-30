#pragma once

#include "Vertex.h"
#include "glm/glm.hpp"
#include <GL/glew.h>
#include <vector>

namespace KingPin
{

// Describes the kind of sorting to do for the sprites
enum class GlyphSortType
{
  NONE,
  FRONT_TO_BACK,
  BACK_TO_FRONT,
  TEXTURE
};

// One Glyph
class Glyph
{

public:
  Glyph(){};

  Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture,
        float Depth, const Color &color)
      : texture(Texture), depth(Depth)
  {

    topLeft.color = color;
    topLeft.setPosition(destRect.x, destRect.y + destRect.w);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    bottomLeft.color = color;
    bottomLeft.setPosition(destRect.x, destRect.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);

    bottomRight.color = color;
    bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    topRight.color = color;
    topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
  }

  Glyph(const glm::vec4 &destRect, const float angle, const glm::vec4 &uvRect,
        GLuint Texture, float Depth, const Color &color)
      : texture(Texture), depth(Depth)
  {

    float cos = std::cos(angle);
    float sin = std::sin(angle);

    glm::mat2x2 rotationMatrix(sin, -cos, cos, sin);

    // Center position of sprite
    glm::vec2 pos(destRect.x, destRect.y);

    // Rotating the corners
    glm::vec2 TopLeft =
        rotationMatrix * glm::vec2(-destRect.w / 2, destRect.z / 2);
    glm::vec2 TopRight =
        rotationMatrix * glm::vec2(destRect.w / 2, destRect.z / 2);
    glm::vec2 BottomLeft =
        rotationMatrix * glm::vec2(-destRect.w / 2, -destRect.z / 2);
    glm::vec2 BottomRight =
        rotationMatrix * glm::vec2(destRect.w / 2, -destRect.z / 2);

    topLeft.color = color;
    topLeft.setPosition(pos.x + TopLeft.x, pos.y + TopLeft.y);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    bottomLeft.color = color;
    bottomLeft.setPosition(pos.x + BottomLeft.x, pos.y + BottomLeft.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);

    bottomRight.color = color;
    bottomRight.setPosition(pos.x + BottomRight.x, pos.y + BottomRight.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    topRight.color = color;
    topRight.setPosition(pos.x + TopRight.x, pos.y + TopRight.y);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
  }

  GLuint texture;
  float depth;
  Vertex topLeft, bottomLeft, topRight, bottomRight;
};
// Stores the information of what spritebatch needs to render
class RenderBatch
{
public:
  RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture)
      : offset(Offset), numVertices(NumVertices), texture(Texture) {}
  GLuint offset;
  GLuint numVertices;
  GLuint texture;
};

// Draws and renders sprites
class SpriteBatch
{
public:
  SpriteBatch();
  ~SpriteBatch();

  // Creates the vertex attribute array object
  void init();

  // Sets the sorttype and clears the _glyphs
  void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

  // Sorts the glyphs
  void end();

  // Creates a glyph and pushes it back to _glyphs
  void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture,
            float depth, const Color &color);
  void draw(const glm::vec4 &destRect, const float angle,
            const glm::vec4 &uvRect, GLuint texture, float depth,
            const Color &color);

  // Renders the batch onto the screen
  void renderBatch();

private:
  GLuint _vbo, _vao;

  std::vector<Glyph> _glyphs;          // Actual glyphs
  std::vector<Glyph *> _glyphPointers; // This is for sorting
  std::vector<RenderBatch> _renderBatches;
  GlyphSortType _sortType;

  // Stores all the glyphs of the same kind in a separate RenderBatch.
  // Stores the vertex data in the _vbo
  void createRenderBatches();
  // Creates vertex array object and binds it to the
  // vertex buffer.
  void createVertexArray();

  // Sorts the glyps accoring to _sortType
  void sortGlyphs();

  // Functions that compare two glyphs
  static bool compareFrontToBack(Glyph *a, Glyph *b);
  static bool compareBackToFront(Glyph *a, Glyph *b);
  static bool compareTexture(Glyph *a, Glyph *b);
};

} // namespace KingPin
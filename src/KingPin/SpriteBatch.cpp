#include "SpriteBatch.h"
#include <algorithm>

namespace KingPin
{

SpriteBatch::SpriteBatch() : _vbo(0), _vao(0) {}
SpriteBatch::~SpriteBatch() {}

void SpriteBatch::init() { createVertexArray(); }

void SpriteBatch::begin(GlyphSortType sortType /*= GlyphSortType::TEXTURE*/)
{
  _sortType = sortType;
  // Clears the data, i.e. restores the sizes
  _renderBatches.clear();

  _glyphs.clear();
}
void SpriteBatch::end()
{
  // Set up the pointers for fast sorting
  _glyphPointers.resize(_glyphs.size());
  for (int i = 0; i < _glyphs.size(); i++)
  {
    _glyphPointers[i] = &_glyphs[i];
  }
  sortGlyphs();
  createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect,
                       GLuint texture, float depth, const Color &color)
{
  _glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::draw(const glm::vec4 &destRect, const float angle,
                       const glm::vec4 &uvRect, GLuint texture, float depth,
                       const Color &color)
{

  _glyphs.emplace_back(destRect, angle, uvRect, texture, depth, color);
}

void SpriteBatch::renderBatch()
{

  // Binds the vertex attribute array
  glBindVertexArray(_vao);
  // Loops through all the different batches with different texture.
  // Renders them on the screen
  for (int i = 0; i < _renderBatches.size(); i++)
  {
    // Binds the texture of the batch
    glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
    // Draws all the vertices of the sprites in the batch
    glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset,
                 _renderBatches[i].numVertices);
  }
  // Unbinds the vertex attribute array
  glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
  // All the vertices sorted in a vector
  std::vector<Vertex> vertices;
  vertices.resize(_glyphPointers.size() * 6);

  // If there are no glyphs stored, we dont need to create any batches
  if (_glyphPointers.empty())
  {
    return;
  }
  int offset = 0;
  int cv = 0; // current vertex

  // Add the first glyph with 6 vertices to the renderBatch
  _renderBatches.emplace_back(0, 6, _glyphPointers[0]->texture);
  vertices[cv++] = _glyphPointers[0]->topLeft;
  vertices[cv++] = _glyphPointers[0]->bottomLeft;
  vertices[cv++] = _glyphPointers[0]->bottomRight;
  vertices[cv++] = _glyphPointers[0]->bottomRight;
  vertices[cv++] = _glyphPointers[0]->topRight;
  vertices[cv++] = _glyphPointers[0]->topLeft;
  offset += 6;

  // Puts the vertices of all the rest glyphs in vertices
  for (int cg = 1; cg < _glyphs.size(); cg++)
  {
    // Check if the next glyph is of the same sort.
    if (_glyphPointers[cg]->texture != _glyphPointers[cg - 1]->texture)
    {
      _renderBatches.emplace_back(offset, 6, _glyphPointers[cg]->texture);
    }
    // If it is the same, we add 6 more vertices to that batch.
    else
    {
      _renderBatches.back().numVertices += 6;
    }
    vertices[cv++] = _glyphPointers[cg]->topLeft;
    vertices[cv++] = _glyphPointers[cg]->bottomLeft;
    vertices[cv++] = _glyphPointers[cg]->bottomRight;
    vertices[cv++] = _glyphPointers[cg]->bottomRight;
    vertices[cv++] = _glyphPointers[cg]->topRight;
    vertices[cv++] = _glyphPointers[cg]->topLeft;
    offset += 6;
  }

  // Bind the buffer
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  // oprhan the buffer, i.e. get a brand new buffer.
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr,
               GL_DYNAMIC_DRAW);
  // upload the data
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex),
                  vertices.data());
  // Unbind the buffer
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void SpriteBatch::createVertexArray()
{

  if (_vao == 0)
  {
    glGenVertexArrays(1, &_vao); // Generates a vertex array object
  }
  // Binds the vertex array object
  glBindVertexArray(_vao);

  if (_vbo == 0)
  {
    glGenBuffers(1, &_vbo); // Generates a vertex buffer object
  }
  // Binds the vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  // Points the position, color and uv attributes of the vertex array object
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, position));
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
                        (void *)offsetof(Vertex, color));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, uv));

  // Enables the vertex attribute pointers
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  // Unbinds the vertex array
  glBindVertexArray(0);
}

void SpriteBatch::sortGlyphs()
{
  switch (_sortType)
  {
  case GlyphSortType::BACK_TO_FRONT:
    std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
                     compareBackToFront);
    break;
  case GlyphSortType::FRONT_TO_BACK:
    std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
                     compareFrontToBack);
    break;
  case GlyphSortType::TEXTURE:
    std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(),
                     compareTexture);
    break;
  }
}

bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b)
{
  return (a->depth < b->depth);
}
bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b)
{
  return (a->depth > b->depth);
}
bool SpriteBatch::compareTexture(Glyph *a, Glyph *b)
{
  return (a->texture < b->texture); // sorts the textures according to texture
                                    // ID
}
} // namespace KingPin
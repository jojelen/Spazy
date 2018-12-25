#pragma once

#include "KingPin/SpriteBatch.h"
#include <glm/glm.hpp>

enum PopID {
	plusOne, start, gameOver
};

class Effect
{
public:
	Effect();

	virtual ~Effect();

  // Draws the effect, returns true if its lifetime runs out.
	virtual bool draw(KingPin::SpriteBatch& spriteBatch) = 0;

protected:
	float _width, _height;

	int _lifetime;
	int _life;

	int _textureID;
	glm::vec2 _position;
};

//-----------------------------------------------------------------------------

class Explosion : Effect
{
  public:
  Explosion(const glm::vec2& pos, const float size);

	~Explosion();

	bool draw(KingPin::SpriteBatch& spriteBatch) override;

private:
  float _size;
};

class PopUp : Effect
{
public:
	PopUp(const glm::vec2& pos, int lifetime, PopID popID);

	~PopUp();

	bool draw(KingPin::SpriteBatch& spriteBatch) override;
};


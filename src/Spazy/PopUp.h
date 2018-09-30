#pragma once

#include "KingPin/SpriteBatch.h"
#include <glm/glm.hpp>

enum PopID {
	plusOne, start, gameOver
};
class PopUp
{
public:
	PopUp(const glm::vec2& _position, int lifetime, PopID popID);

	~PopUp();

	bool draw(KingPin::SpriteBatch& spriteBatch);

private:

	float _width, _height;

	int _lifetime;
	int _life;

	int _textureID;
	glm::vec2 _position;

};


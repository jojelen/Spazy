#pragma once

#include <KingPin/SpriteBatch.h>
#include <KingPin/InputManager.h>

#include <algorithm>

#include "Entity.h"
#include "Asteroid.h"
#include "Laser.h"
#include "PopUp.h"
#include "Spaceship.h"

class GameContent
{
	public:
		GameContent();
		~GameContent();

		void deleteContent();

		void initializeSpriteBatches(float screenWidth, float
				screenHeight);

		void update(float deltaTime);
		void draw();

		void addGameOver();
		void addPlayer(int controls, KingPin::InputManager* inputManager);
		void addAsteroid();
		int getNumPlayers();
		int getNumAsteroids();

	private:

		KingPin::SpriteBatch _entitySpriteBatch;
		KingPin::SpriteBatch _spriteBatch;
		KingPin::SpriteBatch _popBatch;

		std::vector<Entity *> _entities;
		std::vector<Asteroid *> _asteroids;
		std::vector<PopUp *> _popUps;
		std::vector<Laser> _lasers;
		std::vector<Spaceship *> _players;

		// For adding content within frame
		float _screenWidth, _screenHeight; 
		
};

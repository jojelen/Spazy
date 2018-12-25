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

    // @brief: Updates the game content:
    //  1.) Updates the players and subsequently their lasers. Checks for 
    //      collisions with other entities.
    //  2.) Updates other entities: checks DESTROYED status and deletes the 
    //      entity and adds an explosion if so.
		void update(float deltaTime);

		void draw(); // Calls effects and entities draw functions

		void addGameOver(); // Adds a GAME OVER pop up sign
		void addPlayer(int playerNr, KingPin::InputManager* inputManager);
		void addAsteroid();
    void addExplosion( const glm::vec2 pos);

		int getNumPlayers(); // Returns the number of players that are alive
		int getNumAsteroids(); // Returns the number of asteroids

	private:

		KingPin::SpriteBatch _entitySpriteBatch;
		KingPin::SpriteBatch _spriteBatch;
		KingPin::SpriteBatch _popBatch;

		std::vector<Entity *> _entities;
		std::vector<Asteroid *> _asteroids;

    std::vector<Effect * > _effects;

		std::vector<Spaceship *> _players;

		// For adding content within frame
		float _screenWidth, _screenHeight; 
		
};

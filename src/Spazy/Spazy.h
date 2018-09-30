#pragma once

#include <KingPin/Camera2D.h>
#include <KingPin/GLSLProgram.h>
#include <KingPin/InputManager.h>
#include <KingPin/SpriteBatch.h>
#include <KingPin/Window.h>

#include "Entity.h"
#include "Asteroid.h"
#include "Laser.h"
#include "PopUp.h"
#include "Spaceship.h"
#include "World.h"

enum class GameState
{
  PLAY,
  MENU,
  QUIT
};

class Spazy
{
public:
  Spazy();
  ~Spazy();

  void menu();

private:
  
  void run(unsigned int numPlayers = 1);
  void shutDownGame();
  void clearGameContent();

  void initSystems();
  void initShaders();

  /// Main game loop for the program
  void gameLoop();

  void processInput();
  void drawGame();

  void updateDynamicalContent(float deltaTime);

  void startLevel(unsigned int level);
  
  void addPlayer(int controls);
  void addAsteroid();

private:
  /// Member Variables
  KingPin::Window _window;              // The game window
  KingPin::GLSLProgram _textureProgram; // The shader program
  KingPin::InputManager _inputManager;  // Handles input
  KingPin::Camera2D _camera;            // Main Camera

  KingPin::SpriteBatch _entitySpriteBatch;
  KingPin::SpriteBatch _spriteBatch;
  KingPin::SpriteBatch _popBatch;
  std::vector<Entity *> _entities;
  std::vector<Asteroid *> _asteroids;
  std::vector<PopUp *> _popUps;
  std::vector<Laser> _lasers;
  std::vector<Spaceship *> _players;

  
  
  World _world;

  GameState _gamestate;
  bool _windowInitialized;

  int _screenWidth, _screenHeight;
  unsigned int _numPlayers;
  int _fps;
  // int _gunReload;

  int _score;
  void printScore() const;

  int _currentLevel;
};

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
#include "GameContent.h"

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
  

private:
  /// Member Variables
  KingPin::Window _window;              // The game window
  KingPin::GLSLProgram _textureProgram; // The shader program
  KingPin::InputManager _inputManager;  // Handles input
  KingPin::Camera2D _camera;            // Main Camera

  void loadTexturesIntoKingPin();

  GameContent _gameContent; // Handles the asteroids, players, etc.  
  
  World _world;

  GameState _gamestate;
  bool _windowInitialized;

  int _screenWidth, _screenHeight;
  unsigned int _numPlayers;
  int _fps;
  // int _gunReload;

  int _score;
  void printScore() const;

  void addPlayers();

  int _currentLevel;
};

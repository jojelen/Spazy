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
  MENU,
  SINGLE_PLAYER,
  TWO_PLAYER,
  QUIT
};

class Spazy
{
public:
  Spazy();
  ~Spazy();

  void start();

private:
  
  void run(unsigned int numPlayers = 1);
  void shutDownGame();
  void clearGameContent();

  void initSystems();
  void initShaders();

  void menuLoop();
  void gameLoop(); /// Main game loop for the program

  void processInput();
  void drawGame();

  void updateDynamicalContent(float deltaTime);

  void startLevel(unsigned int level);
  
private:
  /// Member Variables
  KingPin::Window _window;              // The game window
  KingPin::GLSLProgram _textureProgram; // The shader program
  KingPin::InputManager _inputManager;  
  KingPin::Camera2D _camera;            
  

  void addEssentialGui();
  void loadTexturesIntoKingPin();

  GameContent _gameContent; // Handles the asteroids, players, etc.  
  
  World _world;

  GameState _gamestate;
  bool _windowInitialized;

  int _screenWidth, _screenHeight;
  unsigned int _numPlayers;
  int _fps;

  int _score;
  void printScore() const;

  void addPlayers();

  int _currentLevel;
};

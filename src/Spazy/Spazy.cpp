#include "Spazy.h"
#include "Asteroid.h"

#include "KingPin/KingPin.h"
#include "KingPin/ResourceManager.h"
#include "KingPin/Timing.h"

#include <SDL/SDL.h>
#include <algorithm>
#include <iostream>
#include <string>

Spazy::Spazy()
    : _screenWidth(1280), _screenHeight(920), _numPlayers(1),
      _gamestate(GameState::MENU), _windowInitialized(false), _currentLevel(1) {
}

Spazy::~Spazy() {}

void Spazy::menu() {

  while (_gamestate == GameState::MENU) {
    std::cout << "Space Q!\n";
    std::cout << "Menu:\n";
    std::cout << " 1. 1 player\n";
    std::cout << " 2. 2 players\n";
    std::cout << " 0. Quit\n";

    std::cout << "Choice: ";
    std::string choice;
    std::getline(std::cin, choice);
    try {
      switch (std::stoi(choice)) {
      case 1:
        run();
        break;
      case 2:
        run(2);
        break;
      case 0:
        _gamestate = GameState::QUIT;
        break;
      default:
        std::cout << "Invalid choice.\n";
        break;
      }
    } catch (...) {
      std::cout << "Invalid choice.\n";
    }
  }
}

void Spazy::run(unsigned int numPlayers) {
  _gamestate = GameState::PLAY;
  _numPlayers = numPlayers;

  initSystems();

  gameLoop();
}

void Spazy::shutDownGame() {
  _gameContent.addGameOver();
  
  _gamestate = GameState::MENU;
}

void Spazy::clearGameContent() {

  _currentLevel = 1;
 _gameContent.deleteContent();

}

void Spazy::initSystems() {
  if (!_windowInitialized) {
    std::cout << "Initializing KingPin!\n"; // DEBUG
    // Initialize KingPin engine
    KingPin::init();
    // Create window
    _window.create("Spazy", _screenWidth, _screenHeight, 0);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // Color of background

    initShaders();

    _gameContent.initializeSpriteBatches(_screenWidth, _screenHeight);

    // Load pngs
    KingPin::ResourceManager::getTexture(
        "src/Spazy/res/textures/asteroid.png");
    KingPin::ResourceManager::getTexture("src/Spazy/res/textures/player.png");
    KingPin::ResourceManager::getTexture(
        "src/Spazy/res/textures/playerLeft.png");
    KingPin::ResourceManager::getTexture(
        "src/Spazy/res/textures/playerRight.png");
    KingPin::ResourceManager::getTexture(
        "src/Spazy/res/textures/playerForward.png");
    KingPin::ResourceManager::getTexture("src/Spazy/res/textures/1.png");
    KingPin::ResourceManager::getTexture(
        "src/Spazy/res/textures/gameover.png");
    KingPin::ResourceManager::getTexture("src/Spazy/res/textures/circle.png");

    // Set closed topology
    Entity::setWorldSize(_screenWidth, _screenHeight);

    // Initialize the Camera2D
    _camera.init(_screenWidth, _screenHeight);
    _windowInitialized = true;
  }

  clearGameContent();

  std::cout << "Initializing Players!\n"; // DEBUG
  // Initialize player spaceship
  for (int i = 0; i < _numPlayers; ++i)
    _gameContent.addPlayer(i, &_inputManager);

  std::cout << "Initializing World!\n"; // DEBUG
  // Initialize the world background
  _world.init();

  startLevel(_currentLevel);
}

void Spazy::startLevel(unsigned int level) {
  for (int i = 0; i < level; ++i)
    _gameContent.addAsteroid();
}

void Spazy::initShaders() {
  // Compile our color shader
  _textureProgram.compileShaders("src/Spazy/res/shaders/textureShading.vert",
                                 "src/Spazy/res/shaders/textureShading.frag");
  _textureProgram.addAttribute("vertexPosition");
  _textureProgram.addAttribute("vertexColor");
  _textureProgram.addAttribute("vertexUV");
  _textureProgram.linkShaders();
}

void Spazy::gameLoop() {
  const float DESIRED_FPS = 60.0f;
  const int MAX_PHYSICS_STEPS = 6;

  KingPin::FpsLimiter fpsLimiter;
  fpsLimiter.setMaxFPS(DESIRED_FPS);

  const float MS_PER_SECOND = 1000.0f;
  const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
  const float MAX_DELTA_TIME = 1.0f;

  float previousTicks = SDL_GetTicks();

  std::cout << "Starting game loop!\n"; // DEBUG
  while (_gamestate == GameState::PLAY) {
    fpsLimiter.begin();

    float newTicks = SDL_GetTicks();
    float frameTime = newTicks - previousTicks;
    previousTicks = newTicks;
    float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

    _inputManager.update();

    processInput();

    int i = 0;
    while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
      float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
      updateDynamicalContent(deltaTime);
      totalDeltaTime -= deltaTime;
      ++i;
    }

    drawGame();

    fpsLimiter.end();
  }
}

void Spazy::processInput() {
  SDL_Event evnt;

  // Constants for camera movement
  const float CAMERA_SPEED = 4.0f;
  const float SCALE_SPEED = 0.1f;

  // If a key gets pressed, this sends the information to _inputManager
  while (SDL_PollEvent(&evnt)) {
    switch (evnt.type) {
    case SDL_QUIT:
      _gamestate = GameState::QUIT;
      break;
    case SDL_MOUSEMOTION:
      _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
      break;
    case SDL_KEYDOWN:
      _inputManager.pressKey(evnt.key.keysym.sym);
      break;
    case SDL_KEYUP:
      _inputManager.releaseKey(evnt.key.keysym.sym);
      break;
    case SDL_MOUSEBUTTONDOWN:
      _inputManager.pressKey(evnt.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      _inputManager.releaseKey(evnt.button.button);
      break;
    }
  }

  if (_inputManager.isKeyPressed(SDLK_q)) {
    _camera.setScale(_camera.getScale() + SCALE_SPEED);
  }
  if (_inputManager.isKeyPressed(SDLK_e)) {
    _camera.setScale(_camera.getScale() - SCALE_SPEED);
  }

  if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
    glm::vec2 mouseCoords = _inputManager.getMouseCoords();
    glm::vec2 worldCoords =
        _camera.convertScreenToWorld(_inputManager.getMouseCoords());

    std::cout << "Mouse coords: " << mouseCoords.x << " " << mouseCoords.y
              << std::endl;
    // std::cout<< "World coords: " << worldCoords.x << " " << worldCoords.y <<
    // std::endl;
  }
}

void Spazy::printScore() const { printf("Score: %i\n", _score); }

void Spazy::updateDynamicalContent(float deltaTime) {

	_gameContent.update( deltaTime);
	
  // Check if there are no players left
  if (_gameContent.getNumPlayers() == 0)
    shutDownGame();

  // Start new level if there are no asteroids left
  if ( _gameContent.getNumAsteroids() == 0 ) {
    std::cout << "Starting level " << _currentLevel + 1 << std::endl; // DEBUG
    startLevel(++_currentLevel);
  }
  _camera.update();
}

void Spazy::drawGame() {
  // std::cout << "Drawing game!\n"; // DEBUG

  // Set the base depth to 1.0
  glClearDepth(1.0);
  // Clear the color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _textureProgram.use();
  // Use texture unit 0
  glActiveTexture(GL_TEXTURE0);

  //----------------------------------------------------------------------------

  GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
  glUniform1i(textureUniform, 0);

  // Grab the camera matrix
  glm::mat4 projectionMatrix = _camera.getCameraMatrix();
  GLint pUniform = _textureProgram.getUniformLocation("P");
  glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

  // Draw world
  _world.draw();

_gameContent.draw();

  //----------------------------------------------------------------------------

  _textureProgram.unuse();

  // Swap our buffer and draw everything to the screen!
  _window.swapBuffer();
}


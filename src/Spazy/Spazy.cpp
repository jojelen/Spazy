#include "Spazy.h"
#include "Asteroid.h"
#include "GuiFeatures.h"

#include "KingPin/GuiWindow.h"
#include "KingPin/KingPin.h"
#include "KingPin/ResourceManager.h"
#include "KingPin/Timing.h"


#include <SDL/SDL.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>


Spazy::Spazy()
    : _screenWidth(1280), _screenHeight(920), _numPlayers(1),
      _gamestate(GameState::MENU), _windowInitialized(false), _currentLevel(1) {
}

Spazy::~Spazy() {}

void Spazy::start() {

  _numPlayers = 0;
  _currentLevel = 0;
  initSystems();

  while (_gamestate != GameState::QUIT) {
    switch (_gamestate) {
    case GameState::MENU: {
      menuLoop();
      break;
    }
    case GameState::SINGLE_PLAYER: {
      run();
      break;
    }
    case GameState::TWO_PLAYER: {
      run(2);
      break;
    }
    }
  }
}

void Spazy::run(unsigned int numPlayers) {
  _numPlayers = numPlayers;

  clearGameContent();

  addPlayers();

  startLevel(_currentLevel);

  gameLoop();
}

void Spazy::shutDownGame() {
  _gameContent.addGameOver();

  _gamestate = GameState::MENU;
}

void Spazy::clearGameContent() {

  _currentLevel = 1;
  _window.clearGui();
  addEssentialGui();
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

    loadTexturesIntoKingPin();

    // Set closed topology
    Entity::setWorldSize(_screenWidth, _screenHeight);

    // Initialize the Camera2D
    _camera.init(_screenWidth, _screenHeight);
    _windowInitialized = true;

    addEssentialGui();
  }

  std::cout << "Initializing World!\n"; // DEBUG
  _world.init();                        // Initialize the world background
}

void Spazy::addEssentialGui() {
  std::unique_ptr<KingPin::GuiWindow> fps(new FpsCounter());
  _window.addGuiWindow(fps);

  std::unique_ptr<KingPin::GuiWindow> level(new LevelCounter(&_currentLevel));
  _window.addGuiWindow(level);

  std::unique_ptr<KingPin::GuiWindow> menu(new Menu(&_gamestate));
  _window.addGuiWindow(menu);
}

void Spazy::startLevel(unsigned int level) {

  // Resets the players to FINE status
  for (int i = 1; i <= _numPlayers; ++i)
    _gameContent.addPlayer(i, &_inputManager, &_window);

  // Adds content of level
  for (int i = 0; i < level; ++i) {
    _gameContent.addRandomAsteroid(100.0f);
  }

  if (level % 3 == 0)
    _gameContent.addUFO();

  // Temp add of flock
  if (level % 2 == 0)
    _gameContent.addFlock(12);
}

void Spazy::addPlayers() {
  std::cout << "Initializing Players!\n"; // DEBUG

  for (int i = 1; i <= _numPlayers; ++i)
    _gameContent.addPlayer(i, &_inputManager, &_window);
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
  while (_gamestate == GameState::SINGLE_PLAYER ||
         _gamestate == GameState::TWO_PLAYER) {
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

void Spazy::menuLoop() {

  const float DESIRED_FPS = 60.0f;
  const int MAX_PHYSICS_STEPS = 6;

  KingPin::FpsLimiter fpsLimiter;
  fpsLimiter.setMaxFPS(DESIRED_FPS);

  const float MS_PER_SECOND = 1000.0f;
  const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;
  const float MAX_DELTA_TIME = 1.0f;

  float previousTicks = SDL_GetTicks();

  std::cout << "Starting menu loop!\n"; // DEBUG
  while (_gamestate == GameState::MENU) {
    fpsLimiter.begin();

    float newTicks = SDL_GetTicks();
    float frameTime = newTicks - previousTicks;
    previousTicks = newTicks;
    float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

    _inputManager.update();

    processInput();

    _camera.update();

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
}

void Spazy::printScore() const { printf("Score: %i\n", _score); }

void Spazy::updateDynamicalContent(float deltaTime) {

  _gameContent.update(deltaTime);

  if (_gameContent.getNumPlayers() == 0)
    shutDownGame();

  // Start new level if there are no asteroids left
  if (_gameContent.getNumEntities() == 0) {
    std::cout << "\nStarting level " << _currentLevel + 1 << std::endl; // DEBUG
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
  _window.showGui();
  // Swap our buffer and draw everything to the screen!
  _window.swapBuffer();
}

void Spazy::loadTexturesIntoKingPin() {
  using namespace KingPin;

  // Load pngs
  ResourceManager::getTexture("src/Spazy/res/textures/asteroid.png");
  ResourceManager::getTexture("src/Spazy/res/textures/asteroidDamaged.png");
  ResourceManager::getTexture("src/Spazy/res/textures/player.png");
  ResourceManager::getTexture("src/Spazy/res/textures/playerForward.png");
  ResourceManager::getTexture("src/Spazy/res/textures/player2.png");
  ResourceManager::getTexture("src/Spazy/res/textures/playerForward2.png");
  ResourceManager::getTexture("src/Spazy/res/textures/1.png");
  ResourceManager::getTexture("src/Spazy/res/textures/gameover.png");
  ResourceManager::getTexture("src/Spazy/res/textures/laserRed.png");
  ResourceManager::getTexture("src/Spazy/res/textures/laserGreen.png");
  ResourceManager::getTexture("src/Spazy/res/textures/smallExplosion1.png");
  ResourceManager::getTexture("src/Spazy/res/textures/smallExplosion2.png");
  ResourceManager::getTexture("src/Spazy/res/textures/smallExplosion3.png");
  ResourceManager::getTexture("src/Spazy/res/textures/smallExplosion4.png");
  ResourceManager::getTexture("src/Spazy/res/textures/smallExplosion5.png");
  ResourceManager::getTexture("src/Spazy/res/textures/smallExplosion6.png");
  ResourceManager::getTexture("src/Spazy/res/textures/enemyShip.png");
}
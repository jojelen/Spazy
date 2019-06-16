#include "HelpFunctions.h"

#include <iostream>
#include <random>

std::vector<glm::vec2> splitVecIntoSeveral(glm::vec2 vec, const int &number)
{
  // std::cout << "Splitting vector\n";
  std::vector<glm::vec2> vectors;
  vectors.resize(number);

  float angleRange = (10.f - glm::length(vec)) * M_PI;
  float fraction = 1.0f / number;

  for (auto &vector : vectors)
  {
    vector.x = number * vec.x;
    vector.y = number * vec.y;
  }
  // Adding the rest to the last one:
  vectors.back().x += vec.x;
  vectors.back().y += vec.y;

  // Check: // DEBUG
  // printVecInfo( "VecIn", vec);
  // for (int i = 0; i < vectors.size(); ++i)
  //    printVecInfo("VecNr " + std::to_string(i), vectors[i]);
  return vectors;
}

void printVecInfo(const std::string &name, const glm::vec2 &vec)
{
  std::cout << name << ": ( " << vec.x << ", " << vec.y << " )"
            << " magn = " << glm::length(vec) << std::endl;
}

float randUnit()
{
  static std::random_device
      rd; // Will be used to obtain a seed for the random number engine
  static std::mt19937 gen(
      rd()); // Standard mersenne_twister_engine seeded with rd()
  static std::uniform_real_distribution<> dist(0., 1.0);


  return (float)dist(gen);
}

glm::vec2 getUnitVec() 
{
  float angle = randUnit() * 2. * M_PI;

  return glm::vec2( cos(angle), sin(angle));
}

int calcScore(EntityType type)
{
  switch(type)
  {
    case SPACESHIP:
    return -50;
    case BIRD: 
    return 5;
    case ASTEROID:
    return 1;
    case ENEMY: 
    return 10;
    default:
    return 0;
  }
}
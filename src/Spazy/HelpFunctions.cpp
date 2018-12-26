#include "HelpFunctions.h"

#include <iostream>
#include <random>

std::vector<glm::vec2> splitVecIntoSeveral(glm::vec2 vec, const int &number)
{
  std::cout << "Splitting vector\n";
  std::vector<glm::vec2> vectors;
  vectors.resize(number);

  for (auto &vector : vectors)
  {
    vector.x = randUnit() * vec.x;
    vec.x -= vector.x;
    vector.y = randUnit() * vec.y;
    vec.y -= vector.y;
  }
  // Adding the rest to the last one:
  vectors.back().x += vec.x;
  vectors.back().y += vec.y;

  Check: // DEBUG
  printVecInfo( "VecIn", vec);
  for (int i = 0; i < vectors.size(); ++i)
     printVecInfo("VecNr " + std::to_string(i), vectors[i]);
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
#include "HelpFunctions.h"

#include <random>
#include <iostream>

std::vector<glm::vec2> splitVecIntoSeveral( glm::vec2 vec, const int &number)
{
  static std::random_device rd;  //Will be used to obtain a seed for the random number engine
  static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  // static std::mt19937 rng;
  // rng.seed(std::random_device()());
  static std::uniform_real_distribution<> dist(0., 1.0);

  std::vector<glm::vec2> vectors;
  vectors.resize( number);

  for (auto &vector : vectors)
  {
    vector.x = dist(gen) * vec.x;
    vec.x -= vector.x;
    vector.y = dist(gen) * vec.y;
    vec.y -= vector.y;
  }
  // Adding the rest to the last one:
  vectors.back().x += vec.x;
  vectors.back().y += vec.y;

  // Check:
  printVecInfo( "VecIn", vec);
  for (int i = 0; i < vectors.size(); ++i)
     printVecInfo("VecNr " + std::to_string(i), vectors[i]);
  return vectors;
}

void printVecInfo( const std::string &name, const glm::vec2 &vec)
{
  std::cout << name << ": ( " << vec.x << ", " << vec.y << " )" << " magn = " << glm::length(vec) <<  std::endl;
}
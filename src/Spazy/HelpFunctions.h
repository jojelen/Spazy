#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

std::vector<glm::vec2> splitVecIntoSeveral( glm::vec2 vec, const int &number);

glm::vec2 getUnitVec();

float randUnit();

void printVecInfo(const std::string &name, const glm::vec2 &vec);
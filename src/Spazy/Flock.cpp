#include "Flock.h"
#include "HelpFunctions.h"

#include <glm/glm.hpp>

Flock::Flock() : _target(nullptr) {}

Flock::~Flock() {}

void Flock::addBird(Bird *bird) { _birds.push_back(bird); }

void Flock::deleteBird(Bird* bird)
{
  for (int i=0; i < _birds.size(); ++i)
  {
    if (bird == _birds[i])
      _birds.erase(_birds.begin() + i);
  }
}

void Flock::updateFlockBehavior(float deltaTime)
{
  align();
  cohesion();
  avoidCollision();
}

void Flock::align()
{
  for (auto &bird : _birds)
  {
    std::vector<Bird *> localBirds = getLocalBirds(bird, _alignRadius);

    bool leaderBird = true;

    if (localBirds.size() > 0)
    {
      glm::vec2 avgVel(0., 0.);
      for (auto &localBird : localBirds)
      {
        avgVel += localBird->getVelocity();
        if (glm::length(bird->getVelocity()) < glm::length(localBird->getVelocity()))
          leaderBird = false;
      }
      avgVel /= localBirds.size();

      glm::vec2 force = avgVel - bird->getVelocity();

      bird->applyForce(0.1f * force, 0.8 * _maxForce);
    }

    if (_target != nullptr)
    {
      glm::vec2 force = _target->getPosition() - bird->getPosition();
      glm::normalize(force);
      bird->applyForce(force, 0.1);
    }

    if (bird->getSpeed() < 1.0f)
      bird->setSpeed( 2.0f);
  }
}

void Flock::cohesion()
{
  for (auto &bird : _birds)
  {
    std::vector<Bird *> localBirds = getLocalBirds(bird, _cohesionRadius);

    if (localBirds.size() > 0)
    {
      glm::vec2 avgPos(0., 0.);
      for (auto &localBird : localBirds)
      {
        avgPos += localBird->getPosition();
      }
      avgPos /= localBirds.size();

      glm::vec2 force = avgPos - bird->getPosition();

      bird->applyForce(0.01f * force, 0.25f * _maxForce);
    }
  }
}

void Flock::setTarget(Entity *target)
{
  _target = target;
}

void Flock::avoidCollision()
{
  for (auto &bird : _birds)
  {
    std::vector<Bird *> localBirds = getLocalBirds(bird, _avoidRadius);

    if (localBirds.size() > 0)
    {
      glm::vec2 allForces(0., 0.);
      for (auto &localBird : localBirds)
      {
        glm::vec2 forceDirection = bird->getPosition() - localBird->getPosition();
        float forcePower = 1. / glm::length(forceDirection);
        glm::normalize(forceDirection);
        allForces += forcePower * forceDirection;
      }
      bird->applyForce(allForces, _maxForce);
    }
  }
}

std::vector<Bird *> Flock::getLocalBirds(Bird *centerBird,
                                         const float radius) const
{
  std::vector<Bird *> localBirds;
  for (auto &bird : _birds)
  {
    if (bird != centerBird)
    {
      if (glm::distance(centerBird->getPosition(), bird->getPosition()) <=
          radius)
        localBirds.push_back(bird);
    }
  }
  return localBirds;
}

Bird *Flock::getClosestBird(Bird *centerBird) const
{
  float minDist = 5000.0f;
  int closestBirdID = 0;
  for (int i = 0; i < _birds.size(); ++i)
  {
    if (_birds[i] != centerBird)
    {
      if (glm::distance(centerBird->getPosition(), _birds[i]->getPosition()) <
          minDist)
      {
        minDist = glm::distance(centerBird->getPosition(), _birds[i]->getPosition());
        closestBirdID = i;
      }
    }
  }
  return _birds[closestBirdID];
}
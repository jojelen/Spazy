#pragma once

#include "Bird.h"

#include <vector>


class Flock
{
  public:
    Flock();
    ~Flock();

  void addBird( Bird* bird);
  void addBirds( std::vector<Bird*> birds);

  void updateFlockBehavior( float deltaTime);

  void setTarget(Entity *target);

  private:

    void align();
    void cohesion();
    void avoidCollision();

    std::vector<Bird*> getLocalBirds(Bird* centerBird, const float radius) const;
    Bird* getClosestBird(Bird* centerBird) const;

  private:
    
    static constexpr float _alignRadius = 400.0f;
    static constexpr float _cohesionRadius = 100.0f;
    static constexpr float _avoidRadius = 50.0f;
    static constexpr float _maxForce = 1.0f;

    Entity* _target;
    std::vector<Bird*> _birds;

};
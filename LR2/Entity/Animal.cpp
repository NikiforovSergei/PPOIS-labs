//
// Created by Egor Vasilkov on 25.11.22.
//

#include "Animal.h"

Animal::Animal(int health,
               int max_health,
               int size,
               const string &name,
               int starvation,
               const int starvation_time,
               int speed,
               bool sex) : Entity(health, max_health, size, name),
                           starvation(starvation),
                           starvationTime(starvation_time),
                           speed(speed),
                           sex(sex) {}
Animal::~Animal() {}



bool Animal::isDied() { return starvation <= 0 or health <= 0; }

int Animal::getStarvation() const { return starvation; }

int Animal::getStarvationTime() const { return starvationTime; }

int Animal::getSpeed() const { return speed; }

bool Animal::getSex() const { return sex; }

void Animal::starving() { starvation -= 1; }

void Animal::saturation() { starvation = starvationTime; }

bool Animal::isLovely(Animal *partner) { return (this->sex != partner->sex) and (this->name == partner->name); }

std::pair<const int, const int> Animal::move() { return {(random() % 3 - 1) * speed,(random() % 3 - 1) * speed}; }



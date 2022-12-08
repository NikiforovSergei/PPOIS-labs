//
// Created by Egor Vasilkov on 25.11.22.
//

#include "Entity.h"

namespace EntityNS {

Entity::Entity(int health, int max_health, int size, const string &name)
    : health(health), maxHealth(max_health), size(size), name(name) {}

Entity::~Entity() = default;

void Entity::getDamage(const int damage) { health -= damage; }

bool Entity::isDied() { return health <= 0; }

string Entity::getName() { return name; }

int Entity::getSize() { return size; }

int Entity::getHealth() { return health; }

int Entity::getMaxHealth() { return maxHealth; }

} // EntityNS
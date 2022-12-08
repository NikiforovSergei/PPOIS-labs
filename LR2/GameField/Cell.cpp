//
// Created by Egor Vasilkov on 25.11.22.
//

#include "Cell.h"
Cell::Cell(int id) : id(id) {}

void Cell::setId(int id) { this->id = id; }

int Cell::getId() const { return id; }

void Cell::putEntity(Plant *entity) {

  if (entityCount() < MaxEntityCount) {
    if (aPlant != nullptr) aPlant = nullptr;

    aPlant = entity;
  }

}

void Cell::putEntity(Animal *entity) {

  if (entityCount() < MaxEntityCount) {
    Animals.push_back(entity);
  }

}

int Cell::entityCount() const { return (Animals.size() + Herbivores.size() + aPlant != nullptr); }

void Cell::putEntity(Herbivore *entity) {

  if (entityCount() < MaxEntityCount) {
    Herbivores.push_back(entity);
  }

}

void Cell::deleteEntity(Plant *entity) { aPlant = nullptr; }

void Cell::deleteEntity(Animal *entity) {

  for (auto it = Animals.begin(); it != Animals.end(); it++) {
    if (*it == entity) {
      Animals.erase(it);
      break;
    }
  }

}

void Cell::deleteEntity(Herbivore *entity) {

  for (auto it = Herbivores.begin(); it != Herbivores.end(); it++) {
    if (*it == entity) {
      Herbivores.erase(it);
      break;
    }
  }

}

void Cell::clearCell() {

  aPlant = nullptr;
  Animals.clear();
  Herbivores.clear();

}

const int Cell::getMaxEntityCount() { return MaxEntityCount; }

bool Cell::isFree() {
  for (auto i : Animals) {
    delete i;
  }
  for (auto i : Herbivores) {
    delete i;
  }
  if (aPlant != nullptr)
    delete aPlant;

  clearCell();
  return entityCount() != 0;

}
const vector<Animal *> &Cell::GetAnimals() const {
  return Animals;
}
void Cell::SetAnimals(const vector<Animal *> &animals) {
  Animals = animals;
}

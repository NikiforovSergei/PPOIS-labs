//
// Created by Egor Vasilkov on 25.11.22.
//

#ifndef TESTLAB2_GAMEFIELD_CELL_H_
#define TESTLAB2_GAMEFIELD_CELL_H_

#include "../Entity/Entity.h"
#include "../Entity/Animal.h"
#include "../Entity/Herbivore.h"
#include "../Entity/Plant.h"
#include <fstream>

using namespace std;

class Cell {
 private:
  const static int MaxEntityCount = 4;
  int id;
  vector<Animal *> Animals;
  vector<Herbivore *> Herbivores;
  Plant *aPlant;

 public:
  Cell(int id);

  int entityCount() const;

  void putEntity(Plant *entity);

  void putEntity(Animal *entity);


  void putEntity(Herbivore *entity);

  void deleteEntity(Plant *entity);

  void deleteEntity(Animal *entity);

  void deleteEntity(Herbivore *entity);

  void clearCell();

  static const int getMaxEntityCount();

  int getId() const;

  void setId(int id);

  bool isFree();

  const vector<Animal *> &GetAnimals() const;
  void SetAnimals(const vector<Animal *> &animals);

  template <typename T>
  requires std::is_same_v<T, Plant>
  Plant *get() { return aPlant; }

  template <typename T>
  requires std::is_same_v<T, Animal>
  std::vector<Animal *> get() { return Animals; }

  template <typename T>
  requires std::is_same_v<T, Herbivore>
  std::vector<Herbivore *> get() { return Herbivores; }

};

#endif //TESTLAB2_GAMEFIELD_CELL_H_

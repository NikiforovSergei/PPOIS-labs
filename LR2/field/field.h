//
// Created by artur on 11/27/22.
//

#ifndef LR2_FIELD_FIELD_H_
#define LR2_FIELD_FIELD_H_

#include <vector>
#include "square.h"
#include <nlohmann/json.hpp>
#include <iomanip>
using json = nlohmann::json;

class Field {
  unsigned long _rows = 0;
  unsigned long _columns = 0;
  unsigned long max_population = 4;

 public:
  std::vector<std::vector<class Square>> squares;
  Field();

  class Square* GetRandomNeighbor(Square &square, int length, bool must_differ);
  void Init(unsigned long rows, unsigned long columns);
  void Save();
  void Load();
  void Clear();
  json ToJSON();
  void Play();
  void Reproduce(Square& square, const std::shared_ptr<class Plant>& plant);
  void Reproduce(Square& square, const std::shared_ptr<class Animal>& animal);
  void Move(Square& square, const std::shared_ptr<class Animal>& animal);
  void GetOld(Square& square, const std::shared_ptr<class Plant>& plant);
  void Die(Square& square, const std::shared_ptr<class Plant>& plant);
  void GetOld(Square& square, const std::shared_ptr<class Animal>& animal);
  void Die(Square& square, const std::shared_ptr<class Animal>& animal);
  void Eat(Square& square, const std::shared_ptr<class Herbivore>& animal);
  void Eat(Square& square, const std::shared_ptr<class Carnivore>& animal);
};

#endif //LR2_FIELD_FIELD_H_

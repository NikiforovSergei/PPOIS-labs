//
// Created by artur on 11/27/22.
//

#ifndef LR2_DWELLERS_DWELLER_H_
#define LR2_DWELLERS_DWELLER_H_

#include <memory>
#include <string>
#include <utility>

class Dweller {
 public:
  enum class Type {
	Plant, Herbivore, Carnivore
  };
  Type GetType();

  Dweller(Type type, std::string name, unsigned int lives, unsigned int size, unsigned int min_size, unsigned int max_size) :
  	type(type), name(std::move(name)), lives(lives), size(size), min_size(min_size), max_size(max_size){};

  std::string name;
  Type type; // тип
  int lives; // пункты жизни
  unsigned int size; // размер
  unsigned int min_size; // размер
  unsigned int max_size; // размер
};

#endif //LR2_DWELLERS_DWELLER_H_

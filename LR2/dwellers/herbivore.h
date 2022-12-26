//
// Created by artur on 11/27/22.
//

#ifndef LR2_DWELLERS_HERBIVORE_H_
#define LR2_DWELLERS_HERBIVORE_H_

#include <utility>
#include "animal.h"

class Herbivore : public Animal {
 public:
  Herbivore(unsigned int size,
			unsigned int min_size,
			unsigned int max_size,
			std::string name,
			unsigned int lifetime,
			unsigned int max_lifetime,
			unsigned int stamina,
			unsigned int max_stamina,
			unsigned int move_length,
			Sex sex)
	  : Animal(Type::Herbivore, size, min_size, max_size, std::move(name), lifetime, max_lifetime, stamina, max_stamina, move_length, sex) {};
  Herbivore(unsigned int size,
			unsigned int min_size,
			unsigned int max_size,
			std::string name,
			unsigned int lifetime,
			unsigned int max_lifetime,
			unsigned int stamina,
			unsigned int max_stamina,
			unsigned int move_length)
	  : Animal(Type::Herbivore, size, min_size, max_size, std::move(name), lifetime, max_lifetime, stamina, max_stamina, move_length) {};

  std::shared_ptr<Herbivore> Clone() {
	return std::make_shared<Herbivore>(min_size, min_size, max_size, name, max_lifetime, max_lifetime, max_stamina, max_stamina, move_length);
  }
};

#endif //LR2_DWELLERS_HERBIVORE_H_

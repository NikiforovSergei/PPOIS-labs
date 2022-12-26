//
// Created by artur on 11/27/22.
//

#ifndef LR2_DWELLERS_ANIMAL_H_
#define LR2_DWELLERS_ANIMAL_H_

#include <utility>

#include "dweller.h"

class Animal : public Dweller {
 public:
  enum class Sex {
	Male, Female
  };
  Sex sex; // пол
  unsigned int move_length; // длина передвижения
  int lifetime; // срок жизни
  unsigned int max_lifetime; // срок жизни
  int stamina; // сколько ходов может оставаться голодным
  unsigned int max_stamina; // сколько ходов может оставаться голодным
  Animal(Type type,
		 unsigned int size,
		 unsigned int min_size,
		 unsigned int max_size,
		 std::string name,
		 unsigned int lifetime,
		 unsigned int max_lifetime,
		 unsigned int stamina,
		 unsigned int max_stamina,
		 unsigned int move_length,
		 Sex sex = rand() % 2 ? Animal::Sex::Female : Animal::Sex::Male)
	  : lifetime(lifetime),
		max_lifetime(max_lifetime),
		sex(sex),
		stamina(stamina),
		max_stamina(max_stamina),
		move_length(move_length),
		Dweller(type, std::move(name), 1, size, min_size, max_size) {};

  Sex OppositeSex() {
	return sex == Animal::Sex::Male ? Animal::Sex::Female : Animal::Sex::Male;
  };

  std::shared_ptr<Animal> Clone() {
	return std::make_shared<Animal>(type, min_size, min_size, max_size, name, max_lifetime, max_lifetime, max_stamina / 2, max_stamina, move_length);
  }
};

#endif //LR2_DWELLERS_ANIMAL_H_

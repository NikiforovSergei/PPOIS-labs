//
// Created by artur on 11/27/22.
//

#ifndef LR2_DWELLERS_PLANT_H_
#define LR2_DWELLERS_PLANT_H_

#include <memory>
#include <utility>
#include "dweller.h"

class Plant : public Dweller {
 public:
  unsigned int min_lives;
  unsigned int max_lives;
  Plant(unsigned int lives, unsigned int min_lives, unsigned int max_lives, std::string name) :
	  min_lives(min_lives),
	  max_lives(max_lives),
  	Dweller(Type::Plant, std::move(name), lives, 2, 2, 20){};

  std::shared_ptr<Plant> Clone() {
	return std::make_shared<Plant>(min_lives, min_lives, max_lives, name);
  }
};

#endif //LR2_DWELLERS_PLANT_H_

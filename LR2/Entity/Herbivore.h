//
// Created by Egor Vasilkov on 25.11.22.
//

#ifndef TESTLAB2_ENTITY_HERBIVORE_H_
#define TESTLAB2_ENTITY_HERBIVORE_H_
#include "Animal.h"
class Herbivore : public Animal{
 protected:

 public:
  Herbivore(int health,
            int max_health,
            int size,
            const string &name,
            int starvation,
            const int starvation_time,
            int speed,
            bool sex);

  ~Herbivore() override;




};

#endif //TESTLAB2_ENTITY_HERBIVORE_H_

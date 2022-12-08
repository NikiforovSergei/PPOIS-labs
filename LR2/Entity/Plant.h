//
// Created by Egor Vasilkov on 25.11.22.
//

#ifndef TESTLAB2_ENTITY_PLANT_H_
#define TESTLAB2_ENTITY_PLANT_H_

#include "Entity.h"
class Plant : public EntityNS::Entity{
 public:
  Plant(int health, int max_health, int size, const string &name);

  ~Plant() override;


};

#endif //TESTLAB2_ENTITY_PLANT_H_

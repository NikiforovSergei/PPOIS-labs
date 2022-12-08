//
// Created by Egor Vasilkov on 25.11.22.
//

#ifndef TESTLAB2_ENTITY_ANIMAL_H_
#define TESTLAB2_ENTITY_ANIMAL_H_

#include "Entity.h"

class Animal : public EntityNS::Entity {
 protected:
  int starvation;
  const int starvationTime;
  int speed;
  bool sex;

 public:
  Animal(int health,
         int max_health,
         int size,
         const string &name,
         int starvation,
         const int starvation_time,
         int speed,
         bool sex);

  ~Animal() override;

  int getStarvation() const;

  int getStarvationTime() const;

  int getSpeed() const;

  bool getSex() const;

  virtual void starving();

  virtual void saturation();

  virtual bool isLovely(Animal *partner);

  virtual std::pair<const int, const int> move();

  int getX();

  int getY();

  virtual bool isDied() override;

};

#endif //TESTLAB2_ENTITY_ANIMAL_H_

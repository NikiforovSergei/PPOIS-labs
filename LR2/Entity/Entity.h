//
// Created by Egor Vasilkov on 25.11.22.
//

#ifndef TESTLAB2_ENTITY_ENTITY_H_
#define TESTLAB2_ENTITY_ENTITY_H_

#include <istream>
#include <vector>
#include <string>

using namespace std;

namespace EntityNS {

class Entity {
 protected:
  int health;
  int maxHealth;
  int size;
  string name;

 public:
  Entity(int health, int max_health, int size, const string &name);

  virtual ~Entity();

  virtual void getDamage(const int damage);

  virtual bool isDied();

  string getName();

  virtual int getSize();

  virtual int getHealth();

  virtual int getMaxHealth();

};

} // EntityNS

#endif //TESTLAB2_ENTITY_ENTITY_H_

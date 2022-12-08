//
// Created by Egor Vasilkov on 25.11.22.
//

#include "Herbivore.h"
Herbivore::~Herbivore() {

}
Herbivore::Herbivore(int health,
                     int max_health,
                     int size,
                     const string &name,
                     int starvation,
                     const int starvation_time,
                     int speed,
                     bool sex) : Animal(health,
                                                        max_health,
                                                        size,
                                                        name,
                                                        starvation,
                                                        starvation_time,
                                                        speed,
                                                        sex) {}

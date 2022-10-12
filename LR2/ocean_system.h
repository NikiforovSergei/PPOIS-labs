//
// Created by konstantin on 29.09.22.
//

#ifndef OCEAN_OCEAN_SYSTEM_H
#define OCEAN_OCEAN_SYSTEM_H

#include "vector"
#include "../liv/living.h"
#include "../oceanfield/ocean.h"

class ocean_system : public ocean{
public:
    void run();

    void show_ocean(); // вывод поля на экран

    void cell_state(int,int); // вывод состояния клетки

    int input(int,int); //проверка ввода

    char check_input_char();

    void next();

    void move(std::vector<class living*> &);

};


#endif //OCEAN_OCEAN_SYSTEM_H

//
// Created by konstantin on 29.09.22.
//

#ifndef OCEAN_OCEAN_H
#define OCEAN_OCEAN_H


#include <utility>
#include <vector>
#include "fstream"
#include "../liv/living.h"
#include <unistd.h>
#include "../error/error.h"

class ocean;

//класс игрвого поля
class ocean  {
public:

    class living* fill_field(const std::string&,const std::string&, int[]);// заполнение вектора с полем

    void delete_ocean(); // удаление поля

protected:
    std::vector<std::vector<std::vector<class living*>>> ocean_field; // поле океана
};



#endif //OCEAN_OCEAN_H

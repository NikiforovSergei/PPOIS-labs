/*!
    \file
	\brief Заголовочный файл с описанием namespace Operation
    \author Иван Титлов

    Задаётся код для некоторых из операций, которые может проводить программа
*/
#ifndef SEM3_PPOIS_LAB1_OPERATIONS_H
#define SEM3_PPOIS_LAB1_OPERATIONS_H

#include "Vector.h"

namespace Operation
{
    void getCorner(std::Vector v1, std::Vector v2);
    void division(std::Vector v1, std::Vector v2);
    void comparison(std::Vector v1, std::Vector v2, char operation);
}

#endif //SEM3_PPOIS_LAB1_OPERATIONS_H

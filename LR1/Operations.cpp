/*!
    \file
	\brief Описан код выполнения некоторых из провдимых пользователем операций
    \author Иван Титлов

   Описано выполнение операций getCorner, division и comparison
*/
#include "Operations.h"
#include <iostream>

/*!
	\brief Находит косинус угла между двумя векторами
    \author Иван Титлов
    \param v1,v2 Вектора, над которыми проводится операция
    \return cos a
    Находится косинус угла с помощью форумлы его нахождения
*/
void Operation::getCorner(std::Vector v1, std::Vector v2) { ///
    double chisl = (v1.getCoordinatesOfVector()[0]*v2.getCoordinatesOfVector()[0]+v1.getCoordinatesOfVector()[1]*v2.getCoordinatesOfVector()[1]+v1.getCoordinatesOfVector()[2]*v2.getCoordinatesOfVector()[2]);
    double znam = (v1.getLength()*v2.getLength());
    std::cout<<"cos a= "+ std::to_string(chisl/znam)+"\n";

}
/*!
	\brief Находит деление вектора на вектор
    \author Иван Титлов
    \param v1,v2 Вектора, над которыми проводится операция
    \return cos a
    Обычное деление длин векторов, над которыми проводится операция
*/
void Operation::division(std::Vector v1, std::Vector v2) {

    std::cout<<"result: "+std::to_string(v1.getLength()/v2.getLength())+"\n";

}
/*!
	\brief Описаны операции сравнения двух веткоров
    \author Иван Титлов
    \param v1,v2 Вектора, над которыми проводится операция
    \return Сравнение принимает значение True или False
    В функции описаны различные операции сравнения со знаками <, >, =
*/
void Operation::comparison(std::Vector v1, std::Vector v2, char operation) {
   switch(operation) {
       case '<': {
           if (v1.getLength() < v2.getLength()) {
               std::cout << "true\n";
           } else std::cout << "false\n";
           break;
       }
       case '>': {
           if (v1.getLength() > v2.getLength()) {
               std::cout << "true\n";
           } else std::cout << "false\n";
           break;
       }
       case '=':{
           if (v1.getLength() == v2.getLength()) {
               std::cout << "true\n";
           } else std::cout << "false\n";
           break;
       }
   }
}



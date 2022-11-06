//
// Created by daniil on 4.11.22.
//

#include "Student.hpp"
#include <iostream>
#include <string>

Student::Student(double grade){
    this->grade=grade;
}

bool Student::operator <(const Student &other) {
    if (grade < other.grade) return true;
    else return false;
}

bool Student::operator >(const Student &other) {
    if (grade>other.grade) return true;
    else return false;
}

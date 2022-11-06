//
// Created by daniil on 4.11.22.
//

#ifndef LAB_3_PPOIS_STUDENT_HPP
#define LAB_3_PPOIS_STUDENT_HPP
#include <string>
#include <vector>

class Student {
public:
    double grade;
    Student(double grade);
    bool operator > (const Student& other);
    bool operator <(const Student& other);
};



#endif //LAB_3_PPOIS_STUDENT_HPP

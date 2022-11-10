#include <iostream>
#include "sorting.hpp"
#include <vector>
#include "Student.hpp"


int main() {
    double temp[] = {9.1, -11, 348, -990};
    std::vector<double> vector_temp = {9.1, -11, 348, -990};
    std::vector<char> symbols_vector_temp = {'z', 'a', 'e', 'w'};
    char symbols_temp[] = {'a', 'c', 'e', 'b'};
    std::vector<Student> students = {Student(9.7), Student(8.8), Student(9.9)};
    std::cout<<"Cocktail sort"<<std::endl;
    std::cout << "Sorting all the students by the grade value:" << std::endl;
    show_sequence(students, 3);
    cocktail_sort(students, 3);
    show_sequence(students, 3);
    std::cout << "Sorting the char array: " << std::endl;
    show_sequence(symbols_temp, 4);
    cocktail_sort(symbols_temp, 4);
    show_sequence(symbols_temp, 4);
    std::cout << "Sorting the double array: " << std::endl;
    show_sequence(temp, 4);
    cocktail_sort(temp, 4);
    show_sequence(temp, 4);
    std::cout<<"Strand sort"<<std::endl;
    std::cout << "Sorting all the students by the grade value:" << std::endl;
    show_sequence(students, 3);
    strand_sort(students, 3);
    show_sequence(students, 3);
    std::cout << "Sorting the char array: " << std::endl;
    show_sequence(symbols_vector_temp, 4);
    strand_sort(symbols_vector_temp, 4);
    show_sequence(symbols_vector_temp, 4);
    std::cout << "Sorting the double array: " << std::endl;
    show_sequence(vector_temp, 4);
    strand_sort(vector_temp, 4);
    show_sequence(vector_temp, 4);

    return 0;
}


#ifndef LAB_3_PPOIS_SORTING_HPP
#define LAB_3_PPOIS_SORTING_HPP

#include <iostream>
#include <list>
#include <vector>
#include "Student.hpp"


template<typename T>
void show_sequence(T &container, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << (container[i]) << " ";
    }
    std::cout << "\n";
}

template<> void show_sequence<> (std::vector<Student> &container, int size){
    for (int i = 0; i < size; ++i) {
        std::cout << (container[i].grade) << " ";
    }
    std::cout << "\n";
}

template<typename T>
void cocktail_sort(T &container, int end) {
    bool swapped = true;
    int start = 0;
    end--;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; i++) {
            if (container[i] > container[i + 1]) {
                auto temp_value = container[i + 1];
                container[i + 1] = container[i];
                container[i] = temp_value;
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        end--;
        for (int i = end - 1; i >= start; i--) {
            if (container[i] > container[i + 1]) {
                auto temp_value = container[i + 1];
                container[i + 1] = container[i];
                container[i] = temp_value;
                swapped = true;
            }
        }
        start++;
    }
}


template <typename T>
void additional_strand_sort(std::list<T> &first_list, std::list<T> &second_list)
{
    if (first_list.empty())
    {
        return;
    }

    std::list<T> help_list;
    help_list.push_back(first_list.front());
    first_list.pop_front();

    for (auto it = first_list.begin(); it != first_list.end();)
    {
        if (*it > help_list.back())
        {
            help_list.push_back(*it);
            it = first_list.erase(it);
        }
        else
        {
            it++;
        }
    }

    second_list.merge(help_list);

    additional_strand_sort(first_list, second_list);
}

template <typename T>
void strand_sort(std::vector<T> &container, int high)
{
    std::list<T> in, out;

    for (int i = 0; i < high; i++)
    {
        in.push_back(container[i]);
    }

    additional_strand_sort(in, out);

    int i = 0;
    for (auto number: out)
    {
        container[i] = number;
        i++;
    }
}


#endif //LAB_3_PPOIS_SORTING_HPP

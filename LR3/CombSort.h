#pragma once
#include <vector>
template < typename T >
void combSort(T* sortArray, int size) //comb sort for arrays
{
    T temp;
    int gap = size;
    bool flag = true;
    while (gap != 1 || flag == true)
    {

        gap = (gap) / 1.2473309;
        if (gap < 1)
            gap = 1;
        flag = false;


        for (int i = 0; i < size - gap; i++)
        {
            if (sortArray[i] > sortArray[i + gap])
            {
                temp = sortArray[i];
                sortArray[i] = sortArray[i + gap];
                sortArray[i + gap] = temp;

                flag = true;
            }
        }
    }
};

template < typename T >
void combSort(std::vector<T> &sortVector) // comb sort for vectors
{
    T temp;
    int gap = sortVector.size();
    bool flag = true;

    while (gap != 1 || flag == true)
    {
        gap = (gap) / 1.2473309;
        if (gap < 1)
            gap = 1;
        flag = false;
        for (int i = 0; i < sortVector.size() - gap; i++)
        {
            if (sortVector[i] > sortVector[i + gap])
            {
                temp = sortVector[i];
                sortVector[i] = sortVector[i + gap];
                sortVector[i + gap] = temp;
                flag = true;
            }
        }
    }
}

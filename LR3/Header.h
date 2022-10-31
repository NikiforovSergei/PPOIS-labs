#pragma once
#include <list>

using namespace std;

template <typename T>
void show(T buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << buffer[i] << " ";
    }
}

template <typename T>
void cocktailSort(T &buffer, int high)
{
    bool swapped = true;
    int start = 0;
    int end = high - 1;

    while (swapped) 
    {
        swapped = false;

        for (int i = start; i < end; i++) 
        {
            if (buffer[i] > buffer[i + 1]) 
            {
                auto Temp = buffer[i + 1];
                buffer[i + 1] = buffer[i];
                buffer[i] = Temp;

                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }

        swapped = false;

        end--;

        for (int i = end - 1; i >= start; i--) 
        {
            if (buffer[i] > buffer[i + 1]) 
            {
                auto Temp = buffer[i + 1];
                buffer[i + 1] = buffer[i];
                buffer[i] = Temp;

                swapped = true;
            }
        }

        start++;
    }
}

void _strandSort(list<double> &in, list<double> &out)
{
    if (in.empty())
    {
        return;
    }

    list<double> sublist;
    sublist.push_back(in.front());
    in.pop_front();

    for (auto it = in.begin(); it != in.end();)
    {
        if (*it > sublist.back())
        {
            sublist.push_back(*it);
            it = in.erase(it);
        }
        else
        {
            it++;
        }
    }
    
    out.merge(sublist);

    _strandSort(in, out);
}

template <typename T>
void strandSort(T &buffer, int high)
{
    list<double> in, out;
   
    for (int i = 0; i < high; i++)
    {
        in.push_back(buffer[i]);
    }

    _strandSort(in, out);

    int i = 0;
    for (auto number: out)
    {
        buffer[i] = number;
        i++;
    }
}


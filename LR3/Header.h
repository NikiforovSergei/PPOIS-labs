#ifndef LAB3_H
#define LAB3_H

#include <string>
#include <functional>
#include <vector>

namespace netsort {

    class sorting_network {
    public:
        template<typename T>
        void sortdir(T* a, int i, int j, int dir) { //возрастание или убывание
            if (dir == (a[i] > a[j])) std::swap(a[i], a[j]);
        }

        template<typename T>
        void merge(T* a, int low, int cnt, int dir) {
            if (cnt > 1) {
                int k = cnt / 2;
                for (int i = low; i < low + k; i++) sortdir(a, i, i + k, dir);
                merge(a, low, k, dir);
                merge(a, low + k, k, dir);
            }
        }

        template<typename T>
        void sort(T* a, int low, int cnt, int dir) {
            if (cnt > 1) {
                int k = cnt / 2;
                sort(a, low, k, 1);
                sort(a, low + k, k, 0);
                merge(a, low, cnt, dir);
            }
        }
    };

    /*template<typename T>
    void quickSort(T* items, int left, int right, int dir) {
        int i = left, j = right;
        int m = items[(i + j) / 2];

        T temp;

        do {
            while ((dir == (items[i] < m)) && (i < right)) i++;
            while ((dir == (items[j] > m)) && (j > left)) j--;
            if (i <= j) {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
                i++;
                j--;
            }
        } while (i <= j);
        if (left < j) quickSort(items, left, j, dir);
        if (right > i) quickSort(items, i, right, dir);
    }*/
    template<typename T>
    void quickSort(T* items, int left, int right, int dir) {
        int i = left, j = right;
        int m = items[(i + j) / 2];

        T temp;
        if (dir) {
            do {
                while ((items[i] < m) && (i < right)) i++;
                while ((items[j] > m) && (j > left)) j--;
                if (i <= j) {
                    temp = items[i];
                    items[i] = items[j];
                    items[j] = temp;
                    i++;
                    j--;
                }
            } while (i <= j);
            if (left < j) quickSort(items, left, j, dir);
            if (right > i) quickSort(items, i, right, dir);
        }
        else {
            do {
                while ((items[i] > m) && (i < right)) i++;
                while ((items[j] < m) && (j > left)) j--;
                if (i <= j) {
                    temp = items[i];
                    items[i] = items[j];
                    items[j] = temp;
                    i++;
                    j--;
                }
            } while (i <= j);
            if (left < j) quickSort(items, left, j, dir);
            if (right > i) quickSort(items, i, right, dir);
        }
        
    }
}

#endif
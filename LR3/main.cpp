#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class ShellSort{
public:
    template <typename T>
    void shell(T& other, int quantity) {
        for (int gap = quantity/2; gap > 0; gap /= 2) {
            for (int i = gap; i < quantity; i++) {
                int temp = other[i];
                int j;
                for (j = i; j >= gap && other[j - gap] > temp; j -= gap){
                    other[j] = other[j - gap];
                }
                other[j] = temp;
            }
        }
    }
};


class RadixSort {
public:
    template <typename T>
    int getmax(T& other, int quantity) {
        int max = other[0];
        for (int i = 0; i < quantity; i++) {
            if (other[i] > max) {
                max = other[i];
            }
        }
        return max;
    }

    template <typename T>
    void countsort(T& other, int n, int exp) {
        int i;
        int* output= new int[n];
        int number[10] = { 0 };
        for (i = 0; i < n; i++) {
            number[(other[i] / exp) % 10]++;
        }
        for (i = 1; i < 10; i++) {
            number[i] += number[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            output[number[(other[i] / exp) % 10] - 1] = other[i];
            number[(other[i] / exp) % 10]--;
        }
        for (i = 0; i < n; i++) {
            other[i] = output[i];
        }
    }
    
    template <typename T>
    void radix(T& other, int count) {
        int exp, m;
        m = getmax(other, count);
        for (exp = 1; m / exp > 0; exp *= 10) {
            countsort(other, count, exp);
        }
    }

};


void printArray(int A[], int size);
void printVector(vector<int> A, int size);



int main() {
    
    srand(time(NULL));
    int switcher;
    int counter;
    int switcher_of_rand;
    int number;
    ShellSort sort1;
    RadixSort sort2;
    
    Begin:
    
    cout << "Введите количество элементов: ";
    cin >> counter;
    int *arr = new int[counter];
    
    
    if(counter > 0){
        
        cout << endl;
        cout << "1. Массив" << endl;
        cout << "2. Вектор" << endl;
        cin >> switcher;
    
    
        if (switcher == 1){
            
            
            TryAgainArray:
            
            cout << endl;
            cout << "1. Ввести вручную" << endl;
            cout << "2. Рандомные числа" << endl;
            cin >> switcher_of_rand;
            
            if(switcher_of_rand == 1){
                for(int i = 0; i < counter; i++){
                    cout << "Введите элемент №" << i + 1 << endl;
                    cin >> number;
                    
                    arr[i] = number;
                }
                
                cout << "Ваш массив: " << endl;
                for (int i = 0; i < counter; i ++){
                    cout << arr[i] << " ";
                }
                cout << endl << "--------------------------" << endl;
                cout << endl;
            }
            
            else if (switcher_of_rand == 2){
                for(int i = 0; i < counter; i++){
                    arr[i] = rand() %50;
                }
                
                cout << "Ваш массив: " << endl;
                for (int i = 0; i < counter; i ++){
                    cout << arr[i] << " ";
                }
                cout << endl << "--------------------------" << endl;
                cout << endl;
            }
            else{
                cout << "Введите корректное число" << endl;
                goto TryAgainArray;
            }
            
            
            cout << "Сортировка Шела:" << endl;
            sort1.shell(arr, counter);
            cout << "Массив: ";
            printArray(arr, counter);
            cout << "Поразрядная сортировка:" << endl;
            sort2.radix(arr, counter);
            cout << "Массив: ";
            printArray(arr, counter);
        }
        
        else if (switcher == 2){
            vector <int> vect;
            
            TryAgainVector:
            
            cout << endl;
            cout << "1. Ввести вручную" << endl;
            cout << "2. Рандомные числа" << endl;
            cin >> switcher_of_rand;
            
            if(switcher_of_rand == 1){
                for (int i = 0; i < counter; i++){
                    cout << "Введите элемент №" << i + 1 << endl;
                    cin >> number;
                    
                    vect.push_back(number);
                }
                
                cout << "Ваш вектор: " << endl;
                for (int i = 0; i < counter; i ++){
                    cout << vect[i] << " ";
                }
                cout << endl << "--------------------------" << endl;
                cout << endl;
            }
            
            else if (switcher_of_rand == 2){
                for (int i = 0; i < counter; i++){
                    vect.push_back(rand() %50);
                }
                
                cout << "Ваш вектор: " << endl;
                for (int i = 0; i < counter; i ++){
                    cout << vect[i] << " ";
                }
                cout << endl << "--------------------------" << endl;
                cout << endl;
            }
            
            else{
                cout << "Введите корректное значение" << endl;
                goto TryAgainVector;
            }
            
            
            
            cout << "Сортировка Шела:" << endl;
            sort1.shell(vect, vect.size());
            cout << "Вектор: ";
            printVector(vect, vect.size());
            cout << "Поразрядная сортировка:" << endl;
            sort2.radix(vect, vect.size());
            cout << "Вектор: ";
            printVector(vect, vect.size());
        }
    }
    else{
        cout << "Невозможно создать массив на " << counter << " элементов." << endl;
        goto Begin;
    }
    
   
    
    
    delete [] arr;
    return 0;
}


void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++) {
        cout << " " << A[i];
    }
    cout << "\n";
}

void printVector(vector<int> A, int size)
{
    for (int i = 0; i < size; i++) {
        cout << " " << A[i];
    }
        cout << "\n";
}

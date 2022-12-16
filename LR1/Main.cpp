#include "Code.cpp"
#include <iostream>

using namespace std;

int main()
{
    Matrix S(3);
    S.print_matrix();
    cout << endl;
    Matrix K(3);
    K.print_matrix();
    cout << endl;
    
    int kod, number;
    while(true)
	{
        cout << endl << "1 - Сложение двух матриц" << endl << "2 - Сложение матрицы с числом" << endl;
		cout << "3 - Вычитание двух матриц" << endl << "4 - Вычитание из матрицы числа" << endl << "5 - Произведение двух матриц" << endl << "6 - Произведение матрицы на число"<< endl;
		cout << "7 - Деление матрицы на число" << endl << "8 - Возведение матрицы в степень" << endl << "9 - Вычисление детерминанта" << endl << "10 - Вычисление нормы" << endl;
		cin >> kod;
       
        switch (kod)
		{
        case 1:
        {
            Matrix C = S + K;
            C.print_matrix();
            break;
        }
        case 2:
        {
            cout << "Введите число: " << endl;
            cin >> number;
            Matrix C = S + number;
            C.print_matrix();
            break;
        }
        case 3:
        {
            Matrix C = S - K;
            C.print_matrix();
            break;
        }
        case 4:
        {
            cout << "Введите число: " << endl;
            cin >> number;
            Matrix C = S - number;
            C.print_matrix();
            break;
        }
        case 5:
        {
            Matrix C = S * K;
            C.print_matrix();
            break;
        }
        case 6:
        {
            cout << "Введите число: " << endl;
            cin >> number;
            Matrix C = S * number;
            C.print_matrix();
            break;
        }
        case 7:
        {
            cout << "Введите число: " << endl;
            cin >> number;
            Matrix C = S / number;
            C.print_matrix();
            break;
        }
        case 8:
        {
            cout << "Введите число: " << endl;
            cin >> number;
            Matrix C = S ^ number;
            C.print_matrix();
            break;
        }
        case 9:
        {
            S.Determinant();
            break;
        }
        case 10:
        {
            S.Minor();
            break;
        }
        }

    }
    
}
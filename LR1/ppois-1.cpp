#include <iostream>
#include "polynomial.h"

int main()
{
    int n, choice;
    double m;
    cout << "Enter a degree of polynomial А " << endl;
    cin >> n;
    Polynomial A(n);
    cout << "Enter coefficients of polynomial A" << endl;
    for (int i = 0; i <= n; i++)
    {
        cin >> m;
        A.set(i, m);
    }
    cout << "Enter a degree of polymoial B " << endl;
    cin >> n;
    Polynomial B(n);
    cout << "Enter coefficients of polynomial A " << endl;
    for (int i = 0; i <= n; i++)
    {
        cin >> m;
        B.set(i, m);
    }
    cout << "A: ";
    A.print();
    cout << "B: ";
    B.print();
     
    cout << endl << "1. see А and В" << endl << "2. value of A with argument x (())" << endl << "3. value of B with argument x (())" << endl << "4. coeff value of A ([])" << endl << "5. coeff value of B ([])" << endl << "6. sum of A and B (+)" << endl << "7. addition В to А (+=)" << endl << "8. addition A to B (+=)" << endl << "9. diff А and В (-)" << endl << "10. diff B and A (-)" << endl << "11. substraction B to A (-=)" << endl << "12. substraction A to B (-=)" << endl << "13. composition A and B (*)" << endl << "14. composition A and B (*=)" << endl << "15. composition B and A (*=)" << endl << "16. division A and B (/)" << endl << "17. division B and A (/)" << endl << "18. division A and B (/=)" << endl << "19. division B and A (/=)" << endl << endl;
    
    do
    {
        cin >> choice;
        switch(choice)
        {
            case 1:
            {
                cout << "A: ";
                A.print();
                cout << "B: ";
                B.print();
                cout << endl;
                break;
            }
            case 2:
            {
                double x;
                cout << "Enter x" << endl;
                cin >> x;
                cout << "A(" << x << ") = " << A(x) << endl;
                break;
            }
            case 3:
            {
                double x;
                cout << "Enter x" << endl;
                cin >> x;
                cout << "B(" << x << ") = " << B(x) << endl;
                break;
            }
            case 4:
            {
                int i;
                cout << "enter the coef number of A (from the end)" << endl;
                cin >> i;
                cout << "A[" << i << "] = " << A[i] << endl;
                break;
            }
            case 5:
            {
                int i;
                cout << "enter the coef number of B (from the end)" << endl;
                cin >> i;
                cout << "B[" << i << "] = " << B[i] << endl;
                break;
            }
            case 6:
            {
                Polynomial C = A + B;
                C.print();
                break;
            }
            case 7:
            {
                A += B;
                A.print();
                break;
            }
            case 8:
            {
                B += A;
                B.print();
                break;
            }
            case 9:
            {
                Polynomial C = A - B;
                C.print();
                break;
            }
            case 10:
            {
                Polynomial C = B - A;
                C.print();
                break;
            }
            case 11:
            {
                A -= B ;
                A.print();
                break;
            }
            case 12:
            {
                B -= A;
                B.print();
                break;
            }
            case 13:
            {
                Polynomial C = A * B;
                C.print();
                break;
            }
            case 14:
            {
                A *= B;
                A.print();
                break;
            }
            case 15:
            {
                B *= A;
                B.print();
                break;
            }
            case 16:
            {
                Polynomial C = A / B;
                cout << "denominator: ";
                B.print();
                C.print();
                
                break;
            }
            case 17:
            {
                Polynomial C = B / A;
                cout << "denominator: ";
                A.print();
                C.print();
                break;
            }
            case 18:
            {
                A /= B;
                A.print();
                break;
            }
            case 19:
            {
                B /= A;
                B.print();
                break;
            }
        }
    } while (choice <= 19 && choice != 0);
}

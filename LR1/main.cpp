#include "pch.h"
#include "Matrixx.h"

using namespace MMM;

//Matrix1.txt

void Menu(Matrixx m)
{
    while (true)
    {
        system("cls");

        int k = 0;
        cout << "Choose function:" << endl << "1. Enter matrix from a file." << endl <<
            "2. Print matrix on a screen" << endl <<
            "3. Matrix++." << endl << "4. ++Matrix." << endl <<
            "5. Matrix--." << endl << "6. --Matrix." << endl <<
            "7. Add a Column or a String." << endl <<
            "8. Delete a Column or a String." << endl <<
            "9. Extract Matrix." << endl << "10. Define type of Matrix." << endl <<
            "11. Transporate Matrix." << endl <<"12. End program" << endl <<
            "----------------------" << endl;
        cin >> k;

        system("cls");

        switch (k)
        {
        case 1:
            {
                string FILE;
                cout << "Enter name of a file: "; cin >> FILE;

                m.enter(FILE);
                break;
            }
        case 2:
            {
                m.print();

                system("pause");
                break;
            }
        case 3:
            {
                m++; break;
            }
        case 4:
            {
                ++m; break;
            }
        case 5:
            {
                m--; break;
            }
        case 6:
            {
                --m; break;
            }
        case 7:
            {
                cout << "Add:" << endl << " 1) A Column" << endl << " 2) A String" << endl;
                int k1 = 0, Temp_Int;
                vector<int> Temp_Vector;
                string Temp_String;
                string Temp_Char;
                cin >> k1;

                switch (k1)
                {
                case 1: 
                    { 
                        cout << "Enter a column size: "; int size; cin >> size;
                        cout << "Enter a column:" << endl;
                        for (int i = 0; i < size; i++)
                        {
                            cin >> Temp_Int;
                            Temp_Vector.push_back(Temp_Int);
                        }
                        
                        m.add(1, 0, Temp_Vector);
                            
                        break;
                    }
                case 2:
                    {
                        cout << "Enter a column size: "; int size; cin >> size;
                        cout << "Enter a column:" << endl;
                        for (int i = 0; i < size; i++)
                        {
                            cin >> Temp_Int;
                            Temp_Vector.push_back(Temp_Int);
                        }

                            m.add(0, 1, Temp_Vector);

                            break;
                    }
                }
                break;

            }
        case 8:
            {
                cout << "Delete:" << endl << " 1) A Column" << endl << " 2) A String" << endl;
                int k1 = 0;
                cin >> k1;

                switch (k1)
                {
                case 1:
                    {
                        m.del(1, 0);

                        break;
                    }
                case 2:
                    {
                        m.del(0, 1);

                        break;
                    }
                }
                break;
            }
        case 9:
            {
                int x1, x2, y1, y2;
                cout << "Enter coordinates of extracted matrix: " << endl;
                cin >> x1 >> y1 >> x2 >> y2;

                m.extract(x1, y1, x2, y2);
                break;
            }
        case 10:
            {
                cout << m.type() << endl;

                system("pause");
                break;
            }
        case 11:
            {
                m.trans();
                break;
            }
        case 12:
            {
            return;
            }
        }
    }

}

int main()
{
    Matrixx m1, m2, m3;
    vector<int> Temp_Vector = { 1, 2, 3, 4 };
    string A = "afa";
    vector<vector<int>> VectorA;

    Menu(m1);
}
#include "RubiksCube.h"
/*****************************************************************//**
 * \file   RubiksCube.cpp
 * \brief  Содержит в себе реализацию класса RubiksCube.
 * 
 * \author dokkabae
 * \date   September 2022
 *********************************************************************/
void RubiksCube::Print() //Вывод
{
    for (int i = 0; i < 3; i++)
    {
        cout << "      ";
        for (int j = 0; j < 3; j++)
        {
            cout << facets[0][i][j] << ' ';
        }cout << endl;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int z = 1; z < 5; z++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << facets[z][i][j] << ' ';
            }
        }cout << endl;
    }
    for (int i = 0; i < 3; i++)
    {
        cout << "      ";
        for (int j = 0; j < 3; j++)
        {
            cout << facets[5][i][j] << ' ';
        }cout << endl;
    }
}
void RubiksCube::Initializate() //Создание из файла
{
    string nameFile = "main.txt";
    ifstream file(nameFile);
    char x, y, z;
    int i = 0;
    vector<vector<char>> facet;
    while (file >> x >> y >> z)
    {
        i++;
        vector<char> string{ x,y,z };
        facet.push_back(string);
        if (i == 3)
        {
            facets.push_back(facet);
            i = 0;
            facet.clear();
        }
    }
}
void RubiksCube::CreateFromFile()
{
    string nameFile;
    cout << "Введите название файла: ";
    cin >> nameFile;
    ifstream file(nameFile);
    char x, y, z;
    int i = 0;
    vector<vector<char>> facet;
    while (file >> x >> y >> z)
    {
        i++;
        vector<char> string{ x,y,z };
        facet.push_back(string);
        if (i == 3)
        {
            facets.push_back(facet);
            i = 0;
            facet.clear();
        }
    }
}
void RubiksCube::CreateRandom()
{
    vector<int> numbers{ -6,-5,-4,-3,-2,-1,1,2,3,4,5,6 };
    int amount = 10 + rand() % (100);
    for (int i = 0; i < amount; i++)
    {
        int index = 0 + rand() % (12);
        int negative = 0 + rand() % (2);
        if (negative == 0)
        {
            checkNegative(numbers[index], true);
        }
        else checkNegative(numbers[index], false);
    }
}
bool RubiksCube::CheckEnded()
{
    bool similar = true;
    for (int i = 0; i < 5; i++)
    {
        char center = facets[i][1][1];
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                facets[i][j][k] == center ? similar = true : similar = false;
                if (!similar) break;
            }
            if (!similar) break;
        }
    }
    return similar;
}
void RubiksCube::InputCommands()
{
    string commands;
    cout << "Введите команды поворота граней кубика через пробел(F,R,L,U,D,B,F',R',L',U',D',B'):";
    cin >> commands;
    commands += ' ';
    for (int i = 0; i < commands.size() - 1; i++)
    {
        bool negative = false;
        if (commands[i + 1] == '\'')
        {
            negative = true;
        }
        switch (commands[i])
        {
        case 'F':checkNegative(1, negative); break;
        case 'R':checkNegative(2, negative); break;
        case 'L':checkNegative(3, negative); break;
        case 'U':checkNegative(4, negative); break;
        case 'D':checkNegative(5, negative); break;
        case 'B':checkNegative(6, negative); break;
        }
    }
    if (CheckEnded())
    {
        cout << "Кубик собран!" << endl;
        Print();
    }
}
void RubiksCube::checkNegative(int number, bool negative)
{
    if (negative)
    {
        ExecuteCommand(number * -1);
    }
    else ExecuteCommand(number);
}
void RubiksCube::ExecuteCommand(int number)
{
    switch (number)
    {
    case 1: PositiveFront(); break;
    case -1: NegativeFront(); break;
    case 2: PositiveRight(); break;
    case -2: NegativeRight(); break;
    case 3: PositiveLeft(); break;
    case -3: NegativeLeft(); break;
    case 4: PositiveUp(); break;
    case -4: NegativeUp(); break;
    case 5: PositiveDown(); break;
    case -5: NegativeDown(); break;
    case 6: PositiveBack(); break;
    case -6: NegativeBack(); break;
    }
}
void RubiksCube::PositiveFront() //Поворонт фронтальной части по часовой
{
    //Крутим только лицевую часть
    vector<vector<char>> front(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            front[i][k] = facets[2][j][i];
            k++;
        }
    }
    facets[2] = front;
    //Крутим соседние квадраты
    vector<char> temp = facets[0][2];
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][2][i] = facets[1][k][2];
        facets[1][k][2] = facets[5][0][k];
        facets[5][0][k] = facets[3][i][0];
        facets[3][i][0] = temp[i];
        k--;
    }
}
void RubiksCube::NegativeFront() //Поворот фронтальной части против часовой
{
    //Крутим только лицевую часть
    vector<vector<char>> front(3, vector<char>(3));
    for (int i = 2; i >= 0; i--)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            front[k][i] = facets[2][i][j];
            k++;
        }
    }
    facets[2] = front;
    //Крутим соседние квадраты
    vector<char> temp = facets[0][2];
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][2][i] = facets[3][i][0];
        facets[3][i][0] = facets[5][0][k];
        facets[5][0][k] = facets[1][k][2];
        facets[1][k][2] = temp[i];
        k--;
    }
}
void RubiksCube::PositiveRight()
{
    //Крутим только правую часть
    vector<vector<char>> right(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            right[i][k] = facets[3][j][i];
            k++;
        }
    }
    facets[3] = right;
    //Крутим соседние квадраты правой части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[0][i][2]);
    }
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][k][2] = facets[2][k][2];
        facets[2][k][2] = facets[5][k][2];
        facets[5][k][2] = facets[4][i][0];
        facets[4][i][0] = temp[k];
        k--;
    }
}
void RubiksCube::NegativeRight()
{
    //Крутим только правую часть
    vector<vector<char>> right(3, vector<char>(3));
    for (int i = 2; i >= 0; i--)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            right[k][i] = facets[3][i][j];
            k++;
        }
    }
    facets[3] = right;
    //Крутим соседние квадраты правой части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[0][i][2]);
    }
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][k][2] = facets[4][i][0];
        facets[4][i][0] = facets[5][k][2];
        facets[5][k][2] = facets[2][k][2];
        facets[2][k][2] = temp[k];
        k--;
    }
}
void RubiksCube::PositiveLeft()
{
    //Крутим только левую часть
    vector<vector<char>> left(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            left[i][k] = facets[1][j][i];
            k++;
        }
    }
    facets[1] = left;
    //Крутим соседние квадраты левой части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[0][i][0]);
    }
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][k][0] = facets[4][i][2];
        facets[4][i][2] = facets[5][k][0];
        facets[5][k][0] = facets[2][k][0];
        facets[2][k][0] = temp[k];
        k--;
    }
}
void RubiksCube::NegativeLeft()
{
    //Крутим только левую часть
    vector<vector<char>> left(3, vector<char>(3));
    for (int i = 2; i >= 0; i--)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            left[k][i] = facets[1][i][j];
            k++;
        }
    }
    facets[1] = left;
    //Крутим соседние квадраты левой части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[0][i][0]);
    }
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][k][0] = facets[2][k][0];
        facets[2][k][0] = facets[5][k][0];
        facets[5][k][0] = facets[4][i][2];
        facets[4][i][2] = temp[k];
        k--;
    }
}
void RubiksCube::PositiveUp()
{
    //Крутим только вверхнюю часть
    vector<vector<char>> up(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            up[i][k] = facets[0][j][i];
            k++;
        }
    }
    facets[0] = up;
    //Крутим соседние квадраты вверхней части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[2][0][i]);
    }
    for (int i = 0; i < 3; i++)
    {
        facets[2][0][i] = facets[3][0][i];
        facets[3][0][i] = facets[4][0][i];
        facets[4][0][i] = facets[1][0][i];
        facets[1][0][i] = temp[i];
    }
}
void RubiksCube::NegativeUp()
{
    //Крутим только вверхнюю часть
    vector<vector<char>> up(3, vector<char>(3));
    for (int i = 2; i >= 0; i--)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            up[k][i] = facets[0][i][j];
            k++;
        }
    }
    facets[0] = up;
    //Крутим соседние квадраты вверхней части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[2][0][i]);
    }
    for (int i = 0; i < 3; i++)
    {
        facets[2][0][i] = facets[1][0][i];
        facets[1][0][i] = facets[4][0][i];
        facets[4][0][i] = facets[3][0][i];
        facets[3][0][i] = temp[i];
    }
}
void RubiksCube::PositiveDown()
{
    //Крутим только вверхнюю часть
    vector<vector<char>> down(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            down[i][k] = facets[5][j][i];
            k++;
        }
    }
    facets[5] = down;
    //Крутим соседние квадраты вверхней части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[2][2][i]);
    }
    for (int i = 0; i < 3; i++)
    {
        facets[2][2][i] = facets[1][2][i];
        facets[1][2][i] = facets[4][2][i];
        facets[4][2][i] = facets[3][2][i];
        facets[3][2][i] = temp[i];
    }
}
void RubiksCube::NegativeDown()
{
    //Крутим только нижнюю часть
    vector<vector<char>> down(3, vector<char>(3));
    for (int i = 2; i >= 0; i--)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            down[k][i] = facets[5][i][j];
            k++;
        }
    }
    facets[5] = down;
    //Крутим соседние квадраты нижней части
    vector<char> temp;
    for (int i = 0; i < 3; i++)
    {
        temp.push_back(facets[2][2][i]);
    }
    for (int i = 0; i < 3; i++)
    {
        facets[2][2][i] = facets[3][2][i];
        facets[3][2][i] = facets[4][2][i];
        facets[4][2][i] = facets[1][2][i];
        facets[1][2][i] = temp[i];
    }
}
void RubiksCube::PositiveBack()
{

    //Крутим только заднюю часть
    vector<vector<char>> back(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            back[i][k] = facets[4][j][i];
            k++;
        }
    }
    facets[4] = back;
    //Крутим соседние квадраты
    vector<char> temp = facets[0][0];
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][0][i] = facets[3][i][2];
        facets[3][i][2] = facets[5][2][k];
        facets[5][2][k] = facets[1][k][0];
        facets[1][k][0] = temp[i];
        k--;
    }
}
void RubiksCube::NegativeBack()
{
    //Крутим только заднюю часть
    vector<vector<char>> back(3, vector<char>(3));
    for (int i = 2; i >= 0; i--)
    {
        int k = 0;
        for (int j = 2; j >= 0; j--)
        {
            back[k][i] = facets[4][i][j];
            k++;
        }
    }
    facets[4] = back;
    //Крутим соседние квадраты
    vector<char> temp = facets[0][0];
    int k = 2;
    for (int i = 0; i < 3; i++)
    {
        facets[0][0][i] = facets[1][k][0];
        facets[1][k][0] = facets[5][2][k];
        facets[5][2][k] = facets[3][i][2];
        facets[3][i][2] = temp[i];
        k--;
    }
}
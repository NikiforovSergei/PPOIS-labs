#include "Header.h"

using namespace std;

class Cube
{

public:

    int side = 1;

    bool GameOver = false;

    char cube_1[6][9] = {
      {'W','W','W','W','W','W','W','W','W'}, // white
      {'G','G','G','G','G','G','G','G','G'}, // green
      {'Y','Y','Y','Y','Y','Y','Y','Y','Y'}, // yellow
      {'B','B','B','B','B','B','B','B','B'}, // blue
      {'O','O','O','O','O','O','O','O','O'}, // orange
      {'R','R','R','R','R','R','R','R','R'}  // red
    };

    char cube[6][9] = {
      {' ',' ',' ',' ',' ',' ',' ',' ',' '}, // white
      {' ',' ',' ',' ',' ',' ',' ',' ',' '}, // green
      {' ',' ',' ',' ',' ',' ',' ',' ',' '}, // yellow
      {' ',' ',' ',' ',' ',' ',' ',' ',' '}, // blue
      {' ',' ',' ',' ',' ',' ',' ',' ',' '}, // orange
      {' ',' ',' ',' ',' ',' ',' ',' ',' '}  // red
    };

    void readFile()
    {
        std::string memoryFile[6];

        std::string path = "My_file.txt";

        int countInputString = 0;

        std::ifstream fin;

        fin.open(path);

        if (!fin.is_open())
        {
            std::cout << "Ошибка открытия файла!" << std::endl;
        }
        else
        {
            std::cout << "Файл открыт!" << std::endl;

            std::string inputString;

            while (!fin.eof())
            {
                inputString = "";

                std::getline(fin, inputString);

                if (inputString.length() == 0)break;

                else
                {
                    if (countInputString < 6)
                    {
                        memoryFile[countInputString++] = inputString;
                    }
                    else printf("Error format input file\n");
                }
            }

        }
        fin.close();

        for (int i = 0; i < 6; i++) {

            int lenghtRow = memoryFile[i].length() + 1;

            strcpy_s(cube[i], lenghtRow, memoryFile[i].c_str());
        }
    }





    enum eDirection
    {
        SIDE_LEFT, SIDE_RIGHT, SWAP_1_1_1, SWAP_1_1_2,
        SWAP_1_2_1, SWAP_1_2_2, SWAP_2_1_1, SWAP_2_1_2,
        SWAP_2_2_1, SWAP_2_2_2, SWAP_3_1_1, SWAP_3_1_2,
        SWAP_3_2_1, SWAP_3_2_2
    };

    eDirection dir;

    bool checkCub(char* a, char* b)
    {
        for (int i = 0; i < 54; i++)
        {
            if (*a++ != *b++)
            {
                return false;
            }
        }
        return true;
    }

    void _swap_surfaces(int face) {
        char corner_1 = cube[face][2], side_1 = cube[face][1];
        /*swap CORNERS*/
        cube[face][2] = cube[face][0];
        cube[face][0] = cube[face][6];
        cube[face][6] = cube[face][8];
        cube[face][8] = corner_1;
        /*SIDE CUBES*/
        cube[face][1] = cube[face][3];
        cube[face][3] = cube[face][7];
        cube[face][7] = cube[face][5];
        cube[face][5] = side_1;
    }

    void _swap_surfaces_c(int face) {
        char corner_1 = cube[face][2], side_1 = cube[face][1];
        /*swap CORNERS*/
        cube[face][2] = cube[face][8];
        cube[face][8] = cube[face][6];
        cube[face][6] = cube[face][0];
        cube[face][0] = corner_1;
        /*SIDE CUBES*/
        cube[face][1] = cube[face][5];
        cube[face][5] = cube[face][7];
        cube[face][7] = cube[face][3];
        cube[face][3] = side_1;
    }

    void printCube() {

        system("cls");

        setlocale(LC_ALL, "Russian");

        cout << endl
            << "Что бы взаимодействовать с гранью 1:правая сторона клавиши w и s;левой сторона клавиши q и a;верхней сторона клавиши t и y;нижней сторона клавиши g и h;" << endl
            << "Что бы взаимодействовать с гранью 2:правая сторона клавиши w и s;левой сторона клавиши q и a;верхней сторона клавиши e и r;нижней сторона клавиши d и f;" << endl
            << "Что бы взаимодействовать с гранью 3:правая сторона клавиши w и s;левой сторона клавиши q и a;верхней сторона клавиши g и h;нижней сторона клавиши t и y;" << endl
            << "Что бы взаимодействовать с гранью 4:правая сторона клавиши w и s;левой сторона клавиши q и a;верхней сторона клавиши d и f;нижней сторона клавиши e и r;" << endl
            << "Что бы взаимодействовать с гранью 5:правая сторона клавиши t и y;левой сторона клавиши g и h;верхней сторона клавиши e и r;нижней сторона клавиши d и f;" << endl
            << "Что бы взаимодействовать с гранью 6:правая сторона клавиши g и h;левой сторона клавиши t и y;верхней сторона клавиши e и r;нижней сторона клавиши d и f;" << endl
            << "Что бы переключатся между гранями используйте клавиши z и x" << endl
            << "Что бы выйти используйте клавишу c" << endl
            << "\n-----" << endl;

        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << endl;
            }
            cout << cube[side][j] << " ";
        }
        cout << "\n-----" << endl;

        cout << "Side: " << side + 1 << endl << endl;

        for (int i = 0; i < 6; i++) {
            cout << "\n-----" << endl;
            for (int j = 0; j < 9; j++) {
                if (j % 3 == 0 && j != 0) {
                    cout << endl;
                }
                cout << cube[i][j] << " ";
            }
            cout << "\n-----";
        }
    }

    void input()
    {
        switch (_getch())
        {
        case 'z':
        {
            dir = SIDE_LEFT;

            break;
        }
        case 'x':
        {
            dir = SIDE_RIGHT;

            break;
        }
        case 'w':
        {
            dir = SWAP_1_1_1;

            break;
        }
        case 's':
        {
            dir = SWAP_1_1_2;

            break;
        }
        case 'q':
        {
            dir = SWAP_1_2_1;

            break;
        }
        case 'a':
        {
            dir = SWAP_1_2_2;

            break;
        }
        case 'e':
        {
            dir = SWAP_2_1_1;

            break;
        }
        case 'r':
        {
            dir = SWAP_2_1_2;

            break;
        }
        case 'd':
        {
            dir = SWAP_2_2_1;

            break;
        }
        case 'f':
        {
            dir = SWAP_2_2_2;

            break;
        }
        case 'g':
        {
            dir = SWAP_3_1_1;

            break;
        }
        case 'h':
        {
            dir = SWAP_3_1_2;

            break;
        }
        case 't':
        {
            dir = SWAP_3_2_1;

            break;
        }
        case 'y':
        {
            dir = SWAP_3_2_2;

            break;
        }
        case 'c':
        {
            GameOver = true;

            break;
        }
        }

    }

    void logic()
    {
        switch (dir)
        {
        case SIDE_LEFT:
        {
            if (side > 0)side--;

            break;
        }
        case SIDE_RIGHT:
        {
            if (side < 5)side++;

            break;
        }
        case SWAP_1_1_1:
        {
            /*
            R: [3, 6, 9]
            white -> green
            green -> yellow
            yellow -> blue
            blue -> white
        */
            char temp_white[3] = { cube[0][2], cube[0][5], cube[0][8] };

            for (int i = 0; i < 3; i++) {
                cube[i][2] = cube[i + 1][2];
                cube[i][5] = cube[i + 1][5];
                cube[i][8] = cube[i + 1][8];
            }

            cube[3][2] = temp_white[0];
            cube[3][5] = temp_white[1];
            cube[3][8] = temp_white[2];

            _swap_surfaces(5);

            break;
        }
        case SWAP_1_1_2:
        {
            /*
            R': [3, 6, 9]
            white -> blue
            blue -> yellow
            yellow -> green
            green -> white
            */
            char temp_blue[3] = { cube[3][2], cube[3][5], cube[3][8] };
            for (int i = 3; i >= 1; i--) {
                cube[i][2] = cube[i - 1][2];
                cube[i][5] = cube[i - 1][5];
                cube[i][8] = cube[i - 1][8];
            }

            cube[0][2] = temp_blue[0];
            cube[0][5] = temp_blue[1];
            cube[0][8] = temp_blue[2];

            _swap_surfaces_c(5);

            break;
        }
        case SWAP_1_2_1:
        {
            /*
            L: [1, 4, 7]
            white -> green
            green -> yellow
            yellow -> blue
            blue -> white
        */
            char temp_white[3] = { cube[0][0], cube[0][3], cube[0][6] };

            for (int i = 0; i < 3; i++) {
                cube[i][0] = cube[i + 1][0];
                cube[i][3] = cube[i + 1][3];
                cube[i][6] = cube[i + 1][6];
            }

            cube[3][0] = temp_white[0];
            cube[3][3] = temp_white[1];
            cube[3][6] = temp_white[2];

            _swap_surfaces_c(4);

            break;
        }
        case SWAP_1_2_2:
        {
            /*
            L: [1, 4, 7]
            while -> blue
            blue -> yellow
            yellow -> green
            green -> white
            */
            char temp_blue[3] = { cube[3][0], cube[3][3], cube[3][6] };
            for (int i = 3; i >= 1; i--) {
                cube[i][0] = cube[i - 1][0];
                cube[i][3] = cube[i - 1][3];
                cube[i][6] = cube[i - 1][6];
            }

            cube[0][0] = temp_blue[0];
            cube[0][3] = temp_blue[1];
            cube[0][6] = temp_blue[2];

            _swap_surfaces(4);

            break;
        }
        case SWAP_2_1_1:
        {
            /*
            U: [1][all]
            red -> green
            green -> orange
            orange -> blue
            blue -> red
        */
            char temp_green[3] = { cube[1][0], cube[1][1], cube[1][2] };
            /*SIDES*/
            // green -> red
            cube[1][0] = cube[5][0]; cube[1][1] = cube[5][1]; cube[1][2] = cube[5][2];
            // red -> blue
            cube[5][0] = cube[3][8]; cube[5][1] = cube[3][7]; cube[5][2] = cube[3][6];
            // blue -> orange
            cube[3][8] = cube[4][0]; cube[3][7] = cube[4][1]; cube[3][6] = cube[4][2];
            // orange -> green
            cube[4][0] = temp_green[0]; cube[4][1] = temp_green[1]; cube[4][2] = temp_green[2];

            _swap_surfaces(0);

            break;
        }
        case SWAP_2_1_2:
        {
            char temp_red[3] = { cube[5][0], cube[5][1], cube[5][2] };
            /*SIDES*/
            // red -> green
            cube[5][0] = cube[1][0]; cube[5][1] = cube[1][1]; cube[5][2] = cube[1][2];
            // green -> orange
            cube[1][0] = cube[4][0]; cube[1][1] = cube[4][1]; cube[1][2] = cube[4][2];
            // orange -> blue
            cube[4][0] = cube[3][8]; cube[4][1] = cube[3][7]; cube[4][2] = cube[3][6];

            // blue -> red
            cube[3][8] = temp_red[0]; cube[3][7] = temp_red[1]; cube[3][6] = temp_red[2];

            _swap_surfaces_c(0);

            break;
        }
        case SWAP_2_2_1:
        {
            char temp_green[3] = { cube[1][6], cube[1][7], cube[1][8] };
            /*SIDES*/
            // green -> red
            cube[1][6] = cube[5][6]; cube[1][7] = cube[5][7]; cube[1][8] = cube[5][8];
            // red -> blue
            cube[5][6] = cube[3][2]; cube[5][7] = cube[3][1]; cube[5][8] = cube[3][0];
            // blue -> orange
            cube[3][0] = cube[4][8]; cube[3][1] = cube[4][7]; cube[3][2] = cube[4][6];
            // orange -> green
            cube[4][6] = temp_green[0]; cube[4][7] = temp_green[1]; cube[4][8] = temp_green[2];
            _swap_surfaces_c(2);

            break;
        }
        case SWAP_2_2_2:
        {
            char temp_red[3] = { cube[5][6], cube[5][7], cube[5][8] };
            /*SIDES*/
            // red -> green
            cube[5][6] = cube[1][6]; cube[5][7] = cube[1][7]; cube[5][8] = cube[1][8];
            // green -> orange
            cube[1][6] = cube[4][6]; cube[1][7] = cube[4][7]; cube[1][8] = cube[4][8];
            // orange -> blue
            cube[4][6] = cube[3][2]; cube[4][7] = cube[3][1]; cube[4][8] = cube[3][0];

            // blue -> red
            cube[3][2] = temp_red[0]; cube[3][1] = temp_red[1]; cube[3][0] = temp_red[2];

            _swap_surfaces(2);

            break;
        }
        case SWAP_3_1_1:
        {
            char temp_white[3] = { cube[0][6], cube[0][7], cube[0][8] };

            cube[0][6] = cube[4][8];
            cube[0][7] = cube[4][5];
            cube[0][8] = cube[4][2];

            cube[4][2] = cube[2][0];
            cube[4][5] = cube[2][1];
            cube[4][8] = cube[2][2];

            cube[2][0] = cube[5][6];
            cube[2][1] = cube[5][3];
            cube[2][2] = cube[5][0];

            cube[5][0] = temp_white[0];
            cube[5][3] = temp_white[1];
            cube[5][6] = temp_white[2];

            _swap_surfaces(1);

            break;
        }
        case SWAP_3_1_2:
        {
            char temp_white[3] = { cube[0][6], cube[0][7], cube[0][8] };

            cube[0][6] = cube[5][0];
            cube[0][7] = cube[5][3];
            cube[0][8] = cube[5][6];

            cube[5][0] = cube[2][2];
            cube[5][3] = cube[2][1];
            cube[5][6] = cube[2][0];

            cube[2][0] = cube[4][2];
            cube[2][1] = cube[4][5];
            cube[2][2] = cube[4][8];

            cube[4][2] = temp_white[2];
            cube[4][5] = temp_white[1];
            cube[4][8] = temp_white[0];

            _swap_surfaces_c(1);

            break;
        }
        case SWAP_3_2_1:
        {
            char temp_white[3] = { cube[0][0], cube[0][1], cube[0][2] };

            cube[0][0] = cube[4][0];
            cube[0][1] = cube[4][3];
            cube[0][2] = cube[4][6];

            cube[4][0] = cube[2][6];
            cube[4][3] = cube[2][7];
            cube[4][6] = cube[2][8];

            cube[2][6] = cube[5][8];
            cube[2][7] = cube[5][7];
            cube[2][8] = cube[5][6];

            cube[5][2] = temp_white[0];
            cube[5][5] = temp_white[1];
            cube[5][8] = temp_white[2];

            _swap_surfaces_c(3);

            break;
        }
        case SWAP_3_2_2:
        {
            char temp_white[3] = { cube[0][0], cube[0][1], cube[0][2] };

            cube[0][0] = cube[5][2];
            cube[0][1] = cube[5][5];
            cube[0][2] = cube[5][8];

            cube[5][2] = cube[2][8];
            cube[5][5] = cube[2][7];
            cube[5][8] = cube[2][6];

            cube[2][6] = cube[4][0];
            cube[2][7] = cube[4][3];
            cube[2][8] = cube[4][6];

            cube[4][0] = temp_white[2];
            cube[4][3] = temp_white[1];
            cube[4][6] = temp_white[0];

            _swap_surfaces(3);

            break;
        }
        }

        char* a = &cube[0][0];
        char* b = &cube_1[0][0];

        if (checkCub(a, b))
        {
            GameOver = true;

            cout << endl << "You WIN" << endl;

        }
    }
};
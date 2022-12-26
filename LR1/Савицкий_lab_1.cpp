#include <iostream>
#include "Cube.h"
#include <vector>
#include <string>
#include <fstream>
std::vector<char>  loadCube();

void main()
{
    Cube cube;
    std::vector<char> bufferCube;
    std::cout << "load cube?(y/n)\n";
    char k;
    std::cin >> k;
    if(k == 'y')
    {
        std::ifstream fin;
        fin.open("cube.txt");
        fin >> cube;
        fin.close();
    }
    
    while (true)
    {
        system("cls");
        bufferCube = cube.getCube();
        std::cout << "1 - rotateClockwiseFrontEdge 2 - rotateClockwiseBackEdge 3 - rotateClockwiseLeftEdge 4 - rotateClockwiseRightEdge 5 - rotateClockwiseTopEdge 6 - rotateClockwiseBotEdge\n7 - rotateCounter-ClockwiseFrontEdge 8 - rotateCounter-ClockwiseBackEdge 9 - rotateCounterClockwiseLeftEdge \n10 - rotateCounter-ClockwiseRightEdge 11 - rotateCounter-ClockwiseTopEdge 12 - rotateCounter-ClockwiseBotEdge";
        std::cout << "\n             ==|Top Edge|=";
        for (int i = 0; i < 3; i++)
        {
            std::cout << "\n             |===|===|===|\n             |";
            for (int j = 0; j < 3; j++)
            {
                std::cout << " " << bufferCube.at(i * 3 + j + 36) << " |";
            }

        }
        std::cout << "\n             |===|===|===|\n";
        std::cout << "=|Left Edge|=|Front Edge|==|Right Edge|=|Back Edge|=";
        for (int i = 0; i < 3; i++)
        {
            std::cout << "\n|===|===|===||===|===|===||===|===|===||===|===|===|\n|";

            for (int j = 0; j < 3; j++)
            {
                std::cout << " " << bufferCube.at(i * 3 + j + 18) << " |";
            }
            std::cout << "|";
            for (int j = 0; j < 3; j++)
            {
                std::cout << " " << bufferCube.at(i * 3 + j) << " |";
            }
            std::cout << "|";
            for (int j = 0; j < 3; j++)
            {
                std::cout << " " << bufferCube.at(i * 3 + j + 27) << " |";
            }
            std::cout << "|";
            for (int j = 0; j < 3; j++)
            {
                std::cout << " " << bufferCube.at(i * 3 + j + 9) << " |";
            }
            std::cout << "|";
        }
        std::cout << "\n|===|===|===||===|===|===||===|===|===||===|===|===|\n             ==|Bot Edge|=";
        for (int i = 0; i < 3; i++)
        {
            std::cout << "\n             |===|===|===|\n             |";
            for (int j = 0; j < 3; j++)
            {
                std::cout << " " << bufferCube.at(i * 3 + j + 45) << " |";
            }
        }
        std::cout << "\n             |===|===|===|\n";
        int key;
        std::cin >> key;
        switch (key)
        {
        case 1:
            cube.rotateClockwiseFrontEdge();
            break;
        case 2:
            cube.rotateClockwiseBackEdge();
            break;
        case 3:
            cube.rotateClockwiseLeftEdge();
            break;
        case 4:
            cube.rotateClockwiseRightEdge();
            break;
        case 5:
            cube.rotateClockwiseTopEdge();
            break;
        case 6:
            cube.rotateClockwiseBotEdge();
            break;
        case 7:
            cube.rotateClockwiseFrontEdge();
            cube.rotateClockwiseFrontEdge();
            cube.rotateClockwiseFrontEdge();
            break;
        case 8:
            cube.rotateClockwiseBackEdge();
            cube.rotateClockwiseBackEdge();
            cube.rotateClockwiseBackEdge();
            break;
        case 9:
            cube.rotateClockwiseLeftEdge();
            cube.rotateClockwiseLeftEdge();
            cube.rotateClockwiseLeftEdge();
            break;
        case 10:
            cube.rotateClockwiseRightEdge();
            cube.rotateClockwiseRightEdge();
            cube.rotateClockwiseRightEdge();
            break;
        case 11:
            cube.rotateClockwiseTopEdge();
            cube.rotateClockwiseTopEdge();
            cube.rotateClockwiseTopEdge();
            break;
        case 12:
            cube.rotateClockwiseBotEdge();
            cube.rotateClockwiseBotEdge();
            cube.rotateClockwiseBotEdge();
            break;
        }
        if (cube.checkForWin()) 
        {
            system("cls");
            std::cout << "==========\n|You Win!|\n==========";
            break;
        }
        
    }
}

std::vector<char>  loadCube()
{
    std::vector<char> buffeCube;
    char buffer[54];
    std::ifstream fin;
    fin.open("cube.txt");
    fin.get(buffer, 54);
    fin.close();
    for (int i = 0; i < 54; i++)
    {
        buffeCube.push_back(buffer[i]);
    }
    return buffeCube;
}
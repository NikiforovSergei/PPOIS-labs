#include "Header.h"

#include "Source.cpp"

int main() {
    Cube cub;

    setlocale(LC_ALL, "Russian");

    cub.readFile();

    while (!cub.GameOver)
    {
        Sleep(150);

        cub.printCube();

        cub.input();

        cub.logic();
    }

    return 0;
}
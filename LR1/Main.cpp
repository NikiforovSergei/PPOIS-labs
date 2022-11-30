/**
* @file
* @brief Main project class.
* 
* Contains control logic, game cycle logic and text information output.
*/
#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/** 
* Main function.
* @return 0 if finished sucessfully, error code otherwise.
*/
int main()
{
    int a = 4;
    int& const b = a;

    cout << "GAME OF FIFTEEN\nControls: [Cell Value] [U/R/D/L]\nEvery instance is solvable\nGood luck!\n\n";
    Game instance; 
    int steps = 0;
    string input;
    string args[3];
    while (!instance.solved()) {
        instance.draw();
        cout << '\n';
        getline(cin, input);
        stringstream stream(input);

        int count = 0; while (stream >> args[count]) count++;

        try {
            if (count == 2) {
                instance.move(stoi(args[0]), Game::ctod(args[1][0]));
                steps++;
            }
            else cout << "Insufficient args!\n";
        } catch (...) { cout << "Wrong input!\n"; }
    }
    instance.draw();
    printf("\nSolved! Steps: %d\n", steps);
}
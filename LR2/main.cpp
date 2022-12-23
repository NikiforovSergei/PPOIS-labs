#include "Train.h"
#include "Railway.h"
#include <ctime>
#include "Randomazer.h"

using namespace std;

int main() {
    srand(time(NULL));

    Train *train = new Train();
    Railway *railway = new Railway(Randomazer::generateRandomStation(), *train);

    railway->startTrain();

    return 0;
}


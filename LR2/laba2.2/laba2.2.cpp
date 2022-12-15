#include <iostream>
#include <vector>
#include <conio.h>
#include <ctime>
#include <string>
using namespace std;

int width = 20, height = 20;
vector<vector<string>> world(width, vector<string>(height));

class predator;
class grass;
class herbivore;

class living {
public:
	vector<int> place(int y, int x, char poisk) {
		for (int j = y - 1; j <= y + 1; j++) {
			for (int i = x - 1; i <= x + 1; i++) {
				if (width > i && i > -1 && height > j && j > -1 && world[j][i][0] == poisk && world[j][i] != world[y][x]) {
					vector<int> pl;
					pl.push_back(i);
					pl.push_back(j);
					return pl;
				}
			}
		}
	}

	void Eat(int y, int x) {
		char extraction;
		if (world[y][x][0] == 'P') {
			extraction = 'H';
		}
		else {
			extraction = 'G';
		}
		const char* liv = &world[y][x][2];
		int age = atoi(liv);
		vector<int> pl = living::place(y, x, extraction);
		if (pl.size() > 0) {
			int X = pl[0];
			int Y = pl[1];
			world[Y][X] = " ";
			age++;
			string wor = to_string(age);
			world[y][x][2] = wor[0];
		}
	}

	void moving(int y, int x) {
		vector<int> pl = living::place(y, x, ' ');
		if (pl.size() > 0) {
			int X = pl[0];
			int Y = pl[1];
			world[Y][X] = world[y][x];
			world[y][x] = " ";
		}
	}
};

class predator : public living {
public:
	void reproduction(int y, int x) {
		vector<int> partner = living::place(y, x, 'P');
		if (partner.size() > 0) {
			vector<int> child = living::place(y, x, ' ');
			if (child.size() > 0) {
				int X = child[0];
				int Y = child[1];
				world[Y][X] = "P|5";
			}
			int X = partner[0];
			int Y = partner[1];
			int age = world[Y][X][2] - '0';
			age = age--;
			string wor = to_string(age);
			world[Y][X][2] = wor[0];
		}
	}
};

class herbivore : public living {
public:
	void reproduction(int y, int x) {
		vector<int> partner = living::place(y, x, 'H');
		if (partner.size() > 0) {
			vector<int> child = living::place(y, x, ' ');
			if (child.size() > 0) {
				int X = child[0];
				int Y = child[1];
				world[Y][X] = "H|6";
			}
			int X = partner[0];
			int Y = partner[1];
			int age = world[Y][X][2] - '0';
			age = age--;
			string wor = to_string(age);
			world[Y][X][2] = wor[0];
		}
	}
};

class grass : public living {
public:
	void reproduction(int y, int x) {
		vector<int> child = living::place(y, x, ' ');
		if (child.size() > 0) {
			int X = child[0];
			int Y = child[1];
			world[Y][X] = "G|4";
		}
		int age = world[y][x][2] - '0';
		age = age--;
		string wor = to_string(age);
		world[y][x][2] = wor[0];
	}
};

void playground() {
	srand(time(NULL));
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int r = rand() % 5;
			switch (r) {
			case 1: world[i][j] = " "; break;
			case 2: world[i][j] = "H|6"; break;
			case 3: world[i][j] = "G|4"; break;
			case 4: world[i][j] = "P|5"; break;
			}
		}
	}
}

void show() {
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		cout << '#';
		for (int j = 0; j < width; j++) {
			/*if (j == 0 || j == width - 1) {
				cout << "#";
			}*/
			/*else*/ if (world[i][j] == "" || world[i][j] == "a") {
				cout << " ";
			}
			else {
				cout << world[i][j][0];
			}
		}
		cout <<'#'<< endl;
	}

	for (int i = 0; i < width+2; i++) {
		cout << "#";
	}
}

void live() {
	int i = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (world[y][x] != " " && world[y][x] != "") {
				int age = world[y][x][2] - '0';
				age = age - 2;
				string wor = to_string(age);
				world[y][x][2] = wor[0];
				if (age == 0 || age < 0) {
					world[y][x] = " ";
				}
				else if (world[y][x][0] == 'P') {
					predator pred;
					pred.reproduction(y, x);
					pred.Eat(y, x);
					pred.moving(y, x);
				}
				else if (world[y][x][0] == 'H') {
					herbivore herb;
					herb.reproduction(y, x);
					herb.Eat(y, x);
					herb.moving(y, x);
				}
				else if (world[y][x][0] == 'G') {
					grass plant;
					plant.reproduction(y, x);
				}
			}
			else {}
		}
	}
}

bool Stop() {
	if (_kbhit) {
		switch (_getch()) {
		case 'x':
			return false;
		default: break;
		}
	}
	return true;
}

int main() {
	playground();
	show();
	while (Stop()) {
		live();
		show();
		Stop();
	}
	return 0;
}
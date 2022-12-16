#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
using namespace std;

int width = 30, height = 30;
vector<vector<string>> world(width, vector<string>(height));

class predator;
class grass;
class herbivore;

class life {
protected:
	vector<int> get_place(int y, int x, char search) {
		for (int j = y - 1; j <= y + 1; j++) {
			for (int i = x - 1; i <= x + 1; i++) {
				if (width > i && i > -1 && height > j && j > -1 && world[j][i][0] == search && world[j][i] != world[y][x]) {
					vector<int> pl;
					pl.push_back(i);
					pl.push_back(j);
					return pl;
				}
			}
		}
	}
public:
	void eat(int y, int x) {
		char extraction;
		if (world[y][x][0] == 'P') {
			extraction = 'H';
		}
		else {
			extraction = 'G';
		}
		const char* liv = &world[y][x][2];
		int age = atoi(liv);
		vector<int> pl = life::get_place(y, x, extraction);
		if (pl.size() > 0) {
			int X = pl[0];
			int Y = pl[1];
			world[Y][X] = " ";
			age++;
			string wor = to_string(age);
			world[y][x][2] = wor[0];
		}
	}

	void move(int y, int x) {
		vector<int> pl = life::get_place(y, x, ' ');
		if (pl.size() > 0) {
			int X = pl[0];
			int Y = pl[1];
			world[Y][X] = world[y][x];
			world[y][x] = " ";
		}
	}
};

class predator : public life {
public:
	void reproduction(int y, int x) {
		vector<int> partner = life::get_place(y, x, 'P');
		if (partner.size() > 0) {
			vector<int> child = life::get_place(y, x, ' ');
			if (child.size() > 0) {
				int X = child[0];
				int Y = child[1];
				world[Y][X] = "P|5";
			}
			int X = partner[0];
			int Y = partner[1];
			int age = world[Y][X][2] - '0';
			age--;
			string wor = to_string(age);
			world[Y][X][2] = wor[0];
		}
	}
};

class herbivore : public life {  
public:
	void reproduction(int y, int x) {
		vector<int> partner = life::get_place(y, x, 'H');
		if (partner.size() > 0) {
			vector<int> child = life::get_place(y, x, ' ');
			if (child.size() > 0) {
				int X = child[0];
				int Y = child[1];
				world[Y][X] = "H|6";
			}
			int X = partner[0];
			int Y = partner[1];
			int age = world[Y][X][2] - '0';
			age--;
			string wor = to_string(age);
			world[Y][X][2] = wor[0];
		}
	}
	void eat(int y, int x) {
		
		const char* liv = &world[y][x][2];
		int age = atoi(liv);
		vector<int> pl = life::get_place(y, x, 'G');
		if (pl.size() > 0) {
			int X = pl[0];
			int Y = pl[1];
			world[Y][X] = " ";
			age -= 2;
			string wor = to_string(age);
			world[y][x][2] = wor[0];
		}
	}
};

class grass : public life {
public:
	void reproduction(int y, int x) {
		vector<int> child = life::get_place(y, x, ' ');
		if (child.size() > 0) {
			int X = child[0];
			int Y = child[1];
			world[Y][X] = "G|4";
		}
		int age = world[y][x][2] - '0';
		age--;
		string wor = to_string(age);
		world[y][x][2] = wor[0];
	}
};

void create_world() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int r = rand() % 5;
			switch (r) {
			case 1: world[i][j] = " "; break;
			case 2: world[i][j] = "H|5"; break;
			case 3: world[i][j] = "G|9"; break;
			case 4: world[i][j] = "P|6"; break;
			}
		}
	}
}

void show_world() {
	system("cls");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		cout << "#";
		for (int j = 0; j < width; j++) {
		
			/*if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else*/ if (world[i][j] == "" || world[i][j] == "a") {
				cout << " ";
			}
			else {
				cout << world[i][j][0];
			}
		}
		cout <<"#"<< endl;
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
					pred.eat(y, x);
					pred.move(y, x);
				}
				else if (world[y][x][0] == 'H') {
					herbivore herb;
					herb.reproduction(y, x);
					herb.eat(y, x);
					herb.move(y, x);
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

bool wait() {
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
	create_world();
	show_world();
	while (wait()) {
		live();
		show_world();
		wait();
	}
	return 0;
}
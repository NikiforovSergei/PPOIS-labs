#include <iostream>
#include "rectangle.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	ifstream file("file.txt");
	setlocale(LC_ALL, "Russian");
	int x1, x2, y1, y2;
	int ch, key, a, i = 1, im;
	char symbol;
	file >> symbol;

	int num = symbol - '0';

	vector<Rect> rect(num);
	while (i < num) {

		file >> symbol;
		x1 = symbol - '0';

		file >> symbol;
		y1 = symbol - '0';

		file >> symbol;
		x2 = symbol - '0';

		file >> symbol;
		y2 = symbol - '0';

		rect[i].def(x1, x2, y1, y2);

		rect[i].Show();

		i++;
	}
	im = i;
	/*cout << "Введите координаты вершин противоположных углов первого прямоугольника, начиная с того, что ближе к [0, 0]" << endl;
	cin >> x11 >> y11 >> x12 >> y12;
	Rect rect[i](x11, x12, y11, y12);
	rect[1].Show();
	cout << "Введите координаты вершин противоположных углов второго прямоугольника, начиная с того, что ближе к [0, 0]" << endl;
	cin >> x21 >> y21 >> x22 >> y22;
	Rect rect[2](x21, x22, y21, y22);
	rect[2].Show();*/
	cout << "1 - Получение координат\n2 - Перемещение\n3 - Изменение размера\n4 - Увеличение размера на единицу по каждой из осей\n5 - Уменьше размера на единицу по каждой из осей\n6 - Построение наименьшего прямоугольника, содержащего два заданных прямоугольника(+)\n7 - Построение наименьшего прямоугльника, содержащего два заданных прямоугольника(+=)\n8 - Построение прямоугольника, являющегося пересечением двух прямоугольников(-)\n9 - Построение прямоугольника, являющегося пересечением двух прямоугольников(-=)" << endl;
	cin >> key;
	while (key!=0){
		switch (key)
		{
		case 1: {
			rect[1].Show();
			rect[2].Show();
			break;
		}

		case 2: {
			cout << "Перемещение по х или по у?" << endl;
			cin >> ch;
			cout << "На сколько?" << endl;
			cin >> a;
			rect[1].Move(ch, a);
			break;
		}

		case 3: {
			cout << "Изменить по х или по у" << endl;
			cin >> ch;
			cout << "На сколько?" << endl;
			cin >> a;
			rect[1].Change(ch, a);
			break;
		}

		case 4: {
			//rect[1].Show();
			//rect[2].Show();
			//rect[1]++;
			//rect[2]++;
			rect[1].Show();
			rect[2].Show();
			++rect[1];
			++rect[2];
			rect[1].Show();
			rect[2].Show();
			break;
		}

		case 5: {
			rect[1].Show();
			rect[2].Show();
			//rect[1]--;
			//rect[2]--;
			//rect[1].Show();
			//rect[2].Show();
			--rect[1];
			--rect[2];
			rect[1].Show();
			rect[2].Show();
			break;
		}

		case 6: {
			Rect newRect;
			newRect = rect[1] + rect[2];
			newRect.Show();
			break;
		}

		case 7: {
			rect[1] += rect[2];
			rect[1].Show();
			break;
		}

		case 8: {
			Rect newRect;
			newRect = rect[1] - rect[2];
			newRect.Show();
			break;
		}

		case 9: {
			rect[1] -= rect[2];
			rect[1].Show();
			break;
		}
		}
		  cout << "1 - Получение координат\n2 - Перемещение\n3 - Изменение размера\n4 - Увеличение размера на единицу по каждой из осей\n5 - Уменьше размера на единицу по каждой из осей\n6 - Построение наименьшего прямоугольника, содержащего два заданных прямоугольника(+)\n7 - Построение наименьшего прямоугльника, содержащего два заданных прямоугольника(+=)\n8 - Построение прямоугольника, являющегося пересечением двух прямоугольников(-)\n9 - Построение прямоугольника, являющегося пересечением двух прямоугольников(-=)" << endl;
		  cin >> key;
	}

}
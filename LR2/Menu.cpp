#include "Menu.h"

using std::cout;
using std::cin;
using std::string;

Menu::Menu(ModelMap &obj) : map(obj)
{};

void Menu::start()
{
	for (int i = 0; i < map.getTrains().size(); ++i)
	{
		cout << "Поезд #" << map.getTrains()[i]->getCurrentLocomotive().getLocomotiveNumber() << "\n";
		cout << "Локомотив:\n" << "Тяговая сила: " << map.getTrains()[i]->getCurrentLocomotive().getTractiveForce() << "\n";
		cout << "Время жизни: " << map.getTrains()[i]->getCurrentLocomotive().getLifeTime() << "\n";
		cout << "Состав:\n";
		cout << "Пассажиры:\n";
		for (int j = 0; j < map.getTrains()[i]->getCurrentChain().getTrainCarList(1).size(); ++j)
		{
			cout << "Занятость: " << map.getTrains()[i]->getCurrentChain().getTrainCarList(1)[j]->getCurrentOccupancy() << " Limit: "
				<< map.getTrains()[i]->getCurrentChain().getTrainCarList(1)[j]->getOccupancyLimit()<< "\n";
		}
		cout << "Товар:\n";
		for (int j = 0; j < map.getTrains()[i]->getCurrentChain().getTrainCarList(1).size(); ++j)
		{
			cout << "Занятость: " << map.getTrains()[i]->getCurrentChain().getTrainCarList(0)[j]->getCurrentOccupancy() << " Limit: "
				<< map.getTrains()[i]->getCurrentChain().getTrainCarList(0)[j]->getOccupancyLimit() << "\n";
		}
	}
}

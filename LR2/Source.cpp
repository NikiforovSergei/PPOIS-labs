#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Header.h"

// ########################################################### [OCEAN] ###########################################################
ImportOcean::ImportOcean()
{
	this->x = 0;
	this->y = 0;
	this->gameType = -1;
}

ImportOcean::ImportOcean(int x, int y, int type)
{
	this->gameType = type;
	this->x = x;
	this->y = y;

	this->gameField.resize(x);
	for (int i = 0; i < this->gameField.size(); i++)
	{
		this->gameField.at(i).resize(y);
	}
}

int ImportOcean::getX()
{
	return this->x;
}

int ImportOcean::getY()
{
	return this->y;
}

void ImportOcean::activate()
{
	srand(time(NULL));

	this->getFileName();
	this->createOcean();
	this->fullnessCheck();
	this->showOcean();

	if (this->gameType == 1)
	{
		int autoGame = 0; int needSteps = 0;

		cout << "Specify the number of moves the program should make -> ";
		cin >> needSteps;
		cout << endl;

		while (autoGame < needSteps)
		{
			autoGame++;

			cout << "[DEATH CHECK]\n";
			for (int i = 0; i < this->gameField.size(); i++)
			{
				for (int j = 0; j < this->gameField.at(i).size(); j++)
				{
					for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
					{
						if (this->gameField.at(i).at(j).at(k) != nullptr)
						{
							this->gameField.at(i).at(j).at(k)->doDeath(i, j, k, *this);
						}
					}
				}
			}

			this->showOcean();

			cout << "[MOVE CHECK]\n";
			for (int i = 0; i < this->gameField.size(); i++)
			{
				for (int j = 0; j < this->gameField.at(i).size(); j++)
				{
					for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
					{
						if (this->gameField.at(i).at(j).at(k) != nullptr)
						{
							if (!this->gameField.at(i).at(j).at(k)->getDoneMovement())
							{
								this->gameField.at(i).at(j).at(k)->doMovement(i, j, k, *this);
							}
						}
					}
				}
			}

			this->showOcean();

			cout << "[EATING CHECK]\n";
			for (int i = 0; i < this->gameField.size(); i++)
			{
				for (int j = 0; j < this->gameField.at(i).size(); j++)
				{
					for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
					{
						if (this->gameField.at(i).at(j).at(k) != nullptr)
						{
							this->gameField.at(i).at(j).at(k)->doEating(i, j, *this);
						}
					}
				}
			}

			this->showOcean();

			cout << "[BREEDING CHECK]\n";
			for (int i = 0; i < this->gameField.size(); i++)
			{
				for (int j = 0; j < this->gameField.at(i).size(); j++)
				{
					for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
					{
						if (this->gameField.at(i).at(j).at(k) != nullptr)
						{
							this->gameField.at(i).at(j).at(k)->doBreeding(i, j, *this);
						}
					}
				}
			}

			this->showOcean();

			for (int i = 0; i < this->gameField.size(); i++)
			{
				for (int j = 0; j < this->gameField.at(i).size(); j++)
				{
					for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
					{
						if (this->gameField.at(i).at(j).at(k) != nullptr)
						{
							if (this->gameField.at(i).at(j).at(k)->getDoneMovement())
							{
								this->gameField.at(i).at(j).at(k)->setDoneMovement(false);
							}
						}
					}
				}
			}
		}
	}
}

void ImportOcean::getFileName()
{
	cin >> this->path;
}

void ImportOcean::createOcean()
{
	ifstream fin(this->path);

	cout << "Trying to open a file" << endl;
	if (!fin.is_open())
	{
		cout << "Error when opening a file" << endl;
	}
	else
	{
		cout << "File opened" << endl << endl;
	}

	int lines = 0; int counter = 0; int words = 0;
	string buffer; string currentWord = "";

	while (!fin.eof())
	{
		while (getline(fin, buffer))
		{
			lines++;
		}
	}

	fin.clear();
	fin.seekg(0, fin.beg);

	int maxWords = (lines * 4) - 5;
	string* value = new string[maxWords];

	while (!fin.eof())
	{
		while (getline(fin, buffer))
		{
			for (int i = 0; i < buffer.size(); i++)
			{
				if (buffer[i] != ' ' && i != buffer.size() - 1)
				{
					currentWord += buffer[i];
					continue;
				}

				if (i == buffer.size() - 1)
				{
					currentWord += buffer[i];
				}

				value[words] += currentWord;
				words++;
				currentWord = "";
			}
		}
	}
	fin.close();

	if (counter == 0)
	{
		this->gameType = stoi(value[0]);
		counter++;
	}

	if (counter == 1)
	{
		this->x = stoi(value[1]);
		this->y = stoi(value[2]);
	}

	this->generateOcean();

	for (int i = 0; i < maxWords; i++)
	{
		if (counter == 1)
		{
			i = i + 2;
			counter++;
			continue;
		}

		if (value[i] == "fish")
		{
			this->gameField.at(stoi(value[i + 2]) - 1).at(stoi(value[i + 3]) - 1).push_back(new class Fish(value[i + 1], value[i]));
			i = i + 3;
			continue;
		}

		if (value[i] == "shark")
		{
			this->gameField.at(stoi(value[i + 2]) - 1).at(stoi(value[i + 3]) - 1).push_back(new class Shark(value[i + 1], value[i]));
			i = i + 3;
			continue;
		}

		if (value[i] == "plankton")
		{
			this->gameField.at(stoi(value[i + 2]) - 1).at(stoi(value[i + 3]) - 1).push_back(new class Plankton(value[i + 1], value[i]));
			i = i + 3;
			continue;
		}

		if (value[i] == "turtle")
		{
			this->gameField.at(stoi(value[i + 2]) - 1).at(stoi(value[i + 3]) - 1).push_back(new class Turtle(value[i + 1], value[i]));
			i = i + 3;
			continue;
		}

		if (value[i] == "dolphin")
		{
			this->gameField.at(stoi(value[i + 2]) - 1).at(stoi(value[i + 3]) - 1).push_back(new class Dolphin(value[i + 1], value[i]));
			i = i + 3;
			continue;
		}
		else
		{
			cout << "Such class doesnt exist";
		}
	}

	delete[] value;
}

void ImportOcean::generateOcean()
{
	ImportOcean Temp(this->x, this->y, this->gameType);
	*this = Temp;
}

void ImportOcean::showOcean()
{
	cout << "\t###########################################################################################################\n\n";

	for (int i = 0; i < this->getX(); i++)
	{
		int showOne = 0; int showTwo = 1; int showThree = 2; int showFour = 3;
		
		for (int j = 0; j < this->getY(); j++)
		{
			if (this->gameField.at(i).at(j).at(showOne) != nullptr)
			{
				cout << "\t" << this->gameField.at(i).at(j).at(showOne)->whoIsIt() << "\t";
			}
			else
			{
				cout << "\t___________\t";
			}
		}

		cout << endl;

		for (int j = 0; j < this->getY(); j++)
		{
			if (this->gameField.at(i).at(j).at(showTwo) != nullptr)
			{
				cout << "\t" << this->gameField.at(i).at(j).at(showTwo)->whoIsIt() << "\t";
			}
			else
			{
				cout << "\t___________\t";
			}
		}
		
		cout << endl;

		for (int j = 0; j < this->getY(); j++)
		{
			if (this->gameField.at(i).at(j).at(showThree) != nullptr)
			{
				cout << "\t" << this->gameField.at(i).at(j).at(showThree)->whoIsIt() << "\t";
			}
			else
			{
			cout << "\t___________\t";
			}
		}

		cout << endl;

		for (int j = 0; j < this->getY(); j++)
		{
			if (this->gameField.at(i).at(j).at(showFour) != nullptr)
			{
				cout << "\t" << this->gameField.at(i).at(j).at(showFour)->whoIsIt() << "\t";
			}
			else
			{
			cout << "\t___________\t";
			}
		}

		cout << endl << endl;
	}

	cout << "\t###########################################################################################################\n\n";
}

void ImportOcean::fullnessCheck()
{
	for (int i = 0; i < this->gameField.size(); i++)
	{
		for (int j = 0; j < this->gameField.at(i).size(); j++)
		{
			int counter = 0;

			for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
			{
				if (this->gameField.at(i).at(j).at(k) != nullptr)
				{
					counter++;
				}
			}

			if (counter <= 4)
			{
				int needToAdd = 4 - counter;

				for (int l = 0; l < needToAdd; l++)
				{
					this->gameField.at(i).at(j).push_back(nullptr);
				}
			}
		}
	}
}

bool ImportOcean::moveWaterfowl(int i, int j, Waterfowl* item, bool answer)
{
	item->setDoneMovement(answer);

	for (int k = 0; k < this->gameField.at(i).at(j).size(); k++)
	{
		if (this->gameField.at(i).at(j).at(k) == nullptr)
		{
			this->gameField.at(i).at(j).at(k) = item;
			return true;
		}
	}

	return false;
}

void ImportOcean::deleteWaterfowl(int i, int j, int k)
{
	this->gameField.at(i).at(j).at(k) = nullptr;
}

Waterfowl* ImportOcean::getLinkWaterfowl(int i, int j, int k)
{
	return this->gameField.at(i).at(j).at(k);
}

int ImportOcean::getSizeWaterfowl(int i, int j, int k)
{
	return this->gameField.at(i).at(j).at(k)->getSizeWaterfowl();
}

string ImportOcean::getTag(int i, int j, int k)
{
	return this->gameField.at(i).at(j).at(k)->getTag();
}

int ImportOcean::getGender(int i, int j, int k)
{
	return this->gameField.at(i).at(j).at(k)->getGender();
}

void ImportOcean::addWaterfowl(int i, int j, int k, Waterfowl* item)
{
	this->gameField.at(i).at(j).at(k) = item;
}
// ########################################################### [WATERFOWL] ###########################################################
string Waterfowl::whoIsIt()
{
	return this->name;
}

int Waterfowl::getSizeWaterfowl()
{
	return this->size;
}

string Waterfowl::getTag()
{
	return this->tag;
}

int Waterfowl::getGender()
{
	return this->gender;
}

bool Waterfowl::getDoneMovement()
{
	return this->doneMovement;
}

void Waterfowl::setDoneMovement(bool answer)
{
	this->doneMovement = answer;
}

void Waterfowl::doDeath(int i, int j, int k, ImportOcean& field)
{
	if (this->lifeCounter == 0)
	{
		field.deleteWaterfowl(i, j, k);
	}
}

void Waterfowl::doMovement(int x, int y, int z, ImportOcean& field)
{
	int moveDirection = rand() % 4; // down - 0; up - 1; left - 2; right - 3;

	if (moveDirection == 0)
	{
		if (field.getX() - 1 >= x + this->movementSpeed)
		{
			this->lifeCounter--;
			field.moveWaterfowl(x + this->movementSpeed, y, this, true);
			field.deleteWaterfowl(x, y, z);
		}
		else
		{
			this->lifeCounter--;
		}
	}

	if (moveDirection == 1)
	{
		if (0 <= x - this->movementSpeed)
		{
			this->lifeCounter--;
			if (field.moveWaterfowl(x - this->movementSpeed, y, this, true))
			{
				field.deleteWaterfowl(x, y, z);
			}
		}
		else
		{
			this->lifeCounter--;
		}
	}

	if (moveDirection == 2)
	{
		if (0 <= y - this->movementSpeed)
		{
			this->lifeCounter--;
			if (field.moveWaterfowl(x, y - this->movementSpeed, this, true))
			{
				field.deleteWaterfowl(x, y, z);
			}
		}
		else
		{
			this->lifeCounter--;
		}
	}

	if (moveDirection == 3)
	{
		if (field.getY() - 1 >= y + this->movementSpeed)
		{
			this->lifeCounter--;
			if (field.moveWaterfowl(x, y + this->movementSpeed, this, true))
			{
				field.deleteWaterfowl(x, y, z);
			}
		}
		else
		{
			this->lifeCounter--;
		}
	}
}

void Waterfowl::doEating(int i, int j, ImportOcean& field)
{
	if (this->hunger == 1)
	{
		for (int k = 0; i < 4; i++)
		{
			if (field.getLinkWaterfowl(i, j, k) != nullptr)
			{
				if (this != field.getLinkWaterfowl(i, j, k))
				{
					if (this->size > field.getSizeWaterfowl(i, j, k))
					{
						this->lifeCounter += field.getSizeWaterfowl(i, j, k);
						field.deleteWaterfowl(i, j, k);
						this->hunger = rand() % 2;
						break;
					}
				}
			}
		}
	}
}

void Shark::doEating(int i, int j, ImportOcean& field)
{
	if (this->hunger == 1)
	{
		for (int k = 0; i < 4; i++)
		{
			if (field.getLinkWaterfowl(i, j, k) != nullptr)
			{
				if (this != field.getLinkWaterfowl(i, j, k))
				{
					if (this->size > field.getSizeWaterfowl(i, j, k))
					{
						if (field.getTag(i, j, k) != "plankton" && field.getTag(i, j, k) != "dolphin")
						{
							this->lifeCounter += field.getSizeWaterfowl(i, j, k);
							field.deleteWaterfowl(i, j, k);
							this->hunger = rand() % 2;
							break;
						}
					}
				}
			}
		}
	}
}

void Waterfowl::doBreeding(int i, int j, ImportOcean& field)
{
	if (this->breed == 1)
	{
		for (int k = 0; i < 4; i++)
		{
			if (field.getLinkWaterfowl(i, j, k) == nullptr)
			{
				Waterfowl* Temp = new class Waterfowl;
				field.addWaterfowl(i, j, k, Temp);
				this->breed = rand() % 2;
				break;
			}
		}
	}
}

void Plankton::doBreeding(int i, int j, ImportOcean& field)
{
	if (this->breed == 1)
	{
		for (int k = 0; i < 4; i++)
		{
			if (field.getLinkWaterfowl(i, j, k) == nullptr)
			{
				Waterfowl* Temp = new class Plankton("Plankton___", "plankton");
				field.addWaterfowl(i, j, k, Temp);
				this->breed = rand() % 2;
				break;
			}
		}
	}
}

void Shark::doBreeding(int i, int j, ImportOcean& field)
{
	int counter = 0;
	if (this->breed == 1)
	{
		for (int k = 0; k < 4; k++)
		{
			if (counter == 1)
			{
				break;
			}

			if (field.getLinkWaterfowl(i, j, k) != nullptr)
			{
				if (this != field.getLinkWaterfowl(i, j, k))
				{
					if (this->tag == field.getTag(i, j, k))
					{
						if (this->gender > field.getGender(i, j, k) || this->gender < field.getGender(i, j, k))
						{
							for (int l = 0; l < 4; l++)
							{
								if (field.getLinkWaterfowl(i, j, l) == nullptr)
								{
									Waterfowl* Temp = new class Shark("Shark______", "shark");
									field.addWaterfowl(i, j, l, Temp);
									this->breed = rand() % 2;
									counter++;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Fish::doBreeding(int i, int j, ImportOcean& field)
{
	int counter = 0;
	if (this->breed == 1)
	{
		for (int k = 0; k < 4; k++)
		{
			if (counter == 1)
			{
				break;
			}

			if (field.getLinkWaterfowl(i, j, k) != nullptr)
			{
				if (this != field.getLinkWaterfowl(i, j, k))
				{
					if (this->tag == field.getTag(i, j, k))
					{
						if (this->gender > field.getGender(i, j, k) || this->gender < field.getGender(i, j, k))
						{
							for (int l = 0; l < 4; l++)
							{
								if (field.getLinkWaterfowl(i, j, l) == nullptr)
								{
									Waterfowl* Temp = new class Fish("Fish_______", "fish");
									field.addWaterfowl(i, j, l, Temp);
									this->breed = rand() % 2;
									counter++;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Dolphin::doBreeding(int i, int j, ImportOcean& field)
{
	int counter = 0;
	if (this->breed == 1)
	{
		for (int k = 0; k < 4; k++)
		{
			if (counter == 1)
			{
				break;
			}

			if (field.getLinkWaterfowl(i, j, k) != nullptr)
			{
				if (this != field.getLinkWaterfowl(i, j, k))
				{
					if (this->tag == field.getTag(i, j, k))
					{
						if (this->gender > field.getGender(i, j, k) || this->gender < field.getGender(i, j, k))
						{
							for (int l = 0; l < 4; l++)
							{
								if (field.getLinkWaterfowl(i, j, l) == nullptr)
								{
									Waterfowl* Temp = new class Dolphin("Dolphin____", "dolphin");
									field.addWaterfowl(i, j, l, Temp);
									this->breed = rand() % 2;
									counter++;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Turtle::doBreeding(int i, int j, ImportOcean& field)
{
	int counter = 0;
	if (this->breed == 1)
	{
		for (int k = 0; k < 4; k++)
		{
			if (counter == 1)
			{
				break;
			}

			if (field.getLinkWaterfowl(i, j, k) != nullptr)
			{
				if (this != field.getLinkWaterfowl(i, j, k))
				{
					if (this->tag == field.getTag(i, j, k))
					{
						if (this->gender > field.getGender(i, j, k) || this->gender < field.getGender(i, j, k))
						{
							for (int l = 0; l < 4; l++)
							{
								if (field.getLinkWaterfowl(i, j, l) == nullptr)
								{
									Waterfowl* Temp = new class Turtle("Turtle_____", "turtle");
									field.addWaterfowl(i, j, l, Temp);
									this->breed = rand() % 2;
									counter++;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

Waterfowl::Waterfowl()
{
	this->size = 0;
	this->movementSpeed = 0;
	this->hunger = rand() % 2;
	this->breed = rand() % 2;
	this->gender = rand() % 2;
	this->lifeCounter = 0;
	this->doneMovement = false;
}

Plankton::Plankton(string name, string tag)
{
	this->name = name;
	this->tag = tag;
	this->size = 1;
	this->movementSpeed = 1;
	this->hunger = -1;
	this->gender = -1;
	this->lifeCounter = 3;
}

Shark::Shark(string name, string tag)
{
	this->name = name;
	this->tag = tag;
	this->size = 5;
	this->movementSpeed = 2;
	this->lifeCounter = 25;
}

Fish::Fish(string name, string tag)
{
	this->name = name;
	this->tag = tag;
	this->movementSpeed = 1;
	this->size = 2;
	this->lifeCounter = 7;
}

Dolphin::Dolphin(string name, string tag)
{
	this->name = name;
	this->tag = tag;
	this->size = 4;
	this->movementSpeed = 3;
	this->lifeCounter = 12;
}

Turtle::Turtle(string name, string tag)
{
	this->name = name;
	this->tag = tag;
	this->size = 3;
	this->movementSpeed = 1;
	this->lifeCounter = 20;
}
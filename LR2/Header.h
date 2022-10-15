#pragma once
#include <vector>

using namespace std;

class ImportOcean
{
private:
	int x, y; // размеры поля
	int gameType; // тип игры
	string path; // название файла для считывания
	vector <vector<vector<class Waterfowl*>>> gameField; // само поле игры

	void getFileName(); // получение названия файла, как аргумента
	void createOcean(); // считывание данных с файла, создание объектов на поле
	void generateOcean(); // генерация поля размера [X]x[Y]

public:
	ImportOcean();
	ImportOcean(int, int, int);
	int getX();
	int getY();
	int getSizeWaterfowl(int, int, int);
	void activate();
	void showOcean();
	void fullnessCheck();
	void deleteWaterfowl(int, int, int);
	bool moveWaterfowl(int, int, Waterfowl*, bool);
	Waterfowl* getLinkWaterfowl(int, int, int);
	string getTag(int, int, int);
	int getGender(int, int, int);
	void addWaterfowl(int, int, int, Waterfowl*);
};

class Waterfowl
{
protected:
	string name; // имя
	string tag; // тег
	int size; // размер, самого большого не могут съесть более меньшие
	int movementSpeed; // скорость, сколько клеток он пройдет
	int hunger; // статус голода (0 - не голоден; 1 - голоден; -1 - НЕ нужно питаться) 
	int breed; // желание спаривания (0 - нету; 1 - есть)
	int gender; // гендер (0 - Ж; 1 - М; -1 - НЕ важно какой)
	int lifeCounter; // жизнь существа
	bool doneMovement; // проверка на то что объект сдвинулся за 1 ход

public:
	Waterfowl();
	int getGender();
	int getSizeWaterfowl();
	string getTag();
	void setDoneMovement(bool);
	bool getDoneMovement();
	virtual string whoIsIt();
	virtual void doMovement(int, int, int, ImportOcean&);
	virtual void doEating(int, int, ImportOcean&);
	virtual void doBreeding(int, int, ImportOcean&);
	virtual void doDeath(int, int, int, ImportOcean&);
};

class Plankton : public Waterfowl
{
public:
	Plankton(string, string);
	void doBreeding(int, int, ImportOcean&) override;
};

class Shark : public Waterfowl
{
public:
	Shark(string, string);
	void doEating(int, int, ImportOcean&) override;
	void doBreeding(int, int, ImportOcean&) override;
};

class Fish : public Waterfowl
{
public:
	Fish(string, string);
	void doBreeding(int, int, ImportOcean&) override;
};

class Dolphin : public Waterfowl
{
public:
	Dolphin(string, string);
	void doBreeding(int, int, ImportOcean&) override;
};

class Turtle : public Waterfowl
{
public:
	Turtle(string, string);
	void doBreeding(int, int, ImportOcean&) override;
};
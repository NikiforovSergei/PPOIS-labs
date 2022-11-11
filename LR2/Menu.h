#pragma once
#include<iostream>
#include "ModelMap.h"


class Menu
{
private:
	ModelMap map;
	std::string	MSG_MAIN_MENU = "\t\t\t Main menu:\n1.Create model\n";
	std::string MSG_INPUT_PATH = "Input path: ";
	std::string MSG_SHOW_INFO = "Info:\n";
public:
	Menu(ModelMap& obj);
	void start();
};


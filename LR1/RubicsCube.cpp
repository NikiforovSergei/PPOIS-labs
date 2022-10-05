#include "RubicsCube.h"
/// <summary>
/// Creating an assembled Rubik's Cube
/// </summary>
void RubicsCube::CreateCube()
{
	std::vector<char> bufferLineOrRow;
	std::vector<std::vector<char>> bufferFace;
	std::vector<char> Colors = { 'o', 'w', 'b', 'y', 'g', 'r' };
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				bufferLineOrRow.push_back(Colors[i]);
			}
			bufferFace.push_back(bufferLineOrRow);
			bufferLineOrRow.clear();
		}
		LinesOfCube.push_back(bufferFace);
		RowsOfCube.push_back(bufferFace);
		bufferFace.clear();
	}
}
/// <summary>
/// Output of the Rubik's Cube state
/// </summary>
void RubicsCube::ShowCube()
{
	std::cout << "\n"
		<< std::setfill(' ') << std::setw(11) << LinesOfCube[1][0][0] << "  " << LinesOfCube[1][0][1] << "  " << LinesOfCube[1][0][2] << "\n"
		<< std::setfill(' ') << std::setw(11) << LinesOfCube[1][1][0] << "  " << LinesOfCube[1][1][1] << "  " << LinesOfCube[1][1][2] << "\n"
		<< std::setfill(' ') << std::setw(11) << LinesOfCube[1][2][0] << "  " << LinesOfCube[1][2][1] << "  " << LinesOfCube[1][2][2] << "\n"
		<< " " << LinesOfCube[2][0][0] << "  " << LinesOfCube[2][0][1] << "  " << LinesOfCube[2][0][2] << "  " << LinesOfCube[0][0][0] << "  " 
		<< LinesOfCube[0][0][1] << "  " << LinesOfCube[0][0][2] << "  " << LinesOfCube[4][0][0] << "  " << LinesOfCube[4][0][1] << "  " << 
		LinesOfCube[4][0][2] << "  " << LinesOfCube[5][0][0] << "  " << LinesOfCube[5][0][1] << "  " << LinesOfCube[5][0][2] << "\n"
		<< " " << LinesOfCube[2][1][0] << "  " << LinesOfCube[2][1][1] << "  " << LinesOfCube[2][1][2] << "  " << LinesOfCube[0][1][0]
		<< "  " << LinesOfCube[0][1][1] << "  " << LinesOfCube[0][1][2] << "  " << LinesOfCube[4][1][0] << "  " << LinesOfCube[4][1][1]
		<< "  " << LinesOfCube[4][1][2] << "  " << LinesOfCube[5][1][0] << "  " << LinesOfCube[5][1][1] << "  " << LinesOfCube[5][1][2] << "\n"
		<< " " << LinesOfCube[2][2][0] << "  " << LinesOfCube[2][2][1] << "  " << LinesOfCube[2][2][2] << "  " << LinesOfCube[0][2][0]
		<< "  " << LinesOfCube[0][2][1] << "  " << LinesOfCube[0][2][2] << "  " << LinesOfCube[4][2][0] << "  " << LinesOfCube[4][2][1]
		<< "  " << LinesOfCube[4][2][2] << "  " << LinesOfCube[5][2][0] << "  " << LinesOfCube[5][2][1] << "  " << LinesOfCube[5][2][2] << "\n"
		<< std::setfill(' ') << std::setw(11) << LinesOfCube[3][0][0] << "  " << LinesOfCube[3][0][1] << "  " << LinesOfCube[3][0][2] << "\n"
		<< std::setfill(' ') << std::setw(11) << LinesOfCube[3][1][0] << "  " << LinesOfCube[3][1][1] << "  " << LinesOfCube[3][1][2] << "\n"
		<< std::setfill(' ') << std::setw(11) << LinesOfCube[3][2][0] << "  " << LinesOfCube[3][2][1] << "  " << LinesOfCube[3][2][2] << "\n";
}
/// <summary>
/// Rotation of the plane of the Rubik's cube
/// </summary>
/// <param name="NumberOfFace"></param>
void RubicsCube::FaceTurn(int NumberOfFace)
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	NumberOfFace -= 1;

	RowsOfCube[NumberOfFace][2] = preCube.LinesOfCube[NumberOfFace][0];
	LinesOfCube[NumberOfFace][0][2] = preCube.LinesOfCube[NumberOfFace][0][0];
	LinesOfCube[NumberOfFace][1][2] = preCube.LinesOfCube[NumberOfFace][0][1];
	LinesOfCube[NumberOfFace][2][2] = preCube.LinesOfCube[NumberOfFace][0][2];

	RowsOfCube[NumberOfFace][0] = preCube.LinesOfCube[NumberOfFace][2];
	LinesOfCube[NumberOfFace][0][0] = preCube.LinesOfCube[NumberOfFace][2][0];
	LinesOfCube[NumberOfFace][1][0] = preCube.LinesOfCube[NumberOfFace][2][1];
	LinesOfCube[NumberOfFace][2][0] = preCube.LinesOfCube[NumberOfFace][2][2];

	LinesOfCube[NumberOfFace][0][1] = preCube.RowsOfCube[NumberOfFace][0][1];
	RowsOfCube[NumberOfFace][1][0] = preCube.RowsOfCube[NumberOfFace][0][1];

	LinesOfCube[NumberOfFace][2][1] = preCube.RowsOfCube[NumberOfFace][2][1];
	RowsOfCube[NumberOfFace][1][2] = preCube.RowsOfCube[NumberOfFace][2][1];
}
/// <summary>
/// Turning the front face of the Rubik's Cube
/// </summary>
void RubicsCube::FTurn()
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	FaceTurn(1);

	RowsOfCube[2][2] = preCube.LinesOfCube[3][0];
	LinesOfCube[2][0][2] = preCube.LinesOfCube[3][0][0];
	LinesOfCube[2][1][2] = preCube.LinesOfCube[3][0][1];
	LinesOfCube[2][2][2] = preCube.LinesOfCube[3][0][2];

	RowsOfCube[4][0] = preCube.LinesOfCube[1][2];
	LinesOfCube[4][0][0] = preCube.LinesOfCube[1][2][0];
	LinesOfCube[4][1][0] = preCube.LinesOfCube[1][2][1];
	LinesOfCube[4][2][0] = preCube.LinesOfCube[1][2][2];

	std::vector<char> buffer = preCube.RowsOfCube[2][2];
	std::reverse(buffer.begin(), buffer.end());
	LinesOfCube[1][2] = buffer;
	RowsOfCube[1][0][2] = buffer[0];
	RowsOfCube[1][1][2] = buffer[1];
	RowsOfCube[1][2][2] = buffer[2];
	buffer.clear();

	buffer = preCube.RowsOfCube[4][0];
	std::reverse(buffer.begin(), buffer.end());
	LinesOfCube[3][0] = buffer;
	RowsOfCube[3][0][0] = buffer[0];
	RowsOfCube[3][1][0] = buffer[1];
	RowsOfCube[3][2][0] = buffer[2];
	buffer.clear();
}
/// <summary>
/// Turning the back face of the Rubik's Cube
/// </summary>
void RubicsCube::BTurn()
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	FaceTurn(6);

	RowsOfCube[2][0] = preCube.LinesOfCube[1][0];
	LinesOfCube[2][0][0] = preCube.LinesOfCube[1][0][0];
	LinesOfCube[2][1][0] = preCube.LinesOfCube[1][0][1];
	LinesOfCube[2][2][0] = preCube.LinesOfCube[1][0][2];

	RowsOfCube[4][2] = preCube.LinesOfCube[3][2];
	LinesOfCube[4][0][2] = preCube.LinesOfCube[3][2][0];
	LinesOfCube[4][1][2] = preCube.LinesOfCube[3][2][1];
	LinesOfCube[4][2][2] = preCube.LinesOfCube[3][2][2];

	LinesOfCube[1][0] = preCube.RowsOfCube[4][2];
	RowsOfCube[1][0][0] = preCube.RowsOfCube[4][2][0];
	RowsOfCube[1][1][0] = preCube.RowsOfCube[4][2][1];
	RowsOfCube[1][2][0] = preCube.RowsOfCube[4][2][2];

	LinesOfCube[3][2] = preCube.RowsOfCube[2][0];
	RowsOfCube[3][0][2] = preCube.RowsOfCube[2][0][0];
	RowsOfCube[3][1][2] = preCube.RowsOfCube[2][0][1];
	RowsOfCube[3][2][2] = preCube.RowsOfCube[2][0][2];
}
/// <summary>
/// Turning the left face of the Rubik's Cube
/// </summary>
void RubicsCube::LTurn()
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	FaceTurn(3);

	RowsOfCube[0][0] = preCube.RowsOfCube[1][0];
	LinesOfCube[0][0][0] = preCube.RowsOfCube[1][0][0];
	LinesOfCube[0][1][0] = preCube.RowsOfCube[1][0][1];
	LinesOfCube[0][2][0] = preCube.RowsOfCube[1][0][2];

	RowsOfCube[3][0] = preCube.RowsOfCube[0][0];
	LinesOfCube[3][0][0] = preCube.RowsOfCube[0][0][0];
	LinesOfCube[3][1][0] = preCube.RowsOfCube[0][0][1];
	LinesOfCube[3][2][0] = preCube.RowsOfCube[0][0][2];

	std::vector<char> buffer = preCube.RowsOfCube[3][0];
	std::reverse(buffer.begin(), buffer.end());
	RowsOfCube[5][2] = buffer;
	LinesOfCube[5][0][2] = buffer[0];
	LinesOfCube[5][1][2] = buffer[1];
	LinesOfCube[5][2][2] = buffer[2];
	buffer.clear();

	buffer = preCube.RowsOfCube[5][2];
	std::reverse(buffer.begin(), buffer.end());
	RowsOfCube[1][0] = buffer;
	LinesOfCube[1][0][0] = buffer[0];
	LinesOfCube[1][1][0] = buffer[1];
	LinesOfCube[1][2][0] = buffer[2];
	buffer.clear();
}

/// <summary>
/// Turning the right face of the Rubik's Cube
/// </summary>
void RubicsCube::RTurn()
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	FaceTurn(5);

	RowsOfCube[0][2] = preCube.RowsOfCube[3][2];
	LinesOfCube[0][0][2] = preCube.RowsOfCube[3][2][0];
	LinesOfCube[0][1][2] = preCube.RowsOfCube[3][2][1];
	LinesOfCube[0][2][2] = preCube.RowsOfCube[3][2][2];

	RowsOfCube[1][2] = preCube.RowsOfCube[0][2];
	LinesOfCube[1][0][2] = preCube.RowsOfCube[0][2][0];
	LinesOfCube[1][1][2] = preCube.RowsOfCube[0][2][1];
	LinesOfCube[1][2][2] = preCube.RowsOfCube[0][2][2];

	std::vector<char> buffer = preCube.RowsOfCube[1][2];
	std::reverse(buffer.begin(), buffer.end());
	RowsOfCube[5][0] = buffer;
	LinesOfCube[5][0][0] = buffer[0];
	LinesOfCube[5][1][0] = buffer[1];
	LinesOfCube[5][2][0] = buffer[2];
	buffer.clear();

	buffer = preCube.RowsOfCube[5][0];
	std::reverse(buffer.begin(), buffer.end());
	RowsOfCube[3][2] = buffer;
	LinesOfCube[3][0][2] = buffer[0];
	LinesOfCube[3][1][2] = buffer[1];
	LinesOfCube[3][2][2] = buffer[2];
	buffer.clear();
}
/// <summary>
/// Rotation of the upper face of the Rubik's Cube
/// </summary>
void RubicsCube::UTurn()
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	FaceTurn(2);

	LinesOfCube[4][0] = preCube.LinesOfCube[5][0];
	RowsOfCube[4][0][0] = preCube.LinesOfCube[5][0][0];
	RowsOfCube[4][1][0] = preCube.LinesOfCube[5][0][1];
	RowsOfCube[4][2][0] = preCube.LinesOfCube[5][0][2];

	LinesOfCube[0][0] = preCube.LinesOfCube[4][0];
	RowsOfCube[0][0][0] = preCube.LinesOfCube[4][0][0];
	RowsOfCube[0][1][0] = preCube.LinesOfCube[4][0][1];
	RowsOfCube[0][2][0] = preCube.LinesOfCube[4][0][2];

	LinesOfCube[2][0] = preCube.LinesOfCube[0][0];
	RowsOfCube[2][0][0] = preCube.LinesOfCube[0][0][0];
	RowsOfCube[2][1][0] = preCube.LinesOfCube[0][0][1];
	RowsOfCube[2][2][0] = preCube.LinesOfCube[0][0][2];

	LinesOfCube[5][0] = preCube.LinesOfCube[2][0];
	RowsOfCube[5][0][0] = preCube.LinesOfCube[2][0][0];
	RowsOfCube[5][1][0] = preCube.LinesOfCube[2][0][1];
	RowsOfCube[5][2][0] = preCube.LinesOfCube[2][0][2];
}
/// <summary>
/// Turning the bottom face of the Rubik's Cube
/// </summary>
void RubicsCube::DTurn()
{
	RubicsCube preCube;
	preCube.LinesOfCube = LinesOfCube;
	preCube.RowsOfCube = RowsOfCube;
	FaceTurn(4);

	LinesOfCube[4][2] = preCube.LinesOfCube[0][2];
	RowsOfCube[4][0][2] = preCube.LinesOfCube[0][2][0];
	RowsOfCube[4][1][2] = preCube.LinesOfCube[0][2][1];
	RowsOfCube[4][2][2] = preCube.LinesOfCube[0][2][2];

	LinesOfCube[5][2] = preCube.LinesOfCube[4][2];
	RowsOfCube[5][0][2] = preCube.LinesOfCube[4][2][0];
	RowsOfCube[5][1][2] = preCube.LinesOfCube[4][2][1];
	RowsOfCube[5][2][2] = preCube.LinesOfCube[4][2][2];

	LinesOfCube[2][2] = preCube.LinesOfCube[5][2];
	RowsOfCube[2][0][2] = preCube.LinesOfCube[5][2][0];
	RowsOfCube[2][1][2] = preCube.LinesOfCube[5][2][1];
	RowsOfCube[2][2][2] = preCube.LinesOfCube[5][2][2];

	LinesOfCube[0][2] = preCube.LinesOfCube[2][2];
	RowsOfCube[0][0][2] = preCube.LinesOfCube[2][2][0];
	RowsOfCube[0][1][2] = preCube.LinesOfCube[2][2][1];
	RowsOfCube[0][2][2] = preCube.LinesOfCube[2][2][2];
}
/// <summary>
/// Checking whether the Rubik's Cube is assembled
/// </summary>
bool RubicsCube::CheckCube()
{
	RubicsCube SolvedCube;
	SolvedCube.CreateCube();
	for (int i = 0; i < 6; i++)
		if (LinesOfCube[i] != SolvedCube.LinesOfCube[i])
			return false;
	return true;
}
/// <summary>
/// Obfuscation of the Rubik's Cube
/// </summary>
void RubicsCube::RandomCube()
{
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int random = rand() % 6 + 1;
		if (random == 1)
			LTurn();
		else if (random == 2)
			RTurn();
		else if (random == 3)
			UTurn();
		else if (random == 4)
			DTurn();
		else if (random == 5)
			FTurn();
		else if (random == 6)
			BTurn();
	}
}
/// <summary>
/// Loading a Rubik's Cube from a file
/// </summary>
void RubicsCube::CubeFromFile()
{
	std::ifstream file("Текст.txt");
	std::vector<std::pair<std::vector<char>, int>> bufferLines;
	std::vector<char> buffer;
	std::vector<int> Faces = { 1, 2, 3, 4, 5, 6 };
	int l = 0, counter = 0;
	while (!file.eof())
	{
		char ch = file.get();
		if (ch == 'r' || ch == 'w' || ch == 'o' || ch == 'b' || ch == 'g' || ch == 'y')
			buffer.push_back(ch);
		if (buffer.size() == 3)
		{
			bufferLines.push_back(std::make_pair(buffer, Faces[l]));
			counter++;
			buffer.clear();
		}
		if (counter == 3)
		{
			counter = 0;
			l++;
		}
	}
	LinesOfCube.resize(6);
	RowsOfCube.resize(6);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (bufferLines[j].second == i + 1)
			{
				LinesOfCube[i].push_back(bufferLines[j].first);
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		RowsOfCube[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			RowsOfCube[i][j].resize(3);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			RowsOfCube[i][0][j] = LinesOfCube[i][j][0];
			RowsOfCube[i][1][j] = LinesOfCube[i][j][1];
			RowsOfCube[i][2][j] = LinesOfCube[i][j][2];
		}
	}
}
/// <summary>
/// Assigning keys to rotate the faces of the Rubik's Cube
/// </summary>
void RubicsCube::Keys()
{
	int key = 0;                            //переменная для хранения ввода  с клавиатуры

	if (_kbhit())                 //проверяет нажата ли клавиша
	{
		key = _getch();              //просит нажать клавишу

		switch (key)                 //дальше идет проверка, код 49-55 это 1-6 клавиши на клавиатуре
		{
		case 49:                        // то вызываем
			LTurn();
			system("cls");
			ShowCube();
			break;
		case 50:                        // то вызываем
			RTurn();
			system("cls");
			ShowCube();
			break;
		case 51:                        // то вызываем
			UTurn();
			system("cls");
			ShowCube();
			break;
		case 52:                        // то вызываем
			DTurn();
			system("cls");
			ShowCube();
			break;
		case 53:
			FTurn();
			system("cls");
			ShowCube();
			break;
		case 54:
			BTurn();
			system("cls");
			ShowCube();
			break;
		case 113:
			for (int i = 0; i < 3; i++)
				LTurn();
			system("cls");
			ShowCube();
			break;
		case 119:
			for (int i = 0; i < 3; i++)
				RTurn();
			system("cls");
			ShowCube();
			break;
		case 101:
			for (int i = 0; i < 3; i++)
				UTurn();
			system("cls");
			ShowCube();
			break;
		case 114:
			for (int i = 0; i < 3; i++)
				DTurn();
			system("cls");
			ShowCube();
			break;
		case 116:
			for (int i = 0; i < 3; i++)
				FTurn();
			system("cls");
			ShowCube();
			break;
		case 121:
			for (int i = 0; i < 3; i++)
				BTurn();
			system("cls");
			ShowCube();
			break;
		case 27:
			std::exit(1);
			break;
		}
	}
}
/// <summary>
/// Menu for working with a Rubik's Cube
/// </summary>
void RubicsCube::Menu()
{
	int choice;
	std::cout << "КУБИК РУБИКА\n1 - Начать игру\n2 - Выход\n";
	std::cin >> choice;
	system("cls");
	switch (choice)
	{
	case 1:
		std::cout << "Желаете начать с собранного, запутанного или кубика из файла?\n1 - Собранный\n2 - Запутанный\n3 - Из файла\n";
		std::cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			CreateCube();
			std::cout << "Успешно!";
			system("cls");
			ShowCube();
			while (true)
			{
				Keys();
			}
			break;
		case 2:
			CreateCube();
			RandomCube();
			std::cout << "Успешно!";
			system("cls");
			ShowCube();
			while (!CheckCube())
			{
				Keys();
			}
			break;
		case 3:
			CubeFromFile();
			std::cout << "Успешно!";
			system("cls");
			ShowCube();
			while (!CheckCube())
			{
				Keys();
			}
			break;
		}


		std::cout << "GAME OVER\n";
		system("pause");
		break;
	case 2:
		system("cls");
		return;
		break;
	default:
		std::cout << "Невернный ввод";
		system("pause");
		system("cls");
		break;
	}
}
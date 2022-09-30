/*!
\file
\brief Заголовочный файл с описанием методов ввода.

Данный файл содержит в себе определения основных методов, используемых для ввода данных в программе.
*/
#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <fstream>
/// <summary>
/// Метод для чтению данных из файла.
/// Результатом является 2 числа представляющих собой размеры матрицы(количество строк, количество столбцов) и 
/// массив вещественных чисел(элементы для заполнения матрицы). 
/// </summary>
/// <param name="path">Путь к файлу содержащему информацию.</param>
/// <returns>tuple<int,int,std::vector<float>></returns>
std::tuple<int, int, std::vector<float>> file_input(std::string& path);
/// <summary>
/// Метод для введения данных из консоли(терминала).
/// Результатом является 2 числа представляющих собой размеры матрицы(количество строк, количество столбцов) и 
/// массив вещественных чисел(элементы для заполнения матрицы). 
/// </summary>
/// <returns>tuple<int,int,std::vector<float>></returns>
std::tuple<int, int, std::vector<float>> console_input();
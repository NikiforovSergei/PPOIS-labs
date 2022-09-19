///\file game.h
/// \brief заголовочный файл
/// содержит основной класс
//
// Created by konstantin on 06.09.22.
//

#ifndef PYATNASHKI_GAME_H
#define PYATNASHKI_GAME_H

#include <vector>
#include <iostream>
#include <ctime>
#include <gtest/gtest.h>

class Game;
///\brief Реализация класса
///
/// \details Данный класс реализует игру птянашки, а также содержит вложенный класс
class Game{
private:

    ///\brief Вложенный класс
    ///
    /// \details создание класса клетки, который будет хранить значение, которое хранится в клетке, а также координаты клетки
    class Cell{
    public:
        //! значение, которое содержит одна клетка
        int number;

        //!координаты числа на игровой сетке
        std::pair<int,int> points;
    };

    //!размер поля
    int size_of_field;

    //!игровое поле
    std::vector<std::vector<Cell>> field;

    //!шаблон выиграшной комбинации
    std::vector<std::vector<int>> pattern_of_winners_set;

    //!хранит координаты пустой клетки
    std::pair<int,int> points_of_empty;

    //! счетчик количества ходов
    int counter_of_move;

public:

    /// \brief оператора индексирования,для просмотра элемента
    /// \param index принимает константную ссылку на индекс вектора, который нужно вернуть
    /// \return вектор строк, который состоит из клеток поля
    /// \author Konstantsin
    /// \see std::vector<std::vector<Cell>> field
    /// \see play_game.cpp
    std::vector<Cell> operator [](const int& index);

    ///\brief метод создания игрового поля
    /// \author Konstantsin
    /// \see std::pair<int,int> points_of_empty
    /// \see std::vector<std::vector<int>> pattern_of_winners_set
    /// \see std::vector<std::vector<Cell>> field
    /// \see int size_of_field
    /// \see bool CheckCellOnRepetition(int number)
    /// \see int CheckInputNumber()
    /// \see game_field.cpp
    void CreateField();

    ///\brief процесс игры
    /// \author Konstantsin
    /// \see void CreateField()
    /// \see void ShowField()
    /// \see void DeleteField()
    /// \see std::pair<int,int> points_of_empty
    /// \see std::vector<std::vector<Cell>> field
    /// \see int size_of_field
    /// \see int number
    /// \see std::pair<int,int> points
    /// \see char CheckInputChar()
    /// \see bool CheckWinnerSet()
    /// \see play_game.cpp
    void PlayProcess();

    ///\brief метод вывода поля на экран
    /// \author Konstantsin
    /// \see int size_of_field;
    /// \see std::vector<std::vector<Cell>> field
    /// \see std::vector<Cell> operator [](int index)
    /// \see game_field.cpp
    void ShowField();

    ///\brief проверка на расстановку клеток без повторения
    /// \param number принимает рандомно сгенерированное число, которое нужно поместить в игровую клетку
    /// \return true, если такого числа на поле нет, и false, если такое число уже имеется
    /// \author Konstantsin
    /// \see int size_of_field;
    /// \see std::vector<std::vector<Cell>> field
    /// \see game_field.cpp
    bool CheckCellOnRepetition(int number);

    ///\brief проверка на ввод для чисел
    /// \return возвращает число, которое необходимо проверить
    /// \author Konstantsin
    /// \throw exception при неправильном вводе
    /// \see game_field.cpp
    int CheckInputNumber();

    ///\brief проверка на ввод для символов
    /// \return возвращает символ, которое необходимо проверить
    /// \author Konstantsin
    /// \throw exception при неправильном вводе
    /// \see play_game.cpp
    char CheckInputChar();

    ///\brief очищает поле
    /// \author Konstantsin
    /// \see std::vector<std::vector<Cell>> field
    /// \see int counter_of_move
    /// \see std::vector<std::vector<int>> pattern_of_winners_set
    /// \see game_field.cpp
    void DeleteField();

    ///\brief проверка на победу
    /// \return true, если клетки расставлены правильно, и false, если это не так
    /// \author Konstantsin
    /// \see  int size_of_field
    /// \see std::vector<std::vector<int>> pattern_of_winners_se
    /// \see std::vector<std::vector<Cell>> field
    /// \see  check_winner.cpp
    bool CheckWinnerSet();

    ///\brief проверка на возможность выиграть при поле со стороной 2
    /// \return true, если выиграть нельзя, и false, если можно
    /// \author Konstantsin
    /// \see  int size_of_field
    /// \see std::vector<std::vector<Cell>> field
    /// \see  game_field.cpp
    /// \see play_game.cpp
    bool CheckUnpossibleWin();
};


#endif //PYATNASHKI_GAME_H
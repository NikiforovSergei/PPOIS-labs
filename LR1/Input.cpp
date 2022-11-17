/*!
   \file
   \author Иван Титлов
   \brief Реализация работы с вводимыми данными

   В данном файле производится считывания, обработка и интерпретация вводимых пользователем данных.
*/

#include "Input.h"
#include "../realization/Vector.h"
#include "../realization/Operations.h"
#include <iostream>
#include <vector>
#include <regex>


/*!
   \author Иван Титлов
   \brief Начинает считывание вектора с открытия скобо
   \param Введенный вользователем вектор Input
   \return Вектор Res.
   В вектор res пушатся все открытия скобок с введённых данных
*/
std::vector<int> setParentheses(std::string input) { ///Начинает считывание вектора с открытия скобок
    std::vector<int> res;
    for(int i=0; i<input.size(); i++){
        if (input[i] == '('){
            res.push_back(i);
        }
    }
    return res;
}

/*!
   \author Иван Титлов
   \brief  Функция находит координаты начал и концов векторов
   \param Введенный вользователем вектор Input
   \return Вектор Arr.
   В вектор Arr записываются целочисленные занчения координат векторов
*/

std::vector<double> setVector(std::string input, int i){
    std::vector<double> arr;
    std::string buffer="";
    while(input[i-1]!=')'){
        if (input[i]>=47 && input[i]<=57){
            buffer+=input[i];
            i++;
        }
        else {
            if (buffer !="") {
                arr.push_back(atoi(buffer.c_str()));
            }
            buffer = "";
            i++;

        }
    }
    return arr;
}
/*!
   \author Иван Титлов
   \brief Устанавливает кординаты векторов
   \param Input, res, parentheses Введенный вользователем вектор Input, вектор res, в которого параллельно функция Setparentheses пушит открытия скобок и считывает их количество, что поможет в будушем найти начала задданных координат векторов
   \return Вектор res
   Устанавливаются координты начала вектора(-ов) под названием Start и координаты конца вектора(-ов) под навзанием Finish, они пушатся в
*/
std::vector<std::vector<double>> divideIntoVectors(std::string input){

    std::vector<int> parentheses = setParentheses(input);

    std::vector<std::vector<double>> res;

    std::vector<double> start = setVector(input, parentheses[0]);

    std::vector<double> finish = setVector(input, parentheses[1]);

    res.push_back(start);
    res.push_back(finish);
    if (parentheses.size()==4) {
        start = setVector(input, parentheses[2]);
        finish = setVector(input, parentheses[3]);

        res.push_back(start);
        res.push_back(finish);
    }
    return res;
}

/*!
   \author Иван Титлов
   \brief setOperation определяет какую операцию хочет выполнить пользователь
   \param res, parentheses
   \return Вектор res
   В res добавляется знак операции (если он есть), которую пользователь хочет провести
*/
std::string setOperation(std::string input){
    std::vector<int> parentheses = setParentheses(input);
    std::string res="";
    if (parentheses.size()==4){
        int i = parentheses[2]-1;
        while(input[i]!=')'){
            res+=input[i];
            i--;
        }
    }
    return res;
}

/*!
   \author Иван Титлов
   \brief ///startOperation выполняет операцию в зависимости от того, что ввел пользователь
   \param res, parentheses, startFinish,input
   \return v1.getInfo или v1.getCoordinatesOfVector в зависимости от операции
   Из вектора res мы достаем значения векторов и проводим над ними операции в зависимости от введённого выражения
*/
void startOperation(std::string operation, std::vector<std::vector<double>> startFinish, std::string input) {
    std::Vector v1{};
    std::Vector v2{};

    if(operation.size()==3) {
        if (startFinish.size() == 4) {
            std::Vector res;
            v1.setStart(startFinish[0]);
            v1.setFinish(startFinish[1]);
            v2.setStart(startFinish[2]);
            v2.setFinish(startFinish[3]);
            switch (operation[1]) {
                case '+': {
                    res=v1+v2;
                    std::cout << res.getInfo();
                    break;
                }
                case '-': {
                    res = v1 - v2;
                    std::cout << res.getInfo();
                    break;
                }
                case '*': {
                    res = v1*v2;
                    std::cout << res.getCoordinatesOfVector()[0]<<", " << res.getCoordinatesOfVector()[1]<<", "<<res.getCoordinatesOfVector()[2];
                    break;
                }
                case '/': {
                    Operation::division(v1, v2);
                    break;
                }
                case '^': {
                    std::cout << std::to_string(v1^v2);
                    break;
                }
                case '<': {
                    Operation::comparison(v1, v2, '<');
                    break;
                }
                case '>': {
                    Operation::comparison(v1, v2, '>');
                    break;
                }
                case '=': {
                    Operation::comparison(v1, v2, '=');
                    break;
                }
            }
        } else {
            if (startFinish.size() == 2) {
                const std::regex r(R"(^(\(\d+\, \d+\, \d+\) \(\d+\, \d+\, \d+\))$)");
                std::smatch s;
                v1.setFinish(startFinish[1]);
                v1.setStart(startFinish[0]);
                if (std::regex_match(input, s, r)) {
                    std::cout << v1.getInfo();
                } else {
                    std::Vector res = v1;
                    res=v1*atoi(&(input[input.size() - 1]));
                    std::cout << res.getInfo();
                }
            }
        }
    }
    else{
        std::Vector res;
        if (startFinish.size() == 4) {
            v1.setStart(startFinish[0]);
            v1.setFinish(startFinish[1]);
            v2.setStart(startFinish[2]);
            v2.setFinish(startFinish[3]);
            if (operation == " =+ ") {
                v1+=v2;
                std::cout<<v1.getInfo();
            } else {
                if (operation == " =- ") {
                    v1-=v2;
                    std::cout<<v1.getInfo();
                } else {
                    if (operation == " =* ") {
                        v1*=v2;
                        std::cout << v1.getCoordinatesOfVector()[0]<<", " << v1.getCoordinatesOfVector()[1]<<", "<<v1.getCoordinatesOfVector()[2];
                    }
                }
            }
        }
        else {
            if (startFinish.size() == 2) {
                const std::regex r(R"(^(\(\d+\, \d+\, \d+\) \(\d+\, \d+\, \d+\))$)");
                std::smatch s;
                v1.setFinish(startFinish[1]);
                v1.setStart(startFinish[0]);
                if (std::regex_match(input, s, r)) {
                    std::cout << v1.getInfo();
                } else {
                    v1*=atoi(&input[input.size() - 1]);
                    std::cout << v1.getInfo();
                }
            }
        }
    }

}
/*!
   \author Иван Титлов
   \brief  сheck проверяет правильно ли введены данные
   \param input, r1, r2
   \return Check принимает занчение False или True

   С помощью регулярных выражений проверяем верность введённых данных.
*/
bool check(std::string input) {
    const std::regex r1(R"(^(\(\d+\, \d+\, \d+\) \(\d+\, \d+\, \d+\)\s(\^|\*|\/|\+|\-|\>|\<)(\=?)\s\(\d+\, \d+\, \d+\) \(\d+\, \d+\, \d+\)(\s?\=?\s?))$)"),
                    r2(R"(^(\(\d+\, \d+\, \d+\) \(\d+\, \d+\, \d+\)( \* \d+)?)(\s?\=?\s?)$)");
    std::smatch s1, s2;
    if(std::regex_match(input,s1, r1) || std::regex_match(input, s2, r2)){
        return true;
    }
    return false;
}
/*!
   \author Иван Титлов
   \brief Основная функция, запускающая программу ввода
   \param input

   В этой фугкции собраны все необходимые операции для работы с введёнными данными
*/
void Input::start() {
    std::cout << std::endl << "Input Vector's operation:" << std::endl;
    std::string input;
    getline(std::cin,input);
    if (check(input)) {
        std::vector<std::vector<double>> startFinish = divideIntoVectors(input);
        std::string operation = setOperation(input);
        startOperation(operation, startFinish, input);

    }
    else {
        std::cout<<"incorrect input\n";
    }
}

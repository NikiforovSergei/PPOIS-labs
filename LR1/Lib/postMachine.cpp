//
// Created by Vladimir Moshchuk on 26.09.22.
//

#include "postMachine.h"

#include <utility>
namespace postMachine {


tapeManager::tapeManager(std::vector<char> tape) {
  this->tape = std::move(tape);///Загрузка вектор-ленты в машину.
}

tapeManager::~tapeManager() {
  tape.clear(); ///Очистка вектор-ленты в машине.
  tape.shrink_to_fit();///Вырванивание вектор-ленты машины.
}

/*!
 * В случае если лента будет пустой, выведет информацию с рекомендацией как заправить ленту.
 * @return
 */
std::string tapeManager::output() {
  if(!tape.empty()) {
    std::string str(tape.begin(), tape.end());
    return str;
  } else{
    return "seems you not initialize tape, just type init_tape: (1,0,1) for example :)";
  }
}
/*!
 * Слияние векторов-команд: введенного пользователем и того что он до этого ввел.
 * @param tapeexec
 */
void tapeManager::push(std::vector<char> tapeexec) {
  this->tape.insert(tapeexec.end(), tapeexec.begin(), tapeexec.end());
}





/*!
 * В случае если лента будет пустой, выведет кракозябру.
 * @return
 */
std::string slide::output() {
  if(!tape.tape.empty()) {
    std::string
        str = std::string(position, '-') + std::string(1, '^') + std::string(tape.tape.size() - position - 1, '-');
    return str;
  }
  else {
    return "xXxXx:/";
  }
}
/*!
 * Просто конструктор.
 * @param tape
 */
slide::slide(tapeManager &tape) : tape(tape) {

}
/*!
 * Проводит проверку на правильность того, что позиция что ввел пользователь <= размеру ленты, иначе позиция становится максимальной.
 * @param pos
 */
void slide::setPos(unsigned int pos) {
  if (pos <= tape.tape.size() - 1) {
    this->position = pos;
  } else {
    this->position = tape.tape.size() - 1;
  }
}
/*!
 *  Проводит проверку на правильность того, что позиция не равна 0, иначе позиция смещается на 1 вниз.
 */
void slide::shiftLeft() {
  if (position!=0) {
    position -= 1;
  }
}
/*!
 *  Проводит проверку на правильность того, что позиция не равна количеству символов в ленте, иначе позиция смещается на 1 вверх.
 */
void slide::shiftRight() {
  if (position!=tape.tape.size() - 1) {
    position += 1;
  }
}





/*!
 * Просто конструктор
 * @param slide
 * @param tape
 */
ruller::ruller(class slide &slide, tapeManager &tape) : slide(slide), tape(tape) {

}
/*!
 * Возвращение вектора-команд.
 * @return
 */
std::vector<std::string> ruller::history() {
  return instruct;
}
/*!
 * Деструктор.
 */
ruller::~ruller() {
  instruct.clear();
  instruct.shrink_to_fit();

  command.clear();
}
/*
 * Свитчер работает как обычный свитч.
 */
void ruller::switcher(int &index) {
  if (!instruct.empty()){///Проверка что у нас не пустая команда.
    std::stringstream varname(instruct[index]);///Загон команды в поток строки.

    std::string temp;

    varname >> temp;///Считывание первого набора элементов строки до пробела.

    if (command.contains(temp)) {///Проверка, есть ли команда в мапе.
      switch (command.find(temp)->second) {///Поиск команды в мапе и переход к кейсам.
        case 1: {///Кейс изменения позиции.
          varname >> temp;
          slide.setPos(std::stoi(temp));
          index++;
          break;
        }
        case 2: {///Кейс смещения каретки вправо.
          slide.shiftRight();
          index++;
          break;
        }
        case 3: {///Кейс смещения каретки влево.
          slide.shiftLeft();
          index++;
          break;
        }

        case 4: {///Кейс изменения символа на 1
          tape.tape[slide.position] = '1';
          index++;
          break;
        }

        case 5: {///Кейс изменения символа на 0
          tape.tape[slide.position] = '0';
          index++;
          break;
        }
        case 6: {///Перемещение к определнной команде в векторе команд.
          goTo(index);
          break;
        }
        case 7: {///Остановка
          isItStop = true;
          break;
        }

        case 9: {///Инициализация вектора-ленты, для последующего загона.
          std::stringstream ss(instruct[index].substr(instruct[index].find('(') + 1,
                                                      instruct[index].find(')') - instruct[index].find('(') - 1));
          std::string token;
          char chr;
          while (getline(ss, token, ',')) {
            if(!token.empty()) {
              assert(token.size()==1);
              chr = token[0];
              tape.tape.push_back(chr);
            }
          }
          index++;
          break;
        }

        case 8: {///Вывод полезной информации о том, как пользоваться.
          help();
          instruct.pop_back();
          break;
        }

        case 10: {///Вывод истории.
          int count = 0;
          instruct.pop_back();
          for(auto& i: history()){
            std::cout<<count<<"\t"<<i<<std::endl;
            count++;
          }
          break;
        }
      }
    }
  }
}
/*!
 * То, что здесь происходит, сущий кошмар.
 * Основная суть в том что на вход приходит команда "? x y"
 * В случае если каретка стоит  на элементе ленты равный 1 - машина переходит к выполнению x команды.
 * В обратном - машина переходит к выполнению y команды.
 * @param index
 */
void ruller::goTo(int &index) {
  if(!tape.tape.empty()) {
    std::stringstream ss(instruct[index]);

    std::string gototrue;
    std::string gotofalse;
    ss >> gototrue;
    ss >> gototrue;
    ss >> gotofalse;
    switch (tape.tape[slide.position]) {
      case '1': {
        index = std::stoi(gototrue);
        switcher(index);
        break;
      }
      case '0': {
        index = std::stoi(gotofalse);
        switcher(index);
        break;
      }
    }
  }
}
/*!
 * Загон строковой команды в вектор команд.
 * @param commandos
 */
void ruller::push(const std::string &commandos) {
  if(commandosCheck(commandos)) {
    instruct.push_back(commandos);
  }
}
/*!
 * Загон вектора-команд в вектор команд машины при помощи слияния.
 * @param commandos
 */
void ruller::push(const std::vector<std::string> &commandos) {
  this->instruct.insert(instruct.end(), commandos.begin(), commandos.end());
}
/*!
 * Возврат размера вектора команд.
 * @return
 */
int ruller::size() {
  return (int) instruct.size();
}
/*!
 * Возврат информации нужна ли остановка системе.
 * @return
 */
bool ruller::stop() const {
  if(isItStop){
    return true;
  }
  return false;
}
/*!
 * Проверка соответствует ли набранная команда набору команд машины.
 * @param commandos
 * @return
 */
bool ruller::commandosCheck(const std::string &commandos) {
  std::stringstream ss(commandos);
  std::string temp;
  ss >> temp;
  if (command.contains(temp)) {
    return true;
  }
  return false;
}
/*!
 * Вывод полезной инфы.
 */
void ruller::help() {
    std::cout << "******Basic Operators******\n"
                 "1.init_tape: (x,y,x,y) - initialize tape, after once initialization just splitted your tape\n"
                 "2.<-/- (shift to the left)\n"
                 "3.->/+ (shift to the right)\n"
                 "4.V/v - insert number (from 0 to 1)\n"
                 "5.X/x - delete number (from 1 to 0)\n"
                 "6.? x y - this is analog of goTo, for example: x = <-, y = ->. If the cell will be empty, go to the x, else to the y\n"
                 "7.! - stop program" << std::endl;
}

}
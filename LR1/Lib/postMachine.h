//
// Created by Vladimir Moshchuk on 26.09.22.
//

#ifndef POSTMACHINE_LIB_POSTMACHINE_H_
#define POSTMACHINE_LIB_POSTMACHINE_H_
#import <iostream>
#import <map>
#import <vector>
#include <sstream>
/*!
 * \brief Пространство имен, в котором описаны все классы машины Поста.
 * В данном пространстве лежат 3 класса: tapeManager, slide, ruller
 */
namespace postMachine {
/*!
 * Данный класс реализует ленту, состояющую из 0 и 1.
 */
class tapeManager {
 private:
  std::vector<char> tape; ///Собственно это и есть наш вектор-лента.
 public:
  explicit tapeManager(std::vector<char> tape); ///Конструктор, можно инициализировать и пустой.

  ~tapeManager();///Деструктор, ничего не обычного, просто деструктор.

  std::string output();///Метод, нужный для вывода того что мы наделали с лентой.

  void push(std::vector<char> tapeexec);///Сам не помню зачем это все нужно, но вроде как для слияния/инициализации ленты.

  friend class slide;

  friend class ruller;

};
/*!
 * Данный класс реализует каретку, очень важный класс, без него ты ничего не сделаешь с лентой.
 */
class slide{
  tapeManager& tape; ///Мало кто бы мог подумать, но наша каретка как-то должна понимать с кем она работает.

 private:

  unsigned int position = 0; ///Это как говориться, база, без данного инта мы бы ничего не сделали, он передает всю информацию об позиции каретки.


 public:

  friend class tapeManager;

  friend class ruller;

  explicit slide(tapeManager &tape); ///Конструктор, обязательно передай ему ленту, иначе чуда не произойдет.

  void shiftLeft(); ///Метод, реализующий смещение каретки влево.

  void shiftRight();///Метод, реализующий смещение каретки вправо.

  void setPos(unsigned int pos);///Метод, способный создать телепортацию.

  std::string output();///Метод, нужный для вывода того где сейчас находиться каретка.
};
/*!
 * Как и все классы в этом проекте, данный крайне важен, однако без него ты мало что сможешь сделать с лентой.
 */
class ruller {

  tapeManager& tape;
  slide& slide;

 private:
  /*!
   * Это наш командный центр, база знаний, так сказать, без данной мапы мы бы не смогли адекватно работать.
   */
  std::map<std::string, int> command{
      {"head_pos:", 1},
      {"->",        2},
      {"<-",        3},
      {"V",         4},
      {"X",         5},
      {"?",         6},
      {"!",         7},
      {"help", 8},
      {"init_tape:", 9},
      {"+", 2},
      {"-", 3},
      {"x", 5},
      {"v", 4},
      {"history", 10}
  };

  std::vector<std::string> instruct; ///Это вектор команд.

  bool isItStop = false; ///Булевая переменная, в которой хранится информация нужно ли стопарить программу.

  void goTo(int& index);///Это буквально гоу ту, перемещает на определенный индекс твоего набора команд.

  bool commandosCheck(const std::string& commandos); ///Метод, реализующий проверку является ли введенная команда валидной.

  void help();///Вывод информации как пользоваться готовой машиной.
 public:
  void push(const std::string& commandos);///Метод для загрузки команды в вектор-команд

  void push(const std::vector<std::string>& commandos);///Метод для загрузки вектора-команд в существующий вектор-команд путем слияния.

  ruller(class slide &slide, tapeManager &tape);///Конструктор

  ~ruller();///Деструктор

  void switcher(int& index);///Основная команда в данном классе, наиважнейшая.

  int size();///Возсращает количество команд введенных ранее

  bool stop() const;///Возвращает true/false когда нужно отключать машину.

  std::vector<std::string> history();///Метод, возвращающий вектор-команд для последующего чтения.
};
}

#endif //POSTMACHINE_LIB_POSTMACHINE_H_

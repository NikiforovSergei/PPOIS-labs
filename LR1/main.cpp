#import <iostream>
#import <fstream>
#import "Lib/postMachine.h"
/*!
 * Класс нужный для полной реализации машины.
 * Чисто использует 3 главных класса по назначению.
 */
class TestMachine {
 private:
  /*!
   * Выводит собсна лого.
   */
  void logo() {
    std::cout
        << "  *&&&&&&&%*             %%%%%%%%%%            @@@@      ((((((((///                                            \n"
           "  @@@@@@@@@@@@*      %%%%%%,   %%%%%%      *@@@  /@@@   ////#@@,,,,                                             \n"
           "   @@@       *@@@    %%%%           %%%%    @@*     @@        @@                                                 \n"
           "   @@@        @@@   %%%%             %%%%   ,@@               @@                                                        \n"
           "   @@@       @@@%   %%%(              %%%     @@@@@@&         @@                                                        \n"
           "   %@@@@@@@@@@@     %%%%              %%%           @@%       @@                                                        \n"
           "    @@@              %%%%            %%%%            @@       @@                                                        \n"
           "    @@@               %%%%%        %%%%     .@@*    @@@       @@,                                                       \n"
           "    @@@                 (%%%%%%%%%%%%         #@@@@@@                                                               \n"
           "    @@@                       %                                        %%%#                                             \n"
           "                     @@   &@@                          &@,                                                              \n"
           "                    &@@& /@@@     ,@@*       /@@@@     ,@@#@@@@/     %%%%%%       @@%@@@@@@@     /@@&  ,@@@             \n"
           "                    @@ @ @ @%   @@   *@@   *@@    @@    @@     @@        %%%       @@.     @@    /@@      @@@    \n"
           "                    @& @@ .@,         @@   @@           @@     @@,       *%%       /@@     ,@@    @@@@@@@@@@@@       \n"
           "                   /@     @@   @@,    @@   @@           @@/    ,@@        %%%       @@&     @@@    @@@            \n"
           "                   @@     @@   @@    *@@   .@@    @@%   /@@     @@        .%%        @@      @@@    ,@@%    &@@,      \n"
           "                   @@     @@    @@@@@ @@     &@@@@@      @@     @@#   (%%%%%%%%%%%   %@@      @@*      .@@@@@@        \n"
        << std::endl;
  }
 public:
  /*!
   * Конструктор класса, нужный для того чтобы пользователь не писал лишнее.
   */
  TestMachine() {
    tape = new postMachine::tapeManager({});
    slide = new postMachine::slide(*tape);
    ruller = new postMachine::ruller(*slide, *tape);
  }
  /*!
   * Простой деструктор, который уничтожает три объекта машины.
   */
  ~TestMachine() {
    delete tape;
    delete slide;
    delete ruller;
  }
  postMachine::tapeManager *tape{};
  postMachine::slide *slide{};
  postMachine::ruller *ruller{};

  /*!
   * Метод для запуска машины из под файла.
   * @param dir
   * @param log
   */
  void flaunch(const std::string &dir, bool log);

  /*!
   * Метод для запуска машины в реальном времени.
   * @param log
   */
  void launch(bool log);

};

void TestMachine::flaunch(const std::string &dir, bool log) {
  logo();
  std::ifstream file(dir);
  std::string command;
  while (std::getline(file, command)) {
    ruller->push(command);
  }
  file.close();

  int index = 0;

  while (true) {
    ruller->switcher(index);

    if (ruller->stop()) {
      break;
    }

    if (log) {
      std::cout << tape->output() << std::endl;
      std::cout << slide->output() << std::endl;
    }
  }

}
void TestMachine::launch(bool log) {
  logo();
  int index = 0;
  std::string command;
  while (true) {
    std::cout << ">>>";
    getline(std::cin, command);
    ruller->push(command);
    ruller->switcher(index);
    if (ruller->stop()) {
      break;
    }
    if (log) {
      std::cout << tape->output() << std::endl;
      std::cout << slide->output() << std::endl;
    }
  }
}
/*!
 * На вход программа может получить несколько флагов:
 * -f работа с файлом
 * -log вывод каждого действия
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
  TestMachine machine;

  bool file = false;
  bool log = false;
  for(int i =0; i < argc; i++) {
    if (strcmp(argv[i], "-f")==0) {
      file = true;
    }
    if (strcmp(argv[i], "-log")==0) {
      log = true;
    }
  }
  if(argc > 1) {
    if(file){
        std::cout<<"Type path to the file: ";

        std::string path;

        std::getline(std::cin, path);

        machine.flaunch(path,log);
    }
    else{
      machine.launch(log);
    }
  }
  else{
    machine.launch(true);
  }
  return 0;
}


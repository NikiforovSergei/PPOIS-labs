//
// Created by Vladimir Moshchuk on 3.09.22.
//

#include "PostMachine.h"

namespace postMachine {

void dataManage::fload(const std::string &path) {

  std::ifstream file(path);
  std::string line, token;

  std::getline(file, line);

  if (line.find("init_tape:")!=std::string::npos) {
    initTape(line);
  } else {
    std::cout << "Basic interpreter has an error: tape wasn`t loaded!" << std::endl;
    exit(-1);
  }
  line.clear();

  while (std::getline(file, line)) {
    instruct.push_back(line);
  }
  file.close();
}
std::string dataManage::print(bool log) {
  std::string stringtape;
  for (auto &&i : tape) {
    stringtape += std::to_string(i);
    if (log) {
      std::cout << i;
    }
  }
  if (log)
    std::cout << std::endl;
  return stringtape;
}

std::string dataManage::initTape(const std::string &line) {
  std::string token;
  std::string substring = line;
  substring = substring.substr(substring.find('(') + 1, substring.find(')') - substring.find('(') - 1);
  std::stringstream ss(substring);

  while (getline(ss, token, ',')) {
    assert(token.size()==1);
    tape.push_back(std::stoi(token));
  }
  return print(false);
}
std::string dataManage::initCommand(const std::string &rule) {

  instruct.push_back(rule);

  return rule;
}
void machine::history(dataManage &data) {
  for (int i =0; i < data.instruct.size(); i++) {
    std::cout << i <<"\t"<<data.instruct[i]<< std::endl;
  }
}

int slide::getPos() const {
  return position;
}

void slide::shiftLeft() {
  if (position!=0) {

    position -= 1;

  }

}

void slide::shiftRight(dataManage &data) {
  if (position!=data.tape.size() - 1) {
    position += 1;
  }
}

void slide::setPos(unsigned int pos) {
  position = pos;
}

void slide::print(dataManage &data) const {
  for (int i = 0; i < position; i++) {
    std::cout << "-";
  }
  std::cout << "^";
  for (int i = (int) data.tape.size() - 1; i > position; i--) {
    std::cout << "-";
  }
  std::cout << std::endl;
}

void machine::switcher(dataManage &data, slide &slide, int &i) {
  std::string temp;
  std::stringstream ss;

  ss << data.instruct[i];

  ss >> temp;
  switch (data.command.find(temp)->second) {
    case 1: {
      std::string temp_inside;

      ss >> temp_inside;

      slide.setPos(std::stoi(temp_inside));

      break;
    }
    case 2:
    case 10: {
      slide.shiftRight(data);
      break;
    }

    case 3:
    case 11: {
      slide.shiftLeft();
      break;
    }

    case 4: {
      data.tape[slide.getPos()] = 1;
      break;
    }

    case 5: {
      data.tape[slide.getPos()] = 0;
      break;
    }
    case 6: {
      goTo(data, slide, ss, i);
      break;
    }
    case 7: {
      return;
    }
    case 8: {
      help();
      break;
    }
    case 9: {
      data.initTape(data.instruct[i]);
      break;
    }
  }
}
int machine::goTo(dataManage &data, slide &slide, std::stringstream &ss, int &i) {
  std::string truediesigion, falsedesigion;

  ss >> truediesigion;
  ss >> falsedesigion;
  switch (data.tape[slide.getPos()]) {
    case 1: {
      i = std::stoi(truediesigion);
      return i;
    }
    case 0: {
      i = std::stoi(falsedesigion);
      return i;
    }
  }
}
std::string machine::flaunch(const std::string &dir, bool log) {
  dataManage data;
  data.fload(dir);
  slide slide;
  for (int i = 0; i!=data.instruct.size(); i++) {
    switcher(data, slide, i);
    if (log) {
      data.print(true);
      slide.print(data);
    }
  }
  history(data);
  return data.print(true);
}
std::string machine::launch(bool log) {
  logo();

  std::string line;
  dataManage data;
  slide slide;

  int indexator = 0;

  while (true) {
    std::cout << ">>>";

    getline(std::cin, line);

    data.initCommand(line);

    if (line=="!") {
      break;
    }
    switcher(data, slide, indexator);
    if (log and line!="help") {
      data.print(true);
      slide.print(data);
    }
    indexator++;
  }
  return data.print(true);
}

void machine::tapechecker(dataManage &data, const std::string &line) {
  if (line.find("init_tape:")!=std::string::npos) {
    data.initTape(line);
  } else {
    std::cout << "Basic interpreter has an error: tape wasn`t loaded!" << std::endl;
    exit(-1);
  }
}

void machine::logo() {
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
void machine::help() {
  std::cout << "******Basic Operators******\n"
               "1.init_tape: (x,y,x,y) - initialize tape, after once initialization just splitted your tape\n"
               "2.<- or - (shift to the left)\n"
               "3.-> or - (shift to the right)\n"
               "4.V - insert number (from 0 to 1)\n"
               "5.X - delete number (from 1 to 0)\n"
               "6.? x y - this is analog of goTo, for example: x = <-, y = ->. If the cell will be empty, go to the x, else to the y\n"
               "7.! - stop program" << std::endl;
}

}
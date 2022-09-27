//
// Created by Vladimir Moshchuk on 26.09.22.
//

#include "postMachine.h"

#include <utility>
namespace postMachine {


tapeManager::tapeManager(std::vector<char> tape) {
  this->tape = std::move(tape);
}

tapeManager::~tapeManager() {
  tape.clear();
  tape.shrink_to_fit();
}

std::string tapeManager::output() {
  std::string str(tape.begin(), tape.end());
  return str;
}
void tapeManager::push(std::vector<char> tapeexec) {
  this->tape.insert(tapeexec.end(), tapeexec.begin(), tapeexec.end());
}






std::string slide::output() {
  std::string
      str = std::string(position, '-') + std::string(1, '^') + std::string(tape.tape.size() - position - 1, '-');
  return str;
}

slide::slide(tapeManager &tape) : tape(tape) {

}

void slide::setPos(unsigned int pos) {
  if (pos <= tape.tape.size() - 1) {
    this->position = pos;
  } else {
    this->position = tape.tape.size() - 1;
  }
}

void slide::shiftLeft() {
  if (position!=0) {
    position -= 1;
  }
}

void slide::shiftRight() {
  if (position!=tape.tape.size() - 1) {
    position += 1;
  }
}






ruller::ruller(class slide &slide, tapeManager &tape) : slide(slide), tape(tape) {

}

std::vector<std::string> ruller::history() {
  return instruct;
}

ruller::~ruller() {
  instruct.clear();
  instruct.shrink_to_fit();

  command.clear();
}

void ruller::switcher(int &index) {
  if (!instruct.empty()) {
    std::stringstream varname(instruct[index]);

    std::string temp;

    varname >> temp;

    if (command.contains(temp)) {
      switch (command.find(temp)->second) {
        case 1: {
          varname >> temp;
          slide.setPos(std::stoi(temp));
          index++;
          break;
        }
        case 2: {
          slide.shiftRight();
          index++;
          break;
        }
        case 3: {
          slide.shiftLeft();
          index++;
          break;
        }

        case 4: {
          tape.tape[slide.position] = '1';
          index++;
          break;
        }

        case 5: {
          tape.tape[slide.position] = '0';
          index++;
          break;
        }
        case 6: {
          goTo(index);
          index++;
          break;
        }
        case 7: {
          isItStop = true;
          break;
        }

        case 9: {
          std::stringstream ss(instruct[index].substr(instruct[index].find('(') + 1,
                                                      instruct[index].find(')') - instruct[index].find('(') - 1));
          std::string token;
          char chr;
          while (getline(ss, token, ',')) {
            assert(token.size()==1);
            chr = token[0];
            tape.tape.push_back(chr);
          }
          index++;
          break;
        }

        case 8: {
          help();
          instruct.pop_back();
          break;
        }
      }
    }
  }
}

void ruller::goTo(int &index) {
  std::stringstream ss(instruct[index]);

  std::string gototrue;
  std::string gotofalse;

  ss >> gototrue;
  ss >> gototrue;
  ss >> gotofalse;
  switch (tape.tape[slide.position]) {
    case '1': {
      int i = std::stoi(gototrue);
      switcher(i);
      break;
    }
    case '0': {
      int i = std::stoi(gotofalse);
      switcher(i);
      break;
    }
  }
}

void ruller::push(const std::string &commandos) {
  if(commandosCheck(commandos)) {
    instruct.push_back(commandos);
  }
}

void ruller::push(const std::vector<std::string> &commandos) {
  this->instruct.insert(instruct.end(), commandos.begin(), commandos.end());
}

int ruller::size() {
  return (int) instruct.size();
}

bool ruller::stop() const {
  if(isItStop){
    return true;
  }
  return false;
}
bool ruller::commandosCheck(const std::string &commandos) {
  if (command.contains(commandos)) {
    return true;
  }
  return false;
}
void ruller::help() {
    std::cout << "******Basic Operators******\n"
                 "1.init_tape: (x,y,x,y) - initialize tape, after once initialization just splitted your tape\n"
                 "2.<-/- (shift to the left)\n"
                 "3.->/- (shift to the right)\n"
                 "4.V/v - insert number (from 0 to 1)\n"
                 "5.X/x - delete number (from 1 to 0)\n"
                 "6.? x y - this is analog of goTo, for example: x = <-, y = ->. If the cell will be empty, go to the x, else to the y\n"
                 "7.! - stop program" << std::endl;
}

}
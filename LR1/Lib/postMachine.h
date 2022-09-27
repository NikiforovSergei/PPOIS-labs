//
// Created by Vladimir Moshchuk on 26.09.22.
//

#ifndef POSTMACHINE_LIB_POSTMACHINE_H_
#define POSTMACHINE_LIB_POSTMACHINE_H_
#import <iostream>
#import <map>
#import <vector>
#include <sstream>

namespace postMachine {
class tapeManager {
 private:
  std::vector<char> tape;
 public:
  explicit tapeManager(std::vector<char> tape);

  ~tapeManager();

  std::string output();

  void push(std::vector<char> tapeexec);

  friend class slide;

  friend class ruller;

};
class slide{
  tapeManager& tape;

 private:

  unsigned int position = 0;

 public:

  friend class tapeManager;

  friend class ruller;

  explicit slide(tapeManager &tape);

  void shiftLeft();

  void shiftRight();

  void setPos(unsigned int pos);

  std::string output();
};

class ruller {

  tapeManager& tape;
  slide& slide;

 private:
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
      {"+", 10},
      {"-", 11}
  };

  std::vector<std::string> instruct;

  bool isItStop = false;

 public:
  void push(const std::string& commandos);

  void push(const std::vector<std::string>& commandos);

  ruller(class slide &slide, tapeManager &tape);

  ~ruller();

  void switcher(int& index);

  void goTo(int& index);
  int size();

  bool stop() const;

  std::vector<std::string> history();
};
}

#endif //POSTMACHINE_LIB_POSTMACHINE_H_

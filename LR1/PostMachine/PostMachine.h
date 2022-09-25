//
// Created by Vladimir Moshchuk on 3.09.22.
//

#ifndef LAB1_POSTMACHINE_H
#define LAB1_POSTMACHINE_H

#import <iostream>
#import <vector>
#import <map>
#import <string>
#import <sstream>
#import <fstream>

namespace postMachine {

class dataManage {
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

  std::vector<int> tape;

  std::vector<std::string> instruct;

  void fload(const std::string &path);

  std::string initTape(const std::string& tape);

  std::string initCommand(const std::string& rule);

  std::string print(bool log);

 public:

  friend class slide;

  friend class machine;

};

class slide {

 private:
  unsigned int position = 0;

 public:

  [[nodiscard]] int getPos() const;

  void shiftLeft();

  void shiftRight(dataManage& data);

  void setPos(unsigned int pos);

  void print(dataManage& data) const;

};

class machine{
 private:

  static void switcher(dataManage& data, slide& slide,int& i);

  static int goTo(dataManage& data, slide& slide, std::stringstream& ss, int& i);

  static void tapechecker(dataManage& data, const std::string& line);

  static void logo();

  static void help();
 public:

  std::string flaunch(const std::string &dir, bool log);

  std::string launch(bool log);

  void history(dataManage &data);
};


}


#endif //LAB1_POSTMACHINE_H

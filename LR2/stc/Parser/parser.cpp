#include "Parser.h"
#include "../Exceptions/Exceptions.h"

namespace stc {

Tree *Parser::makeSet(std::string setLine) {
  Tree *my_set = new Tree;
  std::string temporary_string;
  for (int i = 1; i < setLine.length(); i++) {

    if (setLine[i]=='{') {
      int j = i;
      int counter = 1;
      while (counter!=0) {
        j++;
        if (setLine[j]=='{') counter++;
        else if (setLine[j]=='}') counter--;
      }
      my_set->subsets.push_back(makeSet(setLine.substr(i, j - i + 1)));
      i = j;
    } else if (setLine[i]!=',' && setLine[i]!='}') {
      if (setLine[i]!=' ') {
        temporary_string += setLine[i];
      }
    }

    if (setLine[i]==',' && !temporary_string.empty() || setLine[i]=='}' && !temporary_string.empty()) {
      my_set->elements.push_back(temporary_string);
      temporary_string = "";
    } else continue;
  }
  return my_set;
}


Tree *Parser::subsetCounter(int &i, std::string line) {
  int j = 1;
  int counter = 1;
  while (counter!=0) {
    if (line[j]=='{') counter++;
    else if (line[j]=='}') counter--;

    else if (!(isalpha(line[j]) or isdigit(line[j]) or line[j]==',' or line[j]==' ')) {

      std::cout << "Error: set must not store any characters other than letters and numbers" << std::endl;
      return nullptr;
    }
    j++;
  }
  Tree *a = makeSet(line.substr(0, j + 1));
  i += j - 1;
  return a;
}
void * Parser::pushBackSet(std::vector<Tree *> &lineOfSets, const std::string &line, int& i, char& operation) {
  if (line[i]=='{') {

    Tree *set = subsetCounter(i, line.substr(i));
    if (set!=nullptr)
      lineOfSets.push_back(set);
    else return nullptr;

  } else if (line[i]=='(') {
    int j = i + 1;
    int counter = 1;
    while (counter!=0) {

      if (line[j]=='(') counter++;
      else if (line[j]==')') counter--;
      j++;
    }
    lineOfSets.push_back(solution(line.substr(i + 1, j - i)));
    i += (j - i - 1);
  } else if (line[i]!=' ') {

    operation = line[i];
  }
}

Tree *Parser::solution(const std::string &line) {
  std::vector<Tree *> sets_from_line;
  char operation;
  for (int i = 0; i < line.length(); i++) {

    pushBackSet(sets_from_line, line, i, operation);

    if (sets_from_line.size()==2) {
      try {
        solve(sets_from_line, operation);
      }
      catch (Exception& e){
        std::cout<<e.what()<<std::endl;
      }
    }

  }
  return sets_from_line[0];
}


Tree *SavedSet::solution(const std::string &line) {
  std::vector<Tree *> names_of_sets;
  char operation;
  for (int i = 0; i < line.length(); i++) {

    SavedSet::pushBackSet(names_of_sets, line, i);

    if (isalpha(line[i])) {
      char a;
      a = line[i];
      try {
        if (named_sets.find(a)==named_sets.end()) throw Exception("non-existent variable! ");
        names_of_sets.push_back(named_sets.find(a)->second);
      }
      catch (const char *exception) {
        std::cout << "Error: " << exception << std::endl;
        return nullptr;
      }

    } else if (line[i]!=' ') operation = line[i];

    if (names_of_sets.size() >= 2) {
      try {
        solve(names_of_sets, operation);
      }
      catch (Exception& e){
        std::cout<<e.what()<<std::endl;
      }
    }
  }
  return names_of_sets[0];
}


void Parser::solve(std::vector<Tree *> &namesOfSets, char operation) {
  namesOfSets = {};
  switch (operation) {
    case '+':{
      namesOfSets.push_back(sum(namesOfSets[0], namesOfSets[1]));
      break;
    }
    case '*':{
     namesOfSets.push_back(intersection(namesOfSets[0], namesOfSets[1]));
      break;
    }
    case '-':{
      namesOfSets.push_back(     simetricDifference(namesOfSets[0], namesOfSets[1]));
      break;
    }
    default : {
      throw Exception("What are hell are you doing, man?!?!?!");
    }
  }
}


void SavedSet::saveSets(std::string line) {
  int amount_of_eq = 0;
  int beg_str = (int) line.rfind('=') + 1;
  int end_str = (int) line.length() - beg_str;
  std::string my_nonamed_set = line.substr(beg_str, end_str);
  Tree *found_set = Parser::solution(my_nonamed_set);
  try {

    if (found_set==nullptr) throw Exception("set not must be empty!");

  }
  catch (Exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return;
  }

  for (char i : line) {
    if (i=='=') amount_of_eq++;
  }

  for (int i = 0; i < beg_str - 1; i++) {
    try {
      if (line[i]=='=' or line[i]==' ') { continue; }
      else if (isalpha(line[i]) and isupper(line[i])) {
        try {
          if (amount_of_eq > 0 and (line[i + 1]==' ' or line[i + 1]=='=')) {

            try {
              if (named_sets.find(line[i])==named_sets.end()) {
                std::cout << "Set " << line[i] << " was saved" << std::endl;
                named_sets[line[i]] = found_set;
                amount_of_eq--;
              } else throw Exception("a set with the same name already exists");
            }
            catch (Exception &e) {
              std::cout << "Error: " << e.what() << std::endl;
              return;
            }

          } else throw Exception("incorrect name!");
        }
        catch (Exception &e) {
          std::cout << "Error: " << e.what() << std::endl;
          return;
        }
      } else throw Exception("incorrect name!");
    }
    catch (Exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
      return;
    }

  }
  std::string output;
  Tree::print(found_set, output);
}


void SavedSet::saveSet(std::string my_str) {
  Tree *set_value = solution(my_str.substr(my_str.rfind('=') + 1));
  std::vector<char> names;
  for (int i = 0; i < my_str.rfind('='); i++) {
    if (isalpha(my_str[i])) {
      named_sets[my_str[i]] = set_value;
      std::string output;
      Tree::print(set_value, output);
    }

  }
}

void SavedSet::distr(const std::string &my_str) {
  bool bracket = false, eq = false;
  if (my_str.find('=')!=-1) eq = true;
  if (my_str.find('{')!=-1) bracket = true;

  try {

    if (bracket && eq) {
      saveSets(my_str);
      return;
    } else if (!bracket && !eq) {
      std::string output;
      print(solution(my_str), output);
      return;
    } else if (!bracket && eq) {
      saveSet(my_str);
      return;
    }

    throw Exception("Invalid expression!");
  }
  catch (Exception &e) {
    std::cout << "Error: " << e.what();
  }
}
void *SavedSet::pushBackSet(std::vector<Tree *> &lineOfSets, const std::string &line, int &i) {
  if (line[i] == '(')
  {
    int j = i + 1;
    int counter = 1;
    while (counter != 0)
    {

      if (line[j] == '(') counter++;
      else if (line[j] == ')') counter--;
      j++;
    }
    lineOfSets.push_back(SavedSet::solution(line.substr(i + 1, j - i)));
    i += (j - i - 1);
  }
}

int SubOperation::setSize(Tree *set) {
  return ((int) set->elements.size() + (int) set->subsets.size());
}


void SubOperation::size(std::string str, SavedSet set) {
  while (true) {
    int spaceCounter = (int) str.find(' ');
    if (spaceCounter!=-1) {
      str.replace(spaceCounter, 1, "");
    } else break;
  }

  try {
    int beg = (int) str.find('('), end = (int) str.rfind(')');
    if (str.substr(0, beg)!="size") throw Exception("Function does not exist, did you mean size()?");
    if (str.substr(beg + 1, end - 1 - beg).length()==1 and !isupper(str[5])) throw Exception("wrong value in size()");
    if (str.substr(beg + 1, end - 1 - beg).length()!=1 and isupper(str[5])) throw Exception("wrong value in size()");
  }
  catch (Exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return;
  }

  if (isupper(str[5])) {
    try {
      if (set.named_sets.find(str[5])!=set.named_sets.end())
        std::cout << setSize(set.named_sets[str[5]]);
      else throw Exception("non-existent variable! ");
    }
    catch (Exception &e) {
      std::cout << "Error: " << e.what();
      return;
    }

  } else {
    try {

      Tree *a = Parser::makeSet(str.substr(str.find('(') + 1, str.rfind(')') - str.find('(')));
      if (str[5]!='{') throw Exception("wrong value in size()");
      std::cout << setSize(a);
    }
    catch (Exception &e) {
      std::cout << "Error: " << e.what();
      return;
    }
  }
}
}
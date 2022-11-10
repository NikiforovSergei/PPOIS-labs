#import "stc/Tree/Tree.h"
#import "stc/Parser/Parser.h"
#import "stc/Exceptions/Exceptions.h"
#import <iostream>
int main()

{
  stc::SavedSet save_my_set;

  while (true)
  {
    std::string output;
    bool indicator = false;
    std::string my_line;

    getline(std::cin, my_line);

    if(my_line.empty()){
      continue;
    }

    if (my_line.find("size") != -1)
    {

      stc::SubOperation::size(my_line, save_my_set);
      continue;
    }

    for (int i = 0; i < my_line.length(); i++)
    {
      if (isalpha(my_line[i]) && isupper(my_line[i]))
      {
        save_my_set.distr(my_line);
        indicator = true;
        break;
      }
    }

    if (!indicator)
    {
      try {
        stc::Tree::print(stc::Parser::solution(my_line), output);
        std::cout<<output<<std::endl;
      }
      catch (stc::Exception& e){
        std::cout<<e.what()<<std::endl;
      }
    }
    std::cout<<std::endl;
  }
}
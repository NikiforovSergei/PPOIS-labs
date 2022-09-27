#import <iostream>
#import "Lib/postMachine.h"

void logo(){
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
int main() {
  postMachine::tapeManager tape({'1','1','0', '1', '1', '1'});
  postMachine::slide  slide(tape);
  postMachine::ruller ruller(slide,tape);

  int i =0;
  std::string choose;
  logo();
  while(true){
    std::cout<<">>>";
    getline(std::cin, choose);
    ruller.push(choose);
    ruller.switcher(i);
    std::cout<<tape.output()<<std::endl;
    std::cout<<slide.output()<<std::endl;
    if(ruller.stop()){
      break;
    }
  }
  return 0;
}


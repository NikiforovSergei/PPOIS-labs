#include <iostream>
#include <random>
#include "Entity/Entity.h"
#include "GameField/GameField.h"

int main() {
  std::cout << "Initialize" << std::endl;
  //std::cout << (random() % 3 + 1) * 2;
  string path = "/Users/egorvasilkov/CLionProjects/Testing2/inputEntities.txt";
  string path2 = "/Users/egorvasilkov/CLionProjects/Testing2/outputEntities.txt";

  GameField mygame(20, 20);
  mygame.readEntitiesFromFile(path);

/*  mygame.eat();
  mygame.die();
  mygame.eat();*/
  mygame.eat();
  mygame.die();
/*  mygame.move();
  mygame.move();
  mygame.die();
  mygame.move();*/
  mygame.printStatus(path2);

  std::cout << "End";























  //Plant grass(100, 100, 1, "grass");
  /*

  mygame.game_field.at(0).at(0).putEntity(&grass);
  mygame.game_field.at(2).at(0).putEntity(&grass);

  mygame.game_field.at(2).at(4).putEntity(&grass);
  mygame.game_field.at(4).at(0).putEntity(&grass);

  mygame.diePlant(mygame.game_field.at(4).at(0));*/

  //mygame.game_field.at(3).at(2).putEntity(&grass);
  /*Animal tiger1(80, 100, 20, "tiger", 2, 4, 2, 1);
  Herbivore antilope(80, 100, 20, "antilope1", 2, 3, 3, 1);
  *//*mygame.game_field.at(2).at(3).putEntity(&grass);
  mygame.game_field.at(1).at(1).putEntity(&grass);*//*

  mygame.game_field.at(0).at(0).putEntity(&antilope);
  mygame.game_field.at(0).at(0).putEntity(&tiger1);

  mygame.eatPlant(mygame.game_field.at(0).at(0));
  mygame.eatHerbivores(mygame.game_field.at(0).at(0));

  Herbivore antilope2(80, 100, 20, "antilope2", 2, 3, 3, 1);
  Herbivore antilope3(80, 100, 20, "antilope2", 2, 3, 3, 0);
  mygame.game_field.at(3).at(0).putEntity(&antilope2);
  mygame.game_field.at(3).at(0).putEntity(&antilope3);
  mygame.reproductionHerbivore(mygame.game_field.at(3).at(0));
*/
  //mygame.move();

  return 0;
}

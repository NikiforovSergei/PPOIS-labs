//
// Created by Egor Vasilkov on 25.11.22.
//

#include "GameField.h"
#include <fstream>
#include <iostream>

GameField::GameField(int rows, int columns) : ROWS(rows), COLUMNS(columns) {

  for (int i = 0; i < rows; i++) {
    vector<Cell> buffer;
    for (int j = 0; j < columns; j++) {
      buffer.emplace_back(Cell(10 * (i + 1) + (j + 1)));
    }
    game_field.push_back(buffer);
  }

}

Cell GameField::getCell(int rows, int columns) const { return game_field.at(rows).at(columns); }

void GameField::move() {

  const int width = this->ROWS;
  const int height = this->COLUMNS;

  GameField newField(width, height);

  for (int i = 0; i < width; i++) {

    for (int j = 0; j < height; j++) {

      Cell oldCell = game_field.at(i).at(j);

      if (oldCell.get<Plant>()) newField.game_field.at(i).at(j).putEntity(oldCell.get<Plant>());

      for (Herbivore *k : oldCell.get<Herbivore>()) {
        int MoveToY = j + k->getSpeed();
        int MoveToX = i;

        newField.game_field.at(MoveToX).at(MoveToY).putEntity(k);
      }

      for (Animal *k : oldCell.get<Animal>()) {
        int MoveToY = j + k->getSpeed();
        int MoveToX = i;

        newField.game_field.at(MoveToX).at(MoveToY).putEntity(k);
      }

    }

  }
  game_field = newField.game_field;
}

void GameField::eatPlant(Cell &currentCell) {

  Plant *aPlant = currentCell.get<Plant>();

  for (auto k : currentCell.get<Herbivore>()) {
    if (aPlant != nullptr) {
      aPlant->getDamage(k->getSize());
      k->saturation();
      if (aPlant->isDied()) {
        delete aPlant;
        currentCell.deleteEntity(aPlant);
        break;
      } else
        k->starving();
    }
  }

}

void GameField::eatHerbivores(Cell &tempCell) {

  if (!tempCell.get<Animal>().empty() and !tempCell.get<Herbivore>().empty()) {

    for (int i = 0; i < tempCell.get<Herbivore>().size(); i++) {
      if (tempCell.get<Herbivore>().at(i)->getSpeed() > tempCell.get<Animal>().at(i)->getSpeed()) {
        tempCell.get<Animal>().at(i)->starving();
        break;
      }
      delete tempCell.get<Herbivore>().at(i);
      tempCell.deleteEntity(tempCell.get<Herbivore>().at(i));
    }

  }

}

void GameField::reproductionHerbivore(Cell &tempCell) {
  if (tempCell.entityCount() < 4) {
    bool isMale = false;
    bool isFemale = false;
    for (int i = 0; i < tempCell.get<Herbivore>().size(); i++) {
      if (tempCell.get<Herbivore>().at(i)->getSex() == 1) {
        isMale = true;
      }
      if (tempCell.get<Herbivore>().at(i)->getSex() == 0) {
        isFemale = true;
      }
    }

    if (isFemale && isMale) {
      tempCell.putEntity(new Animal(20, 40, 1, "childAnimal", 1, 2, 1, random() % 2));
    }

  }

}

void GameField::reproductionAnimal(Cell &tempCell) {

  if (tempCell.entityCount() < 4) {
    bool isMale = false;
    bool isFemale = false;
    for (int i = 0; i < tempCell.get<Animal>().size(); i++) {
      if (tempCell.get<Animal>().at(i)->getSex() == 1) {
        isMale = true;
      }
      if (tempCell.get<Animal>().at(i)->getSex() == 0) {
        isFemale = true;
      }
    }

    if (isFemale && isMale) {
      tempCell.putEntity(new Animal(20, 40, 1, "childAnimal", 1, 2, 1, random() % 2));
    }

  }

}

void GameField::diePlant(Cell &tempCell) {

  Plant *aPlant = tempCell.get<Plant>();
  if (!aPlant->getName().empty()) {
    aPlant->getDamage((int) (aPlant->getMaxHealth() * 1 / 30));
    if (aPlant->getHealth() <= 0) {
      delete aPlant;
      aPlant = nullptr;
    }
  }

}

void GameField::dieAnimals(Cell &tempCell) {

  for (auto i : tempCell.get<Animal>()) {
    i->getDamage((int) (i->getMaxHealth() * 1 / 10));
    if (i->isDied()) {
      delete i;
      tempCell.deleteEntity(i);
    }
  }

}

void GameField::dieHerbivores(Cell &tempCell) {

  for (auto i : tempCell.get<Herbivore>()) {
    i->getDamage((int) (i->getMaxHealth() * 1 / 10));
    if (i->isDied()) {
      delete i;
      tempCell.deleteEntity(i);
    }
  }

}

void GameField::readEntitiesFromFile(string &path) {
  std::fstream fileRead;
  fileRead.open(path);

  if (fileRead.is_open()) {
    while (!fileRead.eof()) {
      int i, j, health, maxHealth, size, starvation, starvationTime, speed, sex;
      string Entity, name;

      fileRead >> Entity;
      fileRead >> i;
      fileRead >> j;
      fileRead >> health;
      fileRead >> maxHealth;
      fileRead >> size;
      fileRead >> name;

      if (Entity == "Plant") {
        this->game_field.at(i).at(j).putEntity(new Plant(health, maxHealth, size, name));
        continue;
      }

      fileRead >> starvation;
      fileRead >> starvationTime;
      fileRead >> speed;
      fileRead >> sex;

      if (Entity == "Animal") {
        this->game_field.at(i).at(j).putEntity(new Animal(health,
                                                          maxHealth,
                                                          size,
                                                          name,
                                                          starvation,
                                                          starvationTime,
                                                          speed,
                                                          sex));
      }

      if (Entity == "Herbivore") {
        this->game_field.at(i).at(j).putEntity(new Herbivore(health,
                                                             maxHealth,
                                                             size,
                                                             name,
                                                             starvation,
                                                             starvationTime,
                                                             speed,
                                                             sex));
      }

    }
  }

  fileRead.close();

}

void GameField::eat() {

  const int width = this->ROWS;
  const int height = this->COLUMNS;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      eatPlant(this->game_field.at(i).at(j));
      eatHerbivores(this->game_field.at(i).at(j));
    }
  }

}

void GameField::reproduction() {

  const int width = this->ROWS;
  const int height = this->COLUMNS;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      reproductionHerbivore(this->game_field.at(i).at(j));
      reproductionAnimal(this->game_field.at(i).at(j));
    }
  }

}

void GameField::die() {

  const int width = this->ROWS;
  const int height = this->COLUMNS;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      diePlant(this->game_field.at(i).at(j));
      dieHerbivores(this->game_field.at(i).at(j));
      dieAnimals(this->game_field.at(i).at(j));
    }
  }

}

void GameField::printStatus(string &path) {
  const int width = this->ROWS;
  const int height = this->COLUMNS;

  std::fstream fileWrite;
  fileWrite.open(path);

  if (fileWrite.is_open()) {

      for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {

          fileWrite << "Cell " << i << " " << j << "   ";
          if (!this->game_field.at(i).at(j).get<Plant>()->getName().empty()) {
            fileWrite << "Plant ";
            fileWrite << this->game_field.at(i).at(j).get<Plant>()->getHealth() << " ";
            fileWrite << this->game_field.at(i).at(j).get<Plant>()->getMaxHealth() << " ";
            fileWrite << this->game_field.at(i).at(j).get<Plant>()->getSize() << " ";
            fileWrite << this->game_field.at(i).at(j).get<Plant>()->getName();

            fileWrite << "   ";
          }


          if (!this->game_field.at(i).at(j).get<Herbivore>().empty()) {
            for (auto it : this->game_field.at(i).at(j).get<Herbivore>()) {
              fileWrite << "Herbivore ";
              fileWrite << it->getHealth() << " ";
              fileWrite << it->getMaxHealth() << " ";
              fileWrite << it->getSize() << " ";
              fileWrite << it->getStarvation() << " ";
              fileWrite << it->getStarvationTime() << " ";
              fileWrite << it->getSpeed() << " ";
              fileWrite << it->getSex() << " ";
              fileWrite << it->getName();

              fileWrite << "   ";
            }

          }


          if (!this->game_field.at(i).at(j).get<Animal>().empty()) {
            for (auto it : this->game_field.at(i).at(j).get<Animal>()) {
              fileWrite << "Animal ";
              fileWrite << it->getHealth() << " ";
              fileWrite << it->getMaxHealth() << " ";
              fileWrite << it->getSize() << " ";
              fileWrite << it->getStarvation() << " ";
              fileWrite << it->getStarvationTime() << " ";
              fileWrite << it->getSpeed() << " ";
              fileWrite << it->getSex() << " ";
              fileWrite << it->getName();

              fileWrite << "   ";
            }
          }
          fileWrite << endl;
        }
      }






  }

  fileWrite.close();


}


//
// Created by Egor Vasilkov on 25.11.22.
//

#ifndef TESTLAB2_GAMEFIELD_GAMEFIELD_H_
#define TESTLAB2_GAMEFIELD_GAMEFIELD_H_

#include "Cell.h"

class GameField {
 private:
  int ROWS;
  int COLUMNS;

 public:
  vector<vector<Cell>> game_field;

  GameField(int rows, int columns);

  Cell getCell(int rows, int columns) const;

  void readEntitiesFromFile(string &path);

  void eatPlant(Cell &currentCell);//

  void eatHerbivores(Cell &tempCell);

  void reproductionHerbivore(Cell &tempCell);

  void reproductionAnimal(Cell &tempCell);

  void diePlant(Cell &tempCell);

  void dieAnimals(Cell &tempCell);

  void dieHerbivores(Cell &tempCell);

  virtual void move();

  virtual void eat();

  virtual void reproduction();

  virtual void die();

  virtual void printStatus(string &path);




};

#endif //TESTLAB2_GAMEFIELD_GAMEFIELD_H_

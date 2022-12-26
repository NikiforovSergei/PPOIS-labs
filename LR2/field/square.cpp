//
// Created by artur on 11/27/22.
//

#include <algorithm>
#include "square.h"

Square::Square(int x, int y) : x(x), y(y) {

}
void Square::Add(const std::shared_ptr<Dweller>& dweller) {
  dwellers.push_back(dweller);
  population++;
}

void Square::Remove(const std::shared_ptr<Dweller>& dweller) {
  dwellers.erase(std::remove(dwellers.begin(), dwellers.end(), dweller), dwellers.end());
  population = dwellers.size(); // NOLINT(cppcoreguidelines-narrowing-conversions)
}

int Square::GetPopulation() {
  return population;
};

std::string Square::GetStringType(Dweller::Type type) {
  switch (type) {
	case Dweller::Type::Plant: return "Plant";
	case Dweller::Type::Herbivore: return "Herbivore";
	case Dweller::Type::Carnivore: return "Carnivore";
	default: return "None";
  }
}
void Square::Clear() {
  dwellers.clear();
}

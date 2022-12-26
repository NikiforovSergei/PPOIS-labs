//
// Created by artur on 11/27/22.
//

#include "field.h"
#include "../dwellers/plant.h"
#include <fstream>
using json = nlohmann::json;

Field::Field() = default;

void Field::Init(unsigned long rows, unsigned long columns) {
  Clear();
  _rows = rows;
  _columns = columns;
  for (int x = 0; x < rows; x++) {
	squares.emplace_back();
	for (int y = 0; y < columns; y++) {
	  squares[x].emplace_back(x, y);
	  squares[x][y].Add(std::make_shared<Plant>(50, 50, 100, "Василёк"));
	  squares[x][y].Add(std::make_shared<Herbivore>(50, 50, 100, "Динозаврик", 15, 15, 3, 5, 1));
	  squares[x][y].Add(std::make_shared<Carnivore>(40, 40, 120 - std::rand() % 60, "Лев", 20, 20, 5, 10,3));
	}
  }
}

Square *Field::GetRandomNeighbor(Square &square, const int max_length, bool include_self = false) {
  std::vector<std::vector<int>> directions;
  int length = int(std::rand() % max_length) + 1;
  if (include_self) directions.push_back({{0, 0}});
  if (square.x > length - 1) directions.push_back({-length, 0});
  if (square.x < _rows - length) directions.push_back({length, 0});
  if (square.y > length - 1) directions.push_back({0, -length});
  if (square.y < _columns - length) directions.push_back({0, length});
  if (!directions.size()) return &square;
  std::vector<int> direction = directions[std::rand() % directions.size()];
  return &squares[square.x + direction[0]][square.y + direction[1]];
}

json Field::ToJSON() {
  json state;
  for (const auto& row : squares) {
	for (const auto& square : row) {
	  for (int index = 0; index < square.population; index++) {
		auto& item = state[square.x][square.y][index];
		state[square.x][square.y][index] = {
		  {"type", Square::GetStringType(square.dwellers[index]->type)},
		  {"name", square.dwellers[index]->name},
		  {"lives", square.dwellers[index]->lives},
		  {"size", square.dwellers[index]->size},
		  {"minSize", square.dwellers[index]->min_size},
		  {"maxSize", square.dwellers[index]->max_size}
		};
		if (square.dwellers[index]->type == Dweller::Type::Plant) {
		  auto plant = std::static_pointer_cast<Plant>(square.dwellers[index]);
		  item["minLives"] = plant->min_lives;
		  item["maxLives"] = plant->max_lives;
		}
		if (square.dwellers[index]->type == Dweller::Type::Herbivore || square.dwellers[index]->type == Dweller::Type::Carnivore) {
		  auto animal = std::static_pointer_cast<Animal>(square.dwellers[index]);
		  item["lifetime"] = animal->lifetime;
		  item["maxLifetime"] = animal->max_lifetime;
		  item["stamina"] = animal->stamina;
		  item["maxStamina"] = animal->max_stamina;
		  item["sex"] = animal->sex == Animal::Sex::Male ? "Male" : "Female";
		  item["moveLength"] = animal->move_length;
		}
	  }
	}
  }
  return state;
}

void Field::Save() {
  json state = ToJSON();
  std::ofstream output("../visualization/state.json");
  output << std::setw(2) << state << std::endl;
}

void Field::Load() {
  Clear();
  std::ifstream input("../visualization/state.json");
  json state = json::parse(input);
  _rows = state.size();
  _columns = _rows ? state[0].size() : 0;
  for (int x = 0; x < _rows; x++) {
	for (int y = 0; y < _columns; y++) {
	  Square square(x, y);
	  for (const auto& j_dweller : state[x][y]) {
		auto string_type = j_dweller["type"].get<std::string>();
		if (string_type == Square::GetStringType(Square::GetType<Plant>())) {
		  auto plant = std::make_shared<Plant>(50, 50, 100, "ромашка");
		  square.dwellers.push_back(plant);
		}
	  }
	}
  }
}

void Field::Clear() {
  squares.clear();
}

void Field::Play() {
  for (int x = 0; x < _rows; x++) {
  	for (int y = 0; y < _columns; y++) {
	  auto& square = squares[x][y];
	  for (int index = 0; index < square.population; index++) {
		int initial_population = square.population;
		auto& dweller = square.dwellers[index];
		if (dweller->type == Dweller::Type::Plant) {
		  auto plant = std::static_pointer_cast<Plant>(dweller);
		  Reproduce(square, plant);
		  initial_population = square.population;
		  GetOld(square, plant);
		} else if (dweller->type == Dweller::Type::Herbivore || dweller->type == Dweller::Type::Carnivore) {
		  auto animal = std::static_pointer_cast<Animal>(dweller);
		  Reproduce(square, animal);
		  initial_population = square.population;
		  if (dweller->type == Dweller::Type::Herbivore) {
		  	Eat(square, std::static_pointer_cast<Herbivore>(dweller));
		  } else {
		  	Eat(square, std::static_pointer_cast<Carnivore>(dweller));
		  }
		  GetOld(square, animal);
		  // Ensure the animal is not dead
		  if (initial_population == square.population) {
			Move(square, animal);
		  }
		}
	    if (initial_population != square.population) index -= square.population - initial_population;
	  }
	}
  }
  for (int x = 0; x < _rows; x++) {
	for (int y = 0; y < _columns; y++) {
	  auto &square = squares[x][y];
	  for (int index = 0; index < square.population; index++) {
		int initial_population = square.population;
		auto &dweller = square.dwellers[index];
		if (dweller->type == Dweller::Type::Plant) {
		  auto plant = std::static_pointer_cast<Plant>(dweller);
		  Die(square, plant);
		} else if (dweller->type == Dweller::Type::Herbivore || dweller->type == Dweller::Type::Carnivore) {
		  auto animal = std::static_pointer_cast<Animal>(dweller);
		  Die(square, animal);
		}
		if (initial_population != square.population) index -= square.population - initial_population;
	  }
	}
  }
}

void Field::Reproduce(Square& square, const std::shared_ptr<Plant>& plant) {
  auto target_square = GetRandomNeighbor(square, 1, true);
  auto existing_plant = target_square->Find<Plant>(
	  [&](auto target) {
	return target->name == plant->name;
  });
  if (existing_plant.get()) {
	double phase = 6.0 * (existing_plant->size - existing_plant->min_size) / (existing_plant->max_size - existing_plant->min_size); // NOLINT(cppcoreguidelines-narrowing-conversions)
	existing_plant->lives = existing_plant->min_lives + (plant->max_lives - plant->min_lives) * phase; // NOLINT(cppcoreguidelines-narrowing-conversions)
  } else {
	if (target_square->population < max_population) {
	  target_square->Add(plant->Clone());
	}
  }
}

void Field::Reproduce(Square& square, const std::shared_ptr<Animal>& animal) {
  if (square.population >= max_population || animal->min_size == animal->size) return;
  auto target_animal = square.Find<Herbivore>([&](auto target) {
	return target->name == animal->name && target->sex == animal->OppositeSex() && target->min_size != target->size;
  });
  if (target_animal) {
	square.Add(animal->Clone());
  }
}

void Field::Move(Square& square, const std::shared_ptr<Animal>& animal) {
  auto target_square = GetRandomNeighbor(square, (int)animal->move_length);
  if (target_square->population >= max_population || target_square == &square) return;
  target_square->Add(animal);
  square.Remove(animal);
}


void Field::GetOld(Square& square, const std::shared_ptr<Plant>& plant) {
  if (plant->size < plant->max_size) {
	plant->size += (plant->max_size - plant->min_size) / 6;
	plant->lives *= (int)std::pow((double)plant->max_lives / plant->min_lives, 1.0 / 6);
	if (plant->size >= plant->max_size) {
	  plant->size = plant->max_size;
	}
  }
  plant->lives -= 10;
}
void Field::Die(Square& square, const std::shared_ptr<Plant>& plant) {
  if (plant->lives <= 0) {
	square.Remove(plant);
  }
}

void Field::GetOld(Square& square, const std::shared_ptr<Animal>& animal) {
  if (animal->size < animal->max_size) {
	animal->size += (animal->max_size - animal->min_size) / 6;
	if (animal->size > animal->max_size) animal->size = animal->max_size;
  } else {
	animal->lifetime--;
  }
}
void Field::Die(Square& square, const std::shared_ptr<Animal>& animal) {
  if (animal->lifetime <= 0 || animal->stamina < 0) {
  	square.Remove(animal);
  }
}


void Field::Eat(Square& square, const std::shared_ptr<Herbivore>& animal) {
  auto plant = square.Find<Plant>();
  if (plant) {
	plant->lives -= (int)animal->size / 2;
	double phase = (double)(animal->size - animal->min_size) / (animal->max_size - animal->min_size) * 0.5 + 0.5;
	animal->stamina = (int)(phase * animal->max_stamina);
  } else {
	animal->stamina--;
  }
}

void Field::Eat(Square& square, const std::shared_ptr<Carnivore>& animal) {
  auto herbivore = square.Find<Herbivore>([&](auto herbivore) {
	return herbivore->size < animal->size;
  });
  if (herbivore) {
	square.Remove(herbivore);
	double phase = (double)(animal->size - animal->min_size) / (animal->max_size - animal->min_size) * 0.5 + 0.5;
	animal->stamina = (int)(phase * animal->max_stamina);
  } else {
	animal->stamina--;
  }
}


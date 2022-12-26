//
// Created by artur on 11/27/22.
//

#ifndef LR2_FIELD_SQUARE_H_
#define LR2_FIELD_SQUARE_H_

#include <memory>
#include <vector>
#include <functional>
#include "field.h"
#include "../dwellers/plant.h"
#include "../dwellers/herbivore.h"
#include "../dwellers/carnivore.h"

class Square {
 private:
  int x, y, population = 0;
  std::vector<std::shared_ptr<Dweller>> dwellers;

  static std::string GetStringType(Dweller::Type type);

  template <typename T>
  requires std::is_same_v<T, Herbivore>
  static Dweller::Type GetType() { return Dweller::Type::Herbivore; }

  template <typename T>
  requires std::is_same_v<T, Carnivore>
  static Dweller::Type GetType() { return Dweller::Type::Carnivore; }

  template <typename T>
  requires std::is_same_v<T, Plant>
  static Dweller::Type GetType() { return Dweller::Type::Plant; }

  friend class Field;

 public:
  Square(int x, int y);
  void Add(const std::shared_ptr<Dweller>& dweller);
  void Remove(const std::shared_ptr<Dweller>& dweller);
  void Clear();
  int GetPopulation();


  template <class T = Dweller>
  std::shared_ptr<T> Find(std::function<bool(std::shared_ptr<T>)> predicate = [](auto dweller){ return true; }) {
	auto type = GetType<T>();
	for (auto& dweller : dwellers) {
	  if (dweller->GetType() == type && predicate(std::static_pointer_cast<T>(dweller))) {
		return std::static_pointer_cast<T>(dweller);
	  }
	}
	return nullptr;
  }

  template <class T = Dweller>
  std::vector<std::shared_ptr<T>> FindMany(std::function<bool(std::shared_ptr<T>)> predicate = [](auto dweller){ return true; }) {
	auto type = GetType<T>();
	std::vector<std::shared_ptr<T>> result;
	for (auto& dweller : dwellers) {
	  if (dweller->GetType() == type && predicate(std::static_pointer_cast<T>(dweller))) {
		result.push_back(std::static_pointer_cast<T>(dweller));
	  }
	}
	return result;
  }

};

#endif //LR2_FIELD_SQUARE_H_

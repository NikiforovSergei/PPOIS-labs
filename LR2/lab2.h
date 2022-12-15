#include <utility>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <windows.h>

class Organism {
public:
    virtual std::string type() = 0;

    virtual std::string superclass() = 0;

    virtual void iteration() = 0;

    virtual void nutrition() = 0;

    virtual int get_size() = 0;

    virtual int get_reprod() = 0;

    virtual bool is_alive() = 0;

    

};

class Plankton : public Organism {
    int age;
public:

    Plankton() {
        age = 5;
    }

   
    std::string superclass()  final {
        return "Pl";
    }

    std::string type() override {
        return "Pl";
    }

    void nutrition() override {

    }

    int get_size() override {
        return 1;
    }

    int get_reprod() override {
        return -1;
    }

    void iteration() override {
        age--;
    }

    bool is_alive() override {
        return age > 0;
    }

};

class Animal : public Organism {
protected:
    int hungry_points{}, reprod, age{};

public:
    Animal() {
        reprod = rand() % 2;
    }


    void nutrition() override {
        hungry_points += 10;
    }

    void iteration() override {
        hungry_points -= 10;
        age--;
    }

    int get_reprod() override {
        return reprod;
    }

    bool is_alive() override {
        return hungry_points > 0 && age > 0;
    }
};

class Predator : public Animal {

public:
    std::string superclass()  final {
        return "Predator";
    }
};

class Herbivore : public Animal {

public:
    std::string superclass()  final {
        return "Herbivore";
    }

};

class Shark : public Predator {

public:
    Shark() {
        hungry_points = 50;
        age = 7;
    }

    std::string type() override {
        return "Sh";
    }

    int get_size() override {
        return 2;
    }

};

class Predator_fish : public Predator {

public:
    Predator_fish() {
        hungry_points = 40;
        age = 6;
    }
    std::string type() override {
        return "Pr_f";
    }

    int get_size() override {
        return 1;
    }

};

class Whale : public Herbivore {

public:
    Whale() {
        hungry_points = 60;
        age = 9;
    }

    std::string type() override {
        return "Wh";
    }

    int get_size() override {
        return 3;
    }

};

class Herbivore_fish : public Herbivore {

public:
    Herbivore_fish() {
        hungry_points = 40;
        age = 6;
    }

    std::string type() override {
        return "H_f";
    }

    int get_size() override {
        return 1;
    }

};

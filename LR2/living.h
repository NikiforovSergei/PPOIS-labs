//
// Created by konstantin on 29.09.22.
//

#ifndef OCEAN_LIVING_H
#define OCEAN_LIVING_H

#include "../oceanfield/ocean.h"
#include <iostream>
class living;

enum sex{
    male,
    female
};

enum state{
    shark,// 0
    salmon,// 1
    clown,// 2
    puffer,// 3
    corals,// 4
    seaweed,// 5
    anchovys,//6
    kril //7
};

class living{
public:
    virtual std::string who() = 0;//проверка,кто в клетке

    virtual bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) = 0;//метод, чтобы есть

    virtual std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) = 0;//передвижение

    virtual bool propagate() = 0;//размножение

    virtual bool check_die() = 0;//проверка на смерть

    virtual std::string getInfo() = 0;

    virtual state getType() = 0;

    virtual int getSize() = 0;

    virtual sex getSex() = 0;

    virtual bool hide(const std::vector<std::vector<std::vector<class living*>>>&) = 0;

    virtual void setStop() = 0;

    virtual std::string getName() = 0;

    virtual void setPropogate() = 0;

    virtual std::pair<int,int> getPoint() = 0;

    virtual int getAmouont() = 0;

    virtual bool getCheckStep() = 0;

    virtual void setCheckStep() = 0;

    virtual living* die_from_other() = 0;

    virtual void victim(living*) = 0;

    virtual bool getPropogate_state() = 0;

    virtual int getAge() = 0;

};


class shark : public living{//акула
public:

    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    shark(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

    bool size_cell(const std::vector<living*>& cell);

private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::shark;

    state list_of_priority[4];

    int step = 0;

    bool propogate = false;

    bool stop = false;

    bool check_step = false;

    bool allow_propogate = true;

    living* alives = nullptr;

};

class salmon : public living{//лосось
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    salmon(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

    bool size_cell(const std::vector<living*>& cell);

private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::salmon;

    state list_of_priority[3];

    int step = 0;

    bool propogate = false;

    bool stop = false;

    bool check_step = false;

    bool allow_propogate = true;

    living* alives = nullptr;

};

class puffer : public living{//фугу
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    puffer(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setStop() override;

    std::string getName() override;

    std::pair<int,int> getPoint() override;

    void setPropogate() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

    bool size_cell(const std::vector<living*>& cell);

private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::puffer;

    state list_of_priority[4];

    int step = 0;

    bool propogate = false;

    bool stop = false;

    bool can_hide = false;

    std::pair <int,int> point_hide;

    bool check_step = false;

    bool allow_propogate = true;

    living* alives = nullptr;
};

class clown : public living{//рыба-клоун
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    clown(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

    bool size_cell(const std::vector<living*>& cell);

private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::clown;

    state list_of_priority[2];

    int step = 0;

    bool propogate = false;

    bool stop = false;

    bool can_hide = false;

    std::pair <int,int> point_hide;

    bool check_step = false;

    bool allow_propogate = true;

    living* alives = nullptr;
};

class anchovys : public living{//анчоус
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    anchovys(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

    bool size_cell(const std::vector<living*>& cell);

private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::anchovys;

    state list_of_priority[2];

    int step = 0;

    bool propogate = false;

    bool stop = false;

    bool can_hide = false;

    std::pair <int,int> point_hide;

    bool check_step = false;

    bool allow_propogate = true;

    living* alives = nullptr;

};

class kril : public living{
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    kril(int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

    bool size_cell(const std::vector<living*>& cell);

    bool check_kril();

private:

    std::string name;

    const state type = state::kril;

    int hp = 100;

    int step;

    std::pair<int,int> points;

    bool stop = false;

    bool check_step = false;

};

class corals : public living{
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    corals(const int[]);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setPropogate() override;

    std::string getName() override;

    void setStop() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

private:
    int amount;

    int step = 0;

    std::string name;

    const state type = state::corals;
};

class seaweed : public living{
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    seaweed(const int[]);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    void setPropogate() override;

    std::string getName() override;

    void setStop() override;

    std::pair<int,int> getPoint() override;

    int getAmouont() override;

    bool getCheckStep() override;

    void setCheckStep() override;

    living* die_from_other() override;

    void victim(living*) override;

    bool getPropogate_state() override;

    int getAge() override;

private:
    int amount;

    int step = 0;

    std::string name;

    const state type = state::seaweed;

};
#endif //OCEAN_LIVING_H

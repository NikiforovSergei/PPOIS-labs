//
// Created by konstantin on 29.09.22.
//
#include "living.h"

corals::corals(const int temp[]) {
    this->amount = temp[2];
    this->name = " ";

}

std::string corals::who() {return "кораллы "+name;}


bool corals::propagate() {
    return false;
}

bool corals::check_die() {
    return false;
}

std::string corals::getInfo() {return "\tHP: "+std::to_string(this->amount);}


state corals::getType() {
    return state::corals;
}

bool corals::eat(living* ,const std::vector<std::vector<std::vector<class living*>>>&) {
    return false;
}

bool corals::hide(const std::vector<std::vector<std::vector<class living*>>>&) {
    amount -= 20;
    return false;
}

std::pair<int, int> corals::go(const std::vector<std::vector<std::vector<struct living *>>> &) {
    step++;
    if(step % 10 == 0){
        amount = -1;
    }
    std::pair<int,int> points(0,0);
    return points;
}

std::pair<int, int> corals::see(const std::vector<std::vector<std::vector<struct living *>>> &) {
    return std::pair<int, int>();
}

int corals::getSize() {
    return 0;
}
void corals::victim(living *alive) {
}

living* corals::die_from_other() {
    return nullptr;
}


sex corals::getSex() {
    return female;
}

void corals::setPropogate() {

}

std::string corals::getName() {
    return std::string();
}

void corals::setStop() {

}

std::pair<int, int> corals::getPoint() {
    return std::pair<int, int>();
}

int corals::getAmouont() {
    return this->amount;
}

bool corals::getCheckStep() {
    return false;
}

void corals::setCheckStep() {
}

bool corals::getPropogate_state() {
    return false;
}

int corals::getAge() {
    return 0;
}

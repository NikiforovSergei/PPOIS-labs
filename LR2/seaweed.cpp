//
// Created by konstantin on 29.09.22.
//
#include "living.h"

seaweed::seaweed(const int temp[]) {
    this->amount = temp[2];
    this->name = " ";
}

std::string seaweed::who() {return "водоросли "+name;}

std::pair<int,int> seaweed::go(const std::vector<std::vector<std::vector<class living*>>>& field) {

    step++;
    if(step % 10 == 0){
        amount = -1;
    }
    std::pair<int,int> points(0,0);
    return points;
}

bool seaweed::check_die() {
    return true;
}

std::string seaweed::getInfo() {return "\tHP: "+std::to_string(this->amount);}

state seaweed::getType() {
    return state::seaweed;
}

bool seaweed::propagate() {
    return false;
}

bool seaweed::hide(const std::vector<std::vector<std::vector<class living*>>>&) {
    amount -= 20;
    return false;
}

bool seaweed::eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) {
return false;
}

std::pair<int, int> seaweed::see(const std::vector<std::vector<std::vector<struct living *>>> &) {
    return std::pair<int, int>();
}

int seaweed::getSize() {
    return 0;
}

sex seaweed::getSex() {
    return female;
}

void seaweed::setPropogate() {

}

std::string seaweed::getName() {
    return std::string();
}

void seaweed::setStop() {

}

std::pair<int, int> seaweed::getPoint() {
    return std::pair<int, int>();
}

int seaweed::getAmouont() {
    return this->amount;
}

void seaweed::setCheckStep() {

}

bool seaweed::getCheckStep() {
    return false;
}
void seaweed::victim(living *alive) {
}

living* seaweed::die_from_other() {
    return nullptr;
}

bool seaweed::getPropogate_state() {
    return false;
}

int seaweed::getAge() {
    return 0;
}


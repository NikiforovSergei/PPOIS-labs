//
// Created by konstantin on 29.09.22.
//
#include "living.h"


bool kril::size_cell(const std::vector<living*>& cell){
    int counter = 0;
    for(auto & alive: cell){
        if(alive != nullptr){
            counter++;
        }
    }

    if(counter == 4){
        return true;
    }else{
        return false;
    }
}

kril::kril(int temp[]) {
    points.first = temp[0];
    points.second = temp[1];
    this->hp = temp[2];
    this->name = "  ";

}

bool kril::propagate() {
    hp = 100;

    return true;
}

std::string kril::who() {return "криль  "+name;}

bool kril::check_die() {
    return hp < 0;
}

std::string kril::getInfo() {return "\tHP: "+ std::to_string(this->hp);}

state kril::getType() {
    return state::kril;
}

bool kril::hide(const std::vector<std::vector<std::vector<struct living *>>> &) {
    hp-=10;
    return false;
}

bool kril::eat(living *, const std::vector<std::vector<std::vector<struct living *>>> &) {
    return false;
}

std::pair<int, int> kril::go(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;
    step++;
    hp-=20;
    point = see(field);
    points.first = point.first;
    points.second = point.second;
    check_step = true;

    return point;

}

std::pair<int, int> kril::see(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    srand(time(NULL));
    std::pair<int,int> point;

    while(true) {
        int rands = rand() % 5;
        bool kril_cell = false;

        if(rands == 0) {
            if (points.first > 0) {
                for(auto & alive : field.at(points.first-1).at(points.second)){
                    if (size_cell(field.at(points.first-1).at(points.second))){
                        break;
                    }

                    for(size_t i = 0; i < field.at(points.first-1).at(points.second).size(); i++){
                        if(field.at(points.first-1).at(points.second).at(i) == nullptr){
                            continue;
                        }
                        if(field.at(points.first-1).at(points.second).at(i)->getType() == state::kril){
                            kril_cell = true;
                            break;
                        }
                    }

                    if(alive != nullptr){
                        if(alive->getType() == state::kril && step % 4 == 0){
                            if(alive->getSize() < 100) {
                                alive->propagate();
                            }
                        }
                    }

                    if(kril_cell){
                        kril_cell = false;
                        break;
                    }
                    point.first = points.first - 1;
                    point.second = points.second;
                    return point;
                }
            }
        }
        if(rands == 1) {
            rands = rand() % 3;
            if (points.second > 0) {
                if (rands == 0) {
                    if (points.first > 0) {
                        for(auto & alive : field.at(points.first-1).at(points.second-1)){
                            if (size_cell(field.at(points.first-1).at(points.second-1))){
                                break;
                            }
                            for(size_t i = 0; i < field.at(points.first-1).at(points.second-1).size(); i++){
                                if(field.at(points.first-1).at(points.second-1).at(i) == nullptr){
                                    continue;
                                }
                                if(field.at(points.first-1).at(points.second-1).at(i)->getType() == state::kril){
                                    kril_cell = true;
                                    break;
                                }
                            }
                            if(alive != nullptr){
                                if(alive->getType() == state::kril && step % 4 == 0){
                                    if(alive->getSize() < 100) {
                                        alive->propagate();
                                    }
                                }
                            }

                            if(kril_cell){
                                kril_cell = false;
                                break;
                            }
                            point.first = points.first - 1;
                            point.second = points.second - 1;
                            return point;
                        }
                    }
                }

                if (rands == 1) {
                    if (points.first < field.size() - 1) {
                        for(auto & alive : field.at(points.first+1).at(points.second-1)){
                            if (size_cell(field.at(points.first+1).at(points.second-1))){
                                break;
                            }
                            for(size_t i = 0; i < field.at(points.first+1).at(points.second-1).size(); i++){
                                if(field.at(points.first+1).at(points.second-1).at(i) == nullptr){
                                    continue;
                                }
                                if(field.at(points.first+1).at(points.second-1).at(i)->getType() == state::kril){
                                    kril_cell = true;
                                    break;
                                }
                            }
                            if(alive != nullptr){
                                if(alive->getType() == state::kril && step % 4 == 0){
                                    if(alive->getSize() < 100) {
                                        alive->propagate();
                                    }
                                }
                            }

                            if(kril_cell){
                                kril_cell = false;
                                break;
                            }
                            point.first = points.first + 1;
                            point.second = points.second - 1;
                            return point;
                        }
                    }
                }

                if (rands == 2) {
                    if (points.second > 0) {
                        for(auto & alive : field.at(points.first).at(points.second-1)){
                            if (size_cell(field.at(points.first).at(points.second-1))){
                                break;
                            }
                            for(size_t i = 0; i < field.at(points.first).at(points.second-1).size(); i++){
                                if(field.at(points.first).at(points.second-1).at(i) == nullptr){
                                    continue;
                                }
                                if(field.at(points.first).at(points.second-1).at(i)->getType() == state::kril){
                                    kril_cell = true;
                                    break;
                                }
                            }
                            if(alive != nullptr){
                                if(alive->getType() == state::kril && step % 4 == 0){
                                    if(alive->getSize() < 100) {
                                        alive->propagate();
                                    }
                                }
                            }

                            if(kril_cell){
                                kril_cell = false;
                                break;
                            }

                            point.first = points.first;
                            point.second = points.second - 1;
                            return point;
                        }
                    }
                }
            }
        }

        if(rands == 2) {
            if (points.first < field.size() - 1) {
                for(auto & alive : field.at(points.first+1).at(points.second)){
                    if (size_cell(field.at(points.first+1).at(points.second))){
                        break;
                    }
                    for(size_t i = 0; i < field.at(points.first+1).at(points.second).size(); i++){
                        if(field.at(points.first+1).at(points.second).at(i) == nullptr){
                            continue;
                        }
                        if(field.at(points.first+1).at(points.second).at(i)->getType() == state::kril){
                            kril_cell = true;
                            break;
                        }
                    }
                    if(alive != nullptr){
                        if(alive->getType() == state::kril && step % 4 == 0){
                            if(alive->getSize() < 100) {
                                alive->propagate();
                            }
                        }
                    }

                    if(kril_cell){
                        kril_cell = false;
                        break;
                    }

                    point.first = points.first + 1;
                    point.second = points.second;
                    return point;
                }
            }
        }

        if(rands == 3) {
            rands = rand() % 3;
            if (points.second < field.at(0).size() - 1) {
                if (rands == 0) {
                    if (points.first > 0) {
                        for(auto & alive : field.at(points.first-1).at(points.second+1)){
                            if (size_cell(field.at(points.first-1).at(points.second+1))){
                                break;
                            }
                            for(size_t i = 0; i < field.at(points.first-1).at(points.second+1).size(); i++){
                                if(field.at(points.first-1).at(points.second+1).at(i) == nullptr){
                                    continue;
                                }
                                if(field.at(points.first-1).at(points.second+1).at(i)->getType() == state::kril){
                                    kril_cell = true;
                                    break;
                                }
                            }
                            if(alive != nullptr){
                                if(alive->getType() == state::kril && step % 4 == 0){
                                    if(alive->getSize() < 100) {
                                        alive->propagate();
                                    }
                                }
                            }

                            if(kril_cell){
                                kril_cell = false;
                                break;
                            }
                            point.first = points.first - 1;
                            point.second = points.second + 1;
                            return point;
                        }
                    }
                }

                if (rands == 1) {
                    if (points.first < field.size() - 1) {
                        for(auto & alive : field.at(points.first+1).at(points.second+1)){
                            if (size_cell(field.at(points.first+1).at(points.second+1))){
                                break;
                            }
                            for(size_t i = 0; i < field.at(points.first+1).at(points.second+1).size(); i++){
                                if(field.at(points.first+1).at(points.second+1).at(i) == nullptr){
                                    continue;
                                }
                                if(field.at(points.first+1).at(points.second+1).at(i)->getType() == state::kril){
                                    kril_cell = true;
                                    break;
                                }
                            }
                            if(alive != nullptr){
                                if(alive->getType() == state::kril && step % 4 == 0){
                                    if(alive->getSize() < 100) {
                                        alive->propagate();
                                    }
                                }
                            }

                            if(kril_cell){
                                kril_cell = false;
                                break;
                            }

                            point.first = points.first + 1;
                            point.second = points.second + 1;
                            return point;
                        }
                    }
                }

                if (rands == 2) {
                    if (points.second < field.at(0).size() - 1) {
                        for(auto & alive : field.at(points.first).at(points.second + 1)){
                            if (size_cell(field.at(points.first).at(points.second+1))){
                                break;
                            }
                            for(size_t i = 0; i < field.at(points.first).at(points.second+1).size(); i++){
                                if(field.at(points.first).at(points.second+1).at(i) == nullptr){
                                    continue;
                                }
                                if(field.at(points.first).at(points.second+1).at(i)->getType() == state::kril){
                                    kril_cell = true;
                                    break;
                                }
                            }
                            if(alive != nullptr){
                                if(alive->getType() == state::kril && step % 4 == 0){
                                    if(alive->getSize() < 100) {
                                        alive->propagate();
                                    }
                                }
                            }
                            if(kril_cell){
                                kril_cell = false;
                                break;
                            }
                            point.first = points.first;
                            point.second = points.second + 1;
                            return point;
                        }
                    }
                }
            }
        }

        if(rands == 4){
            return points;
        }
    }
}

int kril::getSize() {
    return 0;
}

sex kril::getSex() {
    return female;
}

void kril::setStop() {

}

std::string kril::getName() {
    return std::string();
}

void kril::setPropogate() {

}

std::pair<int, int> kril::getPoint() {
    return points;
}

int kril::getAmouont() {
    return 0;
}

bool kril::getCheckStep() {
    return check_step;
}

void kril::setCheckStep() {
    this->check_step = false;
}

void kril::victim(living*) {
}

living* kril::die_from_other() {
    return nullptr;
}

bool kril::getPropogate_state() {
    return false;
}

int kril::getAge() {
    return 0;
}



//
// Created by konstantin on 29.09.22.
//
#include "living.h"

bool shark::size_cell(const std::vector<living*>& cell){
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

shark::shark(std::string name, int temp[]) {
    this->name = name;
    this->points.first = temp[0];
    this->points.second = temp[1];
    this->age = temp[2];
    if (temp[3] == 0) {
        this->living_sex = male;
    } else {
        this->living_sex = female;
    }
    this->size = temp[4];
    this->hunger = temp[5];

    this->list_of_priority[0] = state::salmon;
    this->list_of_priority[1] = state::puffer;
    this->list_of_priority[2] = state::clown;
    this->list_of_priority[3] = state::anchovys;
}

std::string shark::who() {return "акула " + name;}

bool shark::eat(living* who, const std::vector<std::vector<std::vector<class living*>>>& file) {

    if(!who->getCheckStep()) {
        if (who->getType() == list_of_priority[0]) {
            victim(who);
            hunger += 20;
            std::cout << who->who() << " was eaten("<<std::endl;
            return true;
        } else {
            if (who->hide(file)) {
                return false;
            } else {
                hunger += 10;
                victim(who);
                std::cout << who->who() << " was eaten("<<std::endl;
                return true;
            }
        }
    }else{
        return false;
    }

}

std::pair<int,int> shark::go(const std::vector<std::vector<std::vector<class living*>>>& field) {

    std::pair<int,int> point;
    step++;
    check_step = true;

    if (step % 2 == 0) {
        age++;
    }
    if(age == 0){
        return points;
    }


    if(step % 3 == 0){
        allow_propogate = true;
    }

    if(stop){
        point.first = points.first;
        point.second = points.second;
    }else {
        point = see(field);
        hunger -= 5;
        points.first = point.first;
        points.second = point.second;
    }
    return point;

}

bool shark::propagate() {
    return this->allow_propogate;
}

bool shark::check_die() {
    if(hunger < 10){
        std::cout<<who()<<" died of hunger"<<std::endl;
        return true;
    }else if(age >= 25){
        if( rand()%2 == 0){
            std::cout<<who()<<" just died"<<std::endl;
            return true;
        }else{
            return false;
        }
    }else{
        return  false;
    }
}

std::string shark::getInfo() {
    return "Age: " + std::to_string(this->age) + "\tSize: " + std::to_string(this->size)+
           "\tSex: " + std::to_string(this->living_sex) + "\tHunger: " + std::to_string(this->hunger);
}

state shark::getType() {
    return state::shark;
}

int shark::getSize() { return size;}

sex shark::getSex() {return living_sex;}

std::pair<int, int> shark::see(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    srand(time(NULL));
    std::pair<int,int> point;

    for (auto &alive: field.at(points.first).at(points.second)) {
        if (size_cell(field.at(points.first).at(points.second))){
            break;
        }
        if(alive == nullptr){
            continue;
        }
        if (alive->getType() == state::shark && alive != this){
            if(alive->getSex() != living_sex && age >= 10 && alive->getAge() >= 10){
                point.first = points.first;
                point.second = points.second;
                if(allow_propogate && alive->propagate()) {
                    alive->setStop();
                    allow_propogate = false;
                    return point;

                }
            }
        }
    }

    if (points.first > 0) {
        for (auto &alive: field.at(points.first - 1).at(points.second)) {
            if (size_cell(field.at(points.first-1).at(points.second))){
                break;
            }
            if(alive == nullptr){
                continue;
            }
            if (alive->getType() == state::shark && alive != this){
                if(alive->getSex() != living_sex && age >= 10 && alive->getAge() >= 10){
                    point.first = points.first - 1;
                    point.second = points.second;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }

        }
    }

    if (points.second > 0) {
        for (auto &alive: field.at(points.first).at(points.second - 1)) {
            if (size_cell(field.at(points.first).at(points.second-1))){
                break;
            }
            if(alive == nullptr){
                continue;
            }
            if (alive->getType() == state::shark && alive != this){
                if(alive->getSex() != living_sex && age >= 10 && alive->getAge() >= 10){
                    point.first = points.first ;
                    point.second = points.second - 1;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }
        }
    }

    if (points.first < field.size() - 1) {
        for (auto &alive: field.at(points.first + 1).at(points.second)) {
            if (size_cell(field.at(points.first+1).at(points.second))){
                break;
            }
            if(alive == nullptr){
                continue;
            }
            if (alive->getType() == state::shark && alive != this){
                if(alive->getSex() != living_sex && age >= 10 && alive->getAge() >= 10){
                    point.first = points.first + 1;
                    point.second = points.second;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }
        }
    }

    if (points.second < field.at(0).size()-1) {
        for (auto &alive: field.at(points.first).at(points.second + 1)) {
            if (size_cell(field.at(points.first).at(points.second+1))){
                break;
            }
            if(alive == nullptr){
                continue;
            }
            if (alive->getType() == state::shark && alive != this){
                if(alive->getSex() != living_sex && age >= 10 && alive->getAge() >= 10){
                    point.first = points.first;
                    point.second = points.second + 1;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (auto &alive: field.at(points.first).at(points.second)) {
            if (size_cell(field.at(points.first).at(points.second))){
                break;
            }
            if(alive == nullptr){
                continue;
            }
            if (alive->getType() == list_of_priority[i]){
                if(this->size >= alive->getSize()){
                    point.first = points.first;
                    point.second = points.second;
                    if(eat(alive, field)){
                        return point;
                    }
                }
            }
        }

        if (points.first > 0) {
            for (auto &alive: field.at(points.first - 1).at(points.second)) {
                if (size_cell(field.at(points.first-1).at(points.second))){
                    break;
                }
                if(alive == nullptr){
                    continue;
                }
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
                        point.first = points.first - 1;
                        point.second = points.second;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }

        if (points.second > 0) {
            for (auto &alive: field.at(points.first).at(points.second - 1)) {
                if (size_cell(field.at(points.first).at(points.second-1))){
                    break;
                }
                if(alive == nullptr){
                    continue;
                }
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
                        point.first = points.first;
                        point.second = points.second - 1;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }

            }
        }

        if (points.first < field.size() - 1) {
            for (auto &alive: field.at(points.first + 1).at(points.second)) {
                if (size_cell(field.at(points.first+1).at(points.second))){
                    break;
                }
                if(alive == nullptr){
                    continue;
                }
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
                        point.first = points.first + 1;
                        point.second = points.second;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }

        if (points.second < field.at(0).size() - 1) {
            for (auto &alive: field.at(points.first).at(points.second + 1)) {
                if (size_cell(field.at(points.first).at(points.second+1))){
                    break;
                }
                if(alive == nullptr){
                    continue;
                }
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
                        point.first = points.first;
                        point.second = points.second + 1;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }
    }


    while(true) {
        int rands = rand() % 5;

        if(rands == 0) {
            if (points.first > 0) {
                for (auto &alive: field.at(points.first - 1).at(points.second)) {
                    if (alive == nullptr) {
                        continue;
                    }
                }
                if (!size_cell(field.at(points.first-1).at(points.second))){
                    point.first = points.first - 1;
                    point.second = points.second;
                    return point;
                }
            }
        }

        if(rands == 1) {
            if (points.second > 0) {
                for (auto &alive: field.at(points.first).at(points.second - 1)) {
                    if (alive == nullptr) {
                        continue;
                    }
                }
                if (!size_cell(field.at(points.first).at(points.second-1))){
                    point.first = points.first ;
                    point.second = points.second - 1;
                    return point;
                }
            }
        }

        if(rands == 2) {
            if (points.first < field.size() - 1) {
                for (auto &alive: field.at(points.first + 1).at(points.second)) {
                    if (alive == nullptr) {
                        continue;
                    }
                }
                if (!size_cell(field.at(points.first+1).at(points.second))) {
                    point.first = points.first + 1;
                    point.second = points.second;
                    return point;
                }
            }
        }

        if(rands == 3) {
            if (points.second < field.at(0).size() - 1) {
                for (auto &alive: field.at(points.first).at(points.second+1)) {
                    if (alive == nullptr) {
                        continue;
                    }
                }
                if (!size_cell(field.at(points.first).at(points.second+1))){
                    point.first = points.first;
                    point.second = points.second + 1;
                    return point;
                }
            }
        }

        if(rands == 4){
            return points;
        }
    }
}


bool shark::hide(const std::vector<std::vector<std::vector<class living*>>>& file) {
    return false;
}

void shark::setStop() {
    this->propogate = true;
    this->stop = true;
}

std::string shark::getName() {
    return this->name;
}

void shark::setPropogate() {
    this->allow_propogate = false;
    this->propogate = false;
    this->stop = false;
}

std::pair<int, int> shark::getPoint() {
    return points;
}

int shark::getAmouont() {
    return 0;
}

bool shark::getCheckStep() {
    return check_step;
}

void shark::setCheckStep() {
    this->check_step = false;
}

living *shark::die_from_other() {
    return this->alives;
}

void shark::victim(living * alives) {
    this->alives = alives;
}

bool shark::getPropogate_state() {
    return this->propogate;
}

int shark::getAge() {
    return this->age;
}

#include <utility>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <windows.h>
#include "lab2.h"





class Cell {

public:

    std::vector<Organism*>organisms;

    Cell() {
        organisms.resize(4);
    };


    void push(Organism* org) {
        if (org->type() == "Pl")
            for (size_t i = 0; i < organisms.size(); i++)
                if (organisms.at(i) && organisms.at(i)->type() == "Pl") {
                    delete organisms.at(i);
                    organisms.at(i) = org;
                    return;
                }

        for (Organism*& o : organisms)
            if (o == nullptr) {
                o = org;
                return;
            }
    }

    void iteration() {
        for (size_t i = 0; i < organisms.size(); i++) {
            if (organisms.at(i)) organisms.at(i)->iteration();
        }
    }

    void death() {
        for (size_t i = 0; i < organisms.size(); i++) {
            if (organisms.at(i) && !organisms.at(i)->is_alive()) {
                delete organisms.at(i);
                organisms.at(i) = nullptr;
            }
        }
    }

    


    void reproduction() {
        if (!is_full()) {

            if (contains("Wh").size() > 1) {

                bool male = false, female = false;
                for (int i : contains("Wh")) {
                    if (organisms.at(i)->get_reprod() == 0) male = true;
                    else if (organisms.at(i)->get_reprod() == 1) female = true;
                }

                if (male && female) {
                    auto* org = new Whale; push(org);
                }

            }

            if (contains("Sh").size() > 1) {

                bool male = false, female = false;
                for (int i : contains("Sh")) {
                    if (organisms.at(i)->get_reprod() == 0) male = true;
                    else if (organisms.at(i)->get_reprod() == 1) female = true;
                }

                if (male && female) {
                    auto* org = new Shark; push(org);
                }

            }

            if (contains("Pr_f").size() > 1) {

                bool male = false, female = false;
                for (int i : contains("Pr_f")) {
                    if (organisms.at(i)->get_reprod() == 0) male = true;
                    else if (organisms.at(i)->get_reprod() == 1) female = true;
                }

                if (male && female) {
                    auto* org = new Predator_fish; push(org);
                }

            }

            if (contains("H_f").size() > 1) {

                bool male = false, female = false;
                for (int i : contains("H_f")) {
                    if (organisms.at(i)->get_reprod() == 0) male = true;
                    else if (organisms.at(i)->get_reprod() == 1) female = true;
                }

                if (male && female) {
                    auto* org = new Herbivore_fish; push(org);
                }

            }

        }
    }

   

    void nutrition() {

        std::vector<int> pl, herbivore, predator;
        for (int i = 0; i < organisms.size(); i++) {
            if (organisms.at(i)) {
                organisms.at(i)->iteration();
                if (organisms.at(i)->superclass() == "Pl") pl.push_back(i);
                else if (organisms.at(i)->superclass() == "Herbivore") herbivore.push_back(i);
                else if (organisms.at(i)->superclass() == "Predator") predator.push_back(i);
            }
        }

       

        if (!pl.empty() && !herbivore.empty()) { //
            delete organisms.at(pl.at(0));
            organisms.at(pl.at(0)) = nullptr;
            organisms.at(herbivore.at(0))->nutrition();
        }

        
        if (!herbivore.empty() && !predator.empty()) {
            if (herbivore.size() == 2 && predator.size() == 2) {
                for (int i : herbivore) {
                    for (int j : predator) {
                        if (organisms.at(i)->get_size() <= organisms.at(j)->get_size()) {
                            delete organisms.at(i);
                            organisms.at(i) = nullptr;
                            organisms.at(j)->nutrition();
                            for (int m = 0; m < predator.size(); m++) {
                                if (predator.at(m) == j)
                                    predator.erase(predator.begin() + m);
                            }
                            for (int m = 0; m < herbivore.size(); m++) {
                                if (herbivore.at(m) == j)
                                    herbivore.erase((herbivore.begin() + m));
                            }
                        }
                        break;
                    }
                }
            }
            else {
                bool found = false;
                for (int i : herbivore) {
                    for (int j : predator) {
                        if (organisms.at(i)->get_size() <= organisms.at(j)->get_size()) {
                            delete organisms.at(i);
                            organisms.at(i) = nullptr;
                            organisms.at(j)->nutrition();
                            found = true;
                        }
                        if (found) break;
                    }
                    if (found) break;
                }
            }
        }
    }


    std::vector<int> contains(const std::string& type) {
        std::vector<int> out;
        for (size_t i = 0; i < organisms.size(); i++)
            if (organisms.at(i) && organisms.at(i)->type() == type)
                out.push_back(i);
        return out;
    }

    bool is_full() {
        for (Organism*& o : organisms)
            if (!o) return false;
        return true;
    }
};


class Field {
    std::vector<std::vector<Cell>> field;
public:
    Field() = default;

    Field(int m, int n) {

        field.clear();

        field.resize(n);
        for (size_t i = 0; i < n; i++) {
            field.at(i).resize(m);
        }
    }

    void print_field() {

        std::cout << "-----------------------------------------------------------------------------------------" << "\n";
        for (std::vector<Cell>& line : field) {

            for (Cell cell : line) {
                if (cell.organisms[0]) std::cout << std::setw(5) << cell.organisms[0]->type();
                else std::cout << std::setw(5) << 0; std::cout << " ";

                if (cell.organisms[1]) std::cout << std::setw(5) << cell.organisms[1]->type();
                else std::cout << std::setw(5) << 0; std::cout << "\t|\t";
            }

            std::cout << "\n";


            for (Cell& cell : line) {
                if (cell.organisms[2]) std::cout << std::setw(5) << cell.organisms[2]->type();
                else std::cout << std::setw(5) << 0; std::cout << " ";

                if (cell.organisms[3]) std::cout << std::setw(5) << cell.organisms[3]->type();
                else std::cout << std::setw(5) << 0; std::cout << "\t|\t";
            }
            std::cout << "\n";



            std::cout << "-----------------------------------------------------------------------------------------" << "\n";
        }
        Sleep(200);
        //system("cls");
        std::cout << "\n\n";


    }

    std::pair<int, int> get_size() {
        return { field.size(), field.at(0).size() };
    }


    void set(Organism* organism, int x, int y) {
       
        field.at(x).at(y).push(organism);
    }

   

    void plankton_reproduction() {
        for (size_t i = 0; i < field.size(); i++) {
            for (size_t j = 0; j < field.at(i).size(); j++) {

                if (!field.at(i).at(j).contains("Pl").empty()) {
                    auto* pl = new Plankton();

                    int attempt = 0;
                    while (true) {

                        if (attempt == 50) {
                            field.at(i).at(j).push(pl);
                            break;
                        }
                        attempt++;

                        int move_x = rand() % 3 - 1, move_y = 0;

                        while (i + move_x < 0 || i + move_x >= field.size())
                            move_x = rand() % 3 - 1;

                        if (move_x == 0) {
                            move_y = rand() % 3 - 1;
                            while (j + move_y < 0 || j + move_y >= field.at(i).size())
                                move_y = rand() % 3 - 1;
                        }

                        if (!field.at(i + move_x).at(j + move_y).is_full())
                        {
                            field.at(i + move_x).at(j + move_y).push(pl);
                            break;
                        }
                    }
                }

            }
        }
    }

    

    void move() {

        std::vector<Organism*> used;

        for (size_t i = 0; i < field.size(); i++) {
            for (size_t j = 0; j < field.at(i).size(); j++) {

                for (size_t n = 0; n < field.at(i).at(j).organisms.size(); n++) {
                    if (field.at(i).at(j).organisms.at(n) && field.at(i).at(j).organisms.at(n)->superclass() != "Pl") {

                        /* Проверка передвигалась ли данная рыба за эту итерцию*/
                        bool used_ptr = false;
                        for (Organism*& o : used)
                            if (o == field.at(i).at(j).organisms.at(n))
                                used_ptr = true;
                        if (used_ptr) break;

                        used.push_back(field.at(i).at(j).organisms.at(n));

                        int attempt = 0;
                        while (true) {

                            if (attempt == 10) break;
                            attempt++;

                            int move_x = rand() % 3 - 1, move_y = 0;

                            while (i + move_x < 0 || i + move_x >= field.size())
                                move_x = rand() % 3 - 1;

                            if (move_x == 0) {
                                move_y = rand() % 3 - 1;
                                while (j + move_y < 0 || j + move_y >= field.at(i).size())
                                    move_y = rand() % 3 - 1;
                            }

                            if (!field.at(i + move_x).at(j + move_y).is_full())
                            {

                                for (size_t m = 0; m < field.at(i + move_x).at(j + move_y).organisms.size(); m++) {
                                    if (!field.at(i + move_x).at(j + move_y).organisms.at(m)) {

                                        field.at(i + move_x).at(j + move_y).organisms.at(m) = field.at(i).at(j).organisms.at(n);
                                        field.at(i).at(j).organisms.at(n) = nullptr;
                                        break;

                                    }
                                }

                                break;

                            }
                        }

                    }
                }

            }
        }

    }

    bool stop() {
        for (std::vector<Cell>& line : field)
            for (Cell& cell : line)
                for (Organism*& o : cell.organisms)
                    if (o && o->superclass() != "Pl")
                        return false;

        return true;
    }

    void iteration(bool more_info = false) {

        /* Передвижение */
        move();

        if (more_info) {
            std::cout << "After move\n";
            print_field();
        }

        /* Питание */
        for (std::vector<Cell>& line : field)
            for (Cell& cell : line)
                cell.nutrition();

        if (more_info) {
            std::cout << "After nutrition\n";
            print_field();
        }

        /*Размножение*/
        plankton_reproduction();
        for (std::vector<Cell>& line : field)
            for (Cell& cell : line)
                cell.reproduction();

        if (more_info) {
            std::cout << "After reproduction\n";
            print_field();
        }

        /* Умирание от старости или от голода */
        for (std::vector<Cell>& line : field)
            for (Cell& cell : line)
                cell.death();

        if (more_info) {
            std::cout << "After death\n";
            print_field();
        }

    }
};

class ReadFromFile {
    std::string file_name;

    std::vector<std::string> read() {
        std::vector<std::string>input;
        std::string line;

        std::ifstream in;
        in.open(file_name);
        if (in.is_open())
        {
            while (getline(in, line))
            {
                input.push_back(line);
            }
        }
        in.close();
        return input;
    }
public:
    ReadFromFile() = default;
    explicit ReadFromFile(std::string file_name) :file_name(std::move(file_name)) {};

    void random_fill_field(Field& f)
    {
       std::vector<std::string>input = read();

        std::stringstream ss; ss << input.at(0);
        int n, m; ss >> m >> n; ss.clear();
        m = 2 + rand()%2;
        n = 2 + rand()%2; 
        f = Field(m, n); 
        for (int i = 1; i < input.size(); i++) {
            std::string org_name;
            ss << input.at(i);
            while (ss >> org_name) {
                if (org_name == "Rand")
                {
                    int rand_num = rand()%3;
                    if (rand_num == 0)
                    {
                    auto* org = new Plankton;
                    f.set(org, (i - 1) / m , (i - 1) % m );
                    }
                    else if (rand_num == 1)
                    {
                        auto* org = new Shark;
                    f.set(org, (i - 1) / m , (i - 1) % m );

                    }
                    else if (rand_num == 2)
                    {
                         auto* org = new Whale;
                    f.set(org, (i - 0) / m , (i - 0) % m );
                    }
                    else if (rand_num == 3)
                    {
                        auto* org = new Predator_fish;
                    f.set(org, (i - 2) / m , (i - 2) % m );
                    }
                }
            }

            ss.clear();
        }
    }


    void fill_field(Field& f) {

        std::vector<std::string>input = read();

        std::stringstream ss; ss << input.at(0);
        int n, m; ss >> m >> n; ss.clear();
        f = Field(m, n);
        for (int i = 1; i < input.size(); i++) {
            std::string org_name;
            ss << input.at(i);
            while (ss >> org_name) {
                if (org_name == "Pl") {
                    auto* org = new Plankton;
                    f.set(org, (i - 1) / m, (i - 1) % m);
                }

                else if (org_name == "Sh") {
                    auto* org = new Shark;
                    f.set(org, (i - 1) / m, (i - 1) % m);
                }
                else if (org_name == "Pr_f") {
                    auto* org = new Predator_fish;
                    f.set(org, (i - 1) / m, (i - 1) % m);
                }
                else if (org_name == "H_f") {
                    auto* org = new Herbivore_fish;
                    f.set(org, (i - 1) / m, (i - 1) % m);
                }
                else if (org_name == "Wh") {
                    auto* org = new Whale;
                    f.set(org, (i - 1) / m, (i - 1) % m);
                }
            }

            ss.clear();
        }
    }
};


int main(int argc, char** argv) {

    srand(time(nullptr));

    std::string file_path;

    bool auto_mode, advanced_print_mode;

    if (argc == 4 && argv[2][0] == '-' && (argv[2][1] == 'a' || argv[2][1] == 's') &&
        argv[3][0] == '-' && (argv[3][1] == 't' || argv[3][1] == 'f')) {

        file_path = std::string(argv[1]);

        if (argv[2][1] == 'a') auto_mode = true;
        else auto_mode = false;

        if (argv[3][1] == 't') advanced_print_mode = true;
        else advanced_print_mode = false;

    }
    else {
        std::cout << "Error: enter arguments"
            "\n\tfirst: file_path \n\tsecond: mode "
            "\n\t\t(-a : automatic modeling / -s : step by step modeling)"
            "\n\tthird: advanced_print_mode \n\t\t(-t : true / -f false)\n";
        return 0;
    }

    Field f;
    ReadFromFile file(file_path);
    file.random_fill_field(f);

    f.print_field();

    int iteration = 0;
    while (true) {

        if (iteration == 6) {
            if (f.stop()) return 0;
            iteration = 0;
        }
        iteration++;

        if (!auto_mode) std::cin.get();

        f.iteration(advanced_print_mode);

        f.print_field();


    }

}
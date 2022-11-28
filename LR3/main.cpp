#include <iostream>
#include "wirth_unoriented_graph.h"

void print_menu() {

    std::cout << "\n";
    std::cout << "[1]  Exit \n";
    std::cout << "[2]  Print graph \n";
    std::cout << "[3]  Add node \n";
    std::cout << "[4]  Add edge \n";
    std::cout << "[5]  Remove node \n";
    std::cout << "[6]  Remove edge \n";
    std::cout << "[7]  Check node presence \n";
    std::cout << "[8]  Check edge presence \n";
    std::cout << "[9]  Print node count \n";
    std::cout << "[10] Print edge count \n";
    std::cout << "[11] Get node degree \n";
    std::cout << "\n";

}

int main() {

    Graph<int> main_container;

    int temp_int_1, temp_int_2;
    int menu_option;


    while (true) {

        print_menu();
        
        std::cin >> menu_option;

        system("cls");

        print_menu();
        
        system("cls");


        switch (menu_option) {
        case 1:

            return 1;

        case 2:

            main_container.print_graph();
            break;

        case 3:

            std::cin >> temp_int_1;
            main_container.add_node(temp_int_1);
            break;

        case 4:

            std::cin >> temp_int_1 >> temp_int_2;
            main_container.add_edge(temp_int_1, temp_int_2);
            break;

        case 5:

            std::cin >> temp_int_1;
            main_container.del_node(temp_int_1);
            break;

        case 6:

            int temp_int_1, temp_int_2;
            std::cin >> temp_int_1 >> temp_int_2;
            main_container.del_edge(temp_int_1, temp_int_2);
            break;

        case 7:

            std::cin >> temp_int_1;
            if (main_container.is_node(temp_int_1))
                std::cout << "Edge [ " << temp_int_1 << " ] found" << std::endl;
            else
                std::cout << "Edge [ " << temp_int_1 << " ] not found" << std::endl;
            break;

        case 8:

            std::cin >> temp_int_1 >> temp_int_2;
            if (main_container.is_edge(temp_int_1, temp_int_2))
                std::cout << "Edge [ " << temp_int_1 << " - " << temp_int_2 << " ] found" << std::endl;
            else
                std::cout << "Edge [ " << temp_int_1 << " - " << temp_int_2 << " ] not found" << std::endl;

            break;

        case 9:

            std::cout << "Node count: " << main_container.count_nodes() << std::endl;
            break;

        case 10:

            std::cout << "Edge count: " << main_container.count_edges() << std::endl;
            break;

        case 11:

            std::cin >> temp_int_1;
            std::cout << "Node degree: " << main_container.pow_node(temp_int_1) << std::endl;
            break;

        }



    }
}

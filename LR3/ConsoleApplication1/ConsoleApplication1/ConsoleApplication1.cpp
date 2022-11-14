#include "Header.h"

int main()
{
    setlocale(LC_ALL, "ru");
    Graph<int> a;
    int choice;
    while (true)
    {
        std::cout << "\n1) Создать граф" << std::endl;
        std::cout << "2) Вывести граф" << std::endl;
        std::cout << "3) Добавить узел" << std::endl;
        std::cout << "4) Добавить ребро" << std::endl;
        std::cout << "5) Удалить ребро" << std::endl;
        std::cout << "6) Удалить узел" << std::endl;
        std::cout << "7) Проверка узла" << std::endl;
        std::cout << "8) Проверка ребра" << std::endl;
        std::cout << "9) Количестов рёбер" << std::endl;
        std::cout << "10) Количество узлов" << std::endl;
        std::cout << "11) Степень вершины" << std::endl;
        std::cout << "" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            a.create_graph();
            break;
        }
        case 2:
        {
            a.print_graph();
            break;
        }
        case 3:
        {
            int x;
            std::cin >> x;
            a.add_node(x);
            break;
        }
        case 4:
        {
            int x, y;
            std::cin >> x >> y;
            a.add_edge(x, y);
            break;
        }
        case 5:
        {
            int x, y;
            std::cin >> x >> y;
            a.del_edge(x, y);
            break;
        }
        case 6:
        {
            int x;
            std::cin >> x;
            a.del_node(x);
            break;
        }
        case 7:
        {
            int x;
            std::cin >> x;
            if (a.is_node(x))
                std::cout << "Узел найден" << std::endl;
            else
                std::cout << "Узел не найден" << std::endl;
            break;
        }
        case 8:
        {
            int x, y;
            std::cin >> x >> y;
            if (a.is_edge(x, y))
                std::cout << "Ребро найдено" << std::endl;
            else
                std::cout << "Ребро не найдено" << std::endl;
            break;
        }
        case 9:
        {
            std::cout << "Количестов рёбер - " << a.count_edges() << std::endl;
            break;
        }
        case 10:
        {
            std::cout << "Количество узлов - " << a.count_nodes() << std::endl;
            break;
        }
        case 11:
        {
            int x;
            std::cin >> x;
            std::cout << "Степень вершины - " << a.pow_node(x) << std::endl;
            break;
        }
        }
    }
}


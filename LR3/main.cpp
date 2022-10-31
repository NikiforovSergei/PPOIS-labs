#include "ungraph.h"
typedef Graph<int> intgraph;
typedef Graph<std::string> strgraph;
typedef Graph<double> doublegraph;
int main()
{
    setlocale(LC_ALL, "Russian");
    intgraph graph;
    IteratorVertex<int> itrv;
    IteratorEdge<int> itre;
    AdjVertex<int> itrav;
    incEdge<int> itrie;
    while (true)
    {
        system("CLS");
        std::cout << "Добавить вершину - 1\nДобавить ребро - 2\nОтобразить матрицу - 3\nУдалить матрицу - 4\nСоздана ли матрица - 5\nИтераторы - 6\nДополнительные функции - 7: ";
        int choice = getChoice<int>();
        switch (choice)
        {
        case 1: 
        {
            std::cout << "Введите информацию вершины: ";
            int number = getChoice<int>(); 
            graph.addVertex(number); 
            itrv.setVertexes(graph.getVertexes());
            itrav.setVertexes(graph.getVertexes(),graph.getEdges());
        } break;
        case 2: 
        {
            std::cout << "Введите вес/имя/вершина1/вершина2 ребра: ";
            double weight = getChoice<double>();
            char name = getChoice<char>();
            int n1 = getChoice<int>();
            int n2 = getChoice<int>();
            if (n1==n2)
            {
                Error error(302);
                system("pause");
                break;
            }
            try
            {
                graph.addEdge(weight, n1, n2, name);
                itre.setEdges(graph.getEdges());
            }
            catch(const int* errorCode)
            {
                Error error(*errorCode);
                system("pause");
            }
        } break;
        case 3: std::cout << graph; system("pause"); break;
        case 4:
        {
            if (graph.empty())
            {
                graph.clear();
            }
        } break;
        case 5:
        {
            std::cout << graph.empty() << std::endl;
            system("pause");
        }break;
        case 6:
        {
            while (true)
            {
                system("CLS");
                std::cout << "Итератор вершин - 1\nИтератор ребер - 2\nИтератор ребер(инц вершине) - 3\nИтератор вершин(смежных вершине) - 4: ";
                int choice = getChoice<int>();
                try
                {
                    switch (choice)
                    {
                    case 1:
                    {
                        std::cout << itrv << std::endl;
                        itrv++;
                        std::cout << itrv << std::endl;
                        ++itrv;
                        std::cout << itrv << std::endl;
                        itrv--;
                        std::cout << itrv << std::endl;
                        --itrv;
                        std::cout << itrv << std::endl;
                        system("pause");
                    }break;
                    case 2:
                    {
                        std::cout << itre << std::endl;
                        itre++;
                        std::cout << itre << std::endl;
                        ++itre;
                        std::cout << itre << std::endl;
                        itre--;
                        std::cout << itre << std::endl;
                        --itre;
                        std::cout << itre << std::endl;
                        system("pause");
                    } break;
                    case 3:
                    {
                        itrie.setVertexes(graph.getVertexes(), graph.getEdges());
                        std::cout << "Введите индекс вершины: ";
                        int choice = getChoice<int>();
                        itrie.findIncEdges(choice,graph.getEdges());
                        std::cout << itrie << std::endl;
                        itrie++;
                        std::cout << itrie << std::endl;
                        ++itrie;
                        std::cout << itrie << std::endl;
                        itrie--;
                        std::cout << itrie << std::endl;
                        --itrie;
                        std::cout << itrie << std::endl;
                        system("pause");
                    }break;
                    case 4:
                    {
                        std::cout << "Введите индекс вершины: ";
                        int choice = getChoice<int>();
                        itrav.findAdjVertexes(choice, graph.getEdges());
                        std::cout << itrav << std::endl;
                        itrav++;
                        std::cout << itrav << std::endl;
                        ++itrav;
                        std::cout << itrav << std::endl;
                        itrav--;
                        std::cout << itrav << std::endl;
                        --itrav;
                        std::cout << itrav << std::endl;
                        system("pause");
                    }
                    default:
                    {
                        Error error(200);
                        system("pause");
                    }
                    }
                }
                catch (const int* errorCode)
                {
                    Error error(*errorCode);
                    system("pause");
                }
                break;
            }
        }break;
        case 7:
        {
            while (true)
            {
                system("CLS");
                std::cout << "Количество вершин - 1\nКоличество ребер - 2\nУдалить вершину - 3\nУдалить ребро - 4\nСтепень вершины - 5\nСтепень ребра - 6\nНаличие вершины в графе - 7\nНаличие ребра между вершинами - 8\nПолучить информацию вершины - 9\nПолучить вес ребра - 10:";
                int choice = getChoice<int>();
                switch (choice)
                {
                case 1: std::cout << "Количество вершин: " << graph.NumberOfVertexes() << std::endl; system("pause"); break;
                case 2: std::cout << "Количество ребер:" << graph.NumberOfEdgex() << std::endl; system("pause"); break;
                case 3: 
                {
                    try
                    {
                        graph.deleteVertex(); 
                    }
                    catch (...)
                    {
                        Error error(300);
                        system("pause");
                    }
                }break;
                case 4: 
                {
                    try
                    {
                        graph.deleteEdge(); 
                    }
                    catch(...)
                    {
                        Error error(301);
                        system("pause");
                    }
                } break;
                case 5: 
                {
                    std::cout << "Введите индекс вершины: "; 
                    int index = getChoice<int>();
                    std::cout << "Степень вершины: " << graph.powerVertex(index); 
                    system("pause");
                } break;
                case 6: 
                {
                    std::cout << "Введите введите имя ребра: " << std::endl; 
                    char name = getChoice<char>();
                    std::cout << "Степень ребра: " << graph.powerEdge(name) << std::endl; 
                    system("pause"); 
                } break;
                case 7:
                {
                    std::cout << "Введите индекс вершины: ";
                    int index = getChoice<int>();
                    std::cout << graph.isVertexExist(index) << std::endl;
                    system("pause");
                } break;
                case 8:
                {
                    std::cout << "Введите индексы двух вершин: ";
                    int fIndex = getChoice<int>();
                    int sIndex = getChoice<int>();
                    std::cout << graph.isEdgeBetVertexes(fIndex, sIndex) << std::endl;
                    system("pause");
                }break;
                case 9:
                {
                    std::cout << "Введите индекс вершины: ";
                    int index = getChoice<int>();
                    try
                    {
                        graph.getVertexData(index);
                    }
                    catch (...)
                    {
                        Error error(304);
                        system("pause");
                    }
                }break;
                case 10:
                {
                    std::cout << "Введите введите имя ребра: " << std::endl;
                    char name = getChoice<char>();
                    try
                    {
                        graph.getEdgeWeight(name);
                    }
                    catch (...)
                    {
                        Error error(301);
                        system("pause");
                    }
                } break;
                default:
                {
                    Error error(200);
                    system("pause");
                }
                }
                break;
            }
        } break;
        default:
        {
            Error error(200);
            system("pause");
        }
        }
    }
    return 0;
}
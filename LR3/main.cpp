#include "graph.h"
#include <iostream>

int main() {

    graph<int> Graph;
    int menu, input, temp;
    bool run_program=true;
    while (run_program) {
        std::cout << "\n1.Add node\n"
                     "2.Add edge\n"
                     "3.Show Graph\n"
                     "4.Amount of node\n"
                     "5.Amount of edge\n"
                     "6.Degree of node\n"
                     "7.Delete node\n"
                     "8.Delete edge\n"
                     "9.Clear Graph\n"
                     "10.exit\n"<<std::endl;
        std::cin >> menu;

        switch (menu) {
            case 1:
                std::cout<<"Create a new node: ";
                std::cin>>input;
                Graph.push_node(input);
                break;
            case 2:
                std::cout<<"Create a new edge between two node: ";
                std::cin>>input>>temp;
                Graph.add_edge(input, temp);
                break;
            case 3:
                std::cout<<"1.Show Graph\n"
                           "2.Show nodes\n"
                           "3.Show nodes in reverse order\n"
                           "4.Show edges\n"
                           "5.Show edges in reverse order\n"
                           "6.Show adjacent nodes for given\n"
                           "7.Show incident edges for a given node\n"<<std::endl;

                std::cin>>menu;

                switch (menu) {
                    case 1:
                        std::cout << Graph;
                        break;
                    case 2:
                        for(auto it = Graph.begin(); it!=Graph.end(); ++it){
                            std::cout<<*it<<" ";
                        }
                        std::cout<<std::endl;
                        break;
                    case 3:
                        for(auto it = Graph.rbegin(); it!=Graph.rend(); ++it){
                            std::cout<<*it<<" ";
                        }
                        std::cout<<std::endl;
                        break;
                    case 4:
                        for(auto it = Graph.edge_begin(); it!=Graph.edge_end(); ++it){
                            std::cout<<"("<<(*it).first<<", "<<(*it).second<<"), ";
                        }
                        std::cout<<std::endl;
                        break;
                    case 5:
                        for(auto it = Graph.edge_rbegin(); it!=Graph.edge_rend(); ++it){
                            std::cout<<"("<<(*it).first<<", "<<(*it).second<<"), ";
                        }
                        std::cout<<std::endl;
                        break;
                    case 6:
                        std::cout<<"Enter a node:";
                        std::cin>>input;
                        for(auto it = Graph.adjacency_node_begin(input); it!=Graph.adjacency_node_end(input); ++it){
                            std::cout<<*it<<" ";
                        }
                        std::cout<<std::endl;
                        break;
                    case 7:
                        std::cout<<"Enter a node:";
                        std::cin>>input;
                        for(auto it = Graph.adjacency_edge_begin(input); it!=Graph.adjacency_edge_end(); ++it){
                            std::cout<<"("<<(*it).first<<", "<<(*it).second<<") ";
                        }
                        std::cout<<std::endl;
                        break;
                    default:
                        std::cout << "Oops, wrong input!";
                        break;
                }

                break;
            case 4:
                std::cout<<"Amount of nodes in Graph: ";
                std::cout<<Graph.node_size();
                break;
            case 5:
                std::cout<<"Amount of edges in Graph: ";
                std::cout<<Graph.edge_size();
                break;
            case 6:
                std::cout<<"Enter a node: ";
                std::cin>>input;
                std::cout << "Degree a node " << input << " is " << Graph.node_degree(input);
                break;
            case 7:
                std::cout<<"Enter a node: ";
                std::cin>>input;
                if(Graph.delete_node(input)){
                    std::cout<<"Node was deleted!";
                }else{
                    std::cout<<"\nError";
                }
                break;
            case 8:
                std::cout<<"Enter a edge: ";
                std::cin>>input>>temp;
                if(Graph.delete_edge(input, temp)){
                    std::cout<<"Edge was deleted!";
                }else{
                    std::cout<<"\nError";
                }
                break;
            case 9:
                Graph.clear();
                break;
            case 10:
                run_program=false;
                break;
            default:
                std::cout << "Oops, wrong input!";
                break;
        }
    }

}

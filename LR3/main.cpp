#include <iostream>
#include "Changed.h"
void print(char i){
    std::cout<<i<<" ";
}
int main() {
    std::vector<char> input(10);
    std::vector<std::vector<int>> input_matrix = {{0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                                                  {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
                                                  {0, 0, 0, 5, 0, 0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 7, 0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0, 9, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0, 0, 9, 0, 0, 0},
                                                  {0, 0, 0, 0, 0, 0, 0, 11, 0, 0},
                                                  {0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
                                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
                                                  {5, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    std::cout<<"Input 10 Letters"<<std::endl;
    for (int i = 0;i<10;i++){
        std::cin>>input[i];
    }
    AdjacencyMatrix<char> TestMatrix(input, input_matrix);
    std::cout<<TestMatrix.size()<<" "<<TestMatrix.PowerOfEdge(0,1)<<std::endl;
    for(auto a = TestMatrix.begin();a!=TestMatrix.end();a++){
        std::cout<<a.Current()<<" ";
    }
    for (auto c = TestMatrix.rbegin();c!=TestMatrix.rend();c--){
        std::cout<<c.Current()<<" ";
    }
    std::cout<<std::endl;
    for (auto d = TestMatrix.REdgeBegin();d!=TestMatrix.REdgeEnd();d--){
        std::cout<<d.Current()<<" ";
    }
    std::cout<<std::endl;
    for (auto d = TestMatrix.EdgeBegin();d!=TestMatrix.EdgeEnd();d++){
        std::cout<<d.Current()<<" ";
    }

    std::cout<<std::endl;
    std::cout<<"Power of Edge: "<<TestMatrix.PowerOfEdge(0,1)<<std::endl;
    TestMatrix.DeleteEdge(0,1);
    std::cout<<"Power of Edge: "<<TestMatrix.PowerOfEdge(0,1)<<std::endl;
    std::cout<<"Size: "<<TestMatrix.size()<<std::endl;
    TestMatrix.DeleteVertex(9);
    std::cout<<"Size: "<<TestMatrix.size()<<std::endl;
    TestMatrix.AddVertex({5, 0, 0, 0, 0, 0, 0, 0, 0, 0},'f');
    std::cout<<"Size: "<<TestMatrix.size()<<std::endl;
    std::cout<<TestMatrix.empty()<<std::endl;
    TestMatrix.clear();
    std::cout<<TestMatrix.empty()<<std::endl;
    return 0;
}

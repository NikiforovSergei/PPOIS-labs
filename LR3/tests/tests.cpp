#include "../src/Spisok.cpp"
#include <gtest/gtest.h>
#include "vector"

//Functions

TEST(TestFunctions, Empty) {
    Spisok<int>A;
    ASSERT_TRUE(A.empty());
}
TEST(TestFunctions, AddNode) {
    Spisok<int>A;
    std::cout<<"\nAdding node 1 to empty graph...\n";
    A.AddNode(1);
    ASSERT_FALSE(A.empty());
    ASSERT_TRUE(A.ContainsNode(1));
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n\n";
}
TEST(TestFunctions, AddEdge) {
    Spisok<int>A;
    std::cout<<"\nAdding edge 1->2 to empty graph...\n";
    A.AddEdge(1, 2);
    ASSERT_FALSE(A.empty());
    ASSERT_TRUE(A.ContainsNode(1));
    ASSERT_TRUE(A.ContainsNode(2));
    ASSERT_TRUE(A.ContainsEdge(1, 2));
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n\n";
}
TEST(TestFunctions, DeleteNode) {
    Spisok<int>A;
    std::cout<<"\nAdding node 1 to empty graph...\n";
    A.AddNode(1);
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());
    std::cout<<"Deleting node 1 ...\n";
    A.DeleteNode(1);
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n\n";
    ASSERT_TRUE(A.empty());
}
TEST(TestFunctions, DeleteEdge) {
    Spisok<int>A;
    std::cout<<"\nAdding edge 1->2 to empty graph...\n";
    A.AddEdge(1, 2);
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());
    std::cout<<"Deleting edge 1->2 ...\n";
    A.DeleteEdge(1, 2);
    ASSERT_FALSE(A.ContainsEdge(1, 2));
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n\n";
}
TEST(TestFunctions, ReadFromFile) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n\n";
    ASSERT_FALSE(A.empty());
}
TEST(TestFunctions, NumOfNodes) {
    Spisok<char>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_char");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());
    std::cout<<"Calculating the number of nodes in the graph...\nNum: "<<A.NumOfNodes()<<"\n\n";
    ASSERT_EQ(A.NumOfNodes(), 6);
}
TEST(TestFunctions, NumOfEdges) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());
    std::cout<<"Calculating the number of edges in the graph...\nNum: "<<A.NumOfEdges()<<"\n\n";
    ASSERT_EQ(A.NumOfEdges(), 8);
}
TEST(TestFunctions, NodeDegree) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());
    std::cout<<"Checking degrees of nodes...\n";
    ASSERT_EQ(A.NodeDegreeIn(5), 1);
    ASSERT_EQ(A.NodeDegreeIn(4), 2);

    ASSERT_EQ(A.NodeDegreeOut(5), 2);
    ASSERT_EQ(A.NodeDegreeOut(4), 0);

    ASSERT_EQ(A.NodeDegreeIn(10), -1);
    ASSERT_EQ(A.NodeDegreeOut(10), -1);
    std::cout<<"Correct!\n\n";
}
TEST(TestFunctions, EdgeDegree) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    std::cout<<"Checking degrees of edges...\n";
    ASSERT_EQ(A.EdgeDegree(1, 2).first, 3);
    ASSERT_EQ(A.EdgeDegree(1, 2).second, 4);

    ASSERT_EQ(A.EdgeDegree(4, 1).first, -1);
    ASSERT_EQ(A.EdgeDegree(4, 1).second, -1);

    ASSERT_EQ(A.EdgeDegree(3, 4).first, 4);
    ASSERT_EQ(A.EdgeDegree(3, 4).second, 2);
    std::cout<<"Correct!\n\n";
}
TEST(TestFunctions, Clear) {
    Spisok<float>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_float");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    std::cout<<"Cleaning graph...\n";
    A.clear();
    ASSERT_TRUE(A.empty());
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
}

//IteratorNodes

TEST(TestIteratorNodes, Init) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes it = Spisok<int>::iterator_nodes(A.begin_nodes());
    std::cout<<"The iterator points to the node: "<<*it<<"\n\n";
    ASSERT_EQ(*it, 1);
}
TEST(TestIteratorNodes, MoveIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes it = Spisok<int>::iterator_nodes(A.begin_nodes());

    std::cout<<"The iterator points to the node: "<<*it<<"\n";
    ASSERT_EQ(*it, 1);

    std::cout<<"Executing it++...\n"; it++;
    std::cout<<"The iterator points to the node: "<<*it<<"\n";
    ASSERT_EQ(*it, 2);

    std::cout<<"Executing it+=3...\n"; it+=3;
    std::cout<<"The iterator points to the node: "<<*it<<"\n\n";
    ASSERT_EQ(*it, 5);
}
TEST(TestIteratorNodes, EqIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes it1 = Spisok<int>::iterator_nodes(A.begin_nodes());
    Spisok<int>::iterator_nodes it2 = Spisok<int>::iterator_nodes(A.begin_nodes());

    std::cout<<"The it1 points to the node: "<<*it1<<"\n";
    ASSERT_EQ(*it1, 1);

    std::cout<<"Executing it2 = it1+3...\n"; it2 = it1+3;
    std::cout<<"The it2 points to the node: "<<*it2<<"\n";
    ASSERT_EQ(*it2, 4);

    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_FALSE(it1 == it2) << "False\n";

    std::cout<<"Executing it1+=3...\n"; it1+=3;
    std::cout<<"The it1 points to the node: "<<*it1<<"\n";
    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_TRUE(it1 == it2) << "True\n";
    std::cout<<"\n\n";
}
TEST(TestIteratorNodes, ErrorOutOfRange) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes it = Spisok<int>::iterator_nodes(A.begin_nodes());

    std::cout<<"The it1 points to the node: "<<*it<<"\n";
    ASSERT_EQ(*it, 1);

    std::cout<<"Executing it+=10...\n";
    ASSERT_THROW(it+=10, std::out_of_range);
}

//IteratorEdges

TEST(TestIteratorEdges, Init) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges it = Spisok<int>::iterator_edges(A.begin_edges());
    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n\n";
    ASSERT_EQ((*it).first, 1); ASSERT_EQ((*it).second, 3);
}
TEST(TestIteratorEdges, MoveIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges it = Spisok<int>::iterator_edges(A.begin_edges());

    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 1); ASSERT_EQ((*it).second, 3);

    std::cout<<"Executing it++...\n"; it++;
    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 1); ASSERT_EQ((*it).second, 2);

    std::cout<<"Executing it+=3...\n"; it+=3;
    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 3); ASSERT_EQ((*it).second, 5);
}
TEST(TestIteratorEdges, EqIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges it1 = Spisok<int>::iterator_edges(A.begin_edges());
    Spisok<int>::iterator_edges it2 = Spisok<int>::iterator_edges(A.begin_edges());

    std::cout<<"The it1 points to the edge: "<<(*it1).first<<"->"<<(*it1).second<<"\n";
    ASSERT_EQ((*it1).first, 1); ASSERT_EQ((*it1).second, 3);

    std::cout<<"Executing it2 = it1+3...\n"; it2 = it1+3;
    std::cout<<"The it2 points to the edge: "<<(*it2).first<<"->"<<(*it2).second<<"\n";
    ASSERT_EQ((*it2).first, 2); ASSERT_EQ((*it2).second, 3);

    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_FALSE(it1 == it2) << "False\n";

    std::cout<<"Executing it1+=3...\n"; it1+=3;
    std::cout<<"The it1 points to the edge: "<<(*it1).first<<"->"<<(*it1).second<<"\n";
    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_TRUE(it1 == it2) << "True\n";
    std::cout<<"\n\n";
}
TEST(TestIteratorEdges, ErrorOutOfRange) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges it = Spisok<int>::iterator_edges(A.begin_edges());

    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 1); ASSERT_EQ((*it).second, 3);

    std::cout<<"Executing it+=10...\n";
    ASSERT_THROW(it+=10, std::out_of_range);
}

//IteratorNodesAdjacent

TEST(TestIteratorNodesAdjacent, Init) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes_of_node it = Spisok<int>::iterator_nodes_of_node(A.begin_nodes_of_node(3));
    std::cout<<"The iterator points to the node: "<<*it<<"\n\n";
    ASSERT_EQ(*it, 5);
}
TEST(TestIteratorNodesAdjacent, MoveIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph ...\n";

    A.AddEdge(1, 2); A.AddEdge(2, 3); A.AddEdge(2, 0);
    A.AddEdge(3, 7); A.AddEdge(2, 4); A.AddEdge(2, 11);
    A.AddEdge(11, 1); A.AddEdge(7, 2); A.AddEdge(7, 3);

    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes_of_node it = Spisok<int>::iterator_nodes_of_node(A.begin_nodes_of_node(2));

    std::cout<<"The iterator points to the node: "<<*it<<"\n";
    ASSERT_EQ(*it, 11);

    std::cout<<"Executing it++...\n"; it++;
    std::cout<<"The iterator points to the node: "<<*it<<"\n";
    ASSERT_EQ(*it, 4);

    std::cout<<"Executing it+=2...\n"; it+=2;
    std::cout<<"The iterator points to the node: "<<*it<<"\n";
    ASSERT_EQ(*it, 3);
}
TEST(TestIteratorNodesAdjacent, EqIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph ...\n";

    A.AddEdge(1, 2); A.AddEdge(2, 3); A.AddEdge(2, 0);
    A.AddEdge(3, 7); A.AddEdge(2, 4); A.AddEdge(2, 11);
    A.AddEdge(11, 1); A.AddEdge(7, 2); A.AddEdge(7, 3);

    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes_of_node it1 = Spisok<int>::iterator_nodes_of_node(A.begin_nodes_of_node(2));
    Spisok<int>::iterator_nodes_of_node it2 = Spisok<int>::iterator_nodes_of_node(A.begin_nodes_of_node(2));


    std::cout<<"The it1 points to the node: "<<*it1<<"\n";
    ASSERT_EQ(*it1, 11);

    std::cout<<"Executing it2 = it1+3...\n"; it2 = it1+3;
    std::cout<<"The it2 points to the node: "<<*it2<<"\n";
    ASSERT_EQ(*it2, 3);

    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_FALSE(it1 == it2) << "False\n";

    std::cout<<"Executing it1+=3...\n"; it1+=3;
    std::cout<<"The it1 points to the node: "<<*it1<<"\n";
    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_TRUE(it1 == it2) << "True\n";
    std::cout<<"\n\n";
}
TEST(TestIteratorNodesAdjacent, ErrorOutOfRange) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_nodes_of_node it = Spisok<int>::iterator_nodes_of_node(A.begin_nodes_of_node(3));
    std::cout<<"The iterator points to the node: "<<*it<<"\n\n";
    ASSERT_EQ(*it, 5);

    std::cout<<"Executing it+=10...\n";
    ASSERT_THROW(it+=10, std::out_of_range);
}

//IteratorEdgesAdjacent

TEST(TestIteratorEdgesAdjacent, Init) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges_of_node it = Spisok<int>::iterator_edges_of_node(A.begin_edges_of_node(5));
    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n\n";
    ASSERT_EQ((*it).first, 5); ASSERT_EQ((*it).second, 2);
}
TEST(TestIteratorEdgesAdjacent, MoveIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";

    A.AddEdge(1, 2); A.AddEdge(2, 3); A.AddEdge(2, 0);
    A.AddEdge(3, 7); A.AddEdge(2, 4); A.AddEdge(2, 11);
    A.AddEdge(11, 1); A.AddEdge(7, 2); A.AddEdge(7, 3);

    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges_of_node it = Spisok<int>::iterator_edges_of_node(A.begin_edges_of_node(2));

    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 2); ASSERT_EQ((*it).second, 11);

    std::cout<<"Executing it++...\n"; it++;
    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 2); ASSERT_EQ((*it).second, 4);

    std::cout<<"Executing it+=3...\n"; it+=2;
    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 2); ASSERT_EQ((*it).second, 3);
}
TEST(TestIteratorEdgesAdjacent, EqIteraror) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";

    A.AddEdge(1, 2); A.AddEdge(2, 3); A.AddEdge(2, 0);
    A.AddEdge(3, 7); A.AddEdge(2, 4); A.AddEdge(2, 11);
    A.AddEdge(11, 1); A.AddEdge(7, 2); A.AddEdge(7, 3);

    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges_of_node it1 = Spisok<int>::iterator_edges_of_node(A.begin_edges_of_node(2));
    Spisok<int>::iterator_edges_of_node it2 = Spisok<int>::iterator_edges_of_node(A.begin_edges_of_node(2));

    std::cout<<"The it1 points to the edge: "<<(*it1).first<<"->"<<(*it1).second<<"\n";
    ASSERT_EQ((*it1).first, 2); ASSERT_EQ((*it1).second, 11);

    std::cout<<"Executing it2 = it1+3...\n"; it2 = it1+3;
    std::cout<<"The it1 points to the edge: "<<(*it1).first<<"->"<<(*it1).second<<"\n";
    ASSERT_EQ((*it2).first, 2); ASSERT_EQ((*it2).second, 3);

    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_TRUE(it1 == it2) << "False\n";

    std::cout<<"Executing it1+=3...\n"; it1+=3;
    std::cout<<"The it1 points to the edge: "<<(*it1).first<<"->"<<(*it1).second<<"\n";
    std::cout<<"Checking if it1 == it2...\n";
    ASSERT_TRUE(it1 == it2) << "True\n";
    std::cout<<"\n\n";
}
TEST(TestIteratorEdgesAdjacent, ErrorOutOfRange) {
    Spisok<int>A;
    std::cout<<"\nFilling an empty graph from a file...\n";
    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    std::cout<<"graph: ";  A.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty());

    Spisok<int>::iterator_edges_of_node it = Spisok<int>::iterator_edges_of_node(A.begin_edges_of_node(5));

    std::cout<<"The iterator points to the edge: "<<(*it).first<<"->"<<(*it).second<<"\n";
    ASSERT_EQ((*it).first, 5); ASSERT_EQ((*it).second, 2);

    std::cout<<"Executing it+=10...\n";
    ASSERT_THROW(it+=10, std::out_of_range);
}

TEST(TestGraphOperators, EQ_UnEQ) {
    Spisok<int>A, B, C, D;

    C.AddNode(1); D.AddNode(2);
    ASSERT_TRUE(C != D);

    C.AddNode(2); D.AddNode(1);
    ASSERT_TRUE(C == D);

    C.AddEdge(1, 2);
    ASSERT_TRUE(C != D);

    D.AddEdge(1, 2);
    ASSERT_TRUE(C == D);

    C.AddEdge(1, 3);
    ASSERT_TRUE(C != D);

    D.AddEdge(1, 3);
    std::cout<<"first graph: ";  C.PrintGraph(); std::cout<<"\n";
    std::cout<<"second graph: ";  D.PrintGraph(); std::cout<<"\n\n";
    ASSERT_TRUE(C == D);

    std::cout<<"\nFilling an empty graphs from a file...\n";

    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    B.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");

    std::cout<<"first graph: ";  A.PrintGraph(); std::cout<<"\n";
    std::cout<<"second graph: ";  B.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty()); ASSERT_FALSE(B.empty());

    std::cout<<"Comparing graphs...\n";

    ASSERT_TRUE(A == B);
    A.AddEdge(4, 1);
    ASSERT_TRUE(A != B);
}
TEST(TestGraphOperators, OtherOperators) {
    Spisok<int>A, B, C, D;

    C.AddNode(1); D.AddNode(2);
    ASSERT_FALSE(C >= D);

    C.AddNode(2); D.AddNode(1);
    ASSERT_TRUE(C <= D);

    C.AddEdge(1, 2);
    ASSERT_TRUE(C > D);

    D.AddEdge(1, 2);
    D.AddEdge(2, 5);
    ASSERT_TRUE(C < D);

    std::cout<<"\nFilling an empty graphs from a file...\n";

    A.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    B.ReadFromFile("/home/alexey_t/git/CLionProjects/ppvis_lab3/input_files/input_int");
    A.AddEdge(4, 1);
    std::cout<<"first graph: ";  A.PrintGraph(); std::cout<<"\n";
    std::cout<<"second graph: ";  B.PrintGraph(); std::cout<<"\n";
    ASSERT_FALSE(A.empty()); ASSERT_FALSE(B.empty());

    std::cout<<"Comparing graphs...\n";

    ASSERT_TRUE(A > B);

}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
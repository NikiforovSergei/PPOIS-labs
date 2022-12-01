
#include "pch.h"
#include"gtest/gtest.h"
#include"../lab3/Header.h"


TEST(TestCaseName, isEmpty) {
    Graph<int> s;
    ASSERT_EQ(s.empty(), 1);
}

TEST(TestCaseName, adding_nodes) {
    Graph<int> s;
    s.AddNode(5);
    ASSERT_EQ(s.empty(), 0);
    ASSERT_EQ(1, s.isContainsNode(5));
}

TEST(TestCaseName, addind_edge) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddEdge(4, 5);
    ASSERT_EQ(s[4]->Key, 4);
    ASSERT_EQ(s.isConteinsEdge(5, 4), 0);
    ASSERT_EQ(s.isConteinsEdge(4,5), 1);

}

TEST(TestCaseName, deleting_edge) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddEdge(4, 5);
    s.DeleteEdge(4, 5);
    ASSERT_EQ(s.isConteinsEdge(4, 5), 0);
}

TEST(TestCaseName, deleting_node) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddEdge(4, 5);
    s.DeleteNode(4);
    ASSERT_EQ(s.isConteinsEdge(4, 5), 0);
    ASSERT_EQ(s.isContainsNode(4), 0);
}

TEST(TestCaseName, NumOfNodes) {
    Graph<double>s;
    s.AddNode(6.4);
    s.AddNode(3.5);
    s.AddNode(1.0);
    s.AddNode(5.77);
    ASSERT_EQ(s.empty(), 0);
    ASSERT_EQ(s.NumOfNodes(), 4);
}
TEST(TestCaseName, NumOfEdges) {
    Graph<double>s;
    s.AddNode(6.4);
    s.AddNode(3.5);
    s.AddNode(1.0);
    s.AddNode(5.77);

    s.AddEdge(6.4, 1.0);
    s.AddEdge(6.4, 5.77);
    s.AddEdge(1.0, 5.77);

    ASSERT_FALSE(s.empty());
    ASSERT_EQ(s.NumOfEdges(), 3);
}

TEST(TestCaseName, number_of_edges_in_and_out) {
    Graph<double>s;
    s.AddNode(6.4);
    s.AddNode(3.5);
    s.AddNode(1.0);
    s.AddNode(5.77);

    s.AddEdge(6.4, 3.5);
    s.AddEdge(6.4, 1.0);
    s.AddEdge(6.4, 5.77);
    s.AddEdge(1.0, 5.77);
    ASSERT_EQ(s.NodeDegreeIn(6.4), 0);
    ASSERT_EQ(s.NodeDegreeOut(6.4), 3);
}


TEST(TestCaseName, power_of_edges) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);


    ASSERT_EQ(s.EdgeDegree(4, 5).first, 3);
    ASSERT_EQ(s.EdgeDegree(4, 5).second, 2);
    ASSERT_EQ(s.EdgeDegree(5, 7).second, 2);
}
TEST(TestCaseName, graph_clear) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);
    
    s.clear();
    ASSERT_EQ(s.empty(), 1);
}

TEST(TestCaseName, nodes_iterator_init) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);

    auto it = Graph<int>::node_iterator(s.begin_nodes());
    ASSERT_EQ(*it, 5);
}

TEST(TestCaseName, nodes_iterator_operations) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);

    auto it1 = Graph<int>::node_iterator(s.begin_nodes());
    auto it2 = Graph<int>::node_iterator(s.begin_nodes());

    ASSERT_EQ(*it1 == *it2, 1);
    it1++;
    ASSERT_EQ(*it1 == *it2, 0);
    ASSERT_EQ(*it1 != *it2, 1);
    it1++;
    it2 += 2;
    ASSERT_EQ(*it1 == *it2, 1);

}
TEST(TestCaseName, iterator_catch_exeptions) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);

    auto it = Graph<int>::node_iterator(s.begin_nodes());
   
    ASSERT_THROW(it += 5, std::out_of_range);
}

TEST(TestCaseName, edges_iterator_operations) {
    Graph<int> s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);
    auto it1 = Graph<int>::edge_iterator(s.begin_edges()); //по выходящим ребрам
    ASSERT_EQ((*it1).first, 5);
    ASSERT_EQ((*it1).second, 7);
    it1++;
    ASSERT_EQ((*it1).first, 4);
    ASSERT_EQ((*it1).second, 7);
    it1++;
    ASSERT_EQ((*it1).first, 4);
    ASSERT_EQ((*it1).second, 6);
    it1++;
    auto it2 = Graph<int>::edge_iterator(s.begin_edges());
    ASSERT_EQ(*it2 != *it1, 1);
    it2 += 3;
    ASSERT_EQ(*it2 == *it1, 1);

}

TEST(TestCaseName, adjacent_nodes_iterator) {
    Graph<int>s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);

    auto it = Graph<int>::adjacent_nodes_iterator(s.begin_nodes_of_node(4));
    ASSERT_EQ(*it, 7);
    it++;
    ASSERT_EQ(*it, 6);
    ASSERT_THROW(it += 2, std::out_of_range);
    auto it1 = Graph<int>::adjacent_nodes_iterator(s.begin_nodes_of_node(5));
    ASSERT_THROW(it1 +=2, std::out_of_range);


}

TEST(TestCaseName, incidence_edges_iterator) {
    Graph<int>s;
    s.AddNode(5);
    s.AddNode(4);
    s.AddNode(6);
    s.AddNode(7);

    s.AddEdge(4, 5);
    s.AddEdge(4, 6);
    s.AddEdge(4, 7);
    s.AddEdge(5, 7);

    auto it = Graph<int>::incidence_edges_iterator(s.begin_edges_of_node(4));
    ASSERT_EQ((* it).first, 4);
    ASSERT_EQ((*it).second, 7);

    it++;
    ASSERT_EQ((*it).first, 4);
    ASSERT_EQ((*it).second, 6);
    ASSERT_THROW(it += 3, std::out_of_range);
    auto it2 = Graph<int>::incidence_edges_iterator(s.begin_edges_of_node(4));
    it = s.begin_edges_of_node(4);
    
    ASSERT_EQ((*it).first == (*it2).first, 1);
    ASSERT_EQ((*it).second == (*it2).second, 1);
    it++;
    ASSERT_EQ((*it).first == (*it2).first, 1);
    ASSERT_EQ((*it).second != (*it2).second, 1);
}   

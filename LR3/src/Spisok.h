//
// Created by alexey_t on 19/10/22.
//
#include "iostream"
#include "fstream"


#ifndef PPVIS_LAB2_SPISOK_H
#define PPVIS_LAB2_SPISOK_H


//Описание типа дугового узла.
template<typename Type>
struct T
{
    Type Id;
    T<Type>* Next;
};

//Описание типа заголовочного узла.
template<typename Type>
struct L
{
    Type Key = NULL; //Имя заголовочного узла.
    int Count = NULL; //Количество предшественников.
    T<Type>* Trail = nullptr; //Указатель на список смежности.
    L<Type>* Next = nullptr; //Указатель на следующий узел в списке заголовочных узлов.
};

template<typename Type>
class Spisok
{

private:
    L<Type>* Head; //Указатель на начало списка заголовочных узлов.
    L<Type>* Tail; //Указатель на фиктивный узел
    // в конце списка заголовочных узлов.
    void SearchGraph (Type, L<Type> *&);
    void Search (Type, L<Type> *&);
public:
    class iterator_nodes;
    class iterator_edges;
    class iterator_edges_of_node;
    class iterator_nodes_of_node;

    Spisok () {//Инициализация списка заголовочных узлов.
        Head = Tail  = new L<Type>; }
    void MakeGraph ();
    void AddEdge(Type, Type);
    void AddNode(Type);
    void DeleteEdge (Type, Type);
    void DeleteEdge (iterator_edges);
    void DeleteEdge (iterator_edges_of_node);
    void PrintGraph ();
    void DeleteNode (Type);
    void DeleteNode(iterator_nodes);
    void DeleteNode(iterator_nodes_of_node);
    bool ContainsNode(Type);
    bool ContainsEdge(Type, Type);
    int NumOfNodes();
    int NumOfEdges();
    int NodeDegreeIn(Type);
    int NodeDegreeOut(Type);
    std::pair<int, int> EdgeDegree(Type, Type);

    void clear();
    bool empty();

    void ReadFromFile(std::string);

    iterator_nodes begin_nodes() const { return iterator_nodes(Head); };
    iterator_nodes end_nodes() const {return iterator_nodes(Tail); };

    iterator_edges begin_edges() const { return iterator_edges(Head); };
    iterator_edges end_edges() const {return iterator_edges(Tail); };

    iterator_edges_of_node begin_edges_of_node(Type key) const {
        L<Type>* curr = Head;
        while(curr){
            if(curr->Key == key)
                return iterator_edges_of_node(curr);
            curr = curr->Next;
        }
        throw std::out_of_range("node_not_found");
    };
    iterator_edges_of_node end_edges_of_node(Type key) const {
        L<Type>* curr = Head;
        T<Type>* curr_edge;
        while(curr){
            if(curr->Key == key){
                curr_edge = curr->Trail;
                while(curr_edge->Next) curr_edge = curr_edge->Next;
                return iterator_edges_of_node(curr, curr_edge);
            }
            curr = curr->Next;
        }
        throw std::out_of_range("node_not_found");
    };

    iterator_nodes_of_node begin_nodes_of_node(Type key) const {
        L<Type>* curr = Head;
        while(curr){
            if(curr->Key == key){
                return iterator_nodes_of_node(curr);
            }
            curr = curr->Next;
        }
        throw std::out_of_range("node_not_found");
    };
    iterator_nodes_of_node end_iterator_nodes_of_node() const {return iterator_nodes_of_node(Tail); };

    inline bool operator==(const Spisok<Type>&);
    inline bool operator!=(const Spisok<Type>&);
    inline bool operator<(Spisok<Type>&);
    inline bool operator<=(Spisok<Type>&);
    inline bool operator>(Spisok<Type>&);
    inline bool operator>=(Spisok<Type>&);

};


#endif //PPVIS_LAB2_SPISOK_H

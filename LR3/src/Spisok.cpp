//
// Created by alexey_t on 19/10/22.
//

#include "Spisok.h"

template<typename Type>
void Spisok<Type>::Search (Type w, L<Type> *&h)
//Функция возвращает в *h указатель на заголовочный узел
//ключом w. Если узел отсутствует, то функция возвращает NULL.
{
    h = Head;
    Tail->Key = w; //Поиск "с барьером".
    while (h->Key!=w) h = h->Next;
    if (h == Tail) //В списке заголовочных узлов нет узла с ключом w.
        h = nullptr;
}

template<typename Type>
void Spisok<Type>::SearchGraph (Type w, L<Type> *&h)
//Функция возвращает в *h указатель на заголовочный узел
//с ключом w. Если заголовочный узел отсутствует, то он
//добавляется в список.
{
    h = Head; Tail->Key = w;
    while (h->Key!=w) h = h->Next;
    if (h==Tail)
        //В списке заголовочных узлов нет узла с ключом w.
        //Поместим его в конец списка *Head.
    {
        Tail = new L<Type>/*leader*/;
        h->Count = 0;
        h->Trail = nullptr;
        h->Next = Tail; }
}

template<typename Type>
void Spisok<Type>::MakeGraph ()
//Функция возвращает указатель Head на ортогональные
//списки смежности, соответствующую ориентированному графу.
{
    int x,y;
    L<Type> *p, *q; //Рабочие указатели.
    T<Type> *t, *r; // Рабочие указатели.
    bool Res; //Флаг наличия дуги.
    std::cout<<"Вводите начальную вершину дуги: ";
    std::cin>>x;
    while (x!=0)
    {
        std::cout<<"Вводите конечную вершину дуги: "; std::cin>>y;
        //Определим, существует ли в графе дуга (x, y)?
        SearchGraph (x,p); SearchGraph (y,q);
        r = p->Trail; Res = false;
        while (r && !Res)
            if (r->Id==y) Res = true;
            else r = r->Next;
        if (!Res) //Если дуга отсутствует, то поместим её в граф.
        { t = new T<Type>; t->Id = y;
            t->Next = p->Trail; p->Trail = t; q->Count++; }
        std::cout<<"Вводите начальную вершину дуги: "; std::cin>>x;
    }
}

template<typename Type>
void Spisok<Type>::AddNode(Type key) {
//Добавление узла (если его не было!)
    L<Type> *h;
    SearchGraph(key, h);
}

template<typename Type>
void Spisok<Type>::AddEdge(Type x,Type y)
//Добавление дуги (x,y) (если ее не было!) к связанной
//структуре, соответствующей ориентированному графу Head.
{
    L<Type>* p, *q; //Рабочие указатели.
    T<Type>* t, *r; //Рабочие указатели.
    bool Res; //Флаг наличия в графе данной дуги.
    //Определим, существует ли в графе дуга (x, y)?
    SearchGraph (x,p);
    SearchGraph (y,q);
    r =  p->Trail; Res = false;
    while (r && !Res)
        if (r->Id==y) Res = true;
        else r = r->Next;
    if (!Res)
    { //Если дуга отсутствует, то поместим её в граф.
        t = new T<Type>; t->Id = y; t->Next = p->Trail;
        p->Trail = t;
        q->Count++;
    }
}

template<typename Type>
void Spisok<Type>::DeleteEdge (Type x, Type y)
//Функция возвращает указатель Head на связанную
//структуру, соответствующую ориентированному графу
//и полученную удалением дуги (x,y).
{
    L<Type> *p, *q; //Рабочие указатели.
    T<Type> *t, *r; //Рабочие указатели.
    bool Res; //Флаг наличия в графе данной дуги.
    //Определим, существует ли в графе дуга (x, y)?
    Search (x, p); Search (y, q);
    if (p && q)
    { //Вершины x и y в графе есть.
        r = p->Trail; Res = false;
        while (r && !Res)
            if (r->Id==y) Res = true;
            else r = r->Next;
        if (Res) {//Если дуга существует, то удалим её.
            if (r==p->Trail){
                p->Trail = p->Trail->Next;
                delete r;
                q->Count--;
            } else {
                t = p->Trail;
                while (t->Next!=r) t = t->Next;
                t->Next = t->Next->Next;
                delete r;
                q->Count--;
            }
        }
    }
}

template<typename Type>
void Spisok<Type>::PrintGraph ()
//Вывод структуры смежности, заданной указателем
//Head и соответствующей ориентированному графу.
{
    L<Type> *p; //Рабочий указатель.
    T<Type> *q; //Рабочий указатель.
    p = Head;
    while (p!=Tail)
    {
        std::cout<<"("<<p->Key; q = p->Trail;
        if(q) std::cout<<"| ";
        while (q)
        {
            std::cout<<q->Id;
            if(q->Next) std::cout<<", ";
            q = q->Next;
        }
        std::cout<<")"; p = p->Next; std::cout<<" ";
    }
}

template<typename Type>
void Spisok<Type>::DeleteNode (Type y)
//Функция возвращает указатель Head на связанную структуру,
//соответствующую графу с удаленной вершиной y.
{
    L<Type>* p, *q; //Рабочие указатели.
    T<Type>* r, *s; //Рабочие указатели.
    Type x; //Рабочая переменная.
    //Удаление всех дуг (x,y), оканчивающихся  в вершине y.
    p = Head;
    while (p!=Tail)
    {
        x = p->Key;
        DeleteEdge (x, y); DeleteEdge(y, x);
        p = p->Next;
    }
    //Удаление списка смежности вершины y.
    SearchGraph (y, p); r = p->Trail;
    while (r!= nullptr)
    { s = r; r = r->Next; delete s; }
    //Удаление узла, содержащего вершину y, из списка заголовочных узлов.
    q = Head;
    if (q==p) { Head = Head->Next; delete q; }
    else {
        while (q->Next!=p) q = q->Next;
        q->Next = p->Next; delete p; }
}

template<typename Type>
bool Spisok<Type>::ContainsNode(Type key) {
//Проверка есть ли в графе узел key
    L<Type>* h; Spisok::Search(key, h);
    return h;
}

template<typename Type>
bool Spisok<Type>::ContainsEdge(Type x, Type y) {
//Проверка есть ли в графе дуга x -> y
    L<Type>* p, *q;
    T<Type>* r;

    Search(x,p);
    Search(y,q);
    if(!p || !q) return false;
    r =  p->Trail;
    while (r){
        if (r->Id==y) return true;
        else r = r->Next;
    }
    return false;
}

template<typename Type>
int Spisok<Type>::NumOfNodes(){
//Функция возвращает количество вершин графа
    L<Type>* p = Head, *q = Tail; int count = 0;
    while (p!=q){
        count++; p = p->Next;
    }
    return count;
}

template<typename Type>
int Spisok<Type>::NumOfEdges(){
//Функция возвращает количество дуг графа
    L<Type>* p = Head, *q = Tail; int count = 0;
    while (p!=q){
        count+=p->Count; p = p->Next;
    }
    return count;
}

template<typename Type>
int Spisok<Type>::NodeDegreeIn(Type key){
//Функция возвращает степень входа вершины key
//Если вершины key нет в графе возвращает -1
    L<Type>* h; Spisok::Search(key, h);
    if(h) return h->Count;
    else return -1;
}

template<typename Type>
int Spisok<Type>::NodeDegreeOut(Type key){
//Функция возвращает степень выхода вершины key
//Если вершины key нет в графе возвращает -1
    L<Type>* h; Spisok::Search(key, h);
    if(h){
        int count = 0;
        T<Type>* ptr = h->Trail;
        while(ptr){
            count++; ptr = ptr->Next;
        }
        return count;
    }
    return -1;
}

template<typename Type>
std::pair<int, int> Spisok<Type>::EdgeDegree(Type x, Type y){
//Функция возвращает степень дуги x->y
//Если дуги x->y нет в графе возвращает {-1; -1}
    if(ContainsEdge(x, y))
        return {NodeDegreeOut(x) + NodeDegreeIn(x), NodeDegreeOut(y) + NodeDegreeIn(y)};
    else return {-1, -1};
}

template<typename Type>
class Spisok<Type>::iterator_nodes{
    L<Type>* curr;

public:

    explicit iterator_nodes(L<Type>* first) : curr(first){};

    Type& operator*(){ return curr->Key; }

    iterator_nodes operator+ (int n) {
        iterator_nodes tmp = *this;
        for(int i = 0; i < n; i++)
        {
            if(tmp.curr->Next->Next)
                tmp.curr = tmp.curr->Next;
            else
                throw std::out_of_range("out_of_range");
        }
        return tmp;
    }

    iterator_nodes& operator+= (int n) {
        for(int i = 0; i < n; i++)
        {
            if(curr->Next->Next)
                curr = curr->Next;
            else
                throw std::out_of_range("out_of_range");
        }
        return *this;
    }

    iterator_nodes operator++(int) {
        iterator_nodes tmp = *this;
        if(curr->Next->Next)
            curr = curr->Next;
        else
            throw std::out_of_range("out_of_range");
        return tmp;
    }

    iterator_nodes& operator++() {
        if(curr->Next->Next){
            curr = curr->Next;
            return *this;
        }
        else
            throw std::out_of_range("out_of_range");
    }

    bool operator!=(const iterator_nodes& it){return curr != it.curr;}
    bool operator==(const iterator_nodes& it){return curr == it.curr;}
};


template<typename Type>
class Spisok<Type>::iterator_edges{
    L<Type>* curr_node;
    T<Type>* curr_edge;

public:

    explicit iterator_edges(L<Type>* first) : curr_node(first){
        curr_edge = curr_node->Trail;
    };

    std::pair<Type, Type> operator*(){ return std::pair<Type, Type>(curr_node->Key, curr_edge->Id); }

    iterator_edges operator+ (int n) {
        iterator_edges tmp = *this;
        for(int i = 0; i < n; i++)
        {
            if(!tmp.curr_edge->Next && !tmp.curr_node->Next->Next)
                throw std::out_of_range("out_of_range");

            if (tmp.curr_edge->Next)
                tmp.curr_edge = tmp.curr_edge->Next;

            else if (tmp.curr_node->Next->Next) {
                do {
                    tmp.curr_node = tmp.curr_node->Next;
                } while (!tmp.curr_node->Trail);

                tmp.curr_edge = tmp.curr_node->Trail;
            }
        }
        return tmp;
    }

    iterator_edges& operator+= (int n) {
        for(int i = 0; i < n; i++)
        {
            if(!curr_edge->Next && !curr_node->Next->Next)
                throw std::out_of_range("out_of_range");

            if (curr_edge->Next)
                curr_edge = curr_edge->Next;

            else if (curr_node->Next->Next) {
                do {
                    curr_node = curr_node->Next;
                } while (!curr_node->Trail);

                curr_edge = curr_node->Trail;
            }
        }
        return *this;
    }

    iterator_edges operator++(int) {
        iterator_edges tmp = *this;

        if(!curr_edge->Next && !curr_node->Next->Next){
            throw std::out_of_range("out_of_range");
        }

        if (curr_edge->Next)
            curr_edge = curr_edge->Next;

        else if (curr_node->Next->Next) {
            do {
                curr_node = curr_node->Next;
            } while (!curr_node->Trail);

            curr_edge = curr_node->Trail;
        }
        return tmp;
    }

    iterator_edges& operator++() {

        if(!curr_edge->Next && !curr_node->Next->Next)
            throw std::out_of_range("out_of_range");

        if (curr_edge->Next)
            curr_edge = curr_edge->Next;

        else if (curr_node->Next->Next) {
            do {
                curr_node = curr_node->Next;
            } while (!curr_node->Trail);

            curr_edge = curr_node->Trail;
        }
        return *this;
    }

    bool operator!=(const iterator_edges& it){return (curr_edge, curr_node) != (it.curr_edge, it.curr_node);}
    bool operator==(const iterator_edges& it){return (curr_edge, curr_node) == (it.curr_edge, it.curr_node);}
};

template<typename Type>
class Spisok<Type>::iterator_edges_of_node{
    L<Type>* curr_node;
    T<Type>* curr_edge;

public:

    explicit iterator_edges_of_node(L<Type>* node) : curr_node(node){
        if(!curr_node->Trail)
            throw std::out_of_range("out_of_range");
        curr_edge = curr_node->Trail;
    };

    iterator_edges_of_node(L<Type>* node, T<Type>* edge) : curr_node(node), curr_edge(edge){};

    std::pair<Type, Type> operator*(){ return std::pair<Type, Type>(curr_node->Key, curr_edge->Id); }

    iterator_edges_of_node operator+ (int n) {
        iterator_edges_of_node tmp = *this;
        for(int i = 0; i < n; i++)
        {
            if(!tmp.curr_edge->Next)
                throw std::out_of_range("out_of_range");//?

            tmp.curr_edge = tmp.curr_edge->Next;
        }
        return tmp;
    }

    iterator_edges_of_node& operator+= (int n) {
        for(int i = 0; i < n; i++)
        {
            if(!curr_edge->Next)
                throw std::out_of_range("out_of_range");//?

            curr_edge = curr_edge->Next;
        }
        return *this;
    }

    iterator_edges_of_node operator++(int) {
        iterator_edges_of_node tmp = *this;

        if(!curr_edge->Next)
            throw std::out_of_range("out_of_range");//?

        curr_edge = curr_edge->Next;

        return tmp;
    }

    iterator_edges_of_node& operator++() {

        if(!curr_edge->Next)
            throw std::out_of_range("out_of_range");

        curr_edge = curr_edge->Next;

        return *this;
    }

    bool operator!=(const iterator_edges_of_node& it){return (curr_edge, curr_node) != (it.curr_edge, it.curr_node);}
    bool operator==(const iterator_edges_of_node& it){return (curr_edge, curr_node) == (it.curr_edge, it.curr_node);}
};

template<typename Type>
class Spisok<Type>::iterator_nodes_of_node{
    T<Type>* curr_node;
public:

    explicit iterator_nodes_of_node(L<Type>* node) : curr_node(node->Trail){};

    Type operator*(){ return curr_node->Id;}

    iterator_nodes_of_node operator+ (int n) {
        iterator_nodes_of_node tmp = *this;
        for(int i = 0; i < n; i++)
        {
            if(!tmp.curr_node->Next)
                throw std::out_of_range("out_of_range");//?

            tmp.curr_node = tmp.curr_node->Next;
        }
        return tmp;
    }

    iterator_nodes_of_node& operator+= (int n) {
        for(int i = 0; i < n; i++)
        {
            if(!curr_node->Next)
                throw std::out_of_range("out_of_range");//?

            curr_node = curr_node->Next;
        }
        return *this;
    }

    iterator_nodes_of_node operator++(int) {
        iterator_nodes_of_node tmp = *this;

        if(!curr_node->Next)
            throw std::out_of_range("out_of_range");//?

        curr_node = curr_node->Next;

        return tmp;
    }

    iterator_nodes_of_node& operator++() {

        if(!curr_node->Next)
            throw std::out_of_range("out_of_range");

        curr_node = curr_node->Next;

        return *this;
    }

    bool operator!=(const iterator_nodes_of_node& it){return curr_node != it.curr_node;}
    bool operator==(const iterator_nodes_of_node& it){return curr_node == it.curr_node;}
};

template<typename Type>
void Spisok<Type>::DeleteEdge(Spisok::iterator_edges it) {
    DeleteEdge((*it).first, (*it).second);
}

template<typename Type>
void Spisok<Type>::DeleteEdge(Spisok::iterator_edges_of_node it) {
    DeleteEdge((*it).first, (*it).second);
}

template<typename Type>
void Spisok<Type>::DeleteNode(Spisok::iterator_nodes it) {
    DeleteNode(*it);
}

template<typename Type>
void Spisok<Type>::DeleteNode(Spisok::iterator_nodes_of_node it) {
    DeleteNode(*it);
}

template<typename Type>
bool Spisok<Type>::empty() {
    return Head == Tail;
}

template<typename Type>
void Spisok<Type>::clear() {
    L<Type>* curr_node = Head, *tmp_node;
    T<Type>* curr_edge, *tmp_edge;
    while(curr_node){

        curr_edge = curr_node->Trail;
        while (curr_edge){
            tmp_edge = curr_edge->Next;
            DeleteEdge(curr_node->Key, curr_edge->Id);
            curr_edge = tmp_edge;
        }

        curr_node = curr_node->Next;
    }
    curr_node = Head;
    while (curr_node){
        tmp_node = curr_node->Next;
        DeleteNode(curr_node->Key);
        curr_node = tmp_node;
    }
}

template<typename Type>
void Spisok<Type>::ReadFromFile(std::string file_path){
    std::string line;

    std::ifstream in(file_path);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            Type x, y;
            in >> x >> y;
            AddEdge(x, y);
        }
    }
    in.close();
}

template<typename Type>
bool NodeAContainsAllEdgesOfNodeB(T<Type>*curr1, T<Type>*curr2) {
    bool is_present;
    T<Type>*begin = curr2;
    while(curr1) {
        is_present = false;
        curr2 = begin;
        while(curr2){
            if(curr1->Id == curr2->Id) {
                is_present = true;
                break;
            }
            curr2 = curr2->Next;
        }
        if(!is_present)
            return false;
        curr1 = curr1->Next;
    }
    return true;
}

template<typename Type>
bool AContainsAllNodesOfB(L<Type>*curr1, L<Type>*curr1Tail, L<Type>*curr2, L<Type>*curr2Tail) {
    bool is_present;
    L<Type>*begin = curr2;
    while(curr1 != curr1Tail) {
        is_present = false;
        curr2 = begin;
        while(curr2 != curr2Tail){
            if(curr1->Key == curr2->Key) {
                if(NodeAContainsAllEdgesOfNodeB(curr1->Trail, curr2->Trail) && NodeAContainsAllEdgesOfNodeB(curr2->Trail, curr1->Trail))
                    is_present = true;
                else
                    return false;
                break;
            }
            curr2 = curr2->Next;
        }
        if(!is_present)
            return false;
        curr1 = curr1->Next;
    }
    return true;
}


template<typename Type>
inline bool Spisok<Type>::operator==(const Spisok<Type>&s2) {
    return AContainsAllNodesOfB(Head, Tail, s2.Head, s2.Tail) && AContainsAllNodesOfB(s2.Head, s2.Tail, Head, Tail);
}
template<typename Type>
inline bool Spisok<Type>::operator!=(const Spisok<Type>&s2) {
    return !(*this == s2);
}
template<typename Type>
inline bool Spisok<Type>::operator<(Spisok<Type>&s2){
    return NumOfEdges()*NumOfNodes() < s2.NumOfEdges()*s2.NumOfNodes();
}
template<typename Type>
inline bool Spisok<Type>::operator > (Spisok<Type>&s2){
    return NumOfEdges()*NumOfNodes() > s2.NumOfEdges()*s2.NumOfNodes();
}
template<typename Type>
inline bool Spisok<Type>::operator <= (Spisok<Type>&s2){
    return *this < s2 || *this == s2;
}
template<typename Type>
inline bool Spisok<Type>::operator >= (Spisok<Type>&s2){
    return *this > s2 || *this == s2;
}


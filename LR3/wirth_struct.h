//
// Created by Vladimir Moshchuk on 7.12.22.
//

#ifndef WIRTH__WIRTH_STRUCT_H_
#define WIRTH__WIRTH_STRUCT_H_

#include <iostream>
#include <memory>
#include <iterator>

template<typename type, typename A = std::allocator<type>>
class wirth_struct {
 private:
  class Trailer;

  class Leader {
   public:
    type Key;
    int Count{};

    Trailer *Trail;
    Leader *Next;
  };

  class Trailer {
   public:
    Leader *Id;
    Trailer *Next;
  };

  Leader *SearchGraph(type);
  Leader *Search(type);

  void free_main_list(Leader **, Leader **);
  void free_trailer(Trailer **);

  Leader *Head; //Указатель на список заголовочных узлов.
  Leader *Tail;
 public:
  wirth_struct() {
    Head = Tail = new (Leader);
  }
  wirth_struct(const wirth_struct<type, A> &other);

  ~wirth_struct();

  void addArc(type, type);
  void deleteArc(type, type);
  void print();
  void deleteNode(type);
  void addNode(type);
  void clear();

  bool find(type);
  bool find(type, type);
  bool empty();

  int node_size();
  int arc_size();
  int degree(type);
  int degree(type, type);

  typedef std::pair<Leader *, Trailer *> pair;
  class iterator_node;
  class iterator_edge;

  iterator_node begin() { return Head; }
  iterator_node end() { return Tail; }

  iterator_edge eBegin(iterator_node &x) {
    return x.temp->Trail;
  }
  iterator_edge eEnd() {
    return nullptr;
  }

  class iterator_node {
   public:
    Leader *temp;
    iterator_node(Leader *value) : temp(value) {}
    Leader &operator++(int) { return *(temp = temp->Next); }
    Leader &operator++() {
      Leader *t = temp;
      temp = temp->Next;
      return *t;
    }
    bool operator!=(const iterator_node &it) { return temp!=it.temp; }
    Leader &operator*() { return *temp; }
  };

  class iterator_edge {
    Trailer *ttemp;
   public:
    iterator_edge(Trailer *value) : ttemp(value) {}
    Trailer &operator++(int) { return *(ttemp = ttemp->Id->Trail); }
    Trailer &operator++() {
      pair t = ttemp;
      ttemp = ttemp->Id->Trail;
      return *t;
    }
    bool operator!=(const iterator_edge &it) { return ttemp!=it.ttemp; }
    Trailer &operator*() { return *ttemp; }
  };

  wirth_struct &operator=(const wirth_struct &other);
  bool operator==(const wirth_struct &other);
  bool operator!=(const wirth_struct &other);
  bool operator>=(wirth_struct &other);
  bool operator<=(wirth_struct &other);
  bool operator>(wirth_struct &other);
  bool operator<(wirth_struct &other);

  Leader &operator[](const int &n);

};

template<typename type, typename A>
bool wirth_struct<type, A>::empty() {
  if(Head == Tail){
    return true;
  }
  return false;
}

template<typename type, typename A>
void wirth_struct<type, A>::clear() {
  Leader *t = Head;
  while (t!=Tail) {
    free_trailer(&(*t).Trail);
    t = (*t).Next;
  }
  free_main_list(&Head, &Tail);

  Head = Tail = new (Leader);

}

template<typename type, typename A>
int wirth_struct<type, A>::degree(type x) {

  Leader *p = Head;

  int count = 0;
  while (p!=Tail) {
    if (p->Key==x) {
      count = p->Count;
    }
    p = p->Next;
  }
  return count;
}

template<typename type, typename A>
int wirth_struct<type, A>::degree(type x, type y) {
  return degree(x) + degree(y);
}
template<typename type, typename A>

typename wirth_struct<type, A>::Leader &wirth_struct<type, A>::operator[](const int &n) {
  if (n <= node_size() && n >= 0) {
    Leader *temp = Head;
    for (int i = 0; temp!=nullptr; i++, temp = temp->Next) {
      if (i==n) return *temp;
    }
  }
}
template<typename type, typename A>
bool wirth_struct<type, A>::operator<(wirth_struct &other) {
  return this->node_size() < other.node_size();
}
template<typename type, typename A>

bool wirth_struct<type, A>::operator>(wirth_struct &other) {
  return this->node_size() > other.node_size();
}

template<typename type, typename A>
bool wirth_struct<type, A>::find(type x) {
  Leader *p;

  p = Head;

  while (p!=Tail) {
    if (p->Key==x) {
      return true;
    }
    p = p->Next;
  }
  return false;
}

template<typename type, typename A>
bool wirth_struct<type, A>::find(type x, type y) {
  Leader *p;

  Trailer *q;
  p = Head;
  while (p!=Tail) {
    if (p->Key==x) {
      q = (*p).Trail;
      while (q!=nullptr) {
        if ((*(*q).Id).Key==y) {
          return true;
        }
        q = (*q).Next;
      }
    }
    p = (*p).Next;
  }
  return false;
}
template<typename type, typename A>
int wirth_struct<type, A>::arc_size() {
  Leader *p;
  Trailer *q;

  int counter = 0;
  p = Head;
  while (p!=Tail) {
    q = (*p).Trail;
    while (q!=nullptr) {
      counter++;
      q = (*q).Next;
    }
    p = (*p).Next;
  }

  return counter;
}
template<typename type, typename A>
int wirth_struct<type, A>::node_size() {
  Leader *p = Head;

  int counter = 0;
  while (p->Next) {
    counter++;
    p = p->Next;
  }

  return counter;
}
template<typename type, typename A>
bool wirth_struct<type, A>::operator<=(wirth_struct &other) {
  return this->node_size() < other.node_size() || operator==(other);
}

template<typename type, typename A>
bool wirth_struct<type, A>::operator>=(wirth_struct &other) {
  return this->node_size() > other.node_size() || operator==(other);
}

template<typename type, typename A>
bool wirth_struct<type, A>::operator!=(const wirth_struct &other) {
  return !operator==(other);
}

template<typename type, typename A>
bool wirth_struct<type, A>::operator==(const wirth_struct &other) {
  Leader *temp_this = this->Head;
  Leader *temp_other = other.Head;
  while (temp_this && temp_other) {
    if (temp_this->Key!=temp_other->Key)
      return false;
    Trailer *ttemp_this = temp_this->Trail;
    Trailer *ttemp_other = temp_other->Trail;
    while (ttemp_this && ttemp_other) {
      if (ttemp_this->Id->Key!=ttemp_other->Id->Key)
        return false;
      ttemp_this = ttemp_this->Id->Trail;
      ttemp_other = ttemp_other->Id->Trail;
    }
    temp_this = temp_this->Next;
    temp_other = temp_other->Next;
  }
  return true;
}

template<typename type, typename A>
wirth_struct<type, A> &wirth_struct<type, A>::operator=(const wirth_struct<type, A> &other) {

  if (this->Head!=nullptr) {
    clear();
  }

  Head = Tail = new (Leader);

  Leader *temp = other.Head;

  while (temp->Next) {
    this->addNode(temp->Key);
    temp = temp->Next;
  }

  temp = other.Head;

  while (temp->Next) {
    Trailer *ttemp = temp->Trail;
    while (ttemp) {
      this->addArc(temp->Key, ttemp->Id->Key);
      ttemp = ttemp->Id->Trail;
    }
    temp = temp->Next;
  }
  return *this;
}

template<typename type, typename A>
wirth_struct<type, A>::wirth_struct(const wirth_struct<type, A> &other) {
  Head = Tail = new (Leader);
  Leader *temp;
  temp = other.Head;
  while (temp->Next) {
    this->addNode(temp->Key);
    temp = temp->Next;
  }

  temp = other.Head;
  while (temp->Next) {
    Trailer *ttemp = temp->Trail;
    while (ttemp) {
      this->addArc(temp->Key, ttemp->Id->Key);
      ttemp = ttemp->Next;
    }
    temp = temp->Next;
  }
}

template<typename type, typename A>
wirth_struct<type, A>::~wirth_struct() {
  //Очистка структуры Вирта.
  Leader *t = Head;
  while (t!=Tail) {
    free_trailer(&(*t).Trail);
    t = (*t).Next;
  }
  free_main_list(&Head, &Tail);
  delete Tail;
}

template<typename type, typename A>
typename wirth_struct<type, A>::Leader *wirth_struct<type, A>::SearchGraph(type w) {
  Leader *h;

  h = Head;
  (*Tail).Key = w;
  while ((*h).Key!=w) h = (*h).Next;
  if (h==Tail)
    //В списке заголовочных узлов нет узла с ключом w.
    //Поместим его в конец списка Head.
  {
    Tail = new (Leader);
    (*h).Count = 0;
    (*h).Trail = nullptr;
    (*h).Next = Tail;
  }
  return h;
}
template<typename type, typename A>
typename wirth_struct<type, A>::Leader *wirth_struct<type, A>::Search(type w)
//Функция возвращает указатель на заголовочный узел
//ключом w. Если узел отсутствует, то функция возвращает NULL .
{
  Leader *h = Head;
  (*Tail).Key = w; //Поиск "с барьером".
  while ((*h).Key!=w) h = (*h).Next;
  if (h==Tail) //В списке заголовочных узлов нет узла с ключом w.
    h = nullptr;
  return h;
}

template<typename type, typename A>
void wirth_struct<type, A>::addArc(type x, type y) {
  Leader *p, *q;    //Рабочие указатели.
  Trailer *t, *r;    //Рабочие указатели.
  bool Res; //Флаг наличия в графе данной дуги.

  //Определим, существует ли в графе дуга (x,y)?
  p = SearchGraph(x);
  q = SearchGraph(y);
  r = (*p).Trail;
  Res = false;
  while ((r!=nullptr) && (!Res))
    if ((*r).Id==q) Res = true; else r = (*r).Next;
  if (!Res) { //Если дуга отсутствует, то поместим её в граф.
    t = new (Trailer);
    (*t).Id = q;
    (*t).Next = (*p).Trail;
    (*p).Trail = t;
    (*q).Count++;
  }
}

template<typename type, typename A>
void wirth_struct<type, A>::deleteArc(type x, type y)
{
  Leader *p, *q;
  Trailer *t, *r;
  bool Res; //Флаг наличия в графе данной дуги.

  //Определим, существует ли в графе дуга (x,y)?
  p = Search(x);
  q = Search(y);
  if ((p!=nullptr) && (q!=nullptr)) { //Вершины x и y в графе есть.
    r = (*p).Trail;
    Res = false;
    while ((r!=nullptr) && (!Res))
      if ((*r).Id==q) Res = true;
      else r = (*r).Next;
    if (Res) {//Если дуга существует, то удалим её.
      if (r==(*p).Trail) {
        (*p).Trail = (*(*p).Trail).Next;
        delete r;
        (*q).Count--;
      } else {
        t = (*p).Trail;
        while ((*t).Next!=r) t = (*t).Next;
        (*t).Next = (*(*t).Next).Next;
        delete r;
        (*q).Count--;
      }
    }
  }
}
template<typename type, typename A>
void wirth_struct<type, A>::print() {
  Leader *p; //Рабочий указатель.
  Trailer *q; //Рабочий указатель.

  p = Head;
  while (p!=Tail) {
    std::cout << (*p).Key << "((";
    q = (*p).Trail;
    while (q!=nullptr) {
      std::cout << (*(*q).Id).Key << " ";
      q = (*q).Next;
    }
    std::cout << "))";
    p = (*p).Next;
    std::cout << " ";
  }
}
template<typename type, typename A>
void wirth_struct<type, A>::deleteNode(type y)
//Функция возвращает указатель Head на структуру Вирта,
//соответствующую графу с удаленной вершиной y.
{
  Leader *p, *q; //Рабочие указатели.
  Trailer *r, *s; //Рабочие указатели.
  type x;    //Рабочая переменная.
  //Удаление всех дуг (x,y), оканчивающихся  в вершине y.
  p = Head;
  while (p!=Tail) {
    x = (*p).Key;
    deleteArc(x, y);
    p = (*p).Next;
  }
  //Удаление списка смежности вершины y.
  p = SearchGraph(y);
  r = (*p).Trail;
  while (r!=nullptr) {
    s = r;
    r = (*r).Next;
    (*(*s).Id).Count++;
    delete s;
  }
  //Удаление узла, содержащего вершину y, из  списка заголовочных узлов.
  q = Head;
  if (q==p) {
    Head = (*Head).Next;
    delete q;
  } else {
    while ((*q).Next!=p) q = (*q).Next;
    (*q).Next = (*p).Next;
    delete p;
  }
}

template<typename type, typename A>
void wirth_struct<type, A>::free_main_list(Leader **Head, Leader **Tail) {
  if (*Head!=*Tail) {
    free_main_list(&(**Head).Next, Tail);
    delete *Head;
    *Head = nullptr;
  }
}

template<typename type, typename A>
void wirth_struct<type, A>::free_trailer(Trailer **X) {
  if (*X!=nullptr) {
    free_trailer(&(**X).Next);
    delete *X;
    *X = nullptr;
  }
}
template<typename type, typename A>
void wirth_struct<type, A>::addNode(type T) {
  SearchGraph(T);
}
#endif //WIRTH__WIRTH_STRUCT_H_

#include <iostream>
#include <vector>
#define TRUE 1
#define FALSE 0
using namespace std;
 typedef struct L *Lref;//Тип: указатель на заголовочный узел.
typedef struct T *Tref;//Тип: указатель на дуговой узел.
//Описание типа заголовочного узла.
typedef struct L {
 public:
  std::string Key;    //Имя заголовочного узла.
  int Count;  //Количество предшественников.
  Tref Trail; //Указатель на список смежности, содержащий "последователей".
  Lref Next;  //Указатель на следующий узел в
  //списке заголовочных узлов.
}Leader;

//Описание типа дугового узла.
typedef struct T {
  Lref Id;
  Tref Next;
} Trailer;
template<class type>
class Spisok {
 private:
  Lref Head; //Указатель на список заголовочных узлов.
  Lref Tail; //Указатель на фиктивный элемент
  //в конце списка заголовочных узлов.
  Lref SearchGraph(type);
  Lref Search(type);
 public:
  Spisok() {//Инициализация списка заголовочных узлов.
    Head = Tail = new (Leader);
  }
  ~Spisok(); //Деструктор.
  void addArc(type, type);
  void deleteArc(type, type);
  void PrintGraph();
  void deleteNode(type);
  void Free1Graph(Lref *, Lref *);
  void Free2Graph(Tref *);
  void addNode(type);
};

int main() {
  Spisok <std::string> A;

  //Построение и вывод структуры Вирта.
  A.addArc("Hello", "hello");
  A.PrintGraph();
  cout << endl;
  A.deleteNode("hi");
  A.PrintGraph();
  cout << endl;

}
template<class type>
Spisok<type>::~Spisok() {
  //Очистка структуры Вирта.
  Lref t = Head;
  while (t!=Tail) {
    Free2Graph(&(*t).Trail);
    t = (*t).Next;
  }
  Free1Graph(&Head, &Tail);
  delete Tail;
}
template<class type>
Lref Spisok<type>::SearchGraph(type w)
//Функция возвращает указатель на заголовочный узел
//с ключом w. Если заголовочный узел отсутствует, то он
//добавляется в список. Head - указатель на структуру Вирта.
{
  Lref h;

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
template<class type>
Lref Spisok<type>::Search(type w)
//Функция возвращает указатель на заголовочный узел
//ключом w. Если узел отсутствует, то функция возвращает NULL .
{
  Lref h = Head;
  (*Tail).Key = w; //Поиск "с барьером".
  while ((*h).Key!=w) h = (*h).Next;
  if (h==Tail) //В списке заголовочных узлов нет узла с ключом w.
    h = nullptr;
  return h;
}

template<class type>
void Spisok<type>::addArc(type x, type y)
//Добавление дуги (x,y) (если ее не было!) к модифицированной структуре
//Вирта, соответствующей ориентированному графу Head.
{
  Lref p, q;    //Рабочие указатели.
  Tref t, r;    //Рабочие указатели.
  bool Res; //Флаг наличия в графе данной дуги.

  //Определим, существует ли в графе дуга (x,y)?
  p = SearchGraph(x);
  q = SearchGraph(y);
  r = (*p).Trail;
  Res = FALSE;
  while ((r!=nullptr) && (!Res))
    if ((*r).Id==q) Res = TRUE; else r = (*r).Next;
  if (!Res) { //Если дуга отсутствует, то поместим её в граф.
    t = new (Trailer);
    (*t).Id = q;
    (*t).Next = (*p).Trail;
    (*p).Trail = t;
    (*q).Count++;
  }
}

template<class type>
void Spisok<type>::deleteArc(type x, type y)
//Функция возвращает указатель Head на структуру
//Вирта, соответствующую ориентированному графу
//и полученную удалением дуги (x,y).
{
  Lref p, q;    //Рабочие указатели.
  Tref t, r;    //Рабочие указатели.
  bool Res; //Флаг наличия в графе данной дуги.

  //Определим, существует ли в графе дуга (x,y)?
  p = Search(x);
  q = Search(y);
  if ((p!=nullptr) && (q!=nullptr)) { //Вершины x и y в графе есть.
    r = (*p).Trail;
    Res = FALSE;
    while ((r!=nullptr) && (!Res))
      if ((*r).Id==q) Res = TRUE;
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

template<class type>
void Spisok<type>::PrintGraph()
//Вывод модифицированной структуры Вирта, заданной указателем
//Head и соответствующей ориентированному графу.
{
  Lref p; //Рабочий указатель.
  Tref q; //Рабочий указатель.

  p = Head;
  while (p!=Tail) {
    cout << (*p).Key << "((";
    q = (*p).Trail;
    while (q!=nullptr) {
      cout << (*(*q).Id).Key << " ";
      q = (*q).Next;
    }
    cout << "))";
    p = (*p).Next;
    cout << " ";
  }
}
template<class type>
void Spisok<type>::deleteNode(type y)
//Функция возвращает указатель Head на структуру Вирта,
//соответствующую графу с удаленной вершиной y.
{
  Lref p, q; //Рабочие указатели.
  Tref r, s; //Рабочие указатели.
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
  }
  else {
    while ((*q).Next!=p) q = (*q).Next;
    (*q).Next = (*p).Next;
    delete p;
  }
}

template<class type>
void Spisok<type>::Free1Graph(Lref *Head, Lref *Tail)
//Очистка динамической памяти, занятой линейным списком,
// заданным указателем *Head.
{
  if (*Head!=*Tail) {
    Free1Graph(&(**Head).Next, Tail);
    delete *Head;
    *Head = nullptr;
  }
}

template<class type>
void Spisok<type>::Free2Graph(Tref *X)
//Очистка динамической памяти, занятой линейным списком,
// заданным указателем *X.
{
  if (*X!=nullptr) {
    Free2Graph(&(**X).Next);
    delete *X;
    *X = nullptr;
  }
}
template<class type>
void Spisok<type>::addNode(type T) {
  SearchGraph(T);
}

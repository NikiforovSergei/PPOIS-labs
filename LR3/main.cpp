#include <iostream>

using namespace std;

struct Trail {

};
struct Node {
  int key;
  int count;
  Node *next;
};

class List {
 private:
  Node *head; //"голова" связанного списка

 public:
  List() //конструктор класса без параметров
  {
    head = NULL; //первого элемента пока нет
  }

  //метод, добавляющий новый узел в список
  void addNode(int d) {
    Node *nd = new Node; //динамически создаем новый узел

    nd->key = d;        //задаем узлу данные
    nd->next = NULL;     //новый узел в конце, поэтому NULL

    if (head==NULL)     //если создаем первый узел
      head = nd;
    else                 //если узел уже не первый
    {
      Node *current = head;

      //ищем в цикле предшествующий последнему узел
      while (current->next!=NULL)
        current = current->next;

      //предшествующий указывает на последний
      current->next = nd;
    }
  }

  //метод, выводящий связанный список на экран
  void printList() {
    Node *current = head;

    while (current!=NULL) {
      cout << current->key << endl;
      current = current->next;
    }
  }
};

int main() {
  List myList;

  myList.addNode(5);
  myList.addNode(11);
  myList.addNode(27);
  myList.addNode(35);
  myList.addNode(50);

  myList.printList();

  return 0;
}
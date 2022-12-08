#include <iostream>
#include "wirth_struct.h"
int main() {
  wirth_struct<int> temp;
  temp.addNode(2);
  temp.addNode(1);
  //temp.addArc(0,1);
  temp.addArc(2, 1);
  temp.addNode(3);
  temp.addArc(2, 3);
  temp.addArc(3,2);
  wirth_struct<int> temp2(temp);

  if (temp==temp2) {
    std::cout << "True!" << std::endl;
  }
  temp.addNode(5);
  if (temp!=temp2) {
    std::cout << "False!" << std::endl;
  }
  std::cout << temp.arc_size() << std::endl;
  temp.print();
  std::cout << std::endl;

  if (temp >= temp2) {
    std::cout << "ogo!" << std::endl;
  }
  if (temp2 <= temp) {
    std::cout << "ogox2" << std::endl;
  }

  if (temp.find(2, 1)) {
    std::cout << "Findally!" << std::endl;
  }
  std::cout << temp[0].Key << std::endl;

  auto i = wirth_struct<int>::iterator_node(temp.begin());
  while (i!=temp.end()) {
    auto j = wirth_struct<int>::iterator_edge(temp.eBegin(i));
    while (j!=temp.eEnd()) {
      std::cout << (*i).Key << "->" << (*j).Id->Key << " ";
      j++;
    }
    i++;
  }
  std::cout << std::endl;
  temp.print();
  std::cout << std::endl;
  std::cout << temp.degree(2) << std::endl;
  std::cout << temp.degree(1, 2) << std::endl;
  temp.clear();
  if (temp.empty()) {
    std::cout << "yep" << std::endl;
  }
  std::cout << temp.arc_size() << std::endl;
  //temp2.print();


}

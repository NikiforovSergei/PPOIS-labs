#include <iostream>
#include "wirth_struct.h"
int main()
{
  wirth_struct<int> temp;
  temp.addNode(2);
  temp.addNode(1);
  temp.addArc(0,1);
  temp.addArc(2,1);
  wirth_struct<int> temp2(temp);

  auto i = wirth_struct<int>::iterator_node(temp.Begin());
  std::cout << "\n";
  while (i != temp.End())
  {
    auto j = wirth_struct<int>::iterator_edge(temp.eBegin(i));
    while (j != temp.eEnd())
    {
      std::cout << (*i).Key << "->"<<(*j).Id->Key<<" ";
      j++;
    }
    i++;
  }
  //temp2.PrintGraph();

}

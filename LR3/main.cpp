#include <iostream>
#include "sort/BinaryTree.h"
#include "sort/MSD.h"

using namespace std;

int main()
{
    BinaryTree<double> tree;
    // добавление элементов в дерево
    vector<double> data_to_sort = {10.1, 2.5, 7.3, 3.6, 14.6, 7.1, 32.1};
    for(auto value : data_to_sort)
    {
        tree.insert(value);
    }
    // обход дерева
    tree.visit([](auto visited_key)
               {
                   cout<<visited_key<<" ";
               });
    cout<<endl;


// Driver Code
    // create the root node
    struct node<int> *root = root->new_node();

    // Stores the unsorted array
    // in the root node
    root->arr.insert(root->arr.end(),
                     {9330, 9950, 718,
                      8977, 6790, 95,
                      9807, 2, 741, 8586,
                      5710, 1});

    cout << "Unsorted array : ";

    // Print the unsorted array
    root->print(root->arr);

    // Find the optimal longest exponent
    int exp = root->get_max_exp(root->arr);

    // Stores the sorted numbers
    vector<int> sorted_arr;

    // Function Call
    root->msd_sort(root, exp, sorted_arr);

    cout << "Sorted array : ";

    // Print the sorted array
    root->print(sorted_arr);
    return 0;
}

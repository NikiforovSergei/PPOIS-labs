#ifndef LAB3_UNTITLED1_MSD_H
#define LAB3_UNTITLED1_MSD_H


#include <iostream>
#include <vector>

using namespace std;

// Linked list node structure
template <typename T>

struct node {
    vector<T> arr;
    struct node *nxt[10];


// Function to create a new node of
// the Linked List
    struct node *new_node(void) {
        struct node *tempNode = new node;

        for (int i = 0; i < 10; i++) {
            tempNode->nxt[i] = NULL;
        }

        // Return the created node
        return tempNode;
    }


// Function to sort the given array
// using MSD Radix Sort recursively
    void msd_sort(struct node *root, T exp,
                  vector<int> &sorted_arr) {
        if (exp <= 0) {
            return;
        }

        int j;

        // Stores the numbers in different
        // buckets according their MSD
        for (int i = 0;
             i < root->arr.size();
             i++) {

            // Get the MSD in j
            j = (root->arr[i] / exp) % 10;

            // If j-th index in the node
            // array is empty create and
            // link a new node in index
            if (root->nxt[j] == NULL) {
                root->nxt[j] = new_node();
            }

            // Store the number in j-th node
            root->nxt[j]->arr.push_back(
                    root->arr[i]);
        }

        // Sort again every child node that
        // has more than one number
        for (int i = 0; i < 10; i++) {

            // If root->next is NULL
            if (root->nxt[i] != NULL) {

                if (root->nxt[i]->arr.size()
                    > 1) {

                    // Sort recursively
                    msd_sort(root->nxt[i],
                             exp / 10,
                             sorted_arr);
                }

                    // If any node have only
                    // one number then it means
                    // the number is sorted
                else {
                    sorted_arr.push_back(
                            root->nxt[i]->arr[0]);
                }
            }
        }
    }

// Function to calculate the MSD of the
// maximum  value in the array
    int get_max_exp(vector<T> arr) {
        // Stores the maximum element
        int mx = arr[0];

        // Traverse the given array
        for (int i = 1; i < arr.size(); i++) {

            // Update the value of maximum
            if (arr[i] > mx) {
                mx = arr[i];
            }
        }

        int exp = 1;

        while (mx > 10) {
            mx /= 10;
            exp *= 10;
        }

        // Return the resultant value
        return exp;
    }

// Function to print an array
    void print(vector<T> arr) {
        for (int i = 0; i < arr.size(); i++)
            cout << arr[i] << " ";

        cout << endl;
    }
};

#endif //LAB3_UNTITLED1_MSD_H
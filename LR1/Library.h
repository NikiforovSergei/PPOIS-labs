#pragma once
#include <iostream>
#include <string>

using namespace std;

class anglo_russkii {
private:



public:
    class Node
    {
    public:
        string angl;
        string rus;
        Node* right;
        Node* left;
        Node(string angl = NULL, string rus = NULL, Node* right = nullptr, Node* left = nullptr)
        {
            this->angl = angl;
            this->rus = rus;
            this->right = right;
            this->left = left;
        }
    };
    int size;
    Node* root;
    friend anglo_russkii operator+= (anglo_russkii x, pair<string, string> s);
    void tree();
    friend anglo_russkii operator-= (anglo_russkii x, string s);
    void view_tree(Node* root, int level);
    Node* get_root() { return root; }
    int get_size() { return size; }
    Node* operator[](string x);
    void change_info(string x, string s);

};
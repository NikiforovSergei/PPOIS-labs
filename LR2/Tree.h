#pragma once

class Node {
public:
    double data;
    Node* left;
    Node* right;

    Node() = default;
 
    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }

    struct Node * addNode(double x, Node* tree) {
        if (tree == NULL) {
            tree = new Node;
            tree->data = x;
            tree->left = NULL;
            tree->right = NULL;
        }
        else if (x < tree->data)
            tree->left = addNode(x, tree->left);
        else
            tree->right = addNode(x, tree->right);
        return(tree);
    }
};
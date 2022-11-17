#pragma once
#include <iostream>
#include <vector>
#include<map>
#include<string>

using namespace std;


template<class t>
struct tree
{
    t info;
    tree* left, * right;
    int NumberOfRepeats = 0;
    
    tree(t info)
    {
        this->info = info;
    }

    tree() {
        this->left = NULL; this->right = NULL;
    };


    tree* MakeLeaf(t info)
    {
        tree<t>* temp = new tree<t>;
        temp->info = info;
        temp->left = temp->right = NULL;
        return temp;

    };

    void AddLeaf(t info) {
        bool find = true;
        tree<t>* anc = new tree<t>;
        tree<t>* temp = new tree<t>;
        temp = this;
        while (temp && find) {
            anc = temp;
            if (info == temp->info) {
                find = false;
                temp->NumberOfRepeats++;
            }
            else
                if (info < temp->info) temp = temp->left;
                else temp = temp->right;
        }
        if (find) {
            temp = MakeLeaf(info);
            if (info < anc->info) anc->left = temp;
            else anc->right = temp;
        }



    }

    void CreateTree(t* list, int size) {
        if (!size) {
            return;
        }
        for (int i = 0; i < size; i++)
        {
            if (!i)
            {
                tree<t>* temp = new tree<t>;
                temp = MakeLeaf(list[i]);
                *this = *temp;
            }

            else {

                this->AddLeaf(list[i]);

            }
        }

    }

    void LRootR(vector<t>& list)
    {
        if (!this)
            return;
        (*(this->left)).LRootR(list);   //рекурсивный вызов левого поддерева
        list.push_back(this->info);
        if (this->NumberOfRepeats)
        {
            for (int i = 0; i < this->NumberOfRepeats; i++)
                list.push_back(this->info);
        }
        (*(this->right)).LRootR(list);  //рекурсивный вызов правого поддерева
    }

    void ShowTree(int level) {
        string str;
        if (this) {
            ShowTree(this->right, level + 1); // Правое поддерево
            for (int i = 0; i < level; i++) str = str + " ";
            cout << str << level << "_ " << this->info << '\n';
            ShowTree(this->left, level + 1); // Левое поддерево
        }


    }


};

template <class t>
void BinaryTreeSort(t*& arr, int size)
{
    vector <t> rez;
    tree<t> root;
    root.CreateTree(arr, size);
    root.LRootR(rez);
    for (int i = 0; i < size; i++)
        arr[i] = move(rez[i]);
}


/// ////////////////////////////////////////////////////////

template<class t>
void RadixSortMSD(t*& arr, int size_of_el)
{
    if (!size_of_el)
        return;
    map<string, int> link; vector <string> arr_str;

    for (int i = 0; i < size_of_el; i++)
    {
        arr_str.push_back(to_string(arr[i]));
        link.insert({ arr_str[i], i });
    }

    auto* ptr = &arr_str.front();



    RadixSortMSD<string>(ptr, size_of_el);


    for (string& i : arr_str)
    {
        int counter = 0;
        for (char j : i)
            if (j == ' ')
                counter++;
        i.resize(i.size() - counter);
    }

    vector <t> rezult;
    for (auto i : arr_str)
        rezult.push_back(arr[link[i]]);
    for (int i = 0; i < size_of_el; i++)
        arr[i] = rezult[i];
}



template<> void RadixSortMSD<string>(string*& arr, int size_of_el)
{
    if (!size_of_el)
        return;
    string max_element = "";

    int max_size = 0;
    for (int i = 0; i < size_of_el; i++)
        if (arr[i].size() > max_size)
            max_size = arr[i].size();


    int max = max_size;

    for (int i = 0; i < size_of_el; i++) {
        if (arr[i].size() < max)
        {
            int dif = max - arr[i].size();
            while (dif)
            {
                if (arr[i][arr[i].length()-1] <= '9' && arr[i][arr[i].length() - 1] >= '0')
                    arr[i] = " " + arr[i];
                else arr[i] += " "; //:
                dif--;
            }
        }
    }
    const double factor = 1.2473309;
    int step = size_of_el;

    for (int position = 0; position < max_size; position++)
    {
        while (step >= 1)
        {
            for (int i = 0; i + step < size_of_el; i++)
            {
                if (((arr[i][position] > arr[i + step][position]) && (position == 0)) ||
                    ((arr[i][position] > arr[i + step][position]) && (arr[i][position - 1] == arr[i + step][position - 1])) ||
                    (arr[i][position] > arr[i + step][position]) && (arr[i + step][position] == '.') ||
                    (arr[i][position] > arr[i + step][position]) && (arr[i + step][position] == ' '))
                {
                    bool flag = false;
                    [=, &flag]()->void {
                        int pos = position;
                        while (pos)
                        {
                            int p = --pos;
                            if (arr[i][p] < arr[i + step][p])
                                flag = true;
                        }
                        return;
                    }();
                   /* if (arr[i + step][position] == ' ')
                        flag = false;*/
                    if (!flag)
                    {
                        string temp = arr[i + step];
                        arr[i + step] = arr[i];
                        arr[i] = temp;
                    }
                }
            }
            step /= factor;
        }
        step = size_of_el;
    }

    if (arr[0][arr[0].length() - 1] <= '9' && arr[0][arr[0].length() - 1] >= '0')
    {

        for (int i = 0; i < size_of_el; i++)
        {
            int counter = 0;
            for (char j : arr[i])
                if (j == ' ')
                    counter++;
            arr[i].erase(0, counter);

        }
        return;
    }

    for (int i = 0; i < size_of_el; i++)
    {
        int counter = 0;
        for (char j : arr[i])
            if (j == ' ')
                counter++;
        arr[i].resize(arr[i].size() - counter);
    }

}


template<> void RadixSortMSD<char>(char*& arr, int size_of_el)
{
    if (!size_of_el)
        return;
    vector <string> arr_str;

    for (int i = 0; i < size_of_el; i++)
    {
        string temp = ""; temp += arr[i];
        arr_str.push_back(temp);
    }

    auto* ptr = &arr_str.front();

    RadixSortMSD<string>(ptr, size_of_el);

    for (int i = 0; i < size_of_el; i++)
        arr[i] = arr_str[i][0];
}
#include "pch.h"
#include"../head.h"

template <class t>
void BinaryTreeSort(t*& arr, int size);

template<class t>
void RadixSortMSD(t*& arr, int size_of_el);

template<> void RadixSortMSD<string>(string*& arr, int size_of_el);

template<> void RadixSortMSD<char>(char*& arr, int size_of_el);


class test
{
public:
    int d;
    bool operator>(test b) {
        if (this->d > b.d)
            return true;
        else return false;
    }
    bool operator<(test b) {
        if (this->d < b.d)
            return true;
        else return false;
    }
    bool operator==(test b) {
        if (this->d == b.d)
            return true;
        else return false;
    } 
    bool operator!=(test b) {
        if (this->d != b.d)
            return true;
        else return false;
    }



    
};

string to_string(test a)
{
    return std::to_string(a.d);
}

TEST(tree, int) {

/////////////////////////ARRAY////////////////////////////////////////////////

int arr[] = { 5, 42, 1,37, 88, 81, 62, 64, 90, 97,1, 52, 20, 91, 61, 36, 80, 42,65, 1,12, 88, 55, 1, 69 };
int arr1[] = { 1,1,1,1,5,12,20,36,37,42,42,52,55,61,62,64,65,69,80,81,88,88,90,91,97 };

auto* ptr = arr;
BinaryTreeSort(ptr, size(arr));

bool rez = false;
for (int i = 0; i < size(arr); i++)
{
    if (i == size(arr) - 1)
        rez = true;
    if (arr[i] != arr1[i])
    {
        i = size(arr) - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);

///////////////////////////////VECTOR////////////////////////////////////////

vector <int> vec = { 5, 42, 1,37, 88, 81, 62, 64, 90, 97,1, 52, 20, 91, 61, 36, 80, 42,65, 1,12, 88, 55, 1, 69 };
vector <int> vec1 = { 1,1,1,1,5,12,20,36,37,42,42,52,55,61,62,64,65,69,80,81,88,88,90,91,97 };

auto* ptr_v = &vec.front();
BinaryTreeSort(ptr_v, vec.size());

rez = false;
for (int i = 0; i < vec.size(); i++)
{
    if (i == vec.size() - 1)
        rez = true;
    if (vec[i] != vec1[i])
    {
        i = vec.size() - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);
}

TEST(tree, double) {
/////////////////////////ARRAY////////////////////////////////////////////////

double arr[] = { 48.68,37.48,28.2,90.6,19.56,86.76,18.28,16.36,69.8,27.88,57.64,53.8,98.28,64.04,96.04,65.32,57,79.4,54.12,14.44 };
double arr1[] = { 14.44,16.36,18.28,19.56,27.88,28.2,37.48,48.68,53.8,54.12,57,57.64,64.04,65.32,69.8,79.4,86.76,90.6,96.04,98.28 };

auto* ptr = arr;
BinaryTreeSort(ptr, size(arr));

bool rez = false;
for (int i = 0; i < size(arr); i++)
{
    if (i == size(arr) - 1)
        rez = true;
    if (arr[i] != arr1[i])
    {
        i = size(arr) - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);
///////////////////////////////VECTOR////////////////////////////////////////

vector <double> vec = { 48.68,37.48,28.2,90.6,19.56,86.76,18.28,16.36,69.8,27.88,57.64,53.8,98.28,64.04,96.04,65.32,57,79.4,54.12,14.44 };
vector <double> vec1 = { 14.44,16.36,18.28,19.56,27.88,28.2,37.48,48.68,53.8,54.12,57,57.64,64.04,65.32,69.8,79.4,86.76,90.6,96.04,98.28 };

auto* ptr_v = &vec.front();
BinaryTreeSort(ptr_v, vec.size());

rez = false;
for (int i = 0; i < vec.size(); i++)
{
    if (i == vec.size() - 1)
        rez = true;
    if (vec[i] != vec1[i])
    {
        i = vec.size() - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);
}

TEST(tree, string) {
/////////////////////////ARRAY////////////////////////////////////////////////

string arr[] = { "fgdf", "fggdfssda", "asdefe", "oipre", "a", "aa", "aba" };
string arr1[] = { "a","aa","aba","asdefe","fgdf","fggdfssda","oipre" };

auto* ptr = arr;
BinaryTreeSort(ptr, size(arr));

bool rez = false;
for (int i = 0; i < size(arr); i++)
{
    if (i == size(arr) - 1)
        rez = true;
    if (arr[i] != arr1[i])
    {
        i = size(arr) - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);

///////////////////////////////VECTOR////////////////////////////////////////

vector <string> vec = { "fgdf", "fggdfssda", "asdefe", "oipre", "a", "aa", "aba" };
vector <string> vec1 = { "a","aa","aba","asdefe","fgdf","fggdfssda","oipre" };

auto* ptr_v = &vec.front();
BinaryTreeSort(ptr_v, vec.size());

rez = false;
for (int i = 0; i < vec.size(); i++)
{
    if (i == vec.size() - 1)
        rez = true;
    if (vec[i] != vec1[i])
    {
        i = vec.size() - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);
}

TEST(tree, char) {
    /////////////////////////ARRAY////////////////////////////////////////////////

    char arr[] = { 's', 'e','s', '\n', 'a'};
    char arr1[] = { '\n', 'a', 'e', 's','s'};

    auto* ptr = arr;
    BinaryTreeSort(ptr, size(arr));

    bool rez = false;
    for (int i = 0; i < size(arr); i++)
    {
        if (i == size(arr) - 1)
            rez = true;
        if (arr[i] != arr1[i])
        {
            i = size(arr) - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);

    ///////////////////////////////VECTOR////////////////////////////////////////

    vector <char> vec = { 's', 'e','s', '\n', 'a' };
    vector <char> vec1 = { '\n', 'a', 'e', 's','s' };

    auto* ptr_v = &vec.front();
    BinaryTreeSort(ptr_v, vec.size());

    rez = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == vec.size() - 1)
            rez = true;
        if (vec[i] != vec1[i])
        {
            i = vec.size() - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
}

TEST(tree, class) {
/////////////////////////ARRAY////////////////////////////////////////////////

vector<vector<int>> arr = { {2,2}, { 1,1 }};

vector<vector<int>> arr1 = { {1,1},{2,2} };

auto* ptr = &arr.front();
BinaryTreeSort(ptr, size(arr));

bool rez = false;

for (int i = 0; i < size(arr); i++)
{
    if (i == size(arr) - 1)
        rez = true;
    if (arr[i] != arr1[i])
    {
        i = size(arr) - 1;
        rez = false;
    }

}
EXPECT_TRUE(rez);

///////////////////////////////VECTOR////////////////////////////////////////

vector <test> vec = { {26 }, { 52 }, { 23 }, { 84 }, { 40 }, { 25 }, { 13 } };
vector <test> vec1 = { {13}, {23}, {25}, {26}, {40},{52},{84} };

auto* ptr_v = &vec.front();
BinaryTreeSort(ptr_v, vec.size());

rez = false;
for (int i = 0; i < vec.size(); i++)
{
    if (i == vec.size() - 1)
        rez = true;
    if (vec[i] != vec1[i])
    {
        i = vec.size() - 1;
        rez = false;
    }

}

EXPECT_TRUE(rez);
}

//_____________________________________________________//

TEST(MSD, int) {

    /////////////////////////ARRAY////////////////////////////////////////////////

    int arr[] = { 5, 42, 1,37, 88, 81, 62, 64, 90, 97,1, 52, 20, 91, 61, 36, 80, 42,65, 1,12, 88, 55, 1, 69 };
    int arr1[] = { 1,1,1,1,5,12,20,36,37,42,42,52,55,61,62,64,65,69,80,81,88,88,90,91,97 };

    auto* ptr = arr; 
    RadixSortMSD(ptr, size(arr));

    bool rez = false;
    for (int i = 0; i < size(arr); i++)
    {
        if (i == size(arr) - 1)
            rez = true;
        if (arr[i] != arr1[i])
        {
            i = size(arr) - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);

    ///////////////////////////////VECTOR////////////////////////////////////////

    vector <int> vec = { 5, 42, 1,37, 88, 81, 62, 64, 90, 97,1, 52, 20, 91, 61, 36, 80, 42,65, 1,12, 88, 55, 1, 69 };
    vector <int> vec1 = { 1,1,1,1,5,12,20,36,37,42,42,52,55,61,62,64,65,69,80,81,88,88,90,91,97};

    auto* ptr_v = &vec.front();
    RadixSortMSD(ptr_v, vec.size());

    rez = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == vec.size() - 1)
            rez = true;
        if (vec[i] != vec1[i])
        {
            i = vec.size() - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
}

TEST(MSD, double) {
    /////////////////////////ARRAY////////////////////////////////////////////////

    double arr[] = { 48.68,37.48,28.2,90.6,19.56,86.76,18.28,16.36,69.8,27.88,57.64,53.8,98.28,64.04,96.04,65.32,57,79.4,54.12,14.44 };
    double arr1[] = { 14.44,16.36,18.28,19.56,27.88,28.2,37.48,48.68,53.8,54.12,57,57.64,64.04,65.32,69.8,79.4,86.76,90.6,96.04,98.28 };

    auto* ptr = arr;
    RadixSortMSD(ptr, size(arr));

    bool rez = false;
    for (int i = 0; i < size(arr); i++)
    {
        if (i == size(arr) - 1)
            rez = true;
        if (arr[i] != arr1[i])
        {
            i = size(arr) - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
    ///////////////////////////////VECTOR////////////////////////////////////////

    vector <double> vec = { 48.68,37.48,28.2,90.6,19.56,86.76,18.28,16.36,69.8,27.88,57.64,53.8,98.28,64.04,96.04,65.32,57,79.4,54.12,14.44 };
    vector <double> vec1 = { 14.44,16.36,18.28,19.56,27.88,28.2,37.48,48.68,53.8,54.12,57,57.64,64.04,65.32,69.8,79.4,86.76,90.6,96.04,98.28 };

    auto* ptr_v = &vec.front();
    RadixSortMSD(ptr_v, vec.size());

    rez = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == vec.size() - 1)
            rez = true;
        if (vec[i] != vec1[i])
        {
            i = vec.size() - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
}

TEST(MSD, string) {
    /////////////////////////ARRAY////////////////////////////////////////////////

    string arr[] = { "fgdf", "fggdfssda", "asdefe", "oipre", "a", "aa", "aba" }; 
    string arr1[] = { "a","aa","aba","asdefe","fgdf","fggdfssda","oipre"};
    
    auto* ptr = arr;
    RadixSortMSD(ptr, size(arr));

    bool rez = false;

    for (int i = 0; i < size(arr); i++)
    {
        if (i == size(arr) - 1)
            rez = true;
        if (arr[i] != arr1[i])
        {
            i = size(arr) - 1;
            rez = false;
        }

    }
    EXPECT_TRUE(rez);


    ///////////////////////////////VECTOR////////////////////////////////////////

    vector <string> vec = { "fgdf", "fggdfssda", "asdefe", "oipre", "a", "aa", "aba" };
    vector <string> vec1 = { "a","aa","aba","asdefe","fgdf","fggdfssda","oipre" };

    auto* ptr_v = &vec.front();
    RadixSortMSD(ptr_v, vec.size());

    rez = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == vec.size() - 1)
            rez = true;
        if (vec[i] != vec1[i])
        {
            i = vec.size() - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
}

TEST(MSD, char) {
    /////////////////////////ARRAY////////////////////////////////////////////////

    char arr[] = { 's', 'e','s', '\n', 'a' };
    char arr1[] = { '\n', 'a', 'e', 's','s' };

    auto* ptr = arr;
    RadixSortMSD(ptr, size(arr));

    bool rez = false;
    for (int i = 0; i < size(arr); i++)
    {
        if (i == size(arr) - 1)
            rez = true;
        if (arr[i] != arr1[i])
        {
            i = size(arr) - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);

    ///////////////////////////////VECTOR////////////////////////////////////////

    vector <char> vec = { 's', 'e','s', '\n', 'a' };
    vector <char> vec1 = { '\n', 'a', 'e', 's','s' };

    auto* ptr_v = &vec.front();
    RadixSortMSD(ptr_v, vec.size());

    rez = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == vec.size() - 1)
            rez = true;
        if (vec[i] != vec1[i])
        {
            i = vec.size() - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
}

TEST(MSD, class) {
    /////////////////////////ARRAY////////////////////////////////////////////////

    test arr[] = { {26 }, { 52 }, { 23 }, { 84 }, { 40 }, { 25 }, { 13 } };

    test arr1[] = { {13}, {23}, {25}, {26}, {40},{52},{84} };

    auto* ptr = arr;
    RadixSortMSD(ptr, size(arr));

    bool rez = false;

    for (int i = 0; i < size(arr); i++)
    {
        if (i == size(arr) - 1)
            rez = true;
        if (arr[i] != arr1[i])
        {
            i = size(arr) - 1;
            rez = false;
        }

    }
    EXPECT_TRUE(rez);

    ///////////////////////////////VECTOR////////////////////////////////////////

    vector <test> vec = { {26 }, { 52 }, { 23 }, { 84 }, { 40 }, { 25 }, { 13 } };
    vector <test> vec1 = { {13}, {23}, {25}, {26}, {40},{52},{84} };

    auto* ptr_v = &vec.front();
    RadixSortMSD(ptr_v, vec.size());

    rez = false;
    for (int i = 0; i < vec.size(); i++)
    {
        if (i == vec.size() - 1)
            rez = true;
        if (vec[i] != vec1[i])
        {
            i = vec.size() - 1;
            rez = false;
        }

    }

    EXPECT_TRUE(rez);
}






































/*// 
    //double arr1[] = { 48.68,37.48,28.2,90.6,19.56,86.76,18.28,16.36,69.8,27.88,57.64,53.8,98.28,64.04,96.04,65.32,57,79.4,54.12,14.44 };
   // string arr1[] = { "fgdf", "fggdfssda", "asdefe", "oipre", "a", "aa", "aba" };
   // test arr1[] = { {26 }, { 52 }, { 23 }, { 84 }, { 40 }, { 25 }, { 13 }};
    //vector <int> rez;

    vector <string > arr1 = { "fgdf", "fggdfssda", "asdefe", "oipre", "a", "aa", "aba" };


  /*  CreateTree(root, arr, size(arr));
    ShowTree<int>(root, 0);

    LRootR(root, rez);*/
    //for (int i : rez)
    //    cout << i << ' ';
    //cout << endl;
 //   cout << rez[0].d << ' ' << rez[1].d << ' ' << rez[2].d << ' ' << rez[3].d << ' ' << rez[4].d << ' ' << rez[5].d << ' ' << rez[6].d << ' ';
   // int arr1[] = {  88, 55, 1, 69 };
//int s = arr1.size(); size(arr1);
//
////auto* ptr = arr1.begin();
//auto* ptr = &arr1.front();
//
//BinaryTreeSort(ptr, s);
//
//for (auto i : arr1)
//cout << i << ' ';
//cout << endl;
//int rezult[] = {1,1,1,1,5,12,20,36,37,42,4252,55,}
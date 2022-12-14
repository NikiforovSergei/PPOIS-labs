#ifndef SET_H
#define SET_H

#include<string>
#include<vector>
using namespace std;


namespace custom_set
{

    class Set

    {
    public:
        Set(vector<string>);
        vector<string> operator + (Set const &obj);
        vector<string> operator - (Set const &obj);
        vector<string> operator * (Set const &obj);
        vector<string> set_add(string);
        vector<string> set_remove(string);
        static vector<string> set_union(vector<string>, vector<string>);
        static vector<string> set_intersection(vector<string>, vector<string>);
        static vector<string> set_difference(vector<string>, vector<string>);
        bool operator [] (string const &obj);
        bool set_inclusion(string);
        bool is_empty();
        int set_length();
        void print();
        void set_boolean();
        void set_set(vector<string>);

    private:
        vector<string> set;
        string bool_calc(vector<string>, int, int);
        string get_elem(string);
    };
}

#endif // SET_H
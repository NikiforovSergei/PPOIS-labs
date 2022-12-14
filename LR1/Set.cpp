#include <iostream>
#include <string>
#include <vector>
#include "Set.h"

using namespace std;
using namespace custom_set;

string Set::bool_calc(vector<string> a, int n, int i){
    string res, res1;
    if (n)
    {
        if (n & 1){
            res.append(a[i] + ",");
        }
        res1 = bool_calc(a, n >> 1, i + 1);
        res += res1;
        return res;
    }
    return res;
}


Set::Set(vector<string> set1) {set = set1;}


vector<string> Set::operator + (Set const &obj){
    vector<string> result_set;
    result_set = set_union(set, obj.set);
    return result_set;
}


vector<string> Set::operator * (Set const &obj){
    vector<string> result_set;
    result_set = set_intersection(set, obj.set);
    return result_set;
}


vector<string> Set::operator - (Set const &obj){
    vector<string> result_set;
    result_set = set_difference(set, obj.set);
    return result_set;
}


bool Set::operator[](const string &obj){
    return set_inclusion(obj);
}


vector<string> Set::set_add(string new_element){
    string new_element_literal, elem_literal;
    Set target(set);
    if (!target.set_inclusion(new_element)){
        set.push_back(new_element);
        cout << "The element has succesfully added to the set!";
    }else{
        cout<<"The element already exist";
    }
    return set;
}

vector<string> Set::set_remove(string element_to_remove){
    int pos = 0;
    string elem_literal;
    for (string elem: set){
        elem_literal = elem;
        if (elem_literal == element_to_remove){
            set.erase(set.begin()+pos);
            cout << "The element has succesfully removed from the set!";
            return set;
        }
        pos++;
    }
    cout << "There's no match for passed element!";
    return set;
}


vector<string> Set::set_union(vector<string> set_1, vector<string> set_2){
    vector<string> result_set{set_1};
    for (string el1:set_2) {
        bool isHere = false;
        for (string el2: result_set) {
            if (el1.compare(el2)==0){
                isHere = true;
                break;
            }
        }
        if (!isHere) result_set.push_back(el1);
    }
    return result_set;
}


vector<string> Set::set_intersection(vector<string> set_1, vector<string> set_2){
    vector<string> result_set;
    for (string el1:set_1) {
        for (string el2:set_2) {
            if (el1.compare(el2)==0){
                result_set.push_back(el1);
                break;
            }
        }
    }
    return result_set;
}


vector<string> Set::set_difference(vector<string> set_1, vector<string> set_2){
    vector<string> result_set;
    for (string el1:set_1) {
        bool isHere = false;
        for (string el2:set_2) {
            if (el1.compare(el2)==0){
                isHere = true;
                break;
            }
        }
        if (!isHere) result_set.push_back(el1);
    }
    return result_set;
}


bool Set::set_inclusion(string target){
    string parsed_elem;
    for (string elem: set){
        parsed_elem = elem;
        if (parsed_elem == target)
            return true;
    }
    return false;
}


int Set::set_length(){
    return set.size();
}


bool Set::is_empty(){
    if (set.empty())
        return true;

    return false;
}


void Set::print() {
    cout << "The set is: "<<endl;
    cout << "{ ";
    for (string element: set){
        if (element == "%"){
            cout << "{}";
            break;
        }
        cout << element + ", ";
    }
    cout << "}"<<endl;
}

void Set::set_boolean()
{
    vector<string> res;
    int r, i, size;
    string s;
    size = set.size();
    r = 1 << size;
    for (i = 0; i < r; i++){
        s = bool_calc(set, i, 0);
        res.push_back(s);

    }
    cout << "{ ";
    for (string elem: res){
        cout << "{" << elem << "}" << ", ";
    }
    cout << "}";
}
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Element
{
    Element* left, * right;
    string nullpoint = "Element not found", eng_word, rus_word;

public:
    Element(string eng_inp, string rus_inp) {
        eng_word = eng_inp;
        rus_word = rus_inp;
        left = right = nullptr;
    } 

    string get_eng() {
        return eng_word;
    }

    string get_rus() {
        return rus_word;
    }

    string& get_trans() {
        return rus_word;
    }

    Element* get_left() {
        return left;
    }

    Element* get_right() {
        return right;
    }

    string& nullpointer() {
        return nullpoint;
    }   

    void set_eng(string eng_inp) {
        this->eng_word = eng_inp;
    }

    void set_rus(string rus_inp) {
        this->rus_word = rus_inp;
    }

    void del_trans(){
        this->rus_word = "";
    }

    void set_left(Element* left_inp) {
        left = left_inp;
    }

    void set_right(Element* right_inp) {
        right = right_inp;
    }

}; 

class Dictionary
{
private:
    Element* root;

    int elements_count(Element* node);

public:     

    void add_node(Element* node, string eng_inp, string rus_inp);

    string& find_word(Element* t, string eng_inp); 

    void change_tr(Element* t, string eng_inp, string new_rus); 

    Element* delete_word(Element* node, string eng_inp); 
    
    int get_num_of_w();

    string operator[] (string eng_inp);
    void operator[] (pair<string, string> transl); 
    void operator -= (string eng_inp); ///overloaded operator of deleting the word
    void operator += (pair<string, string> eng_inp); ///overloaded operator of adding a word and one translation to this word
};
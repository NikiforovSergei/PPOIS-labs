#include "dict.h"
using namespace std;

/*!
     \brief adding a node (word) to a tree (dictionary)
 */

void Dictionary::add_node(Element* node, string eng_inp, string rus_inp) {
    if (!root) {
        Element* temp = new Element(eng_inp, rus_inp);
        root = temp;      
    }
    else {
        Element* prev, * temp;
        bool has_dub = true;
        temp = node; prev = temp;

        while (temp && has_dub)
        {
            prev = temp;
            if (eng_inp == temp->get_eng())
            {
                cout << "Слово уже есть в словаре";
                has_dub = false;
                break;
            }
            if (eng_inp < temp->get_eng()) {
                temp = temp->get_left();
                continue;
            }
            if (eng_inp > temp->get_eng())
                temp = temp->get_right();
        }
        if (has_dub)
        {      
            Element* new_node = new Element(eng_inp, rus_inp);
            temp = new_node;
            if (eng_inp < prev->get_eng())
                prev->set_left(temp);
            else
                prev->set_right(temp);
        }
    }
}

/*!
     \brief looking for a word and its translation
     \return Russian translation of the desired English word
 */

string& Dictionary::find_word(Element* el_pointer, string eng_inp)
{
    if (!el_pointer)
        return root->nullpointer(); 
    if (eng_inp == el_pointer->get_eng()) return el_pointer->get_trans();
 
    if (eng_inp < el_pointer->get_eng())
        return find_word(el_pointer->get_left(), eng_inp);
    if (eng_inp > el_pointer->get_eng())
        return find_word(el_pointer->get_right(), eng_inp);
}

/*!
     \brief changes the translation of a word that already exists in the dictionary
 */

void Dictionary::change_tr(Element* el_pointer, string eng_inp, string new_rus)
{
    if (!el_pointer) return ;
    if (eng_inp == el_pointer->get_eng())
    {
        el_pointer->set_rus(new_rus);
    }

    if (eng_inp < el_pointer->get_eng())
        change_tr(el_pointer->get_left(), eng_inp, new_rus);
    if (eng_inp > el_pointer->get_eng())
        change_tr(el_pointer->get_right(), eng_inp, new_rus);
}

/*!
     \brief removes a word and its translation from the dictionary
 */

Element* Dictionary::delete_word(Element* node, string eng_inp)
{
    bool trying_to_delete_root = false;
    if (!node) return node;
    if (node == root) trying_to_delete_root = true;
    if (eng_inp == node->get_eng()) 
    {
        Element* tmp;
        if (!node->get_right())
            tmp = node->get_left();
        else {
            Element* p = node->get_right();
            if (!p->get_left()) {
                p->set_left(node->get_left());
                tmp = p;
            }
            else {
                Element* pmin = p->get_left();
                while (pmin->get_left()) {
                    p = pmin;
                    pmin = p->get_left();
                }
                p->set_left(pmin->get_right());
                pmin->set_left(node->get_left());
                pmin->set_right(node->get_right());
                tmp = pmin;
            }
        }
        delete node;
        if (trying_to_delete_root) root = tmp;
        return tmp;
    }
    else if (eng_inp < node->get_eng())
        node->set_left(delete_word(node->get_left(), eng_inp));
    else
        node->set_right(delete_word(node->get_right(), eng_inp));
    return node;
}

/*!
     \brief counts the number of words in the dictionary
 */

int Dictionary::elements_count(Element* node) {
    int count = 0;
    if (node) {
        count++;
        if (node->get_left())
            count += elements_count(node->get_left());
        if (node->get_right())
            count += elements_count(node->get_right());
    }
    return count;
}

int Dictionary::get_num_of_w() {
    return elements_count(root);
}

string Dictionary::operator[] (string eng_inp)  ///overloaded operator to get translations
{
    return find_word(root, eng_inp);
}

void Dictionary::operator[] (pair<string, string> transl) ///overloaded operator to change the translation
{
    this->change_tr(root, transl.first, transl.second);
}

void Dictionary::operator-= (string eng_inp) ///overloaded operator of deleting the word
{
    this->delete_word(root, eng_inp);
}

void Dictionary::operator+= (pair<string, string> input) ///overloaded operator of adding a word and one translation to this word
{
    this->add_node(root, input.first, input.second);
}
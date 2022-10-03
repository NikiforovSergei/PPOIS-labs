#include <iostream>
#include <string>
#include <vector>
#include "Set.h"

using namespace std;
using namespace custom_set;

/*!
 * \brief recursively figuring out a multiset boolean
 * \param a - given multiset
 * \param n - bitwise shift
 * \param i - index
 * \return an element of multiset boolean
 */
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

/*!
 * \brief get coefficients of an element
 * \param element - given element of multiset
 * \return integer value (element coefficient)
 */
int Set::get_coeff(string element){
    bool is_one = true;
    string coef;
    for (char elem: element){
        if (not (elem >= '0' and elem <= '9')){
            if (is_one)
                return 1;
            else
                return stoi(coef);
        }
        else{
            coef.push_back(elem);
            is_one = false;
        }
    }
    return stoi(coef);
}

/*!
 * \brief get an element (without its coefficient)
 * \param element - given element of multiset
 * \return element (without coefficient)
 */
string Set::get_elem(string element){
    string given_element;
    for (char elem: element){
        if (not (elem >= '0' and elem <='9'))
           given_element.push_back(elem);
        else if (given_element.size() > 0)
           given_element.push_back(elem);
    }
    return given_element;
}

/*!
 * \brief class constructor
 * \param set1 - given multiset
 */
Set::Set(vector<string> set1) {set = set1;}

/*!
 * \brief override '+' operator
 * \param obj - the second literal object
 * \return union of two multisets
 */
vector<string> Set::operator + (Set const &obj){
    vector<string> result_set;
    result_set = set_union(set, obj.set);
    return result_set;
}

/*!
 * \brief override '*' operator
 * \param obj - the second literal object
 * \return intersection of two multisets
 */
vector<string> Set::operator * (Set const &obj){
    vector<string> result_set;
    result_set = set_intersection(set, obj.set);
    return result_set;
}

/*!
 * \brief override '-' operator
 * \param obj - the second literal object
 * \return difference of two multisets
 */
vector<string> Set::operator - (Set const &obj){
    vector<string> result_set;
    result_set = set_difference(set, obj.set);
    return result_set;
}

/*!
 * \brief override '[]' operator
 * \param obj - target element
 * \return result of inclusion checkout (true/false)
 */
bool Set::operator[](const string &obj){
    return set_inclusion(obj);
}

/*!
 * \brief add a given to multiset
 * \param new_element - given element
 * \return updated multiset
 */
    vector<string> Set::set_add(string new_element){
        int new_element_coeff, pos = 0;
        string new_element_literal, elem_literal;
        Set target(set);
        if (not target.set_inclusion(get_elem(new_element))){
            set.push_back(new_element);
        }
        else{
            new_element_coeff = get_coeff(new_element);
            new_element_literal = get_elem(new_element);
            for (string element: set){
                elem_literal = get_elem(element);
                if (elem_literal == new_element_literal){
                    set.erase(set.begin()+pos);
                    set.insert(set.begin()+pos, to_string(get_coeff(element) + new_element_coeff)+elem_literal);
                    cout << "The element has succesfully added to the multiset!";
                    return set;
                }
                pos++;
            }
        }
        cout << "The element has succesfully added to the multiset!";
        return set;
    }

/*!
 * \brief remove an element from multiset
 * \param element_to_remove - given element
 * \return updated multiset
 */
    vector<string> Set::set_remove(string element_to_remove){
        int pos = 0;
        string elem_literal;
        for (string elem: set){
            elem_literal = get_elem(elem);
            if (elem_literal == element_to_remove){
                set.erase(set.begin()+pos);
                cout << "The element has succesfully removed from the multiset!";
                return set;
            }
            pos++;
        }
        cout << "There's no match for passed element!";
        return set;
    }

/*!
 * \brief inion of two multisets
 * \param set_1 - the first given set
 * \param set_2 - the second given set
 * \return result of the union
 */
    vector<string> Set::set_union(vector<string> set_1, vector<string> set_2){
        vector<string> result_set;
        string elem_1, elem_2, target;
        int max_elem, coef_1, coef_2;

        for (int i=0;i<set_1.size();i++){
            for (int k=0;k<set_2.size();k++){
                Set res(result_set);
                target = get_elem(set_1[i]);
                    elem_1 = get_elem(set_1[i]);
                    elem_2 = get_elem(set_2[k]);
                    if (elem_1 == elem_2){
                        coef_1 = get_coeff(set_1[i]);
                        coef_2 = get_coeff(set_2[k]);
                        max_elem = max(coef_1, coef_2);
                        if (max_elem == coef_1)
                            result_set.push_back(set_1[i]);
                        else
                            result_set.push_back(set_2[k]);
                    }
        }
        }
        for (int i=0;i<set_1.size();i++){
            Set res = result_set;
            target = get_elem(set_1[i]);
            if (not res.set_inclusion(target))
                result_set.push_back(set_1[i]);
        }
        for (int k=0;k<set_2.size();k++){
            for (int i=0;i<set_1.size();i++){
                Set res(result_set);
                target = get_elem(set_2[k]);
                if (not res.set_inclusion(target)){
                    elem_1 = get_elem(set_1[i]);
                    elem_2 = get_elem(set_2[k]);
                    if (elem_1 == elem_2){
                        coef_1 = get_coeff(set_1[i]);
                        coef_2 = get_coeff(set_2[k]);
                        max_elem = max(coef_1, coef_2);
                        if (max_elem == coef_1){
                            if (not res.set_inclusion(get_elem(set_1[i])))
                                result_set.push_back(set_1[i]);
                        }
                        else
                            if (not res.set_inclusion(get_elem(set_2[k])))
                                result_set.push_back(set_2[k]);
                    }
                    else
                        result_set.push_back(set_2[k]);
                }
                else
                    if (not res.set_inclusion(get_elem(set_2[k])))
                        result_set.push_back(set_2[k]);
        }
        }

        return result_set;
    }

/*!
 * \brief intersection of two multisets
 * \param set_1 - the first given multiset
 * \param set_2 - the second give multiset
 * \return result of the intersection
 */
    vector<string> Set::set_intersection(vector<string> set_1, vector<string> set_2){
        vector<string> result_set;
        string elem_1, elem_2, target;
        int min_elem, coef_1, coef_2;

        for (int i=0;i<set_1.size();i++){
            for (int k=0;k<set_2.size();k++){
                Set res(result_set);
                target = get_elem(set_1[i]);
                if (not res.set_inclusion(target)){
                    elem_1 = get_elem(set_1[i]);
                    elem_2 = get_elem(set_2[k]);
                    if (elem_1 == elem_2){
                        coef_1 = get_coeff(set_1[i]);
                        coef_2 = get_coeff(set_2[k]);
                        min_elem = min(coef_1, coef_2);
                        if (min_elem == coef_1)
                            result_set.push_back(set_1[i]);
                        else
                            result_set.push_back(set_2[k]);
                    }
                }
            }
        }
        Set res(result_set);
        for (string elem: set_2){
            target = get_elem(elem);
            if (not res.set_inclusion(target))
                result_set.push_back(elem);
        }

        for (string elem: set_1){
            target = get_elem(elem);
            if (not res.set_inclusion(target))
                result_set.push_back(elem);
        }

        return result_set;
    }

/*!
 * \brief difference of two multisets
 * \param set_1 - the first given multiset
 * \param set_2 - the second given multiset
 * \return result of difference
 */
    vector<string> Set::set_difference(vector<string> set_1, vector<string> set_2){
        vector<string> result_set;
        Set res2(set_2);
        string target, elem_1, elem_2;
        int coef_1, coef_2;

        for (int i=0;i<set_1.size();i++){
            target = get_elem(set_1[i]);
            for (int k=0;k<set_2.size();k++){
                Set res(result_set);
                if (not res.set_inclusion(target)){
                    elem_1 = get_elem(set_1[i]);
                    elem_2 = get_elem(set_2[k]);
                    if (elem_1 == elem_2){
                        coef_1 = get_coeff(set_1[i]);
                        coef_2 = get_coeff(set_2[k]);
                        if (coef_1 > coef_2)
                            result_set.push_back(to_string(coef_1 - coef_2) + get_elem(set_1[i]));
                    }
                }
            }
        }
        Set res(result_set);
        for (string elem: set_1){
            target = get_elem(elem);
            if (not res.set_inclusion(target) and not res2.set_inclusion(target))
                result_set.push_back(elem);
        }

        return result_set;
    }

/*!
 * \brief Check inclusion of element
 * \param target - target element for the checkout
 * \return true/false
 */
bool Set::set_inclusion(string target){
    string parsed_elem;
    for (string elem: set){
        parsed_elem = get_elem(elem);
        if (parsed_elem == target)
            return true;
    }
    return false;
}

/*!
 * \brief Length of multiset
 * \return integer value
 */
int Set::set_length(){
    return set.size();
    }

/*!
 * \brief Check whether set is emtpy
 * \return true/false
 */
bool Set::is_empty(){
    if (set.empty())
        return true;

    return false;
}

/*!
 * \brief multiset output
 */
    void Set::print() {
        cout << "The multiset is: "<<endl;
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

/*!
 * \brief Figure out multiset boolean
 */
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

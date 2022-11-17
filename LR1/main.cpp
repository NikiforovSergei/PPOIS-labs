#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include "classes.h"
#include <typeinfo>
#include <gtest/gtest.h>
using namespace std;
/**
 проверяет является ли текущий элемент строки открытием фигурной скобки
 \param inp текущий элемент строки
 \return true если текущий эллемент { false в любом другом случае
  */
bool Opening_of_bracers(char inp) {
    return inp == '{';
}
/**
 проверяет является ли текущий элемент строки запятой
 \param inp текущий элемент строки
 \return true если текущий эллемент запятая false в любом другом случае
  */
bool comma(char inp) {
    return inp == ',';
}
/**
 проверяет является ли текущий элемент строки концом строки
 \param inp текущий элемент строки
 \return true если текущий эллемент 0 false в любом другом случае
  */
bool End_of_String(char inp) {
    return inp == 0;
}
/**
 в строке считывает и выводит в вектор функции separator эллемент подстроку являющуюся мультимножеством
 \param i ссылка на счётчик
 \param line отредактированая строка ввода
 \param elements ссылка на вектор вывода
  */
void Bracers(int &i, string line, vector<string> &elements) {
    string buffer;
    buffer+=line[i];
    i++;
    int count1 = 1, count2=0;
    for (;count1 != count2;i++){
        if (line[i] == '}')count2 ++;
        if (line[i] == '{')count1 ++;
        buffer+=line[i];
    }
    elements.push_back(buffer);
    buffer.clear();
    i++;
}
/**
 выводит одиночный элемент после которо стоит запятая или конец строки
 \param i ссылка на счётчик
 \param line отредактированая строка ввода
 \param elements ссылка на вектор вывода
  */
void Comma_and_End(string &buffer, vector<string> &elements) {
    if (comma(buffer[0]))
        buffer.erase(0,1);
    elements.push_back(buffer);
    buffer.clear();
}
/**
 Преобразует стоку в класс MultiSet
 \param objects ссылка на объекты создаваемого класса
 \param sets ссылка на мультимножества создаваемого класса
  */
void constructor(vector<string> &objects, vector<MultiSet> &sets,string input) {
    vector<string> buffer;
    buffer = separator(std::move(input));
    for (int iterator = 0;iterator<buffer.size();iterator++ ){
        if (buffer[iterator] == "{}"){
            buffer.erase(buffer.begin()+iterator);
        }
    }
    for (auto &i: buffer) {
        if (i[0] == '{' ) {
            auto *t = new MultiSet(i);
            sets.push_back(*t);
        } else {
            objects.push_back(i);
        }
    }
}
/**
 Разделяет строку на элементы и мультимножества
 \param[in] input входная строка
 \return вектор состоящий из символов и подстрок
 */
vector<string> separator(string input) {
    string buffer, corrected;
    vector<string> elem;
    if (!input.empty()){
        remove(input.begin(), input.end(), ' ');
        corrected = input.substr(1, input.size()-2);
        for (int i= 0; i< (input.size()-1);i++){
            if (Opening_of_bracers(corrected[i]))
                Bracers(i, corrected, elem);
            if (comma(corrected[i]))
                Comma_and_End(buffer, elem);
            if (End_of_String(corrected[i]))
                Comma_and_End(buffer, elem);
            buffer+=corrected[i];
        }
    }
    return elem;
}

string MultiSet::MultiSet_to_string() {
    string result1 = "{";
    for (int i = 0 ; i<objects.size();i++){
        result1 +=(objects[i]);
        if (i <= objects.size()-2 && objects.size() != 1){
            result1+=',';
        }
        if (!sets.empty() && i == objects.size()-1){
            result1+=',';
        }
    }
    for (int i = 0; i<sets.size();i++){
        result1+=sets[i].MultiSet_to_string();
        if (i != sets.size()-1){
            result1+=',';
        }
    }
    result1+='}';
    return result1;
}
/**
 \defgroup Multiplication Операция умножения
 \brief этот модуль предназначен для реализации перегрузки операторов * и *=
 */
///@{
/**
  проиводит операцию декартовоо произведения над мультимножествами первого множителя и объектами второго
 */
void Multiplication_set_object(string buffer, string tuple, MultiSet &obj, vector<string> &objects, MultiSet &Mult) {
    for (auto & set1 : obj.GetSets()){
        tuple = '<' + set1.MultiSet_to_string() + ',';
        for (auto & obj1: objects){
            buffer = tuple+obj1+'>';
            Mult.Add_Object(buffer);
        }
    }
}
/**
  проиводит операцию декартовоо произведения над объектами первого множителя и объектами второго
 */
void Multiplication_object_object(string buffer, string tuple, MultiSet &obj, vector<string> &objects,MultiSet &Mult){
    for (auto& obj1 : objects){
        tuple  = '<' + obj1+',';
        for (auto & obj2: obj.GetObjects()){
            buffer = tuple+obj2+'>';
            Mult.Add_Object(buffer);
        }
    }
}
/**
  проиводит операцию декартовоо произведения над объектами первого множителя и мультимножествами второго
 */
void Multiplication_object_set(string buffer, string tuple, MultiSet &obj,vector<MultiSet> &sets,MultiSet &Mult){
    for (auto& obj1 : obj.GetObjects()){
        tuple  = '<' + obj1+',';
        for (auto & set1: sets){
            buffer = tuple+set1.MultiSet_to_string()+'>';
            Mult.Add_Object(buffer);
        }
    }
}
/**
  проиводит операцию декартовоо произведения над мультимножествами первого множителя и мультимножествами второго
 */
void Multiplication_set_set(string buffer, string tuple, MultiSet &obj, vector<MultiSet> &sets, MultiSet &Mult){
    for (auto & set1 : obj.GetSets()){
        tuple = '<' + set1.MultiSet_to_string() + ',';
        for (auto & set2 : sets){
            buffer = tuple+set2.MultiSet_to_string()+'>';
            Mult.Add_Object(buffer);
        }
    }
}
///@}
/**
 \defgroup Diffrence Операция разности
 \brief этот модуль предназначен для реализации перегрузки операторов - и -=
 */
 ///@{
/**
 отнимает от мультимножеств первого элемента мультимножества второго
 */
void Difference_of_Sets(MultiSet &obj,vector<MultiSet> &sets){
    for (auto & set:sets){
        for (int counter = 0;counter<obj.GetSets().size(); counter++){
            if (set.MultiSet_to_string() == sets[counter].MultiSet_to_string()){
                sets.erase(sets.begin()+counter);
                break;
            }
        }
    }
}
/**
 отнимает от объектов первого элемента объекты второго
 */
void Difference_of_Objects(MultiSet &obj,vector<string> &objects) {
    for (auto &object: obj.GetObjects()) {
        for (int counter = 0; counter < objects.size(); counter++) {
            if (object == objects[counter]) {
                objects.erase(objects.begin() + counter);
                break;
            }
        }
    }
}
///@}
class MultiSetTest:public::testing::Test
{
protected:
    void SetUp() {
        string example = "{a,a,c,{a,b,b},{},{a,{c,c}}}";
        multiset = new MultiSet{example};
    }
    void TearDown(){
        delete multiset;
    }
    MultiSet *multiset;
};

TEST_F(MultiSetTest, GetterTest){
vector<string> expec = {"a","a","c"};
EXPECT_EQ(expec, multiset->GetObjects());
}
TEST_F(MultiSetTest, TypeCheck){
vector<string> expec;
expec.push_back("a");
expec.push_back("a");
expec.push_back("c");
for (int i = 0; i<expec.size();i++)
EXPECT_EQ(typeid(expec[i]).name(),typeid(multiset->GetObjects()[i]).name());
}
bool Test_Vector_Iter(vector<string> input, vector<string> expectations){
    bool check = true;
    if (!input.empty() && !expectations.empty()){
    for (int i = 0;i<input.size();i++){
        if (input[i] != expectations[i]){
            check = false;
            break;
        }
    }
        return check;}
    else
        return check;
}

TEST_F(MultiSetTest, IncludedSets){
    vector<string> expec_2{"a","b","b"};
    vector<string> expec_3{"a"};
    vector<string> expec_4;
    vector<string> expec_5{"c","c"};
    vector<MultiSet> list= multiset->GetSets();
    for (auto i = 0; list.size() > i; i++){
        switch (i) {
            case 0:
                EXPECT_EQ(true, Test_Vector_Iter(list[i].GetObjects(), expec_2));
                break;
            case 1:
                EXPECT_EQ(true, Test_Vector_Iter(list[i].GetObjects(), expec_4));
                break;
            case 2:
                EXPECT_EQ(true, Test_Vector_Iter(list[i].GetObjects(), expec_3));
                break;
            case 3:
                EXPECT_EQ(true, Test_Vector_Iter(list[i].GetObjects(), expec_5));
                break;
        }
    }
}

TEST_F(MultiSetTest, getter_of_objects){
    vector<string> test_get_obj;
    vector<string> expected{"a","a","c"};
    test_get_obj = multiset->GetObjects();
    EXPECT_EQ(expected, test_get_obj);
}
TEST_F(MultiSetTest, getter_of_multisets){
    vector<MultiSet> test_get_multiset;
    test_get_multiset = multiset->GetSets();
    MultiSet first{"{a,b,b}"};
    MultiSet third{"{a,{c,c}}"};
    vector<MultiSet> expected{first,third};
    EXPECT_EQ(expected[0].GetObjects(),test_get_multiset[0].GetObjects());
    EXPECT_EQ(expected[1].GetObjects(),test_get_multiset[1].GetObjects());
}

TEST(MultiSet, Adding_Multiset){
    MultiSet multiset{"{a,a,c,{a,b,b},{},{a,{c,c}}}"};
    MultiSet test{"{a,a,b,c,d}"};
    multiset.Add_MultiSet(test);
    EXPECT_EQ(test.GetObjects(), multiset.GetSets()[2].GetObjects());
}
TEST(MultiSet, Adding_Object){
    string test = "tst";
    MultiSet multiset{"{a,a,c,{a,b,b},{},{a,{c,c}}}"};
    multiset.Add_Object(test);
    EXPECT_EQ(test, multiset.GetObjects()[3]);
}


TEST(MultiSet, Deleting_object){
    MultiSet multiset{"{a,a,c,{a,b,b},{},{a,{c,c}}}"};
    int place = 0;
    multiset.DeleteObject(place);
    EXPECT_EQ(2,multiset.GetObjects().size());
}

TEST(MultiSet, Deleting_set){
    MultiSet multiset{"{a,a,c,{a,b,b},{},{a,{c,c}}}"};
    int place = 0;
    multiset.DeleteSet(place);
    EXPECT_EQ(1,multiset.GetSets().size());
}

TEST_F(MultiSetTest, Boolean){
    string expected = "{{},{a,b,b},{a,{c,c}}}";
    string boolean = multiset->BooleanofMultiSet();
    EXPECT_EQ(expected, boolean);
}
TEST(MultiSet, OpeningOfBracers){
    ASSERT_EQ(Opening_of_bracers('{'),true);
}
TEST(MultiSet,comma){
    ASSERT_EQ(comma(','),true);
}
TEST(MultiSet, End_of_String){
    ASSERT_EQ(End_of_String(0),true);
}
TEST(MultiSet, plus_overload){
    MultiSet multiset1{"{a,b,c}"};
    MultiSet multiset2{"{z,x,c}"};
    MultiSet expect{"{a,b,c,z,x,c}"};
    MultiSet multiset3 = multiset1 + multiset2;
    EXPECT_EQ(expect.GetObjects(), multiset3.GetObjects());
}
TEST(MultiSet,plus_equal_overload){
    MultiSet multiset1{"{a,b,c}"};
    MultiSet multiset2{"{z,x,c}"};
    MultiSet expect{"{a,b,c,z,x,c}"};
    multiset1+=multiset2;
    EXPECT_EQ(expect.GetObjects(), multiset1.GetObjects());
}
TEST(MultiSet,difference_overload){
    MultiSet multiset1{"{a,b,c}"};
    MultiSet multiset2{"{z,x,c}"};
    MultiSet expect{"{a,b}"};
    MultiSet multiset3 = multiset1 - multiset2;
    EXPECT_EQ(expect.GetObjects(), multiset3.GetObjects());
}
TEST(MultiSet, difference_equal_overload){
    MultiSet multiset1{"{a,b,c}"};
    MultiSet multiset2{"{z,x,c}"};
    MultiSet expect{"{a,b}"};
    multiset1-=multiset2;
    EXPECT_EQ(expect.GetObjects(), multiset1.GetObjects());
}

TEST(MultiSet, multiplication_overload){
    MultiSet multiset1{"{a,b}"};
    MultiSet multiset2{"{z,x}"};
    vector<string> expect{"<a,z>","<a,x>","<b,z>","<b,x>"};
    MultiSet multiset3 = multiset1 * multiset2;
    EXPECT_EQ(expect, multiset3.GetObjects());
}
TEST(MultiSet,multiplication_equal_overload){
    MultiSet multiset1{"{a,b}"};
    MultiSet multiset2{"{z,x}"};
    vector<string> expect{"<a,z>","<a,x>","<b,z>","<b,x>"};
    multiset1 *=multiset2;
    EXPECT_EQ(expect, multiset1.GetObjects());
}

TEST(MultiSet,squere_bracers_overload){
    MultiSet multiset{"{a,b}"};
    string expect{"a"};
    EXPECT_EQ(expect, multiset["a"]);
}
int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}



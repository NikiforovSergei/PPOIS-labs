/**
\file
\brief Заголовочный файл с описанием класса мультмножеств и прообразами используемых функций

Данный файл содержит в себе класс мультимножеств
*/
#ifndef LABA_1_CLASSES_H
#define LABA_1_CLASSES_H

#include<string>
#include<vector>
#include<iostream>

std::vector<std::string> separator(std::string);
class MultiSet;

void constructor(std::vector<std::string>&,std::vector<MultiSet>&,std::string);

using namespace std;

bool Opening_of_bracers(char);

bool comma(char);

bool End_of_String(char);

void Bracers(int &, string, vector<string> &);

void Comma_and_End(string &, vector<string> &);

void Multiplication_set_set(string, string, MultiSet &, vector<MultiSet> &, MultiSet &);

void Multiplication_set_object(string, string, MultiSet &,  vector<string> &, MultiSet &);

void Multiplication_object_object(string, string, MultiSet &, vector<string> &,MultiSet &);

void Multiplication_object_set(string, string, MultiSet &,vector<MultiSet> &,MultiSet&);

void Difference_of_Objects(MultiSet &, vector<string> &);

void Difference_of_Sets (MultiSet &, vector<MultiSet> &);


class MultiSet{
    /// эллементы мультимножества не являющиеся мультимножествами
    vector<string> objects;
    /// мультимножества внутри мультимножества
    vector<MultiSet> sets;
public:
    /**
     конструктор класса MuliSet
     \param input строка из которо создаётся класс
     */
    explicit MultiSet(string input){
        constructor(objects,sets,input);
    }
    /**
     деструктор класса MultiSet
     */
     ~MultiSet(){
        objects.clear();
        sets.clear();
    }
    /**
     добаляет мультимножество в вектор мультимножеств
     \param input добавляемое мультимножество
     */
    void Add_MultiSet(MultiSet input){
        sets.push_back(input);
    };
    /**
     добаляет объект в вектор объектов
     \param input добавляемый объект
     */
    void Add_Object(string input){
        objects.push_back(input);
    };
    /**
     геттер объектов принадлежащих мультимножеству
     \return вектор объектов мультимножества
     */
    vector<string> GetObjects(){
        return objects;
    }
    /**
    геттер мультимножеств принадлежащих мультимножеству
     \return вектор мультимножеств мультимножества
    */
    vector<MultiSet> GetSets(){
        return sets;
    }
    /**
     удаление мультимножества по заданной позиции в векторе мультиножеств
     \param place позиция удаляемого объекта в векторе Мультимножеств
     */
    void DeleteSet(int place){
        sets.erase(sets.begin()+place);
    }
    /**
     удаление объекта по заданной позиции в векторе объектов
     \param place позиция удаляемого объекта в векторе Мультимножеств
     */
    void DeleteObject(int place){
        objects.erase(objects.begin()+place);
    }
    /**
     геттер мощности мультимножесва
     \return мощность мультимножества
     */
    int PowerOfMultiset(){
        int power = objects.size()+sets.size();
        return power;
    }
    /**
     перегрузка оператора +
     */
    MultiSet operator + (MultiSet obj){
        MultiSet Sum{"{}"};
        Sum.objects = objects;
        Sum.sets = sets;
        for (auto & object : obj.objects){
            Sum.objects.push_back(object);
        }
        for (auto & set : obj.sets){
            Sum.sets.push_back(set);
        }
        return Sum;
    }
    /**
     перегрузка оператора +=
     */
    void operator += (MultiSet obj){
        for (auto & object : obj.objects){
            objects.push_back(object);
        }
        for (auto & set : obj.sets){
            sets.push_back(set);
        }
    }
    /**
    преобразование объекта класса в виде строки
     */
    string MultiSet_to_string();
    /**
     перегрузка оператора *
     */
    MultiSet operator * (MultiSet obj){
        MultiSet Mult{"{a}"};
        Mult.objects.clear();
        string buffer, tuple;
        Multiplication_set_set(buffer,tuple,obj,sets,Mult);
        Multiplication_set_object(buffer, tuple, obj, objects, Mult);
        Multiplication_object_object(buffer, tuple, obj, objects, Mult);
        Multiplication_object_set(buffer, tuple, obj, sets,Mult);
        return Mult;
    }
    /**
     перегрузка оператора []
     \return возвращает объект класса если н присутствует в мультимножестве и nullptr если такого элемента нет
     */
    string operator [] (string obj){
        for (auto & object : objects){
            if (obj == object){
                return obj;
            }
        }
        for (auto & set : sets){
            if (obj == set.MultiSet_to_string())
            return obj;
        }
        return nullptr;
    }
    /**
     перегрузка оператора *=
     */
    void operator *=(MultiSet obj){
        string buffer, tuple;
        MultiSet Mult{"{a}"};
        Mult.objects.clear();
        Multiplication_set_set(buffer,tuple,obj,sets,Mult);
        Multiplication_set_object(buffer, tuple, obj, objects, Mult);
        Multiplication_object_object(buffer, tuple, obj, objects, Mult);
        Multiplication_object_set(buffer, tuple, obj, sets,Mult);
        objects = Mult.objects;
    }
    /**
     перегрузка оператора -
     */
    MultiSet operator -(MultiSet obj){
        MultiSet Mult{"{}"};
        MultiSet Buffer{"{}"};
        Mult.objects = objects;
        Mult.sets = sets;
        Difference_of_Objects(obj, objects);
        Difference_of_Sets(obj, sets);
        Buffer.objects = objects;
        Buffer.sets = sets;
        objects = Mult.objects;
        sets = Mult.sets;
        return Buffer;
    }
    /**
     перегрузка оператора -=
     */
    void operator -=(MultiSet obj){
        Difference_of_Objects(obj, objects);
        Difference_of_Sets(obj, sets);
    }
    /**
     \return возвращает название класса
     */
    string Name(){
        return typeid(this).name();
    }
    /**
     \return возвращает строку содержащую булеан мультимножества
     */
    string BooleanofMultiSet(){
        string output = "{{},";
        for (auto &set: sets){
            output+=set.MultiSet_to_string()+',';
        }
        output.erase(output.end()-1);
        return output+'}';
    }

    /**
     отображение элементов входящих в мультимножество
     */
};

#endif //LABA_1_CLASSES_H

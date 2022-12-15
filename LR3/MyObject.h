//
// Created by Игнат Готин on 30.11.22.
//

#ifndef PPOIS_LABA3_2_MYOBJECT_H
#define PPOIS_LABA3_2_MYOBJECT_H


class MyObject //класс для проверки
{
public:
    int key;
    MyObject(int key)
    {
        this->key = key;
    }
    friend bool operator < (const MyObject a, const MyObject b)
    {
        return a.key < b.key;
    }
    friend bool operator > (const MyObject a, const MyObject b)
    {
        return a.key > b.key;
    }
    friend bool operator == (const MyObject a, const MyObject b)
    {
        return a.key == b.key;
    }

};


#endif //PPOIS_LABA3_2_MYOBJECT_H

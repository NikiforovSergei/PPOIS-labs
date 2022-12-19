#ifndef PPOIS_LABA3_2_MYOBJECT_H
#define PPOIS_LABA3_2_MYOBJECT_H

class MyObject
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

#endif
#pragma once
#include<iostream>
#include <cmath>
using namespace std;

class Polynomial
{
public:
    Polynomial(int);
    
    void set(int, double);
    
    void print();
    
    Polynomial operator +(const Polynomial& other);
    
    Polynomial& operator +=(const Polynomial& other);
    
    Polynomial operator -(const Polynomial& other);
    
    Polynomial& operator -=(const Polynomial& other);
    
    Polynomial operator *(const Polynomial& other);
    
    Polynomial& operator *=(const Polynomial& other);
    
    Polynomial operator /(const Polynomial& other);
    
    Polynomial& operator /=(const Polynomial& other);
    
    Polynomial& operator =(const Polynomial& other);
    
    double operator()(double x);
    
    double operator[](int index);
    
private:
    int power;
    
    double* f;
    
    Polynomial copy(const Polynomial& other);
    
    bool Zero();
};

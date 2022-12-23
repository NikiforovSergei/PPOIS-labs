#pragma once
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<sstream>
#include<cctype>
#include<algorithm>
#include<exception>
using namespace std;
enum TOKEN_TYPE
{
    NAME, NUMBER, END_BEGIN, SIN, COS, TAN, CTG, ASIN, ACOS, ATAN, ACTG, POW, SQRT, CBRT,
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
    PRINT = ';', ASSIGN = '=', LP = '(', RP = ')'
};
const double PI_2 = 1.5708;
string getTokenName(TOKEN_TYPE);
TOKEN_TYPE getToken(string&);
string getLowerCase(string&);
bool isfoo(TOKEN_TYPE);
class Var
{
private:
    map<string, double> table;
public:
    Var();
    Var(string, double);
    double getValue(string);
    void setValue(string, double);
};
class Error
{
private:
    int NUMBER_ERROR;
public:
    Error(int);
    void error();
};
vector<double> getParametr(bool&, int, string, Var& vars);
class Lexeme
{
private:
    double number_value;
    string string_value;
    TOKEN_TYPE token;
public:
    Lexeme();
    Lexeme(const Lexeme&);
    Lexeme(double, TOKEN_TYPE);
    Lexeme(string, TOKEN_TYPE);
    void Print();
    void setValue(double);
    void setSValue(string);
    double getDValue(Var& vars);
    string getVar();
    TOKEN_TYPE getType();
};
class LexemeBuffer
{
private:
    vector<Lexeme> lexemes;
public:
    vector<Lexeme> getLexemes();
    void setLexeme(Lexeme);
    void Clear();
};
class LexemeAnalyzer
{
private:
    bool isgood = true;
    double number_value;
    string string_value; 
    TOKEN_TYPE current_token;
public:
    void get_token(LexemeBuffer&);
};

void findMinus(vector<Lexeme>&);
bool isop(Lexeme&);

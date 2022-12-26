#include <iostream>
#include <stdio.h>
#include "string"
#include "vector"
#include "math.h"

using namespace std;

vector<pair<string, int>> variables;

class Tree{
    class Lexeme{
    public:
        string _name;
        vector<string> _lec;
        int _val;
        pair <int, int> _funcVar;
        Lexeme* _childrenLeft;
        Lexeme* _childrenRight;
        Lexeme* _parent = nullptr;

        Lexeme(){};
        Lexeme(Lexeme* parent, Lexeme* chLeft, Lexeme* chRight, string name){
            _name = name;
            _parent = parent;
            _childrenLeft = chLeft;
            _childrenRight = chRight;
        };

        Lexeme(Lexeme* parent, Lexeme* chLeft, Lexeme* chRight, string name, vector<string> lec, pair<int, int> pr){
            _name = name;
            _parent = parent;
            _childrenLeft = chLeft;
            _childrenRight = chRight;
            _funcVar = pr;
            _lec = lec;
        };

        Lexeme(Lexeme* parent, Lexeme* chLeft, Lexeme* chRight, string name, vector<string> lec, int val){
            _name = name;
            _parent = parent;
            _childrenLeft = chLeft;
            _childrenRight = chRight;
            _val = val;
            _lec = lec;
        };
        Lexeme(Lexeme* parent, Lexeme* chLeft, Lexeme* chRight, string name, vector<string> lec){
            _name = name;
            _parent = parent;
            _childrenLeft = chLeft;
            _childrenRight = chRight;
            _lec = lec;
        };
        virtual int calc(){};
    };

    class Plus : public Lexeme {
    public:
        Plus() {};
        Plus(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name) : Lexeme(parent, chLeft, chRight, name) {};
        int calc() {
            return this->_childrenLeft->calc() + this->_childrenRight->calc();
        }
    };

    class Minus : public Lexeme {
    public:
        Minus() {};
        Minus(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name) : Lexeme(parent, chLeft, chRight, name) {};
        int calc() {
            return this->_childrenLeft->calc() - this->_childrenRight->calc();
        }
    };

    class Multiply : public Lexeme {
    public:
        Multiply() {};
        Multiply(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name) : Lexeme(parent, chLeft, chRight, name) {};
        int calc() {
            return this->_childrenLeft->calc() * this->_childrenRight->calc();
        }
    };

    class Division : public Lexeme {
    public:
        Division() {};
        Division(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name) : Lexeme(parent, chLeft, chRight, name) {};
       int calc() {
            return this->_childrenLeft->calc() / this->_childrenRight->calc();
        }
    };

    class Constant : public Lexeme {
    public:
        Constant() {};
        Constant(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name, vector<string> lec, int val) : Lexeme(parent, chLeft, chRight, name, lec, val) {};
        int calc() {
            return this->_val;
        }
    };

    class Variable : public Lexeme {
    public:
        Variable() {};
        Variable(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name, vector<string> lec) : Lexeme(parent, chLeft, chRight, name, lec) {};
        int calc(){
            for (int i = 0; i < variables.size(); ++i)
                if(variables[i].first == _lec[0])
                return variables[i].second;
        }
    };

    class Func : public Lexeme {
    public:
        Func() {};
        Func(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name, vector<string> lec, pair<int, int> ps) : Lexeme(parent, chLeft, chRight, name, lec, ps) {};
        Func(Lexeme *parent, Lexeme *chLeft, Lexeme *chRight, string name, vector<string> lec, int val) : Lexeme(parent, chLeft, chRight, name, lec, val) {};

        int calc() {
            if (_lec[0] == "sin(")
                return sin(_val);
                else if(_lec[0] == "pow(")
                    return pow(_funcVar.first, _funcVar.second);
                else if(_lec[0] == "cos(")
                    return cos(_val);
                    else if(_lec[0] == "tg(")
                        return sin(_val)/cos(_val);
                           else if (_lec[0] == "sqrt(")
                            return sqrt(_val);
        }
    };

    int Priority(string str) {
        if (str == "+" || str == "-") return 5;
        else if (str == "/" || str == "*") return 4;
        else if (str == "sin(" || str == "pow("
        || str == "cos(" || str == "pow(" || str == "sqrt(") return 3;
        else if(str == "(" || str == ")") return 0;
        else return 2;
    };

    Lexeme* Inflection(vector<string> lec, Lexeme *parent) {
        vector<string> left, right;
        int priority, intPriority = 0, maxpriority = 0, place = 0;
        if(lec[0] == "(" && lec[lec.size() - 1] == ")")
        {
            auto iter = lec.cbegin();
            lec.erase(iter);
            lec.pop_back();
        }
        for (int i = 0; i < lec.size(); ++i) {
            priority = 0;
            if (lec[i] == "(")
                intPriority-=2;
            else if (lec[i] == ")")
                intPriority+=2;
            priority = intPriority + Priority(lec[i]);
            if (maxpriority <= priority) {
                maxpriority = priority;
                place = i;
            }
        }
        //делим лексемы по сторонам
        for (int i = 0; i < place; ++i)
            left.push_back(lec[i]);
        for (int i = place + 1; i < lec.size(); ++i)
            right.push_back(lec[i]);

        //создаем узел нужного типа, устанавливаем значени полей и возвращаем указатель на узел.
        if (lec[place] == "+") {
            string name = "Plus";
            Plus *node = new Plus(parent, Inflection(left, node), Inflection(right, node), name);
            return node;
        } else if (lec[place] == "-") {
            string name = "Minus";
            Minus *node = new Minus(parent, Inflection(left, node), Inflection(right, node), name);
            return node;
        } else if (lec[place] == "/") {
            string name = "Div";
            Division *node = new Division(parent, Inflection(left, node), Inflection(right, node), name);
            return node;
        } else if (lec[place] == "*") {
            string name = "Mult";
            Multiply *node = new Multiply(parent, Inflection(left, node), Inflection(right, node), name);
            return node;
        } else if (lec[place] == "sin(" || lec[place] == "cos(" || lec[place] == "tg(" ||
                   lec[place] == "sqrt(" || lec[place] == "ctg(") {
            string name = "Func";
            Func *node = new Func(parent, nullptr, nullptr, name, lec, stoi(lec[place + 1]));
            return node;
        }
            else if(lec[place] == "pow("){
                string name = "Func";
                pair<int, int> ps;
                ps.first = stoi(lec[place + 1]);
                ps.second = stoi(lec[place + 2]);
                Func *node = new Func(parent, nullptr, nullptr, name, lec, ps);
                return node;
            }
            else
        {
            const char* ch = lec[place].c_str();
            if(!isalpha((ch[0])))
            {
            int val = stoi(lec[place]);
            string name = "Const";
            Constant *node = new Constant(parent, nullptr, nullptr, name, lec, val);
            return node;
            }
        else{
            string name = "Var";
            Variable *node = new Variable(parent, nullptr, nullptr, name, lec);
            return node;
            }
        }
    };

    Lexeme* _root;

    //подготовка и разбиение строки на лексемы
    vector<string> SplitLex(string str) {
        vector<string> lexem;
        string temp = "";
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == ' ' || str[i] == ',') {
                lexem.push_back(temp);
                temp = "";
            } else temp += str[i];
        }
        lexem.push_back(temp);
        return lexem;
    }

public:
    Tree(string lex){
        for (int i = 0; i < lex.size(); ++i) {
            if (lex[i] == '=') {
                vector<string> eq = SplitLex(lex);
                variables.emplace_back(eq[0], stoi(eq[2]));
                return;
            }
        }
            _root = Inflection(SplitLex(lex), nullptr);
            cout << _root->calc() << endl;
    }
};

int main(){
    string s;
    while(true){
        cout << "i need a dollar!" << endl;
        getline(cin, s);
        Tree tree(s);
    }
}

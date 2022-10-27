#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ClassCopy.h"
#include "Check.h"
#include "Cut.h"
#include "MUL.h" // just for polymorphism
#include "Add.h"
#include "Print_smth.h"
#include "Debug.h"

#define SCRIPT "\
compile.cmd \
"

using namespace std;

int main(int argc, char* argv[])
{
    string name;
    bool debug_prog = false;

    if (argc == 2) {
        name = string(argv[1]);
    }
    if (argc == 3) {
        name = string(argv[1]);
        if (string(argv[2]) == "-debug") {
            debug_prog = true;
        }
    }

    /*if (name.find(" -debug") < name.size()) {
        debug_prog = true;
        name.erase(name.begin() + name.find(" ") + 1, name.end());
    }*/

    string s;
    vector<string> program;


    ifstream in;
    in.open(name);

    while (!in.eof()) {
        getline(in, s);
        if (s.find("#") != 0) {
            if (s.find("#") < s.size()) {
                s.erase(s.begin() + s.find(" #"), s.end());
            }
            program.push_back(s);
        }
    }

    in.close();

    ofstream out; 
    name.erase(name.begin() + name.find("."), name.end());
    
    name = name + ".cpp";
    out.open(name);
    name.erase(name.begin() + name.find("."), name.end());
    CopySource stack;
    stack.copy_class(out);

    /*
    ************************************ Function declaration ************************************
    */
    vector<string> initialized;
    Check check;

    for (int i = 0; i < program.size(); i++) {
        if (!program[i].find("function")) {
            string func_name;
            func_name = program[i];
            func_name.erase(func_name.begin(), func_name.begin() + func_name.find(" ") + 1);
            if (func_name != "main") {
                out << "int " << func_name << "();\n\n";
            }
        }
    }

    /*
   ************************************ Methods declaration ************************************
   */

    string last_function;
    Cut cut_str;

    for (int i = 0; i < program.size(); i++) {
        /*if (program[i].find("function ") == 0 || program[i].find(" ") == program[i].find(" ")) {
            string func_name;
            func_name = program[i];
            func_name.erase(func_name.begin(), func_name.begin() + func_name.find(" ") + 1);
            if (func_name != "main") {
                out << "int " << func_name << "(){\n";
                out << "  Stack stack;\n";
            }
        }*/
        if (program[i].find("function ") == 0) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);
            last_function = program[i];
            out << "int " << program[i] << "(){\n";
            out << "    Stack stack;\n";
        }
        
        if (program[i].find("push") == 0) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);
            stack.copy_push(out, program[i]);
            debug_program(out, program[i], debug_prog);
        }

        if (program[i].find("pop ") == 0) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);

            int j = 0;
            for (int j = 0; j < initialized.size(); j++) {
                if (program[i] == initialized[j]) {
                    j++;
                }
            }
            if (j == 0) {
                initialized.push_back(program[i]);
                out << "    int " << program[i] << "; \n";
            }
            out << "    " << program[i] << " = stack.pop();\n";
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "pop") {
            out << "    stack.pop();\n";
            debug_program(out, program[i], debug_prog);
        }

        if (program[i].find("peek ") == 0) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);

            int j = 0;
            for (int j = 0; j < initialized.size(); j++) {
                if (program[i] == initialized[j]) {
                    j++;
                }
            }
            if (j == 0) {
                initialized.push_back(program[i]);
                out << "    int " << program[i] << "; \n";
            }

            stack.copy_peek(out, program[i]);
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "dup") {
            stack.copy_dup(out);
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "add") {//polymorphysm
            //stack.copy_add(out);
            Add a_add;
            Print_smth u_print;
            out <<"    stack." << u_print.print(a_add) << "\n";
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "sub") {
            stack.copy_sub(out);
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "div") {
            stack.copy_div(out);
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "mul") {//polymorphysm
            //stack.copy_mul(out);
            Mul a_mul;
            Print_smth u_print;
            out << "    stack." << u_print.print(a_mul) << "\n";
            debug_program(out, program[i], debug_prog);
        }

        if (program[i] == "return") {
            if (last_function == "main") {
                out << "    cout << stack.pop() << endl;\n";
                out << "    system(\"pause\");\n";
                out << "    return 0;\n}\n";
            }
            else {
                out << "    return stack.pop();\n}\n";
            }
        }

        if (!program[i].find("goto")) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);
            out << "  goto " << program[i] << ";\n";

        }

        if (program[i].find("ifeq") == 0) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);
            out << "    if(1 < 2){\n";
            out << "        int local_number_for_eq_1, local_number_for_eq_2;\n";
            out << "        local_number_for_eq_1 = stack.pop();\n";
            out << "        local_number_for_eq_2 = stack.pop();\n";
            out << "        if(local_number_for_eq_1 == local_number_for_eq_2){\n";
            out << "            goto " << program[i] << ";\n";
            out << "        }\n";
            out << "    }\n";
            
        }

        if (!program[i].find("ifgr")) {
            check.check_two(program[i]);
            cut_str.cut(program[i]);
            out << "    if(1 < 2){\n";
            out << "        int local_number_for_eq_1, local_number_for_eq_2;\n";
            out << "        local_number_for_eq_1 = stack.pop();\n";
            out << "        local_number_for_eq_2 = stack.pop();\n";
            out << "        if(local_number_for_eq_1 > local_number_for_eq_2){\n";
            out << "           goto " << program[i] << ";\n";
            out << "        }\n";
            out << "    }\n";
           
        }

        if (program[i].find(":") == program[i].size() - 1) {
            out << program[i]<<"\n";
        }

        
    }
    out.close();


    /*
    ************************************ Script to compile new cpp *************************************
    */

    ofstream script;
    script.open("compile.cmd");

    script << "g++ " << name << ".cpp -o " << name << "\n";
    script << name;

    script.close();

    system(SCRIPT);
}
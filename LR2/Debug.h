#pragma once
#include <fstream>
#include <string>
#include "ClassCopy.h"

void debug_program(std::ofstream& out, std::string str,bool debug_prog) {
    CopySource stack;
    if (debug_prog) {
        if (str != "\0" && str != "{" && str != "\}") {
            stack.copy_print(out);
            out << "    system(\"pause\");\n";
        }
    }
}
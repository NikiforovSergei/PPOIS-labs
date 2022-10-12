#include <iostream>
#include "oceanfield/ocean.h"
#include "system/ocean_system.h"
#include "system/file.h"

ocean_system* read_from_file(std::string&);// чтение из файла

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"ru");
    srand(time(NULL));
    std::string error = "ERROR:\n"
                        "\tPlease: check amount of argument";
    std::string name;
    if(argc==2){
        name = "/home/konstantin/CLionProjects/Ocean/cmake-build-debug/" + std::string(argv[1]);
    }else{
        std::cout<<error;
        return  0;
    }
    ocean_system *ocean = read_from_file(name);
    ocean->run();
    return  0;
}


ocean_system* read_from_file(std::string& name_file){
    std::fstream load_from_file;
    load_from_file.exceptions(std::fstream::badbit | std::fstream::failbit);

    try{
        load_from_file.open(name_file, std::ifstream::in);
    }catch (const std::exception& e){
        std::cout<<e.what()<<std::endl;
    }

    ocean_system *system = new file(load_from_file);
    load_from_file.close();

    return system;
}

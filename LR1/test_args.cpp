#include "patterns.cpp"
#include "machine.cpp"

#include "fstream"

std::pair<std::string, patterns> read_from_file(std::string file_path = "patterns"){
    std::ifstream in;

    in.open(file_path);
    patterns p; in >> p;
    in.close();

    in.open("ribbon");
    std::string str; in>>str;
    in.close();

    return {str, p};
}

int main(int argc, char **argv) {
    std::string file_path = "patterns";
    bool log_bool = false;

    if (argc > 1){
        file_path = std::string(argv[1]);
        if (argc > 2){
            if ("-log" == std::string(argv[2])) log_bool = true;
        }
    }
    std::pair<std::string, patterns> ribbon_patterns = read_from_file(file_path);
    if (log_bool){
        machine m =machine(ribbon_patterns.first, ribbon_patterns.second);
        m.start(true);
        std::cout<<m.get_ribbon()<<std::endl;

    } else {
        machine m =machine(ribbon_patterns.first, ribbon_patterns.second);
        m.start(false);
        std::cout<<m.get_ribbon()<<std::endl;
    }
}

#include "hfile.h" 


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");

    cout << "Input path:";
    string name;
    std::cin >> name;
    cout << "\n";
    bool log_check = 0;
    if (argc > 1)
    {
        string s = argv[1];
        if (s == "-log") {
            log_check = 1;
        }
        else { cout << "Несуществующий аргумент" << endl; }
    }
    Menu my_object(log_check,name);
    my_object.menu_choose();
}
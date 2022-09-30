#include"PPOIS_1.h" 


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    bool log_check = 0;
    if (argc > 1)
    {
        string s = argv[1];
        if (s == "-log") {
            log_check = 1;
        }
        else { cout << "non-existent argument" << endl; }
    }
    Menu my_object(log_check);
    my_object.menu_choose();
}


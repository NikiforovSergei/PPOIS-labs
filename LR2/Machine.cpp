#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include "Machine.h"

using namespace std;

UserCard Atm::operations() {
    string path;
    int choise = 0;
    double balance;
    int cards, passwo;
    int pass;
    string users,card,passw,balan;
    int kod = -1;
    cout << "Enter name" << endl;
    getline(cin, path);
    ifstream user("database\\" + path + ".txt");
    //path = "Lady.txt";
    if (user.is_open()) {
        getline(user, card);
        //user >> cards;
        cout << card << endl;
        getline(user, passw);
        pass = stoi(passw);
        cout << pass << endl;
        getline(user, users);
        cout << users << endl;;
        getline(user,balan);
        stringstream str;
        str << balan;
        str >> balance;
        //balance = stoi(balan);
        cout << balance << endl;
        //cout << card << " " << passw << " " << users << " " << balance;
    }
    else {
        operations();
    }
    cout << "Operations:\n0 - exit\n1 - to make a deposit\n2 - withdraw money from the account\n3 - transfer money to another account\n4 - account balance\n5 - new card owner\n" << endl;
    cin >> kod;
    do {
        switch (kod)
        {
        case 1: {
            //authorization(pass);
            if (!authorization(pass)) {
                cout << "Authorization is failed" << endl;
            }
            else {
                double money;
                cout << "Enter money, that you want to deposit" << endl;
                cin >> money;
                replenishment(path, money);
            }
            break;
        }
        case 2: {
            //authorization(pass);
            if (!authorization(pass)) {
                cout << "Authorization is failed" << endl;
            }
            else {
                double money;
                cout << "Enter money, that you want to deposit" << endl;
                cin >> money;
                withdrawal(path, money);
            }
            break;
        }
        case 3: {
            //authorization(pass);
            if (!authorization(pass)) {
                cout << "Authorization is failed" << endl;
            }
            else {
                string SecondPath;
                cout << "Enter Name of the card holder you want to transfer to" << endl;
                getline(cin, SecondPath);
                double money;
                cout << "How much money you want to transfer" << endl;
                cin >> money;
                transfer(path, SecondPath, money);
            }
            break;
        }
        case 4: {
            //authorization(pass);
            ifstream usere("database\\" + path + ".txt");
            //path = "Lady.txt";
            if (usere.is_open()) {
                getline(usere, card);
                //user >> cards;
                //cout << card << endl;
                getline(usere, passw);
                //pass = stoi(passw);
                //cout << pass << endl;
                getline(usere, users);
                //cout << users << endl;;
                getline(usere, balan);
                stringstream str;
                str << balan;
                str >> balance;
                //balance = stoi(balan);
                //cout << balance << endl;
                //cout << card << " " << passw << " " << users << " " << balance;
            }
            if (!authorization(pass)) {
                cout << "Authorization is failed" << endl;
            }
            else {
                cout << "Your current balance is: " << balance << endl;
            }
            break;
        }
        case 5: {
            int password;
            cout << "Enter the password to add New User" << endl;
            cin >> password;
            if (password != 1234) {
                cout << "Wrong!" << endl;
            }
            else {
                NewUser();
            }
            break;
        }
        }
        //while (choise == 0) {
        cout << "Would you like to continue?\n1 - yes\n0 - no" << endl;
        cin >> choise;
        if (choise == 1) {
            cout << "operations:\n0 - exit\n1 - to make a deposit\n2 - withdraw money from the account\n3 - transfer money to another account\n4 - account balance\n5 - new card owner" << endl;
            cin >> kod;
        }
        else kod == 0;
        //}
    }while (kod > 0);
    user.close();
    choise = 0;
    while (choise == 0) {
        cout << "Finish the job?\n1 - yes\n2 - no" << endl;
        cin >> choise;
        if (choise == 1) {
            return operations();
        }
        else if (choise == 2) {
            //return end();
            cout << "Thank you!" << endl;
        }
        else {
            cout << "Incorrect choise" << endl;
        }
    }
}

bool Atm::authorization(int passw) {
    int password;
    //cout << password;
    cout << "Enter your password to authorize" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> password;
        if (password == passw) {
            return true;
        }
        else {
            cout << "Incorrect password";
        }
    }
    return false;
}

void Atm::replenishment(string path, double money) {
    double balance;
    int cards, passwo, pass;
    string users, card, passw, balan;
    ifstream user("database\\" + path + ".txt");
    //path = "Lady.txt";
    if (user.is_open()) {
        getline(user, card);
        //user >> cards;
        cout << card << endl;
        getline(user, passw);
        pass = stoi(passw);
        cout << pass << endl;
        getline(user, users);
        cout << users << endl;;
        getline(user, balan);
        stringstream str;
        str << balan;
        str >> balance;
        //balance = stoi(balan);
        cout << balance << endl;
        //cout << card << " " << passw << " " << users << " " << balance;
    }
    balance = balance + money;
    user.close();
    string road = "database\\" + path + ".txt";
    ofstream usere;
    usere.open(road);
    if (usere.is_open()) {
        usere << card << endl;
        usere << passw << endl;
        usere << users << endl;
        usere << balance << endl;
    }

}

void Atm::withdrawal(string path, double money) {
    double balance;
    int cards, passwo, pass;
    string users, card, passw, balan;
    ifstream user("database\\" + path + ".txt");
    if (user.is_open()) {
        getline(user, card);
        cout << card << endl;
        getline(user, passw);
        pass = stoi(passw);
        cout << pass << endl;
        getline(user, users);
        cout << users << endl;;
        getline(user, balan);
        stringstream str;
        str << balan;
        str >> balance;
        //balance = stoi(balan);
        cout << balance << endl;
        //cout << card << " " << passw << " " << users << " " << balance;
    }
    if (balance - money >= 0) {
        balance = balance - money;
        user.close();
        string road = "database\\" + path + ".txt";
        ofstream usere;
        usere.open(road);
        if (usere.is_open()) {
            usere << card << endl;
            usere << passw << endl;
            usere << users << endl;
            usere << balance << endl;
        }
    }
    else
    {
        user.close();
        cout << "Not enough money" << endl;
    }
}

void Atm::transfer(string path, string SecondPath, double money) {
    double balance1, balance2;
    int cards1, cards2, passwo1, passwo2, pass1, pass2;
    string users1, users2, card1, card2, passw1, passw2, balan1, balan2;
    ifstream user("database\\" + path + ".txt");
    if (user.is_open()) {
        getline(user, card1);
        cout << card1 << endl;
        getline(user, passw1);
        pass1 = stoi(passw1);
        cout << pass1 << endl;
        getline(user, users1);
        cout << users1 << endl;;
        getline(user, balan1);
        stringstream str;
        str << balan1;
        str >> balance1;
        //balance = stoi(balan);
        cout << balance1 << endl;
        //cout << card << " " << passw << " " << users << " " << balance;
    }
    if (balance1 - money >= 0) {
        balance1 = balance1 - money;
        user.close();
        string road = "database\\" + path + ".txt";
        ofstream usere;
        usere.open(road);
        if (usere.is_open()) {
            usere << card1 << endl;
            usere << passw1 << endl;
            usere << users1 << endl;
            usere << balance1 << endl;
        }
        usere.close();
        ifstream user2("database\\" + SecondPath + ".txt");
        if (user2.is_open()) {
            getline(user, card2);
            cout << card2 << endl;
            getline(user, passw2);
            pass2 = stoi(passw2);
            cout << pass2 << endl;
            getline(user, users2);
            cout << users2 << endl;;
            getline(user, balan2);
            stringstream str;
            str << balan2;
            str >> balance2;
            //balance = stoi(balan);
            cout << balance2 << endl;
            //cout << card << " " << passw << " " << users << " " << balance;
        }
        balance2 = balance2 + money;
        user2.close();
        string road2 = "database\\" + SecondPath + ".txt";
        ofstream usere2;
        usere2.open(road2);
        if (usere.is_open()) {
            usere << card2 << endl;
            usere << passw2 << endl;
            usere << users2 << endl;
            usere << balance2 << endl;
        }
        usere2.close();
    }
    else {
        user.close();
        cout << "Not enough money" << endl;
    }
}

void Atm::NewUser() {
    //string path;
    double balance;
    int cards, passwo, pass;
    string users, card, passw, balan;
    cout << "Enter the last name ant first name of owner" << endl;
    cin >> users;
    cout << "Enter the card ID" << endl;
    cin >> cards;
    string path = "database\\" + users + ".txt";
    ofstream usere;
    usere.open(path);
    if (usere.is_open()) {
        usere << cards;
        srand(time(0));
        passwo = (rand() % 9) * 1000 + (rand() % 9) * 100 + (rand() % 9) * 10 + (rand() % 9);
        usere << passwo;
        usere << users;
        usere << 0;
    }
}

//
// Created by User on 21.09.2022.
//


#include "CashMachine.h"
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <windows.h>
#include <unistd.h>

namespace fs = std::experimental::filesystem;

bool CashMachine::exists(string name){
    HANDLE fileHandle;
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER szDir;
    WIN32_FIND_DATA fileData;
    fileHandle = FindFirstFile("database\\*", &ffd);

    if (INVALID_HANDLE_VALUE == fileHandle)
        printf("Invalid File Handle Value \n");

    do
    {
        if (ffd.cFileName == deleteSpaces(name)){
            return true;
        }
    } while (FindNextFile(fileHandle, &ffd) != 0);
    return false;
}

void CashMachine::save(string path, Card card) {
    fout.open("database\\"+deleteSpaces(path));
    fout<<card.getCardId()<<endl<<card.getPassword()<<endl<<card.getOwner()<<endl<<card.getBalance();
    fout.close();
}

Card CashMachine::getCardNow(){
    return cardNow;
}

void CashMachine::setCardNow(string path) {
    fin.open("database\\"+path);
    if(fin.is_open()){
        string buff;
        getline(fin, buff);
        cardNow.setCardId(atoi(buff.c_str()));
        getline(fin, buff);
        cardNow.setPassword(atoi(buff.c_str()));
        getline(fin, buff);
        cardNow.setOwner(buff);
        getline(fin,buff);
        cardNow.setBalance(stod(buff));
    }
    fin.close();
}

string CashMachine::deleteSpaces(string path) {
    string res="";
    for(int i=0; i<path.size(); i++){
        if(path[i]!=' '){
            res+=path[i];
        }
    }
    return res;
}

void CashMachine::withdrawal(string path, double money) {
    setCardNow(path);
    cardNow.setBalance(cardNow.getBalance()-money);
    save(path, cardNow);
}

void CashMachine::replenishment(string path, double money) {
    setCardNow(path);
    cardNow.setBalance(cardNow.getBalance()+money);
    save(path, cardNow);
}

void CashMachine::transfer(string pathFrom, string pathTo, double money) {
    Card to;
    to.setInfo(pathTo);
    cardNow.setInfo(pathFrom);
    cardNow.setBalance(cardNow.getBalance()-money);
    save(pathFrom, cardNow);
    to.setBalance(to.getBalance()+money);
    save(pathTo, to);
}

void CashMachine::registerNewCard(int id, string name, double balance, int password) {
    cardNow.setCardId(id);
    cardNow.setOwner(name);
    cardNow.setBalance(balance);
    cardNow.setPassword(password);
    save(deleteSpaces(name), cardNow);

}


void CashMachine::start() {
    cout<<"Enter the last name and first name of the owner\n";
    string name;
    getline(cin, name);
    if (!exists(name)){
        cout<<"User does not exist\ndo you want to register? (y/n)\n";
        char kod;
        cin>>kod;
        if(kod == 'n'){
            return;
        }
        else{
            int id, password;
            cout<<"Enter the card ID\n";
            cin>>id;
            srand(time(0));
            password=(rand()%10-1)*1000+(rand()%10-1)*100+(rand()%10-1)*10+(rand()%10-1);
            cout<<"your password: "<<password<<endl;
            sleep(5);
            system("cls");
            registerNewCard(id, name, 0, password);
        }
    }
    setCardNow(deleteSpaces(name));
    if (authorization()) {
        operations();
    }
}

Card CashMachine::operations() {
    cout<<"operations:\n0 - exit\n1 - to make a deposit\n2 - withdraw money from the account\n3 - transfer money to another account\n4 - account balance\n";
    int kod;
    cin >> kod;
    string path = deleteSpaces(cardNow.getOwner());
    switch (kod) {
        case 0:{
            return cardNow;
        }
        case 1:{
            double money;
            cin>>money;
            replenishment(path, money);
            break;
        }
        case 2: {
            double money;
            cin >> money;
            withdrawal(path, money);
            break;
        }
        case 3:{
            string ownerOfSecondCard="", empty = "";
            getline(cin,empty);
            getline(cin,ownerOfSecondCard);
            while (!exists(deleteSpaces(ownerOfSecondCard))) {
                getline(cin, ownerOfSecondCard);
                cout<<"User does not exist\nRepeat please\n";
            }

            double money;
            cin >> money;
            transfer(path, deleteSpaces(ownerOfSecondCard), money);
            break;
        }
        case 4:{
            cout<<cardNow.getBalance()<<endl;
            break;
        }
    }
    cout<<"would you like to continue? (y/n)\n";
    char repeat;
    cin>>repeat;
    system("cls");
    if(repeat=='y') {
        return operations();
    }
    else {
        return cardNow;
    }
}

bool CashMachine::authorization() {
    int password;
    cin >> password;
    for(int i=0; i<3; i++) {
        if (password == cardNow.getPassword()) {
            return true;
        }
    }
    return false;
}

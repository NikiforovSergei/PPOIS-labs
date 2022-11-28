#include <iostream>
#include "BANKS.h"
#include "ATMScreens.h"
#include <conio.h>
#include<fstream>//>
#include <utility>
std::vector<std::string> Splitter(std::string input){
    std::vector<std::string> output;
    std::string buffer;
    int iter = 0;
    do {
        if (input[iter]==' '){
            output.push_back(buffer);
            buffer="";
        }
        else{
            buffer+=input[iter];
        }
        iter++;
        if (input[iter]==0){
            output.push_back(buffer);
        }
    }
    while(input[iter]!=0);
    return output;
}
std::vector<CardAccount> CheckingDatabase(std::string& datab){
    std::ifstream database(datab);
    double cash;
    std::vector<CardAccount> data;
    std::string line;
    while(std::getline(database,line)){
        std::vector<std::string> current;
        current = Splitter(line);
        cash = std::stod(current[0]);
        std::string cardnumber = current[1];
        std::string pincode = current[2];
        CardAccount temporary {cash, cardnumber, pincode};
        data.push_back(temporary);
    }
    database.close();
    return data;
}
std::vector<User> PossibleUsers(std::string& user){
    std::ifstream Users(user);
    double buffer_cash;
    std::string line;
    std::vector<User> UsersFiles;
    while(std::getline(Users, line)){
        std::vector<std::string> current;
        current = Splitter(line);
        BankCard temp_card;
        std::string buffer_name,buffer_pin="0000";
        buffer_name = current[0];
        buffer_cash = std::stod(current[1]);
        User temporary{buffer_name, buffer_pin,temp_card, buffer_cash};
        UsersFiles.push_back(temporary);
    }
    Users.close();
    return UsersFiles;
}
void AccountLinker(std::vector<User> &UsersFiles, std::vector<CardAccount> &Accounts){
    for (int i = 0;i<Accounts.size();i++){
        UsersFiles[i].LinkCard(Accounts[i]);
    }
}
BANK BankInfoReading(std::vector<CardAccount> database, std::string& bank){
    std::ifstream Bank(bank);
    long double Bank_cash;
    std::string buffer;
    getline(Bank,buffer);
    Bank_cash = std::stod(buffer);
    BANK current(std::move(database),Bank_cash);
    return current;
}
User CurrentUserIs(std::vector<User> UsersBase){
    std::string fname;
    std::cout<<"Who are you?"<<std::endl;
    std::cin>>fname;
    for (auto & i : UsersBase){
        if (fname == i.GetName()){
            std::cout<<"Name is correct"<<std::endl<<"Welcome "<<i.GetName()<<"!"<<std::endl;
            return i;
        }
    }
    std::cout<<"There is no such user"<<std::endl;
    getch();
    std::exit(0);
}
void SaveChangesIntoBase(User CurrenUser,const CardAccount& current_account,BANK currentbank,std::vector<User> UsersBase){
    std::vector<CardAccount> AccountsBase = currentbank.GetDataBase();
    for (int i=0;;i++){
        if (CurrenUser.GetName()==UsersBase[i].GetName()){
            UsersBase[i]=CurrenUser;
            AccountsBase[i]=current_account;
            break;
        }
    }
    std::ofstream Accounts("database.txt");
    std::ofstream Users("UsersList.txt");
    for(int i = 0;i<AccountsBase.size();i++){
        Accounts<<AccountsBase[i].ViewScore()<<" "<<AccountsBase[i].GetCardNumber()<<" "<<AccountsBase[i].GetPinCode()<<std::endl;
        Users<<UsersBase[i].GetName()<<" "<<UsersBase[i].GetCash()<<" "<<"0000"<<std::endl;
    }
    std::ofstream BankInfo("Bank.txt");
    BankInfo<<currentbank.GetScore();
    Accounts.close();
    Users.close();
    BankInfo.close();
}
int main(int argc,char *argv[] ) {
    std::string database = argv[1];
    std::string userslist = argv[2];
    std::string bank = argv[3];
    std::vector<User> UsersBase;
    std::vector<CardAccount> AccountsBase;
    AccountsBase = CheckingDatabase(database);
    UsersBase = PossibleUsers(userslist);
    AccountLinker(UsersBase, AccountsBase);
    [[maybe_unused]] bool access;
    int input;
    Launching_Screen screen1;
    User CurrentUser = CurrentUserIs(UsersBase);
    Insert_card screen2;
    std::cin>>input;
    CardAccount current_account;
    if (input == 1) {
        current_account = Insert_card::Processing(CurrentUser, AccountsBase);
        screen2.button1();
    }
    else{
        screen2.button2();
    }
    Pincode_window screen3;
    std::cin>>input;
    if (input == 1){
        screen3.button1(current_account);
    }
    else {
        screen3.button2();
    }
    BANK currentbank = BankInfoReading(AccountsBase, bank);
    Main_Menu screen4(CurrentUser, current_account, currentbank);
    while(input!=4){
        screen4.ShowScreen();
        std::cin>>input;
        switch(input){
            case 1:screen4.button1();break;
            case 2:screen4.button2();break;
            case 3:screen4.button3();break;
            case 4:screen4.button4();input=4;break;
            default :break;
        }
    }
    CurrentUser = screen4.SaveUser();
    current_account = screen4.SaveAccount();
    currentbank = screen4.SaveBankInfo();
    SaveChangesIntoBase(CurrentUser,current_account,currentbank,UsersBase);
}
#include <iostream>
#include <string>
#include "Menu.h"
#include <vector>
#include "parser.h"
#include "Set.h"
using namespace custom_set;
using namespace std;
namespace Menu {
    void print(){
        string input1, input2,element;
        vector<string> parsed_set_1,parsed_set_2;

        while (true) {
            cout << "Enter set1: \n";
            cin >> input1;
            parsed_set_1 = set_parser(input1);
            if (parsed_set_1.size()==0) break;
            if(parsed_set_1[0].compare("error")==0) cout<<"Dublicates were found!\nPlease try again\n";
            else break;
        }

        while (true) {
            cout << "Enter set2: \n";
            cin >> input2;
            parsed_set_2 = set_parser(input2);
            if (parsed_set_2.size()==0) break;
            if(parsed_set_2[0].compare("error")==0) cout<<"Dublicates were found!\nPlease try again\n";
            else break;
        }

        while(true) {
            Set set1(parsed_set_1), set2(parsed_set_2);
            cout << "1 - add element\n"
                    "2 - delete element\n"
                    "3 - power\n"
                    "4 - inclusion\n"
                    "5 - union\n"
                    "6 - intersection\n"
                    "7 - difference\n"
                    "8 - boolean\n";
            int kod;
            int num;
            cin >> kod;
            switch (kod) {



                case 1: {
                    cout << "Which set do you want to add an element to? (1/2) ";
                    cin >> num;
                            switch (num) {
                                case 1: {
                                    cout << "Enter the element to add: ";
                                    cin >> element;
                                    set1.set_add(element);
                                    set1.print();
                                    break;
                                }
                                case 2: {
                                    cout << "Enter the element to add: ";
                                    cin >> element;
                                    set2.set_add(element);
                                    set2.print();
                                    break;
                                }
                                default:
                                    cout << "Enter a valid option!";
                            }
                            break;
                        }

                        case 2: {
                            cout << "Which set do you want to remove an element from? (1/2) ";
                            cin >> num;
                            switch (num) {
                                case 1: {
                                    cout << "Enter the element to remove: ";
                                    cin >> element;
                                    set1.set_remove(element);
                                    set1.print();
                                    break;
                                }
                                case 2: {
                                    cout << "Enter the element to remove: ";
                                    cin >> element;
                                    set2.set_remove(element);
                                    set2.print();
                                    break;
                                }
                                default:
                                    cout << "Enter a valid option!";
                            }
                            break;
                        }

                    case 3: {
                        cout << "Which set's length do you want to get? (1/2) ";
                    cin >> num;
                    switch (num) {
                        case 1: {
                            cout << "The length of set 1 is ";
                            cout << set1.set_length()<<endl;
                            break;
                        }
                        case 2: {
                            cout << "The length of set 2 is ";
                            cout << set2.set_length()<<endl;
                            break;
                        }
                        default:
                            cout << "Enter a valid option!";
                    }
                    break;
                }
                case 4: {
                    cout << "In which set do you want to check inclusion? (1/2) ";
                    cin >> num;
                    switch (num) {
                        case 1: {
                            cout << "Enter the element to check: ";
                            cin >> element;
                            cout << set1[element] << endl;
                            break;
                        }
                        case 2: {
                            cout << "Enter the element to check: ";
                            cin >> element;
                            cout << set2[element] << endl;
                            break;
                        }
                        default:
                            cout << "Enter a valid option!";
                    }
                    break;
                }
                case 5: {
                    Set res = set1 + set2;
                    res.print();
                    break;
                }
                case 6: {
                    Set res = set1 * set2;
                    res.print();
                    break;
                }
                case 7: {
                    Set res = set1 - set2;
                    res.print();
                    break;
                }
                case 8: {
                    cout << "Which set do you want to get boolean of? (1/2) ";
                    cin >> num;
                    switch (num) {
                        case 1: {
                            set1.set_boolean();
                            break;
                        }
                        case 2: {
                            set2.set_boolean();
                            break;
                        }
                        default:
                            cout << "Enter a valid option!";
                    }
                    cout << endl;
                    break;
                }
                default: {
                    cout << "incorrect input\ntry again\n";
                    print();
                }



            }
        }
    }


}
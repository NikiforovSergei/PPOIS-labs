#include <string>
#include <iostream>
#include <vector>
#include <Set.h>
#include <parser.h>

using namespace std;
using namespace custom_set;

int main(){
    string input1, input2, element;
    vector<string> parsed_set_1, parsed_set_2;
    int choice;

    cout<<"Enter first set: ";
    cin >> input1;

    cout<<"Enter second set: ";
    cin >> input2;

    cout << "\n";

    while (true){
//        input1 = "{3a, e, 3b, 10x, 2h, 3{3g}}";
//        input2 = "{4a, 2e, u, 5b, x, p, 2{3g}, {}}";

        parsed_set_1 = set_parser(input1);
        parsed_set_2 = set_parser(input2);

        Set set1(parsed_set_1), set2(parsed_set_2);

        cout <<"Choose the operation you want: \n\n";
        cout <<"1) Union \n";
        cout <<"2) Intersection \n";
        cout <<"3) Difference \n";
        cout <<"4) Boolean \n";
        cout <<"5) Add an element \n";
        cout <<"6) Remove an element \n";
        cout <<"7) Inclusion of an element \n";
        cout <<"8) Length of a multiset \n";
        cout <<"9) Is empty \n\n";

        cin >> choice;

        switch (choice){
        case 1: {
            Set res = set1 + set2;
            res.print();
            break;
        }
        case 2: {
            Set res = set1 * set2;
            res.print();
            break;
        }
        case 3: {
            Set res = set1 - set2;
            res.print();
            break;
        }
        case 4: {
            cout << "Which multiset do you want to get boolean of? (1/2) ";
            cin >> choice;
            switch (choice){
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
            break;
        }
        case 5: {
            cout << "Which multiset do you want to add an element to? (1/2) ";
            cin >> choice;
            switch (choice){
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
        case 6: {
            cout << "Which multiset do you want to remove an element from? (1/2) ";
            cin >> choice;
            switch (choice){
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
        case 7: {
            cout << "In which multiset do you want to check inclusion? (1/2) ";
            cin >> choice;
            switch (choice){
            case 1: {
                cout << "Enter the element to check: ";
                cin >> element;
                cout << set1[element];
                break;
            }
            case 2: {
                cout << "Enter the element to check: ";
                cin >> element;
                cout << set2[element];
                break;
            }
            default:
                cout << "Enter a valid option!";
            }
            break;
        }
        case 8: {
            cout << "Which multiset's length do you want to get? (1/2) ";
            cin >> choice;
            switch (choice){
            case 1: {
                cout << "The length of multiset 1 is ";
                cout << set1.set_length();
                break;
            }
            case 2: {
                cout << "The length of multiset 2 is ";
                cout << set2.set_length();
                break;
            }
            default:
                cout << "Enter a valid option!";
            }
            break;
        }
        case 9: {
            cout << "Which multiset is empty? (1/2) ";
            cin >> choice;
            switch (choice){
            case 1: {
                cout << set1.is_empty();
                break;
            }
            case 2: {
                cout << set2.is_empty();
                break;
            }
            default:
                cout << "Enter a valid option!";
            }
            break;
        }
        }
        cout << "\n";
    }
    return 0;
}

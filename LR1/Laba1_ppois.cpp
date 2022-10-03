#include "Header.h"

 int menu() {
     cout << "Create a rectangle\n" << "Enter coordinates of diagonas points\n";
     int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
     cin >> x1 >> y1 >> x2 >> y2;
     Rectangle ABCD(x1, y1, x2, y2);
     cout << "Enter name\n";
     string name;
     cin >> name;
     ABCD.SetName(name);
     int key = 0;
     cout << endl;
     while (1) {
         cout << endl << "Select an action:\n" << "0:Exit\n" << "1:Change rectangle\n" << "2:Get Coordinates and name\n" << "3:Move rectangle\n" << "4:Switch size\n" << "5:Increase preincrementaly\n" << "6:Increase postincrementaly\n"
             << "7:Decrease preincrementaly\n" << "8:Decrease postincrementaly\n" << "9:Build with +\n" << "10:Build with +=\n" << "11:Build with -\n" << "12:Build with -=\n";
         cin >> key;
         switch (key) {
         default: return 0;
         case 1: {cout << "Enter coordinates of diagonas points\n";
             cin >> x1 >> y1 >> x2 >> y2;
             ABCD.Set_rectangle_coordinates(x1, y1, x2, y2);
             cout << "Enter name\n";
             cin >> name;
             ABCD.SetName(name);
             ABCD.Show_rectangle_coordinates();
             cout << endl << ABCD.GetName() << endl;
             break; }
         case 2: {cout << endl;  ABCD.Show_rectangle_coordinates(); cout << ABCD.GetName() << endl; break; }
         case 3: {cout << endl << "Move in which direction?\n" << "1:Up\n" << "2:Right\n" << "3:Down\n" << "4:Left\n";
             int direction_id = 0;
             cin >> direction_id;
             cout << "How much to move?\n";
             int num = 0;
             cin >> num;
             ABCD.MoveRectangle(direction_id, num);
             break; }
         case 4: {cout << endl  << "Which side to move?\n" << "1:Up\n" << "2:Right\n" << "3:Down\n" << "4:Left\n";
             int direction_id = 0;
             cin >> direction_id;
             cout << "How much to move?\n" << "Positive number to increase, negative to decrease\n";
             int num = 0;
             cin >> num;
             switch (direction_id)
             {
             case 1: {ABCD.MoveUpSide(num); break; }
             case 2: {ABCD.MoveRightSide(num); break; }
             case 3: {ABCD.MoveDownSide(num); break; }
             case 4: {ABCD.MoveLeftSide(num); break; }
             default:
                 break;
             }
             break; }
         case 5: {++ABCD; break; }
         case 6: {ABCD++; break; }
         case 7: {--ABCD; break; }
         case 8: {ABCD--; break; }
         case 9: {cout << endl << "Create the second rectangle\n" << "Enter coordinates of diagonas points\n";
             int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
             cin >> X1 >> Y1 >> X2 >> Y2;
             Rectangle abcd(X1, Y1, X2, Y2);
             Rectangle NEWRECT = ABCD + abcd;
             ABCD = NEWRECT; break; }
         case 10: {cout << endl << "Create the second rectangle\n" << "Enter coordinates of diagonas points\n";
             int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
             cin >> X1 >> Y1 >> X2 >> Y2;
             Rectangle abcd(X1, Y1, X2, Y2);
             ABCD += abcd; break; }
         case 11: {cout << endl << "Create the second rectangle\n" << "Enter coordinates of diagonas points\n";
             int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
             cin >> X1 >> Y1 >> X2 >> Y2;
             Rectangle abcd(X1, Y1, X2, Y2);
             Rectangle NEWRECT = ABCD - abcd;
             ABCD = NEWRECT; break; }
         case 12: {cout << endl << "Create the second rectangle\n" << "Enter coordinates of diagonas points\n";
             int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
             cin >> X1 >> Y1 >> X2 >> Y2;
             Rectangle abcd(X1, Y1, X2, Y2);
             ABCD -= abcd; break; }
         }
     }
 }

 int main()
 {
     menu();
     return 0;
 }
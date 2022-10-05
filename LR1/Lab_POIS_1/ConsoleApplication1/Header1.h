/**
* @file Header.h
* @author Daniil Kimstach
* @brief This file contain all necessary definitions
*/

#pragma once


#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

/**
* @brief Class which describes a partition(slot) in a Turing machine
* @param 'value' - binary value of the number
*/
class Partition {
private:
    string value;
public:
    /**
   * @brief Default constructor without parameters
   */
    Partition() {

    }
    /**
   * @brief Default constructor with parameters
   * @param[in] 'value' - binary value of the number in the Turing machine
   */

    Partition(string value) {
        this->value = value;
    }
    /**
    * @brief Return partitions's value
    * @return 'value' - binary value
    */
    string get_value() {
        return value;
    }
    /**
   * @brief Set partiton's values
   * @param[in] 'value' - binary value
   */
    void set_value(string val) {
        this->value = val;
    }
    /**
    * @brief Allows to convert the value of a number from the 10 system to binary
    * @param[in] number to convert into binary value
    * @return binary value of the number
    */
    string IntToBin(int number) {
        string temp_number;
        int temp = number;
        while (number) {
            if (number % 2 == 0) {
                temp_number += '0';
            }
            else if (number % 2 != 0) {
                temp_number += '1';
            }
            number /= 2;
        }
        string num;
        for (int i = temp_number.length() - 1; i > -1; --i) {
            num += temp_number[i];
        }

        if (num.length() < 5) {
            while (num.length() < 5) {
                num = "0" + num;
            }
        }
        if (temp < 0) {
            num[0] = '1';
        }
        return num;
    }
    /**
   * @brief Allows to convert the value of a number from the binary system to 10 system
   * @param[in] number to convert into binary value
   * @return 10 value of the number
   */
    int BinToInt(string& val) {
        int int_value = 0;

        for (int i = 1; i < val.length(); ++i) {
            if (val[i] == '0') {
                continue;
            }
            else if (val[i] == '1') {
                int_value += pow(2, (val.length() - i - 1));
            }
        }
        if (val[0] == '1') {
            int_value *= -1;
        }
        return int_value;

    }
    /**
    * @brief create new object of the class 'Partition' with the attribute 'value' that
    * is equal to sum of the values of the another objects. Also this method convert 10 system value 
    * of the second object into the binary
    *
    * overload of + operator
    */
    Partition operator+(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 + int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
    * @brief create new object of the class 'Partition' with the attribute 'value' that
    * is equal to difference of the values of the another objects. Also this method convert 10 system value
    * of the second object into the binary
    *
    * overload of - operator
    */
    Partition operator-(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 - int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
    * @brief create new object of the class 'Partition' with the attribute 'value' that
    * is equal to multiplication of the values of the another objects. Also this method convert 10 system value
    * of the second object into the binary
    *
    * overload of * operator
    */
    Partition operator*(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 * int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
   * @brief create new object of the class 'Partition' with the attribute 'value' that
   * is equal to division of the values of the another objects. Also this method convert 10 system value
   * of the second object into the binary
   *
   * overload of / operator
   */
    Partition operator/(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 / int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
 * @brief create new object of the class 'Partition' with the attribute 'value' that
 * is equal to bitwise left shift of the values of the another objects. Also this method convert 10 system value
 * of the second object into the binary
 *
 * overload of << operator
 */
    Partition operator <<(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 << int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
 * @brief create new object of the class 'Partition' with the attribute 'value' that
 * is equal to bitwise right shift of the values of the another objects. Also this method convert 10 system value
 * of the second object into the binary
 *
 * overload of >> operator
 */
    Partition operator>>(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 >> int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
 * @brief create new object of the class 'Partition' with the attribute 'value' that
 * is equal to XOR of the values of the another objects. Also this method convert 10 system value
 * of the second object into the binary
 *
 * overload of ^ operator
 */
    Partition operator ^(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 ^ int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
* @brief create new object of the class 'Partition' with the attribute 'value' that
* is equal to logival operator 'and' of the values of the another objects. Also this method convert 10 system value
* of the second object into the binary
*
* overload of & operator
*/
    Partition operator &(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 & int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }
    /**
* @brief create new object of the class 'Partition' with the attribute 'value' that
* is equal to  logical operator 'or' of the values of the another objects. Also this method convert 10 system value
* of the second object into the binary
*
* overload of | operator
*/
    Partition operator |(const Partition& other) {
        Partition temp;
        int int_value_1 = BinToInt(value);
        int int_value_2 = 0;
        for (int i = 1; i < other.value.length(); ++i) {
            if (other.value[i] == '0') {
                continue;
            }
            else if (other.value[i] == '1') {
                int_value_2 += pow(2, (other.value.length() - i - 1));
            }
        }
        if (other.value[0] == '1') {
            int_value_2 *= -1;
        }
        int result = int_value_1 | int_value_2;
        string number = IntToBin(result);
        temp.value = number;
        return temp;
    }

};
/**
* @brief Class which describes a tape of the Turing Machine
* @param act, first_value, second_value, result, end_program - all the types of the partition in the tape
* first_value, second_value, result after the calculating are containg the values of the objects of the class 'Partition'
* 
*/
class Tape {
private:
    string act;
    string first_value;
    string second_value;
    string result;
    string end_program;
public:
    /**
    * @brief Default constructor with the default parameters for the result, and_program fields
    */
    Tape() {
        result = "00000";
        end_program = "11111";
    }
    /**
    * @brief Constructor with the parameters, they are: action(the type of calculating), first_value, second_value, result
    * @param[in] action, first_val, second_val, res - the main partition of the tape, end of the program is qual to '00000' in any case 
    */
    Tape(string action, string first_val, string second_val, string res) {
        act = action;
        first_value = first_val;
        second_value = second_val;
        result = res;
    }
    /**
    * @brief Setting tape's partitions
    * @param[in] res -  tape's result of the program 
    */
    void set_result(string res) {
        result = res;
    }
    /**
    * @brief Setting tape's value of the first partition 
    * @param[in] first_val -  tape's value  of the first partition
    */
    void set_first_value(string first_val) {
        first_value = first_val;
    }
    /**
    * @brief Setting tape's value of the second partition
    * @param[in] second_val -  tape's value  of the second partition
    */
    void set_second_value(string second_val) {
        second_value = second_val;
    }
    /**
    * @brief Setting tape's type of the calculating
    * @param[in] act -  tape's type of the calculating
    */
    void set_operation(string operation) {
        act = operation;
    }
    /**
    * @brief All the parts of the tape are here
    */
    void ShowTape() {
        end_program = "1111";
        cout << "|" << act << "|" << first_value << "|" << second_value << "|"
        << result << "|" << end_program << "|" << endl;
    }
};
/**
* @brief Class which describes a rod(reading a file class)
* @param filename, operation, first_value, second_value, result, exit - all the types that are needed for the rod
* first_value, second_value, result after the calculating are containg the values of the objects of the class 'Partition'
*
*/
class Rod {
private:
    string filename, operation, first_value, second_value, result, exit;
    Tape tape;
public:
    /**
   * @brief Default constructor
   */
    Rod() {

    }
    /**
 * @brief Default constructor
 * @param filename - for the operations with the file
 */
    Rod(string name) {
        filename = name;
    }
    /**
* @brief reading the file and defining all the values of the tape
*/
    void Read() {
        string line;
        fstream in(filename); // окрываем файл для чтения
        if (in.is_open())
        {
            while (getline(in, line))
            {
                cout << line << endl;
            }
        }
        int space = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == ' ') {
                space++;
            }
            else if (space == 0) {
                operation += line[i];
            }
            else if (space == 1) {
                first_value += line[i];
            }
            else if (space == 2) {
                second_value += line[i];
            }
            else if (space == 3) {
                result += line[i];
            }
            else if (space == 4) {
                exit += line[i];
            }
        }

        in.close();     // закрываем файл

    }
    /**
* @brief Calculating the result due to the kind of the operation
*/
    void Result() {
        Partition first_val(first_value);
        Partition second_val(second_value);
        if (operation == "00001") {
            Partition res = first_val + second_val;
            result = res.get_value();
        }
        else if (operation == "00010") {
            Partition res = first_val - second_val;
            result = res.get_value();
        }
        else if (operation == "00100") {
            Partition res = first_val * second_val;
            result = res.get_value();
        }
        else if (operation == "01000") {
            Partition res = first_val / second_val;
            result = res.get_value();
        }
        else if (operation == "10000") {
            Partition res = first_val << second_val;
            result = res.get_value();
        }
        else if (operation == "00011") {
            Partition res = first_val >> second_val;
            result = res.get_value();
        }
        else if (operation == "00111") {
            Partition res = first_val ^ second_val;
            result = res.get_value();
        }
        else if (operation == "01111") {
            Partition res = first_val & second_val;
            result = res.get_value();
        }
        else if (operation == "001111") {
            Partition res = first_val | second_val;
            result = res.get_value();
        }
        tape.set_operation(operation);
        tape.set_first_value(first_value);
        tape.set_second_value(second_value);
        tape.ShowTape();
    }
    /**
* @brief Writing values into the files(a part of test menu)
*/
    void Write() {
        ofstream file(filename);
        cout << "Операция +: 00001" << endl;
        cout << "Операция -: 00010" << endl;
        cout << "Операция *: 00100" << endl;
        cout << "Операция /: 01000" << endl;
        cout << "Операция <<: 10000" << endl;
        cout << "Операция >>: 00011" << endl;
        cout << "Операция ^: 00111" << endl;
        cout << "Операция &: 01111" << endl;
        cout << "Операция |: 001111" << endl;
        cout << "Введите операцию: " << endl;
        string oper;
        cin >> oper;
        cout << "Введите первое слагаемое: " << endl;
        string first_val;
        cin >> first_val;
        cout << "Введите второе слагаемое: " << endl;
        string  second_val;
        cin >> second_val;
        string line = oper + " " + first_val + " " + second_val + " " + "00000" + " " + "11111";
        file << line;

    }
    /**
* @brief Writing the result into the file
*/
    void WriteResult() {
        ofstream file(filename);
        string line = operation + " " + first_value + " " + second_value + " " + result + " " + exit;

        file << line;
        file.close();
        tape.set_result(result);
        tape.ShowTape();

    }
};
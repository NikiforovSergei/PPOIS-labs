#include <string>
#include <iostream>
#include <fstream>
#include "TuringsMachine.h"

namespace Tape
{
	/**
	///Function show_Tape shows tape in console
	*/
	void Tape::show_Tape(std::string temp_Tape)
	{
		std::string temp_line = temp_Tape;
		std::cout << "|";
		for (int i = 0; i < temp_line.size(); i++)
		{
			std::cout << temp_line[i];
			if (i == 0)
			{
				continue;
			}
			if ((i + 1) % 9 == 0)
			{
				std::cout << "|";
			}
		}
	}

}

namespace Rules
{
	/**
	///Function show_rules shows rules in console
	*/
	void Rules::show_rules(Rules rules)
	{
		Rule temp;
		for (int i = 0; i < rules.get_rules().size(); i++)
		{
			temp = rules.get_rules()[i];
			std::cout << "Condition: " << temp.condition << "Direction: " << temp.direction << "Type:" << temp.type << std::endl;
		}
	}

	/**
	///Function add_rule adds new rule
	*/
	void Rules::add_rule(Rule temp_rule, Rules rules)
	{
		std::vector<Rule> temp_rules = rules.get_rules();
		temp_rules.push_back(temp_rule);
		rules.set_rules(temp_rules);
	}

	/**
	///Function remove_rule removes rule from rule's list
	*/
	std::vector<Rule> Rules::remove_rule(Rules rules, int number_of_rule)
	{
		std::vector<Rule> temp_rules = rules.get_rules();
		number_of_rule--;
		temp_rules.erase(temp_rules.begin() + number_of_rule);
		return temp_rules;
	}
}

namespace Bogie
{
	/**
	*Correct existing tape, check the correct input for condition and direction
	*/
	std::string Bogie::check_Cells(std::string tape, int n, std::string direct)
	{
		std::string temp_tape = tape;
		if (n < 0)
		{
			for (int i = 0; i < fabs(n); i++)
			{
				temp_tape += "010101010";
			}
			temp_tape += tape;
			set_Condition(fabs(n));
		}
		else if (n >= (tape.size() / 9))
		{
			temp_tape += tape;
			for (int i = 0; i < n - (tape.size() / 9); i++)
			{
				temp_tape += "010101010";
			}
			set_Condition(n - (tape.size() / 9));
		}
		if (direct == "R" && n == (tape.size() / 9))
		{
			temp_tape += "010101010";
			set_Condition(tape.size() / 9);
		}
		else if (direct == "L" && n == 0)
		{
			std::string temp = temp_tape;
			temp_tape = "010101010";
			temp_tape += temp;
			set_Condition(1);
		}
		return temp_tape;
	}

	/**
	///Function int_To_Bin converts integer to binary
	*/
	std::string Bogie::int_To_Bin(int number)
	{
		std::string temp_result = "";
		if (number < 0)
		{
			temp_result.push_back('0');
		}
		else
		{
			temp_result.push_back('1');
		}
		int temp_number = fabs(number);
		if (temp_number == 0)
		{
			temp_result = "000000000";
			return temp_result;
		}
		while (temp_number != 1)
		{
			if (temp_number % 2 == 0)
			{
				temp_result.push_back('0');
				temp_number = temp_number / 2;
			}
			else
			{
				temp_result.push_back('1');
				temp_number = temp_number / 2;
			}
		}
		return temp_result;
	}

	/**
	///Function bin_To_Int convert binary to integer
	*/
	int Bogie::bin_To_Int(std::string value)
	{
		std::string temp_value = value;
		int result = 0;
		for (int i = 1; i < temp_value.size(); i++)
		{
			if (temp_value[i] == '1')
			{
				result += pow(2, temp_value.size() - i - 1);
			}
		}
		if (temp_value[0] == '0')
		{
			result = 0 - result;
		}
		return result;
	}

	/**
	///Function addition adds required symbols to line
	*/
	std::string Bogie::addition(std::string temp_Str)
	{
		std::string temp = "";
		char temp_sign = temp_Str[0];
		temp.push_back(temp_sign);
		for (int i = 0; i < 9 - temp_Str.length(); i++)
		{
			temp.push_back('0');
		}
		for (int i = 1; i < temp_Str.length(); i++)
		{
			temp.push_back(temp_Str[i]);
		}
		return temp;
	}

	/**
	///Function fill_Cell fills Cell by a binary code
	*/
	std::string Bogie::fill_Cell(Tape::Tape Tape1, std::string Cell1, std::string direct, int n)
	{
		std::string temp_Value = "";
		std::string temp_Tape = Tape1.get_Tape();
		if (direct == "R")
		{
			for (int i = n * 9; i < (n + 1) * 9; i++)
			{
				temp_Value.push_back(temp_Tape[i]);
			}
		}
		else if (direct == "L")
		{
			for (int i = (n - 1) * 9; i < n * 9; i++)
			{
				temp_Value.push_back(temp_Tape[i]);
			}
		}
		return temp_Value;
	}

	///Function SUM summarise two values of two cells
	std::string Bogie::SUM(std::string Cell1, std::string Cell2)
	{
		std::string temp_Value1 = Cell1;
		std::string temp_Value2 = Cell2;
		int temp_int_Value1 = 0;
		int temp_int_Value2 = 0;
		temp_int_Value1 = bin_To_Int(temp_Value1);
		temp_int_Value2 = bin_To_Int(temp_Value2);
		int temp_int_result = 0;
		temp_int_result = temp_int_Value1 + temp_int_Value2;
		std::string result = int_To_Bin(temp_int_result);
		return result;
	}

	/**
	///Function DIFF finds difference between two cells
	*/
	std::string Bogie::DIFF(std::string Cell1, std::string Cell2)
	{
		std::string temp_Value1 = Cell1;
		std::string temp_Value2 = Cell2;
		int temp_int_Value1 = 0;
		int temp_int_Value2 = 0;
		temp_int_Value1 = bin_To_Int(temp_Value1);
		temp_int_Value2 = bin_To_Int(temp_Value2);
		int temp_int_result = 0;
		temp_int_result = fabs(temp_int_Value1 - temp_int_Value2);
		std::string result = int_To_Bin(temp_int_result);
		return result;
	}

	/**
	///Function Comp composite two cells
	*/
	std::string Bogie::COMP(std::string Cell1, std::string Cell2)
	{
		std::string temp_Value1 = Cell1;
		std::string temp_Value2 = Cell2;
		int temp_int_Value1 = 0;
		int temp_int_Value2 = 0;
		temp_int_Value1 = bin_To_Int(temp_Value1);
		temp_int_Value2 = bin_To_Int(temp_Value2);
		int temp_int_result = 0;
		temp_int_result = temp_int_Value1 * temp_int_Value2;
		std::string result = int_To_Bin(temp_int_result);
		return result;
	}

	/**
	///Function Not_V finds value opposite to temp value
	*/
	std::string Bogie::Not_V(std::string temp_Cell)
	{
		std::string temp_Value = temp_Cell;
		for (int i = 0; i < temp_Value.size(); i++)
		{
			if (temp_Value[i] == '1')
			{
				temp_Value[i] = '0';
			}
			else if (temp_Value[i] == '0')
			{
				temp_Value[i] = '1';
			}
		}
		return temp_Value;
	}

	/**
	///Function OR finds logic or between two cells
	*/
	std::string Bogie::OR(std::string Cell1, std::string Cell2)
	{
		std::string temp_Value1 = Cell1;
		std::string temp_Value2 = Cell2;
		std::string result = "";
		for (int i = 0; i < temp_Value1.length(); i++)
		{
			if (temp_Value1[i] == '1')
			{
				if (temp_Value2[i] == '0')
				{
					result += "1";
				}
				else if (temp_Value2[i] == '1')
				{
					result += "1";
				}
			}
			else if (temp_Value1[i] == '0')
			{
				if (temp_Value2[i] == '0')
				{
					result += "0";
				}
				else if (temp_Value2[i] == '1')
				{
					result += "1";
				}
			}
		}
		return result;
	}

	/**
	///Function XOR finds logic xor between two cells
	*/
	std::string Bogie::XOR(std::string Cell1, std::string Cell2)
	{
		std::string temp_Value1 = Cell1;
		std::string temp_Value2 = Cell2;
		std::string result = "";
		for (int i = 0; i < temp_Value1.length(); i++)
		{
			if (temp_Value1[i] == '1')
			{
				if (temp_Value2[i] == '0')
				{
					result += "1";
				}
				else if (temp_Value2[i] == '1')
				{
					result += "0";
				}
			}
			else if (temp_Value1[i] == '0')
			{
				if (temp_Value2[i] == '0')
				{
					result += "0";
				}
				else if (temp_Value2[i] == '1')
				{
					result += "1";
				}
			}
		}
		return result;
	}

	/*
	///Function AND finds logic and between two cells
	*/
	std::string Bogie::AND(std::string Cell1, std::string Cell2)
	{
		std::string temp_Value1 = Cell1;
		std::string temp_Value2 = Cell2;
		std::string result = "";
		for (int i = 0; i < temp_Value1.length(); i++)
		{
			if (temp_Value1[i] == '1')
			{
				if (temp_Value2[i] == '0')
				{
					result += "0";
				}
				else if (temp_Value2[i] == '1')
				{
					result += "1";
				}
			}
			else if (temp_Value1[i] == '0')
			{
				if (temp_Value2[i] == '0')
				{
					result += "0";
				}
				else if (temp_Value2[i] == '1')
				{
					result += "0";
				}
			}
		}
		return result;
	}

	/**
	///Function BLS finds binary left shift of cell
	*/
	std::string Bogie::BLS(std::string temp_Cell, int n)
	{
		std::string temp_Value = temp_Cell;
		for (int i = 0; i < temp_Value.size(); i++)
		{
			if (i >= temp_Value.size() - n)
			{
				temp_Value[i] = '0';
			}
			else if (i < temp_Value.size() - n)
			{
				temp_Value[i] = temp_Value[i + 1];
			}
		}
		return temp_Value;
	}

	/**
	///Function BRS finds binary right shift of cell
	*/
	std::string Bogie::BRS(std::string temp_Cell, int n)
	{
		std::string temp_Value = temp_Cell;
		for (int i = temp_Value.size() - 1; i >= 0; i--)
		{
			if (i < n)
			{
				temp_Value[i] = '0';
			}
			else if (i >= n)
			{
				temp_Value[i] = temp_Value[i - 1];
			}
		}
		return temp_Value;
	}
}

namespace Input_Output_File
{
	/**
	///Function input_from_file inputs from file value of line in Turing's machine
	*/
	std::string Input_Output_File::input_from_file(std::string in_file)
	{
		std::ifstream in_File(in_file);
		std::string temp_Str = "";
		getline(in_File, temp_Str);
		in_File.close();
		return temp_Str;
	}

	/**
	///Function input_from_file_rules inputs from file rules in Turing's machine
	*/
	std::vector<Rule> Input_Output_File::input_from_file_rules(std::string in_rules_file)
	{
		std::ifstream in_Rules_File(in_rules_file);
		std::vector<Rule> temp_rules;
		std::string line = "";
		getline(in_Rules_File, line);
		for (int i = 0; i < line.length(); i += 4)
		{
			Rule temp_rule;
			std::string temp_line = "";
			temp_line += line[i];
			temp_rule.condition = stoi(temp_line);
			temp_rule.direction = line[i + 1];
			temp_rule.type = line[i + 2];
			temp_rule.operation = line[i + 3];
			temp_rules.push_back(temp_rule);
		}
		in_Rules_File.close();
		return temp_rules;
	}

	/**
	///Function output_in_file outputs in file value of line in Turing's machine
	*/
	void Input_Output_File::output_in_file(std::string out_Tape, std::string out_file)
	{
		std::ofstream out_File(out_file);
		std::string temp_Str = out_Tape;
		out_File << temp_Str;
		out_File.close();
	}

	/**
	///Function output_in_file_rules outputs rules in file
	*/
	void Input_Output_File::output_in_file_rules(Rules::Rules rules, std::string out_rules_file)
	{
		std::ofstream out_Rules_File;
		out_Rules_File.open(out_rules_file);
		std::vector<Rule> temp_Rules = rules.get_rules();
		for (int i = 0; i < temp_Rules.size(); i++)
		{
			out_Rules_File << temp_Rules[i].condition;
			out_Rules_File << temp_Rules[i].direction;
			out_Rules_File << temp_Rules[i].type;
			out_Rules_File << temp_Rules[i].operation;
		}
		out_Rules_File.close();
	}
}
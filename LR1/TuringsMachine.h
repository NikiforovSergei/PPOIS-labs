#pragma once

#include <string>
#include <vector>

struct Rule
{
	int condition;
	std::string direction;
	std::string type;
	std::string operation;
};

namespace Tape
{
	class Tape
	{
	private:
		std::string line;

	public:
		Tape()
		{

		}
		Tape(std::string temp_value)
		{
			this->line = temp_value;
		}
		std::string get_Tape()
		{
			return this->line;
		}
		void set_Tape(std::string temp_value)
		{
			this->line = temp_value;
		}
		void show_Tape(std::string temp_Tape);
		void add_Cell(std::string temp_Cell)
		{
			this->line += temp_Cell;
		}
		std::string rewrite_Cell(std::string Cell, int condition)
		{
			int j = 0;
			for (int i = condition * 9; i < (condition + 1) * 9; i++)
			{
				this->line[i] = Cell[j];
				j++;
			}
			return this->line;
		}

	};
}

namespace Rules
{
	class Rules
	{
	private:
		std::vector<Rule> rules;
		Rule temp_rule;

	public:
		Rules()
		{

		}
		void set_rule(int n)
		{
			this->temp_rule = get_rules()[n];
		}
		Rule get_rule()
		{
			return this->temp_rule;
		}
		void set_rules(std::vector<Rule> rule)
		{
			this->rules = rule;
		}
		std::vector<Rule> get_rules()
		{
			return this->rules;
		}
		void show_rules(Rules rules);
		void add_rule(Rule temp_rule, Rules rules);
		std::vector<Rule> remove_rule(Rules rules, int number_of_rule);

	};
}

namespace Bogie
{
	class Bogie
	{
	private:
		std::string direction;
		int condition;

	public:
		Bogie()
		{

		}
		Bogie(std::string value, int cond)
		{
			this->direction = value;
			this->condition = cond;
		}
		void set_Direction(std::string value)
		{
			this->direction = value;
			return;
		}
		std::string get_Direction()
		{
			std::string temp = this->direction;
			return temp;
		}
		void set_Condition(int num)
		{
			this->condition = num;
			return;
		}
		int get_Condition()
		{
			int temp_num = this->condition;
			return temp_num;
		}
		std::string check_Cells(std::string tape, int n, std::string direct);
		int bin_To_Int(std::string temp_Value);
		std::string int_To_Bin(int number);
		std::string addition(std::string temp_Cell);
		std::string fill_Cell(Tape::Tape Tape1, std::string Cell1, std::string direct, int n);
		std::string SUM(std::string Cell1, std::string Cell2);
		std::string DIFF(std::string Cell1, std::string Cell2);
		std::string COMP(std::string Cell1, std::string Cell2);
		std::string Not_V(std::string Cell1);
		std::string OR(std::string Cell1, std::string Cell2);
		std::string XOR(std::string Cell1, std::string Cell2);
		std::string AND(std::string Cell1, std::string Cell2);
		std::string BLS(std::string temp_Cell, int n);
		std::string BRS(std::string temp_Cell, int n);

	};
}

namespace Input_Output_File
{
	class Input_Output_File
	{
	private:
		std::string name_of_in_file;
		std::string name_of_out_file;
		std::string name_rules_of_file;

	public:
		std::string get_in()
		{
			return this->name_of_in_file;
		}
		std::string get_out()
		{
			return this->name_of_out_file;
		}
		std::string get_rules_in()
		{
			return this->name_rules_of_file;
		}
		void set_in_from(std::string name_of_file)
		{
			this->name_of_in_file = name_of_file;
		}
		void set_out_in(std::string name_of_file)
		{
			this->name_of_out_file = name_of_file;
		}
		std::string input_from_file(std::string name_of_file);
		std::vector<Rule> input_from_file_rules(std::string in_rules_file);
		void output_in_file(std::string out_Tape, std::string name_of_file);
		void output_in_file_rules(Rules::Rules rules, std::string temp_rules);
	};
}
#include <iostream>
#include <string>
#include <fstream>
#include "TuringsMachine.h"
#include <Windows.h>
using namespace std;

int Menu(Tape::Tape temp_Tape, Rules::Rules temp_rule)
{
	cout << "\n--------------------------\n";
	temp_Tape.show_Tape(temp_Tape.get_Tape());
	cout << endl;
	cout << "Direction: " << temp_rule.get_rule().direction << endl << "Condition: " << temp_rule.get_rule().condition << endl << "Type:" << temp_rule.get_rule().type << endl;
	int variant = 0;
	cout << "\n--------------------------\n";
	cout << "\n--------------------------\n";
	cout << "Choose variant:\n";
	cout << "(1)Fill Cells\n";
	cout << "(2)Add/Remove rule\n";
	cout << "(3)Set rule\n";
	cout << "(4)SUM\n";
	cout << "(5)DIFF\n";
	cout << "(6)COMP\n";
	cout << "(7)NOT_V\n";
	cout << "(8)OR\n";
	cout << "(9)XOR\n";
	cout << "(10)AND\n";
	cout << "(11)BLS\n";
	cout << "(12)BRS\n";
	cout << "(0)Exit the program";
	cout << "\n--------------------------\n";
	cout << "\n--------------------------\n";
	cin >> variant;
	return variant;
}

void output_string(Tape::Tape temp_Tape, Rules::Rules temp_rule)
{
	cout << "\n--------------------------\n";
	temp_Tape.show_Tape(temp_Tape.get_Tape());
	cout << endl;
	cout << "Direction: " << temp_rule.get_rule().direction << endl << "Condition: " << temp_rule.get_rule().condition << endl << "Type:" << temp_rule.get_rule().type <<
		endl << "Operation:" << temp_rule.get_rule().operation << endl;
	cout << "\n--------------------------\n";
}

int main(int argc, char* argv[])
{
	bool var = false;
	Rules::Rules rules;
	Input_Output_File::Input_Output_File In_Out_File;
	Input_Output_File::Input_Output_File In_Out_File_Rules;
	Tape::Tape tape(In_Out_File.input_from_file("input.txt"));
	In_Out_File.set_in_from("input.txt");
	In_Out_File.set_out_in("output.txt");
	vector<Rule> temp_rules = In_Out_File.input_from_file_rules("rules.txt");
	rules.set_rules(temp_rules);
	rules.set_rule(0);
	string direct = "", type = "";
	direct = rules.get_rule().direction;
	type = rules.get_rule().type;
	string Cell1 = "", Cell2 = "";
	int cond = 0, v = 0, num = 0;
	cond = rules.get_rule().condition;
	Bogie::Bogie Carr(direct, cond);
	Cell1 = Carr.fill_Cell(tape, Cell1, Carr.get_Direction(), Carr.get_Condition());
	Cell2 = Carr.fill_Cell(tape, Cell2, direct, cond + 1);
	if (argc > 1 && strcmp(argv[1], "-log") == 0)
	{
		for (int i = 0; i < rules.get_rules().size(); i++)
		{
			output_string(tape, rules);
			rules.set_rule(i);
			Rule temp_rule;
			temp_rule = rules.get_rule();
			tape.set_Tape(Carr.check_Cells(tape.get_Tape(), temp_rule.condition, temp_rule.direction));
			Cell1 = Carr.fill_Cell(tape, Cell1, temp_rule.direction, temp_rule.condition);
			if (temp_rule.direction == "R")
			{
				Cell2 = Carr.fill_Cell(tape, Cell1, temp_rule.direction, temp_rule.condition + 1);
			}
			else if (temp_rule.direction == "L")
			{
				Cell2 = Carr.fill_Cell(tape, Cell1, temp_rule.direction, temp_rule.condition);
			}
			if (temp_rule.operation == "+")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.SUM(Cell1, Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.SUM(Cell1, Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "-")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.DIFF(Cell1, Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.DIFF(Cell1, Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "*")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.COMP(Cell1, Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.COMP(Cell1, Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "/")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.Not_V(Cell1)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.Not_V(Cell1)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "|")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.OR(Cell1, Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.OR(Cell1, Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "^")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.XOR(Cell1, Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.XOR(Cell1, Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "&")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.AND(Cell1, Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.AND(Cell1, Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == "<")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.BLS(Cell1, num)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.BLS(Cell1, num)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (temp_rule.operation == ">")
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.BRS(Cell1, num)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.BRS(Cell1, num)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
		}
	}
	while (TRUE)
	{
		switch (Menu(tape, rules))
		{
		case 1:
			tape.set_Tape(Carr.check_Cells(tape.get_Tape(), Carr.get_Condition(), Carr.get_Direction()));
			Cell1 = Carr.fill_Cell(tape, Cell1, Carr.get_Direction(), Carr.get_Condition());
			if (Carr.get_Direction() == "R")
			{
				Cell2 = Carr.fill_Cell(tape, Cell1, Carr.get_Direction(), Carr.get_Condition() + 1);
			}
			else if (Carr.get_Direction() == "L")
			{
				Cell2 = Carr.fill_Cell(tape, Cell1, Carr.get_Direction(), Carr.get_Condition());
			}
			break;

		case 2:
			cout << "(1)Add Rules\n(2)Remove Rules" << endl;
			int r;
			cin >> r;
			if (r == 1)
			{
				cout << "Add rules:" << endl;
				char dir, typ;
				int con;
				Rule temp_rul;
				cout << "Input rule's condition" << endl;
				cin >> con;
				temp_rul.condition = con;
				cout << "Input rule's direction" << endl;
				cin >> dir;
				temp_rul.direction = dir;
				cout << "Input rule's type" << endl;
				cin >> typ;
				temp_rul.type = typ;
				temp_rules.push_back(temp_rul);
				rules.set_rules(temp_rules);
				In_Out_File_Rules.output_in_file_rules(rules, "rules.txt");
			}
			else if (r == 2)
			{
				cout << "Input number of rule you would like to remove:" << endl;
				int l = 0;
				cin >> l;
				rules.set_rules(rules.remove_rule(rules, l));
				In_Out_File_Rules.output_in_file_rules(rules, "rules.txt");
			}
			break;

		case 3:
			cout << "Input number of rule you would like to set:" << endl;
			int number;
			cin >> number;
			while (number > temp_rules.size())
			{
				cout << "Error this number of rules doesn't exist" << endl << "Try again" << endl;
				cin >> number;
			}
			rules.set_rule(number - 1);
			Carr.set_Condition(rules.get_rule().condition);
			Carr.set_Direction(rules.get_rule().direction);
			break;

		case 4:
			if (rules.get_rule().type == "r")
			{
				tape.rewrite_Cell(Carr.addition(Carr.SUM(Cell1, Cell2)), rules.get_rule().condition);
			}
			else if (rules.get_rule().type == "a")
			{
				tape.add_Cell(Carr.addition(Carr.SUM(Cell1, Cell2)));
			}
			In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			break;

		case 5:
			if (rules.get_rule().type == "r")
			{
				tape.rewrite_Cell(Carr.addition(Carr.DIFF(Cell1, Cell2)), rules.get_rule().condition);
			}
			else if (rules.get_rule().type == "a")
			{
				tape.add_Cell(Carr.addition(Carr.DIFF(Cell1, Cell2)));
			}
			In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			break;

		case 6:
			if (rules.get_rule().type == "r")
			{
				tape.rewrite_Cell(Carr.addition(Carr.COMP(Cell1, Cell2)), rules.get_rule().condition);
			}
			else if (rules.get_rule().type == "a")
			{
				tape.add_Cell(Carr.addition(Carr.COMP(Cell1, Cell2)));
			}
			In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			break;

		case 7:
			cout << "First or second cell?" << endl << "(1)First" << endl << "(2)Second" << endl;
			cin >> v;
			if (v == 1)
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.Not_V(Cell1)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.Not_V(Cell1)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (v == 2)
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.Not_V(Cell2)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.Not_V(Cell2)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			break;

		case 8:
			if (rules.get_rule().type == "r")
			{
				tape.rewrite_Cell(Carr.addition(Carr.OR(Cell1, Cell2)), rules.get_rule().condition);
			}
			else if (rules.get_rule().type == "a")
			{
				tape.add_Cell(Carr.addition(Carr.OR(Cell1, Cell2)));
			}
			In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			break;

		case 9:
			if (rules.get_rule().type == "r")
			{
				tape.rewrite_Cell(Carr.addition(Carr.XOR(Cell1, Cell2)), rules.get_rule().condition);
			}
			else if (rules.get_rule().type == "a")
			{
				tape.add_Cell(Carr.addition(Carr.XOR(Cell1, Cell2)));
			}
			In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			break;

		case 10:
			if (rules.get_rule().type == "r")
			{
				tape.rewrite_Cell(Carr.addition(Carr.AND(Cell1, Cell2)), rules.get_rule().condition);
			}
			else if (rules.get_rule().type == "a")
			{
				tape.add_Cell(Carr.addition(Carr.AND(Cell1, Cell2)));
			}
			In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			break;

		case 11:
			cout << "Choose cell to BLS" << endl << "(1)First" << endl << "(2)Second" << endl;
			cin >> v;
			cout << "Input number: " << endl;
			cin >> num;
			if (v == 1)
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.BLS(Cell1, num)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.BLS(Cell1, num)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (v == 2)
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.BLS(Cell2, num)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.BLS(Cell2, num)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			break;

		case 12:
			cout << "Choose cell to BRS" << endl << "(1)First" << endl << "(2)Second" << endl;
			cin >> v;
			cout << "Input number: " << endl;
			cin >> num;
			if (v == 1)
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.BRS(Cell1, num)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.BRS(Cell1, num)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			else if (v == 2)
			{
				if (rules.get_rule().type == "r")
				{
					tape.rewrite_Cell(Carr.addition(Carr.BRS(Cell2, num)), rules.get_rule().condition);
				}
				else if (rules.get_rule().type == "a")
				{
					tape.add_Cell(Carr.addition(Carr.BRS(Cell2, num)));
				}
				In_Out_File.output_in_file(tape.get_Tape(), In_Out_File.get_out());
			}
			break;

		case 0:
			cout << "Exiting the program...";
			return 0;
			break;
		}
	}
}
#include "Header.h"
void Read_a_line::read_line()
{

	//написать size для A

	/*Sets_and_operations* a = new Sets_and_operations;
	
	Another_operations b;*/
	Saved_Set save_my_set;
	save_my_set.named_sets;
	while (true)
	{
		bool indicator = 0; //для проверки
		string my_line;
		cout << endl;

		getline(cin, my_line);

		if (my_line.find("[") != -1) //проверка, вызывает ли пользователь подмножество 
		{
			cout << endl;
			Set::get_info(subset(my_line, save_my_set));
			continue;
		}

		if (my_line.find("size") != -1)  //проверка, вызывает ли пользователь метод size
		{

			size(my_line, save_my_set);
			continue;
		}

		for (int i = 0; i < my_line.length(); i++)
		{
			if (isalpha(my_line[i]) && isupper(my_line[i])) //проверка на работу с названным множеством
			{
				save_my_set.distr(my_line);
				indicator = true;
				break;
			}
		}


		
		if (!indicator)
		{
			Set::get_info(Sets_and_operations::solution(my_line));
		}
	}
}

/*void Read_a_line::save_sets(string line)
{
	vector<string> names;
	while (true)
	{
		int a = line.find('=');
		if (a!=-1)
		{
			string name_of_perem;
			for (int i = 0; i < a; i++)
			{
				if (isalpha(line[i]) && isupper(line[i]) || line[i] == ' ')
				{
					if (line[i] != ' ') name_of_perem += line[i];
				}
				else cout << "Here would be a mistake";
			}
			names.push_back(name_of_perem);
			line.erase(0, a+1);

		}
		else break;
	}
	Sets_and_operations a;
	Set* named_set = a.solution(line);
	for (int i = 0; i < names.size(); i++)
	{
		named_sets[names[i]] = named_set;
	}
}*/
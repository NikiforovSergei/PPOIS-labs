#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <map>

class multiset{

private:

	std::pair<char, std::vector<std::string>>* set_container;


public:


	void load_set_container(std::string path) {

		std::ifstream file;

		file.open(path);

		if (!file.is_open())
			exit(0);
		else {

			std::pair<char, std::vector<std::string>>* output_set = new std::pair<char, std::vector<std::string>>;

			std::stringstream ss;

			char temp_set_name;

			int bracket_count = 0;

			std::string temp_string = "";

			std::string temp_element = "";

			std::vector<std::string> temp_vector;


			while (file >> temp_set_name)
			{

				std::getline(file, temp_string);

				ss << temp_string;
				ss >> temp_string;

				while (ss >> temp_string) {

					if (temp_string == "{")
						bracket_count++;

					if (bracket_count == 1 && temp_string == "{")
						temp_string = "";

					if (temp_string == "}")
						bracket_count--;

					if (temp_string != "," && bracket_count >= 2) {

						temp_element += temp_string + ' ';

					}
					else if ((temp_string == "," && bracket_count == 1) || (bracket_count == 0 && temp_string == "}") && temp_string != "{") {


						temp_vector.push_back(temp_element);

						temp_element.clear();

					}
					else if ((temp_string != "," && bracket_count == 1) || (temp_string == "," && bracket_count > 1) && temp_string != "{") {

						temp_element += temp_string;

					}





				}

				*output_set = std::make_pair(temp_set_name, temp_vector);
				set_container = output_set;

				ss.clear();
				temp_vector.clear();
			}



			file.close();


		}

	}

	void get_set_container_from_string(std::string string) {

			std::pair<char, std::vector<std::string>>* output_set = new std::pair<char, std::vector<std::string>>;

			std::stringstream ss;

			ss << string;
			
			char temp_set_name;

			int bracket_count = 0;

			std::string temp_string = "";

			std::string temp_element = "";

			std::vector<std::string> temp_vector;


			while (ss >> temp_set_name)
			{
				
				ss >> temp_string;

				while (ss >> temp_string) {

					if (temp_string == "{")
						bracket_count++;

					if (bracket_count == 1 && temp_string == "{")
						temp_string = "";

					if (temp_string == "}")
						bracket_count--;

					if (temp_string != "," && bracket_count >= 2) {

						temp_element += temp_string + ' ';

					}
					else if ((temp_string == "," && bracket_count == 1) || (bracket_count == 0 && temp_string == "}") && temp_string != "{") {


						temp_vector.push_back(temp_element);

						temp_element.clear();

					}
					else if ((temp_string != "," && bracket_count == 1) || (temp_string == "," && bracket_count > 1) && temp_string != "{") {

						temp_element += temp_string;

					}





				}

				*output_set = std::make_pair(temp_set_name, temp_vector);
				set_container = output_set;

				ss.clear();
				temp_vector.clear();
			}



	}

	void get_set_container_from_char(const char* char_array) {

		get_set_container_from_string(std::string(char_array));

	}

	void print_set_container() {


			std::cout << set_container->first << " = { ";

			for (int i = 0; i < set_container->second.size(); i++)
				if (i == set_container->second.size() - 1)
					std::cout << set_container->second[i] << ' ';
				else
					std::cout << set_container->second[i] << " , ";


			std::cout << " }\n";
		
	}

};







int main() {

	multiset container;

	container.load_set_container("input.txt");
	container.print_set_container();

	container.get_set_container_from_char("C = { 5 , A , {} , 5 , 5 , 5 , { LK , { { 1 , 2 } , A , { 3 , 4 } } } , 8 }");
	container.print_set_container();

	container.get_set_container_from_string("C = { 5 , A , {} , 5 , 5 , 5 , { LK , { { 1 , 2 } , A , { 3 , 4 } } } }");
	container.print_set_container();

	container.load_set_container("test.txt");
	container.print_set_container();

}

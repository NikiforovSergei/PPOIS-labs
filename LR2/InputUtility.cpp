#include "InputUtility.h"

std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<std::vector<int>>> parseInfo(std::string path)
{
	std::ifstream fin(path);
	std::stringstream ss;
	std::string line;
	std::vector<std::vector<int>> graph;
	std::vector<std::vector<int>> rsLocation;
	std::vector<std::vector<int>> trainInfo;
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::getline(fin, line);
			if (line == "Graph:")
				while (true)
				{		
					std::vector<int> temp;
					std::getline(fin, line);
					if (line == "RSLocation:")
						break;
					ss << line;
					while (ss >> line)
					{
						if (line == "->")
							continue;
						if (line[0] == '(')
						{
							std::string tempo;
							for (int i = 1; i < line.size(); ++i)
								if (line[i] != ')')
									tempo += line[i];
							temp.push_back(std::stoi(tempo));
						}
						else
							temp.push_back(std::stoi(line));
					}
					graph.push_back(temp);
					ss.clear();
				}
			if (line == "RSLocation:")
				while (true)
				{
					std::vector<int> temp;
					std::getline(fin, line);
					if (line == "Trains:")
						break;
					ss << line;
					while (ss >> line)
					{
						if (line == "GRS")
						{
							temp.push_back(-1);
							continue;
						}
						if (line == "PRS")
						{
							temp.push_back(-2);
							continue;
						}
						if (line == "MRS")
						{
							temp.push_back(-3);
							continue;
						}
						if (line == "->")
							continue;
						if (line[0] == '(')
						{
							std::string tempo;
							for (int i = 1; i < line.size(); ++i)
								if (line[i] != ')')
									tempo += line[i];
							temp.push_back(std::stoi(tempo));
						}
						else
							temp.push_back(std::stoi(line));
					}
					rsLocation.push_back(temp);
					ss.clear();
				}
			if(line == "Trains:")
				while (true)
				{
					std::vector<int> temp;
					std::getline(fin, line);
					if (line.empty())
						break;
					ss << line;
					while (ss >> line)
					{
						if (line == "Loc")
						{
							temp.push_back(-1);
							continue;
						}
						if (line == "->")
							continue;
						if (line == "GTÑ")
						{
							temp.push_back(-2);
							continue;
						}
						if (line == "PTÑ")
						{
							temp.push_back(-3);
							continue;
						}
						if (line == "Route:")
						{
							temp.push_back(-4);
							continue;
						}
						if (line == ";")
						{
							continue;
						}
						if (line[0] == '(')
						{
							std::string tempo;
							for (int i = 1; i < line.size(); ++i)
								if (line[i] != ')')
									tempo += line[i];
							temp.push_back(std::stoi(tempo));
						}
						else
							temp.push_back(std::stoi(line)); 
					}
					trainInfo.push_back(temp);
					ss.clear();
				}
		}
	}
	return std::make_tuple(graph,rsLocation,trainInfo);
}
#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>


std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, std::vector<std::vector<int>>> parseInfo(std::string path);

#include"Header.h"

vector<Set> Insert(vector<Set> data, vector<Set> new_data) {
	vector<Set> result;

	for (auto it : data)
		result.push_back(it);

	for (int i = 0; i < new_data.size(); i++) {
		bool is_alright_here = false;
		for (int j = 0; j < result.size(); j++) {
			if (new_data[i].get_indtf() == result[j].get_indtf()) {
				is_alright_here = true; break;
			}
		}
		if (!is_alright_here) result.push_back(new_data[i]);
	}
	return result;
}
#include"Header.h"

Operations::Operations(){
	
}

Set Operations::set_boolean(Set set) {
	vector<string> buf_ch_vec = set.get_elements();
	vector<Set> buf_set_vec = set.get_subsets();
	Set buf_set;

	for (size_t i = 1; i < buf_ch_vec.size(); i++) {
		for (size_t j = 0; j < buf_ch_vec.size(); j++) {
			Set buf;
			for (size_t k = j; k < buf_ch_vec.size(); k++) {
				if (buf.get_elements().size() == i)
					break;
				else
					buf.Add_element(buf_ch_vec[k]);
			}
			buf.build_new_indtf();
			buf_set.Add_subset(buf);
		}
	}
	buf_set.Add_subset(set);
		Set empty_set;
		empty_set.set_indtf("{}");
		buf_set.Add_subset(empty_set);
	buf_set.build_new_indtf();
	return buf_set;
}



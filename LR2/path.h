#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<set>
#include"element.h"
#include"document.h"

using namespace std;

namespace xml {
	class Searcher {
		string path;
		vector<Element*> request_result;
		vector<string> requests;
		Document* document;
		unordered_map<string, vector<Element*>> searching_table;


		string create_path(const string& path);
		vector<Element*> attribute_request(const string& current, bool logical_not);
		vector<Element*> text_request(const string& current, bool logical_not);
		vector<Element*> check_txt(const string& text, bool logical_not);
		pair<string, string> get_requests_strings(const string& op, const string& current);
		vector<Element*> text_ot_attr(const string& str);
		
		vector<Element*> recurion_check(const string& current, const string& logical_op);

		vector<Element*> process_logicalOP(const string& current);

		pair<string, string> getAttributeValue(string request_result);

		void fill_request();

		vector<Element*> check_attr(const string& name,const string& value, bool logical_not);

		void make_table(Element* root);

	public:
		Searcher(Document* doc, string path);
		vector<Element*> get_result();
		void parse();
	};
}

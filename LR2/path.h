#pragma once
#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<set>
#include"element.h"
#include"document.h"

namespace xml {
	class Searcher {
		std::string path;
		std::vector<Element*> request_result;
		std::vector<std::string> requests;
		Document* document;
		std::unordered_map<std::string, std::vector<Element*>> searching_table;


		std::string create_path(const std::string& path);
		std::vector<Element*> attribute_request(const std::string& current, bool logical_not);
		std::vector<Element*> text_request(const std::string& current, bool logical_not);
		std::vector<Element*> check_txt(const std::string& text, bool logical_not);
		std::pair<std::string, std::string> get_requests_strings(const std::string& op, const std::string& current);
		std::vector<Element*> text_ot_attr(const std::string& str);

		std::vector<Element*> recurion_check(const std::string& current, const std::string& logical_op);

		std::vector<Element*> process_logicalOP(const std::string& current);

		std::pair<std::string, std::string> getAttributeValue(std::string request_result);

		void fill_request();

		std::vector<Element*> check_attr(const std::string& name, const std::string& value, bool logical_not);

		void make_table(Element* root);

	public:
		Searcher(Document* doc, std::string path);
		std::vector<Element*> get_result();
		void parse();
	};
}
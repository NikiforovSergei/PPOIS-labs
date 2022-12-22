#include"path.h"

using namespace xml;

Searcher::Searcher(Document* doc, std::string path) {
	this->document = doc;
	this->path = path;
}

std::vector<Element*> Searcher::get_result() {
	return request_result;
}


void Searcher::parse() {
	if (path == "/") { request_result.push_back(document->root); return; }
	make_table(document->root);

	std::string current = create_path(path);
	if (current.find("[") != std::string::npos) {
		size_t pos = current.find("[");
		requests.push_back(current.substr(0, pos));
		current = current.substr(pos, path.size());

	}
	else { requests.push_back(current); fill_request(); return; }

	if (current.find("||") != std::string::npos || current.find("&&") != std::string::npos)
		request_result = process_logicalOP(current);
	else {
		if (current.find("attr") != std::string::npos)
			request_result = attribute_request(current, current.find("!") != std::string::npos);
		else
			request_result = text_request(current, current.find("!") != std::string::npos);
	}
}

std::string Searcher::create_path(const std::string& path) {
	std::string current = "";
	for (int i = 1; i < path.size(); ++i) {
		current += path[i];
	}
	while (current.find("/") != std::string::npos) {
		size_t pos = current.find("/");
		requests.push_back(current.substr(0, pos));
		current = current.substr(pos + 1, path.size());
	}
	return current;
}
std::vector<Element*> Searcher::attribute_request(const std::string& current, bool logical_not) {

	std::string attr_name = getAttributeValue(current).second;
	std::string attr_value = getAttributeValue(current).first;
	return check_attr(attr_name, attr_value, logical_not);
}
std::vector<Element*> Searcher::text_request(const std::string& current, bool logical_not) {
	size_t pos1 = current.find("(") + 2;
	size_t pos2 = current.find(")");
	std::string text = current.substr(pos1, pos2 - pos1 - 1);
	return check_txt(text, logical_not);
}

std::vector<Element*> Searcher::check_txt(const std::string& text, bool logical_not) {
	std::vector<Element*> req;
	for (auto node : searching_table[requests.back()]) {
		std::string node_text = node->getText();
		if (node_text.find('\n') != std::string::npos) node_text = node_text.substr(0, node_text.find('\n'));
		if (!logical_not) {

			if (node_text == text) {
				req.push_back(node);
			}
		}
		else {
			if (node_text != text) {
				req.push_back(node);
			}
		}
	}
	return req;
}
std::pair<std::string, std::string> Searcher::get_requests_strings(const std::string& op, const std::string& current) {
	std::string first_request, second_request;
	size_t pos = current.find(op);
	first_request = current.substr(0, pos);
	second_request = current.substr(pos + 2, current.size());
	return{ first_request,second_request };
}
std::vector<Element*> Searcher::text_ot_attr(const std::string& str) {
	if (str.find("||") != std::string::npos || str.find("&&") != std::string::npos) {
		std::vector<Element*> a;
		return a;
	}
	else if (str.find("attr") != std::string::npos)
		return attribute_request(str, str.find("!") != std::string::npos);
	else
		return text_request(str, str.find("!") != std::string::npos);

}
std::vector<Element*> Searcher::recurion_check(const std::string& current, const std::string& logical_op) {
	std::vector<Element*> left_v, right_v;
	std::string left = get_requests_strings(logical_op, current).first;
	std::string right = get_requests_strings(logical_op, current).second;
	left_v = process_logicalOP(left);
	right_v = process_logicalOP(right);
	left_v = text_ot_attr(left).empty() ? left_v : text_ot_attr(left);
	right_v = text_ot_attr(right).empty() ? right_v : text_ot_attr(right);
	std::vector<Element*> result;
	if (logical_op == "&&") {
		for (auto i : right_v.size() > left_v.size() ? left_v : right_v) {
			bool flag = false;
			for (auto j : right_v.size() > left_v.size() ? right_v : left_v) {
				if (i == j) flag = true;
			}
			if (flag) result.push_back(i);
		}
		return result;
	}
	else if (logical_op == "||") {
		result = right_v.size() > left_v.size() ? right_v : left_v;
		for (auto i : right_v.size() > left_v.size() ? left_v : right_v) {
			bool flag = false;
			for (auto j : right_v.size() > left_v.size() ? right_v : left_v) {
				if (i == j) flag = true;
			}
			if (!flag) result.push_back(i);
		}
		return result;
	}
}

std::vector<Element*> Searcher::process_logicalOP(const std::string& current) {
	std::vector<Element*> result;
	if (current.find("||") != std::string::npos) {
		result = recurion_check(current, "||");
	}
	else if (current.find("&&") != std::string::npos) {
		result = recurion_check(current, "&&");
	}
	return result;

}

std::pair<std::string, std::string> Searcher::getAttributeValue(std::string request_result) {
	size_t pos = request_result.find("attr");
	request_result = request_result.substr(pos + 6);

	pos = request_result.find(',');
	std::string attr_name = request_result.substr(0, pos - 1);

	request_result = request_result.substr(pos + 1, path.size());
	pos = request_result.find(')');
	std::string attr_value = request_result.substr(2, pos - 3);
	return { attr_value,attr_name };
}

void Searcher::fill_request() {
	for (auto node : searching_table[requests.back()]) { request_result.push_back(node); }
}

std::vector<Element*> Searcher::check_attr(const std::string& name, const std::string& value, bool logical_not) {
	std::vector<Element*> req;
	for (auto node : searching_table[requests.back()]) {
		for (auto attribute : node->getAttributes()) {
			if (!logical_not) {
				if (attribute.getName() == name && attribute.getValue() == value) {
					req.push_back(node);
				}
			}
			else {
				if (attribute.getName() != name || attribute.getValue() != value) {
					req.push_back(node);
				}
			}

		}
	}
	return req;

}


void Searcher::make_table(Element* root) {
	if (root->children.size() > 0)
		for (auto child : root->children)
			make_table(child);
	searching_table[root->value].push_back(root);
}
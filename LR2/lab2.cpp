#include <iostream>
#include"parser.h"
#include"path.h"
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
	using namespace xml;
	setlocale(LC_ALL, "Rus");
	std::string a;
		std::cout << "1:/" << std::endl << "2:/bookstore" << std::endl << "3:/bookstore/book" << std::endl << "4:/bookstore/book/title[attr(“lang”, “en”)]" << std::endl << "5:/bookstore/book/title[attr(“lang”, “en”) || text(“Learn XML”)]" << std::endl;
		std::cout << std::endl << "ââåäèòå ÷èñëî" << std::endl;
		int kod;
		std::cin >> kod;
		switch (kod)
		{
		case 1:
			a = "/";
			break;
		case 2:
			a = "/bookstore";
			break;
		case 3:
			a = "/bookstore/book";
			break;
		case 4:
			a = "/bookstore/book/title[attr(“lang”, “en”)]";
			break;
		case 5:
			a = "/bookstore/book/title[attr(“lang”, “en”) || text(“Learn XML”)]";
			break;
		}
		std::ifstream in;
		std::string file_name = "XML.xml";
		in.open(file_name);
		std::ofstream txtFile;
		Parser reader(&in);
		reader.process();
		std::string search_request = a;
		Searcher p(reader.document, search_request);
		p.parse();
		int i = 1;
		auto requests = p.get_result();
		if (requests.empty()) std::cout << "Nothing founded";
		else
			for (auto node : requests) {
				std::cout << i++ << " element:\nName: " << node->value << "\n" << "Text: " << node->getText()
					<< "\nAttributes: ";
				for (auto attribute : node->getAttributes()) {
					std::cout << attribute.getName() << " = " << attribute.getValue();
				}
				std::cout << "\n\n";
			}

		return 0;
}
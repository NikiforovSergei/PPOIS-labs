#include<iostream>
#include"parser.h"
#include"path.h"

using namespace xml;
using namespace std;

int main()
{
	ifstream in;
	string file_name = "XML.xml";
	in.open(file_name);
	Parser reader(&in);
	reader.process();
	string search_request;
	cin >> search_request;
	Searcher p(reader.document, search_request);
	p.parse();
	int i = 1;
	auto requests = p.get_result();
	if (requests.empty())
	{
		cout << "Nothing founded";
	}
	else
	{ 
		for (auto node : requests)
		{
			cout << i << " element:\nName: " << node->value << "\n" << "Text: " << node->getText();
			i++;
			for (auto attribute : node->getAttributes())
			{
				cout << "\nAttributes: " << attribute.getName() << " = " << attribute.getValue();
			}
			cout << "\n";
		}
	}
	return 0;
}
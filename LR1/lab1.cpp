/// \file lab1.cpp
/// \brief файл, содержащий реализацию классов и функцию main
/// 
/// \autor Koltovich Denis
/// \date 22.09.2022
#include"lab1.h"
#include"test.h"
using namespace std;
void Alphabet::setPattern(string& pattern) { this->pattern = pattern; }

string Alphabet::getPattern() { return pattern; }

bool Alphabet::is_valid(const string& word) {
    for (auto ch : word)
        if (pattern.find(ch) == string::npos) return false;
    return true;
}

bool Alphabet::is_valid(const string& left_part, const string& right_part) {
    string word = left_part + right_part;
    for (auto ch : word)
        if (pattern.find(ch) == string::npos) return false;
    return true;
}

void Tape::setAlphabet(string& pattern) { alphabet.setPattern(pattern); }

void Tape::setRules(vector<pair<string, string>>& rules) {
	for (auto i : rules) {
		if (!alphabet.is_valid(i.first, i.second)) return;
	}
	this->rules.clear();
	this->rules = rules;
}

void Tape::setWord(string& word) {
	if (!alphabet.is_valid(word)) return;
	this->word = word;
}

vector<pair<string, string>>& Tape::getRules() { return rules; }

void Tape::setAction(pair<string, string> action) { this->action = action; }

string Tape::getWord() { return word; }

void Tape::delete_rule(int index) {
	rules.erase(rules.begin() + index);
}

void Tape::deleteRules() { rules.clear(); }

void Tape::changeRule(int index, string& left_part, string& right_part) {
	if (!alphabet.is_valid(left_part, right_part)) {
		cout << "Invalid rules\n";
		return;
	}
	rules.push_back({ left_part,right_part });
	swap(rules[index], rules.back());
	rules.pop_back();
}
void Tape::addRule(string& left_part, string& right_part) {
	if (!alphabet.is_valid(left_part, right_part)) {
		cout << "Invalid rules\n";
		return;
	}
	this->rules.push_back({ left_part, right_part });
}
void Tape::getInfo(string& word) {
	cout << "word:\t" << word << "\n" << "Executed rule:\t" << action.first << " -> " << action.second << "\n_________________________\n";
}
void Tape::Read() {
	cout << "\nEnter the alphabet:\n_________________________\n";
	cin >> pattern;
	alphabet.setPattern(pattern);
	do {
		cout << "\nEnter the word:\n_________________________\n";
		cin >> word;
	} while (alphabet.is_valid(word));

	cout << "\n_________________________\nEnter the num of rules:\n_________________________\n";
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cout << "\nEnter " << i + 1 << " rule:\n_________________________\n";
		string a, b;
		cin >> a >> b;
		if (!alphabet.is_valid(a, b)) {
			cout << "Invalid rules! Try again\n";
			cin >> a >> b;
		}
		rules.push_back({ a,b });
	}
}
void Tape::operator>>(const string& filename) {
	ifstream in;
	in.open(filename);
	if (!in.is_open()) {
		std::cout << "Open Error!" << "\n";
	}
	else {
		in >> pattern;
		alphabet.setPattern(pattern);
		string line;
		in >> word;
		if (!alphabet.is_valid(word)) {
			cout << "Invalid word!";
			exit(0);
		}
		while (getline(in, line))
		{
			for (int i = 0; i < line.size(); ++i) {
				if (line[i] == '-' && line[i + 1] == '>') {
					string a, b;
					a = line.substr(0, i);
					b = line.substr(i + 2, line.size() - i - 1);
					if (!alphabet.is_valid(a, b)) {
						cout << "Invelid rule(s)!";
						exit(0);
					}
					rules.push_back({ a,b });
					break;
				}
			}
		}
	}
}
void Tape::Write() {
	cout << "\n_________________________\nAlphabet:\t" << alphabet.getPattern() << "\n";
	cout << "Word:\t" << word << "\nRules:\n";
	for (int i = 0; i < rules.size(); ++i) {
		cout << "\t\t" << rules[i].first << " -> " << rules[i].second << "\n";
	}
	cout << "\n_________________________\n";
}

Interpretator::Interpretator(string & word) {
	this->word = word;
}

string Interpretator::getWord() { return word; }
void Interpretator::setWord(string& word) { this->word = word; }

void Interpretator::rule_executing(string& a, string& b) {
	size_t position;
	if (a == "") word.insert(0, b);
	else if (b == "") {
		position = word.find(a);
		word.erase(position, a.size());
	}
	else {
		position = word.find(a);
		word.erase(position, a.size());
		word.insert(position, b);
	}
	tape.setWord(word);
	if (this->log) { tape.setAction({ a,b }); tape.getInfo(word); }
}
void Interpretator::changeLog() {
	if (!log) log = true;
	else log = false;
}

void Interpretator::execute(vector<pair<string, string>>& rules) {
	for (size_t i = 0; i < rules.size(); ++i) {
		if (flag) break;
		if (i == rules.size() - 1 && word.find(rules[i].first) == std::string::npos) flag = true;
		else if (word.find(rules[i].first) != std::string::npos) {
			rule_executing(rules[i].first, rules[i].second);
			execute(rules);
		}
	}
	flag = false;
}



int main(int argc, char* argv[])
{
    string word;
    string alphabet;
    Tape tape;
    string filename = "file.txt";
    tape >> filename;
    word = tape.getWord();
    Interpretator inter(word);
    if (argc > 1) {
        string log(argv[1]);
        if (log == "-log") {
            inter.changeLog();
			tape.Write();
            //std::cout << "word:\t" << tape.getWord() << "\n_________________________\n";
            inter.execute(tape.getRules());
            cout << inter.getWord();
			return 0;
        }
		else if (log == "test") {
			Test test;
			test.testmain();
			return 0;
		}
    }
	inter.execute(tape.getRules());
	cout << inter.getWord();
}
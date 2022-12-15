#include "Lexeme.h"
Var vars;

Error::Error(int NUMBER_ERROR) 
{
	this->NUMBER_ERROR = NUMBER_ERROR;
	cout << "Ошибка: " << NUMBER_ERROR << " ";
	switch (NUMBER_ERROR)
	{
	case 100: cout << "Введите выражение" << endl; break;
	case 101: cout << "Неправильный символ" << endl; break;
	case 102: cout << "Неправильный символt. Пропущено число, параметр, значение" << endl; break;
	case 103: cout << "Неправильный символ. Пропущены параметры" << endl; break;
	}
}

vector<Lexeme> LexemeBuffer::getLexemes()
{
	return lexemes;
}
void LexemeBuffer::setLexeme(Lexeme lexeme)
{
	lexemes.push_back(lexeme);
}
void LexemeBuffer::Clear()
{
	lexemes.clear();
}
void LexemeAnalyzer::get_token(LexemeBuffer& lexemes)
{
	while (true)
	{
		char ch = 0;
		do
		{
			if (!cin.get(ch)) return;
		} while (ch != '\n' && isspace(ch));
		switch (ch)
		{
		case 0:
		case '}':
		case '{':
		case '\\':
		case '[':
		case ']':
		case ':':
		case ';': {Error error(101); cin.ignore(cin.rdbuf()->in_avail()); }
		case '\n':return;
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
		case '=':
		{
			string value = "";
			value.push_back(static_cast<char>(ch));
			Lexeme lexeme(value, TOKEN_TYPE(ch));
			lexemes.setLexeme(lexeme);
		} break;
		case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': case '.':
		{
			cin.putback(ch);
			double number;
			cin >> number;
			Lexeme lexeme(number, TOKEN_TYPE(NUMBER));
			lexemes.setLexeme(lexeme);
		} break;
		default:
			if (isalpha(ch))
			{
				string_value = "";
				string_value.push_back(ch);
				while (cin.get(ch) && isalpha(ch)) string_value.push_back(ch); //читаем все буковки
				cin.putback(ch);
				string_value = getLowerCase(string_value);
				if ((strcmp(string_value.c_str(), "sin") == 0 || strcmp(string_value.c_str(), "cos") == 0 || strcmp(string_value.c_str(), "tan") == 0 || strcmp(string_value.c_str(), "ctg") == 0 || strcmp(string_value.c_str(), "asin") == 0 || strcmp(string_value.c_str(), "acos") == 0 || strcmp(string_value.c_str(), "atan") == 0 || strcmp(string_value.c_str(), "actg") == 0 || strcmp(string_value.c_str(), "pow") == 0 || strcmp(string_value.c_str(), "sqrt") == 0 || strcmp(string_value.c_str(), "cbrt") == 0))
				{
					TOKEN_TYPE string_token = getToken(string_value);
					cin.get(ch);
					int k = 0;
					do
					{
						if (ch == ')')k--;
						else if (ch == '(') k++;
						string_value.push_back(ch);
					} while (cin.get(ch) && k != 0);
					cin.putback(ch);
					Lexeme lexeme(string_value, string_token);
					lexemes.setLexeme(lexeme);
				}
				else {
					Lexeme lexeme(string_value, TOKEN_TYPE(NAME)); lexemes.setLexeme(lexeme);
				}
			}
			else Error error(100); break;
		}
	}
}

Lexeme::Lexeme()
{

}

Lexeme::Lexeme(double value, TOKEN_TYPE type)
{
	this->number_value = value;
	this->token = type;
}

Lexeme::Lexeme(string value, TOKEN_TYPE type)
{
	this->string_value = value;
	this->token = type;
}

void Lexeme::Print()
{
	if (string_value.size() == 0)
	{
		cout << number_value;
	}
	else cout << string_value;
	cout << " " << getTokenName(token) << endl;
}

Lexeme::Lexeme(const Lexeme& other)
{
	this->number_value = other.number_value;
	this->string_value = other.string_value;
	this->token = other.token;
}


void Lexeme::setValue(double value)
{
	number_value = value;
}

void Lexeme::setSValue(string value)
{
	string_value = value;
}


TOKEN_TYPE Lexeme::getType()
{
	return token;
}

string Lexeme::getVar()
{
	return string_value;
}

string getTokenName(TOKEN_TYPE token)
{
		switch (token)
		{
		case 0: return "NAME";
		case 1: return "NUMBER";
		case 3: return "SIN";
		case 4: return "COS";
		case 5: return "TAN";
		case 6: return "CTG";
		case 7: return "ASIN";
		case 8: return "ACOS";
		case 9: return "ATAN";
		case 10: return "ACTG";
		case 11: return "POW";
		case 12: return "SQRT";
		case 13: return "CBRT";
		case 40: return "LP";
		case 41: return "RP";
		case 42: return "MUL";
		case 43: return "PLUS";
		case 45: return "MINUS";
		case 47: return "DIV";
		case 61: return "ASSIGN";
		}
		return "?";
}
string getLowerCase(string& string_value)
{
	transform(string_value.begin(), string_value.end(), string_value.begin(), ::tolower);
	return string_value;
}

vector<double> getParametr(bool& param,int k,string string_value, Var& vars)
{
	vector<double> parametrs;
	string value;
	int isnegative = 1;
	for (int i = k; i < string_value.length(); i++)
	{
		if (string_value[i] == '-')
		{
			isnegative = -1;
		}
		if (isdigit(string_value[i]) || string_value[i] == '.')
		{
			param = true;
			value += string_value[i];
		}
		else if (isalpha(string_value[i]))
		{
			param = true;
			value += string_value[i];
		}
		else if (string_value[i] == ',')
		{
			if (isalpha(value[0]))
			{
				parametrs.push_back(isnegative*vars.getValue(value));
			}else parametrs.push_back(isnegative*stof(value));
			value = "";
			isnegative = 1;
		}
	}
	if (isalpha(value[0]))
	{
		parametrs.push_back(isnegative*vars.getValue(value));
	}
	else parametrs.push_back(isnegative*stof(value));
	return parametrs;
}

TOKEN_TYPE getToken(string& string_value)
{
	if (!strcmp(string_value.c_str(), "sin"))
	{
		return SIN;
	}
	else if(!strcmp(string_value.c_str(), "cos"))
	{
		return COS;
	}
	else if (!strcmp(string_value.c_str(), "tan"))
	{
		return TAN;
	}
	else if (!strcmp(string_value.c_str(), "ctg"))
	{
		return CTG;
	}
	else if (!strcmp(string_value.c_str(), "asin"))
	{
		return ASIN;
	}
	else if (!strcmp(string_value.c_str(), "acos"))
	{
		return ACOS;
	}
	else if (!strcmp(string_value.c_str(), "atan"))
	{
		return ATAN;
	}
	else if (!strcmp(string_value.c_str(), "actg"))
	{
		return ACTG;
	}
	else if (!strcmp(string_value.c_str(), "pow"))
	{
		return POW;
	}
	else if (!strcmp(string_value.c_str(), "sqrt"))
	{
		return SQRT;
	}
	else if (!strcmp(string_value.c_str(), "cbrt"))
	{
		return CBRT;
	}
	return END_BEGIN;
}
bool isfoo(TOKEN_TYPE token)
{
	for (int i = 3; i < 14; i++)
	{
		if (token == i) return true;
	}
	return false;
}

Var::Var()
{

}

Var::Var(string varName, double varValue)
{
	table.emplace(varName, varValue);
}

void Var::setValue(string varName, double varValue)
{
	if (table.count(varName)>=1)
	{
		table.erase(varName);
	}
	table.emplace(varName, varValue);
}

double Var::getValue(string varName)
{
	return table[varName];
}

bool isop(Lexeme& lexeme)
{
	switch (lexeme.getType())
	{
	case 42: return true;
	case 43: return true;
	case 45: return true;
	case 47: return true;
	case 61: return true;
	}
	return false;
}

void findMinus(vector<Lexeme>& lexemes)
{
		if ((lexemes[0].getType() == 45) && (lexemes[1].getType() == NUMBER || isfoo(lexemes[1].getType()) || lexemes[1].getType() == NAME)) // 45 - minus
		{
			if (lexemes[1].getType() == NUMBER)
			{
				lexemes[1].setValue(-lexemes[1].getDValue(vars));
			}
			else if (isfoo(lexemes[1].getType())) lexemes[1].setSValue("-" + lexemes[1].getVar());
			else if (lexemes[1].getType() == NAME) lexemes[1].setSValue("-" + lexemes[1].getVar());
			lexemes.erase(lexemes.begin());
		}
		for (int i = 0; i < lexemes.size()-1; i++)
		{
			if ((isop(lexemes[i])) && (lexemes[i+1].getType()==45)) //45 - minus
			{
				lexemes.erase(lexemes.begin() + i + 1);
				if (lexemes[i + 1].getType() == NUMBER)
				{
					lexemes[i + 1].setValue(-lexemes[i + 1].getDValue(vars));
				} else if (isfoo(lexemes[i + 1].getType())) lexemes[i + 1].setSValue("-" + lexemes[i + 1].getVar());
				else if (lexemes[i+1].getType() == NAME) lexemes[i+1].setSValue("-" + lexemes[i+1].getVar());
			}
			else if ((lexemes[i].getType() == LP) && (lexemes[i+1].getType()==45))
			{
				lexemes.erase(lexemes.begin() + i + 1);
				if (lexemes[i + 1].getType() == NUMBER)
				{
					lexemes[i + 1].setValue(-lexemes[i + 1].getDValue(vars));
				}
				else if (isfoo(lexemes[i + 1].getType())) lexemes[i + 1].setSValue("-" + lexemes[i + 1].getVar());
				else if (lexemes[i+1].getType() == NAME) lexemes[i+1].setSValue("-" + lexemes[i+1].getVar());
			}
		}
}
double Lexeme::getDValue(Var& vars)
{
	if (isfoo(token))
	{
		int n = 0;
		int k = 1;
		if (string_value[0] == '-') k = -1;
		switch (token)
		{
		case ASIN:
		case ACOS:
		case ATAN:
		case ACTG:
		case SQRT:
		case CBRT: n = 4; break;
		default:n = 3;
			break;
		}
		bool param = false;
		vector<double> parametr = getParametr(param, n, string_value, vars);
		if (!param)
		{
			Error error(103);
		}
		else
		{
			switch (token)
			{
			case 3: return sin(parametr[0]) * k;
			case 4: return cos(parametr[0]) * k;
			case 5: return tan(parametr[0]) * k;
			case 6: return 1 / tan(parametr[0]) * k;
			case 7: return asin(parametr[0]) * k;
			case 8: return acos(parametr[0]) * k;
			case 9: return atan(parametr[0]) * k;
			case 10: return PI_2 - atan(parametr[0]) * k;
			case 11: return pow(parametr[0], parametr[1]) * k;
			case 12: return sqrt(parametr[0]) * k;
			case 13: return cbrt(parametr[0]) * k;
			}
		}
		return 0;
	}
	return number_value;
}
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int l;

struct node{
	string eng;
	string rus;
	node* left;
	node* right;
};

class tree{
	node* leaf = nullptr;
	int count = 0;
	void vvod(string a, string b, node* root) {
			if (a > root->eng && root->right) {
				vvod(a, b, root->right);
			}
			else if (a > root->eng && !root->right) {
				root->right = new node;
				root->right->eng = a;
				root->right->rus = b;
				root->right->left = NULL;
				root->right->right = NULL;
				count++;
			}
			else if (a < root->eng && root->left) {
				vvod(a, b, root->left);
			}
			else if (a < root->eng && !root->left) {
				root->left = new node;
				root->left->eng = a;
				root->left->rus = b;
				root->left->left = NULL;
				root->left->right = NULL;
				count++;
			}	
	}
	void vivod(node* root) {
		if (root == NULL) {
			cout << "������� �������� �������� � �������" << endl;
		}
		else {
			cout << root->eng << " - " << root->rus << endl;
			if (root->left != NULL) {
				vivod(root->left);
			}
			if (root->right != NULL) {
				vivod(root->right);
			}
		}
	}
	void poisk(string a, node* root) {
		if (root != NULL) {
			if (a == root->eng) {
				cout<< root->eng << " - "<<root->rus<<endl;
			}
			else if (a < root->eng) {
				poisk(a, root->left);
			}
			else {
				poisk(a, root->right);
			}
		}
		else {
			cout << "����� �� �������!" << endl;
		}
	}
	void udalit(string a, node* root) {
		node* del, * prev_del, * R, * prev_R;
		del = root;
		prev_del = nullptr;
		while (del != nullptr && del->eng != a)
		{
			prev_del = del;
			if (del->eng > a) del = del->left;
			else del = del->right;
		}
		if (del == nullptr)
		{
			cout << "����� �� �������!" << endl;
			return;
		}
		if (del->right == nullptr) R = del->left;
		else
			if (del->left == nullptr) R = del->right;
			else
			{
				prev_R = del;
				R = del->left;
				while (R->right != nullptr)
				{
					prev_R = R;
					R = R->right;
				}
				if (prev_R == del) R->right = del->right;
				else {
					R->right = del->right;
					prev_R->right = R->left;
					R->left = del->left;
				}
			}
		if (del == root) root = R;
		else
			if (del->eng < prev_del->eng)
				prev_del->left = R;
			else prev_del->right = R;
		delete del;
		count--;
	}
	void zamena(string a, string b, node* root) {
		if (root != NULL)
		{
			if (a == root->eng) {
				root->rus = b;
			}
			if (a < root->eng) {
				zamena(a,b, root->left);
			}
			else {
				zamena(a, b, root->right);
			}

		}
		else {
			cout << "����� �� �������!" << endl;

		}
	}
	void chislo(node * root){
		cout <<"���������� ����: " << count << endl;
	}

	void deletetree(node * root) {
		if (root != NULL) {
			deletetree(root->right);
			deletetree(root->left);
			delete root;
			count = 0;
		}
	}
	
public:
	string x, y;
	void insert(string a, string b) {
		if(leaf!=NULL){
			vvod(a, b, leaf);
		}
		else {
			leaf = new node;
			leaf->eng = a;
			leaf->rus = b;
			leaf->left = NULL;
			leaf->right = NULL;
			count++;
		}
	}
	
	tree& operator +=(const tree& other) {
		insert(other.x, other.y);
		return *this;
	}

	void print() {
		vivod(leaf);
	}


	void search(string a) {
		poisk(a, leaf);
	}
	
	tree& operator [](const tree& other) {
		if (l == 1) {
			search(other.x);
		}
		if(l == 2){
			reinsert(other.x, other.y);
		}
		return *this;
	}

	void reinsert(string a, string b) {
		zamena(a, b, leaf);
	}


	void destroy(string a) {
		udalit(a, leaf);
	}

	tree& operator -=(const tree& other) {
		destroy(other.x);
		return *this;
	}

	void number(){
		chislo(leaf);
	}

	void file() {
		deletetree(leaf);
		leaf = nullptr;
		string a, b;
		ifstream fin("laba.txt");
		while (!fin.eof()) {
			fin >> a;
			fin >> b;
			if (leaf != NULL) {
				vvod(a, b, leaf);
			}
			else {
				leaf = new node;
				leaf->eng = a;
				leaf->rus = b;
				leaf->left = NULL;
				leaf->right = NULL;
				count++;
			}
		}
	}
};




int main() 
{
	setlocale(LC_ALL, "ru");
	tree dict;
	tree bor;
	int m;
	string a, b;
	ifstream fin("Laba.txt");
	int n;
	bool choice = true;
	while (choice) {

		cout << "-----------------------------------------------------------" << endl
			<< "�����-������� �������" << endl << "�������� ��������:" << endl
			<< "1.���������� ����������� ����� � �������� ��� ����" << endl
			<< "2.�������� �������" << endl
			<< "3.�������� ����� �� �������" << endl
			<< "4.����� �������� ����������� �����" << endl
			<< "5.������ �������� ����������� �����" << endl
			<< "6.����������� ���������� ����" << endl
			<< "7.�������� ������� �� �����" << endl
			<< "8.�������� �������" << endl
			<< "0.�����" << endl
			<< "-----------------------------------------------------------" << endl;
		cin >> n;
		switch (n) {
		case 1:
			cout << "������� ���������� ����:" << endl;
			cin >> m;
			for (int i = 0; i < m; i++) {
				cout << "������� ���������� �����:" << endl;
				cin >>dict.x;
				cout << "������� ������� ����� �����:" << endl;
				cin >> dict.y;
				dict += dict;
			}
			break;

		case 2:
			dict.print();
			break;
		case 3:
			cout << "������� ����� ������� ������ �������:" << endl;
			cin >> dict.x;
			dict -= dict;
			break;
		case 4:
			l = 1;
			cout << "������� ����� ������� ������ �����:" << endl;
			cin >> dict.x;
			dict = dict [dict];
			break;
		case 5:
			l = 2;
			cout << "������� ����� ��� �������� ������ �������� �������:" << endl;
			cin >> dict.x;
			cout << "������� ����� �������:" << endl;
			cin >> dict.y;
			dict = dict[dict];
			break;
		case 6:
			dict.number();
			break;
		case 7:
			dict.file();
			break;
		case 8:
			system("cls");
			break;
		case 0:
			choice = false;
			break;
		default:
			cout << "������� ����� �� ������� ������:" << endl;
			break;
		}
	}
}
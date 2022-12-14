#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int l;

struct node {
	string eng;
	string rus;
	node* left;
	node* right;
};

class tree {

private:
	node* leaf = nullptr;
	int count = 0;
	void input(string a, string b, node* root) {
		if (a > root->eng && root->right) {
			input(a, b, root->right);
		}
		else if (a > root->eng && !root->right) {
			root->right = new node;
			root->right->eng = a;
			root->right->rus = b;
			root->right->left = NULL;
			root->right->right = NULL;
		}
		else if (a < root->eng && root->left) {
			input(a, b, root->left);
		}
		else if (a < root->eng && !root->left) {
			root->left = new node;
			root->left->eng = a;
			root->left->rus = b;
			root->left->left = NULL;
			root->left->right = NULL;
		}
	}
	void output(node* root) {
		if (root == NULL) {
			cout << "Add elements first" << endl;
		}
		else {
			cout << root->eng << " - " << root->rus << endl;
			if (root->left != NULL) {
				output(root->left);
			}
			if (root->right != NULL) {
				output(root->right);
			}
		}
	}
	void findTo(string a, node* root) {
		if (root != NULL) {
			if (a == root->eng) {
				cout << root->eng << " - " << root->rus << endl;
			}
			else if (a < root->eng) {
				findTo(a, root->left);
			}
			else {
				findTo(a, root->right);
			}
		}
		else {
			cout << "Cannot find the word!" << endl;
		}
	}
	void del(string a, node* root) {
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
			cout << "Cannot find the word!" << endl;
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
	void swap(string a, string b, node* root) {
		if (root != NULL)
		{
			if (a == root->eng) {
				root->rus = b;
			}
			if (a < root->eng) {
				swap(a, b, root->left);
			}
			else {
				swap(a, b, root->right);
			}

		}
	}
	void val(node* root) {
		cout << "Words count: " << count << endl;
	}

	void deletetree(node* root) {
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
		if (leaf != NULL) {
			input(a, b, leaf);
			count++;
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
		output(leaf);
	}


	void search(string a) {
		findTo(a, leaf);
	}

	tree& operator [](const tree& other) {
		if (l == 1) {
			search(other.x);
		}
		if (l == 2) {
			reinsert(other.x, other.y);
		}
		return *this;
	}

	void reinsert(string a, string b) {
		swap(a, b, leaf);
	}


	void destroy(string a) {
		del(a, leaf);
	}

	tree& operator -=(const tree& other) {
		destroy(other.x);
		return *this;
	}

	void number() {
		val(leaf);
	}

	void file() {
		deletetree(leaf);
		leaf = nullptr;
		string a, b;
		ifstream fin("test.txt");
		while (!fin.eof()) {
			fin >> a;
			fin >> b;
			if (leaf != NULL) {
				input(a, b, leaf);
			}
			else {
				leaf = new node;
				leaf->eng = a;
				leaf->rus = b;
				leaf->left = NULL;
				leaf->right = NULL;
			}
			count++;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	tree dict;
	int m;
	string a, b;
	ifstream fin("test.txt");
	int n;
	bool choice = true;

	while (choice) {

			cout<<"Choose the action:" << endl
			<< "1.Add word and translation" << endl
			<< "2.View" << endl
			<< "3.Delete" << endl
			<< "4.Find" << endl
			<< "5.Swap" << endl
			<< "6.Count of words" << endl
			<< "7.From file" << endl
			<< "8.Clear" << endl
			<< "0.Exit" << endl;
		cin >> n;
		switch (n) {
		case 1:
			cout << "Count of words:" << endl;
			cin >> m;
			for (int i = 0; i < m; i++) {
				cout << "Input eng word:" << endl;
				cin >> dict.x;
				cout << "Input translation:" << endl;
				cin >> dict.y;
				dict += dict;
			}
			break;

		case 2:
			dict.print();
			break;
		case 3:
			cout << "Input the word u will delete:" << endl;
			cin >> dict.x;
			dict -= dict;
			break;
		case 4:
			l = 1;
			cout << "Input the word which u want to find:" << endl;
			cin >> dict.x;
			dict = dict[dict];
			break;
		case 5:
			l = 2;
			cout << "Which word will u swap:" << endl;
			cin >> dict.x;
			cout << "New translation:" << endl;
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
			cout << "Reinput:" << endl;
			break;
		}
	}
}
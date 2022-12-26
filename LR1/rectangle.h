#pragma once
//#include <string>
using namespace std;

class Rect {
private:
	int x1_;
	int x2_;
	int y1_;
	int y2_;
public:
	Rect();
	Rect(int, int, int, int);
	~Rect();

	void def(int, int, int, int);

	void SetCoor(int, int, int, int);

	//��������� ��������� ������
	void Show();

	//�����������
	void Move(int, int);

	//��������� �������
	void Change(int, int);

	//���������� ������� �� ������� �� ������ �� ����
	void More(int);

	//���������� ������� �� ������� �� ������ �� ����
	void Less(int);

	//���������� ����������� ��������������, ����������� ��� �������� ��������������
	void Twosmall(Rect, Rect);

	//���������� ����������� ��������������, ����������� ��� �������� ��������������, � �������������
	void Twosmallass(Rect, Rect);

	//���������� ��������������, ����������� ����� ������ (������������) ���� ���������������
	void Twounif(Rect, Rect);

	//���������� ��������������, ����������� ����� ������ (������������) ���� ���������������, � ����������
	void Twounifass(Rect, Rect);

	Rect& operator ++();

	Rect& operator --();

	Rect operator +(const Rect& other);

	Rect operator +=(const Rect& other);

	Rect operator -(const Rect& other);

	Rect operator -=(const Rect& other);

	void operator =(const Rect& other);

};
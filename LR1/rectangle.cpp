#include <iostream>
#include "rectangle.h"
#include <string>
#include <vector>

using namespace std;

Rect::Rect(int x1, int x2, int y1, int y2) {
	SetCoor(x1, x2, y1, y2);
}
Rect::~Rect(){
}
Rect::Rect() {
	this->x1_ = 0;
	this->x2_ = 0;
	this->y1_ = 0;
	this->y2_ = 0;
}

void Rect::def(int x1, int x2, int y1, int y2) {
	this->x1_ = x1;
	this->x2_ = x2;
	this->y1_ = y1;
	this->y2_ = y2;
}

void Rect::SetCoor(int x1, int x2, int y1, int y2) {
	x1_ = x1;
	x2_ = x2;
	y1_ = y1;
	y2_ = y2;
}

void Rect::Show() {
	cout << "< " << x1_ << ", " << y1_ << " >, " << "< " << x1_ << ", " << y2_ << " >, " << "< " << x2_ << ", " << y1_ << " >, " << "< " << x2_ << ", " << y2_ << " >" << endl;
}

void Rect::Move(int ch, int a) {
	if (ch == 1) {
		x1_ = x1_ + a;
		x2_ = x2_ + a;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
	if (ch == 2) {
		y1_ = y1_ + a;
		y2_ = y2_ + a;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
}

void Rect::Change(int ch, int a) {
	if (ch == 1) {
		if (x1_ > x2_)
			x1_ = x1_ + a;
		if (x2_ > x1_)
			x2_ = x2_ + a;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
	if (ch == 2) {
		if (y1_ > y2_)
			y1_ = y1_ + a;
		if (y2_ > y1_)
			y2_ = y2_ + a;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
}

/*void Rect::More(int ch) {
	if (ch == 1) {
		++x1_;
		++x2_;
		++y1_;
		++y2_;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
	if (ch == 2) {
		x1_++;
		x2_++;
		y1_++;
		y2_++;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
}

void Rect::Less(int ch) {
	if (ch == 1) {
		--x1_;
		--x2_;
		--y1_;
		--y2_;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
	if (ch == 2) {
		x1_--;
		x2_--;
		y1_--;
		y2_--;
		Rect newRect(x1_, x2_, y1_, y2_);
		newRect.Show();
	}
}


void Rect::Twosmall(Rect Rect1, Rect Rect2) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	x1 = Rect1.x1_; x2 = Rect1.x2_;
	x3 = Rect2.x1_; x4 = Rect2.x2_;
	y1 = Rect1.y1_;	y2 = Rect1.y2_;
	y3 = Rect2.y1_;	y4 = Rect2.y2_;
	int x, y, x11, x22, y11, y22, x12, x34, x23, y12, y34, y23;
	if (x2 > x1) x12 = x2 - x1; else x12 = x1 - x2;
	if (x4 > x3) x34 = x4 - x3; else x34 = x3 - x4;
	if (x1 < x3) {
		if (x3 > x2) x23 = x3 - x2; else x23 = x2 - x3;
	}
	if (x1 > x3) {
		if (x1 > x4) x23 = x1 - x4; else x23 = x4 - x1;
	}
	if (y2 > y1) y12 = y2 - y1; else y12 = y1 - y2;
	if (y4 > y3) y34 = y4 - y3; else y34 = y3 - y4;
	if (y1 < y3) {
		if (y3 > y2) y23 = y3 - y2; else y23 = y2 - y3;
	}
	if (y1 > y3) {
		if (y1 > y4) y23 = y1 - y4; else y23 = y4 - y1;
	}
	x = x12 + x34 + x23;
	y = y12 + y34 + y23;
	if ((x2 > x3 && y2 > y3) || (x2 > x3 && y1 > y4) || (x1 > x4 && y2 > y3) || (x1 > x4 && y1 > y4)) {
		x = x - 2 * x23;
		y = y - 2 * y23;
	}
	if (x1 < x2) {
		if (y1 < y2) Rect1.SetCoor(x1, x1 + x, y1, y1 + y);
		if (y2 < y1) Rect1.SetCoor(x1, x1 + x, y2, y2 + y);
	}
	if (x2 < x1) {
		if (y1 < y2) Rect1.SetCoor(x2, x2 + x, y1, y1 + y);
		if (y2 < y1) Rect1.SetCoor(x2, x2 + x, y2, y2 + y);
	}
	if (x3 < x4) {
		if (y3 < y4) Rect2.SetCoor(x3, x3 + x, y3, y3 + y);
		if (y4 < y3) Rect2.SetCoor(x3, x3 + x, y4, y4 + y);
	}
	if (x4 < x3) {
		if (y3 < y4) Rect2.SetCoor(x4, x4 + x, y3, y3 + y);
		if (y4 < y3) Rect2.SetCoor(x4, x4 + x, y4, y4 + y);
	}
	Rect1.Show();
	Rect2.Show();
}

void Rect::Twosmallass(Rect Rect1, Rect Rect2) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	x1 = Rect1.x1_; x2 = Rect1.x2_;
	x3 = Rect2.x1_; x4 = Rect2.x2_;
	y1 = Rect1.y1_;	y2 = Rect1.y2_;
	y3 = Rect2.y1_;	y4 = Rect2.y2_;
	int x, y, x11, x22, y11, y22, x12, x34, x23, y12, y34, y23;
	if (x2 > x1) x12 = x2 - x1; else x12 = x1 - x2;
	if (x4 > x3) x12 += x4 - x3; else x12 += x3 - x4;
	if (x1 < x3) {
		if (x3 > x2) x12 += x3 - x2; else x12 += x2 - x3;
	}
	if (x1 > x3) {
		if (x1 > x4) x12 += x1 - x4; else x12 += x4 - x1;
	}
	if (y2 > y1) y12 = y2 - y1; else y12 = y1 - y2;
	if (y4 > y3) y12 += y4 - y3; else y12 += y3 - y4;
	if (y1 < y3) {
		if (y3 > y2) y12 += y3 - y2; else y12 += y2 - y3;
	}
	if (y1 > y3) {
		if (y1 > y4) y12 += y1 - y4; else y12 += y4 - y1;
	}
	//x = x12 + x34 + x23;
	//y = y12 + y34 + y23;
	if ((x2 > x3 && y2 > y3) || (x2 > x3 && y1 > y4) || (x1 > x4 && y2 > y3) || (x1 > x4 && y1 > y4)) {
		x12 = x12 - 2 * x23;
		y12 = y12 - 2 * y23;
	}
	if (x1 < x2) {
		if (y1 < y2) Rect1.SetCoor(x1, x1 + x12, y1, y1 + y12);
		if (y2 < y1) Rect1.SetCoor(x1, x1 + x12, y2, y2 + y12);
	}
	if (x2 < x1) {
		if (y1 < y2) Rect1.SetCoor(x2, x2 + x12, y1, y1 + y12);
		if (y2 < y1) Rect1.SetCoor(x2, x2 + x12, y2, y2 + y12);
	}
	if (x3 < x4) {
		if (y3 < y4) Rect2.SetCoor(x3, x3 + x12, y3, y3 + y12);
		if (y4 < y3) Rect2.SetCoor(x3, x3 + x12, y4, y4 + y12);
	}
	if (x4 < x3) {
		if (y3 < y4) Rect2.SetCoor(x4, x4 + x12, y3, y3 + y12);
		if (y4 < y3) Rect2.SetCoor(x4, x4 + x12, y4, y4 + y12);
	}
	Rect1.Show();
	Rect2.Show();
}

void Rect::Twounif(Rect Rect1, Rect Rect2) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	double x11=0.5, x22=0.5, y11=0.5, y22=0.5;
	x1 = Rect1.x1_; x2 = Rect1.x2_;
	x3 = Rect2.x1_; x4 = Rect2.x2_;
	y1 = Rect1.y1_;	y2 = Rect1.y2_;
	y3 = Rect2.y1_;	y4 = Rect2.y2_;
	if (x4 > x1) {
		if (x2 > x1) {
			if (x3 < x4) {
				if (x3 < x2) {
					x11 = x3; x22 = x2;
				}
				else cout << "Не существует" << endl;
			}
			if (x4 < x3) {
				if (x4 < x2) {
					x11 = x4; x22 = x2;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (x1 > x2) {
			if (x3 < x4) {
				if (x3 < x1) {
					x11 = x3; x22 = x1;
				}
				else cout << "Не существует" << endl;
			}
			if (x4 < x3) {
				if (x4 < x1) {
					x11 = x4; x22 = x1;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (x1 > x4) {
		if (x4 > x3) {
			if (x1 < x2) {
				if (x2 < x4) {
					x11 = x2; x22 = x4;
				}
				else cout << "Не существует" << endl;
			}
			if (x2 < x1) {
				if (x3 < x4) {
					x11 = x1; x22 = x4;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (x3 > x4) {
			if (x1 < x2) {
				if (x1 < x3) {
					x11 = x1; x22 = x3;
				}
				else cout << "Не существует" << endl;
			}
			if (x1 < x2) {
				if (x2 < x3) {
					x11 = x2; x22 = x3;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (y4 > y1) {
		if (y2 > y1) {
			if (y3 < y4) {
				if (y3 < y2) {
					y11 = y3; y22 = y2;
				}
				else cout << "Не существует" << endl;
			}
			if (y4 < y3) {
				if (y4 < y2) {
					y11 = y4; y22 = y2;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (y1 > y2) {
			if (y3 < y4) {
				if (y3 < y1) {
					y11 = y3; y22 = y1;
				}
				else cout << "Не существует" << endl;
			}
			if (y4 < y3) {
				if (y4 < y1) {
					y11 = y4; y22 = y1;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (y1 > y4) {
		if (y4 > y3) {
			if (y1 < y2) {
				if (y2 < y4) {
					y11 = y2; y22 = y4;
				}
				else cout << "Не существует" << endl;
			}
			if (y2 < y1) {
				if (y3 < y4) {
					y11 = y1; y22 = y4;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (y3 > y4) {
			if (y1 < y2) {
				if (y1 < y3) {
					y11 = y1; y22 = y3;
				}
				else cout << "Не существует" << endl;
			}
			if (y1 < y2) {
				if (y2 < y3) {
					y11 = y2; y22 = y3;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (x11 != 0.5 && x22 != 0.5 && y11 != 0.5 && y22 != 0.5) {
		Rect IRect(x11, x22, y11, y22);
		IRect.Show();
	}
}

void Rect::Twounifass(Rect Rect1, Rect Rect2) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	double x11 = 0.5, x22 = 0.5, y11 = 0.5, y22 = 0.5;
	x1 = Rect1.x1_; x2 = Rect1.x2_;
	x3 = Rect2.x1_; x4 = Rect2.x2_;
	y1 = Rect1.y1_;	y2 = Rect1.y2_;
	y3 = Rect2.y1_;	y4 = Rect2.y2_;
	if (x4 > x1) {
		if (x2 > x1) {
			if (x3 < x4) {
				if (x3 < x2) {
					x11 = x22 = x2;
					x11 -= x3;
				}
				else cout << "Не существует" << endl;
			}
			if (x4 < x3) {
				if (x4 < x2) {
					x11 = x22 = x2;
					x11 -= x4;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (x1 > x2) {
			if (x3 < x4) {
				if (x3 < x1) {
					x11 = x22 = x1;
					x11 -= x3;
				}
				else cout << "Не существует" << endl;
			}
			if (x4 < x3) {
				if (x4 < x1) {
					x11 = x22 = x1;
					x11 -= x4;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (x1 > x4) {
		if (x4 > x3) {
			if (x1 < x2) {
				if (x2 < x4) {
					x11 = x22 = x4;
					x11 -= x2;
				}
				else cout << "Не существует" << endl;
			}
			if (x2 < x1) {
				if (x1 < x4) {
					x11 = x22 = x4;
					x11 -= x1;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (x3 > x4) {
			if (x1 < x2) {
				if (x1 < x3) {
					x11 = x22 = x3;
					x11 -= x1;
				}
				else cout << "Не существует" << endl;
			}
			if (x1 < x2) {
				if (x2 < x3) {
					x11 = x22 = x3;
					x11 -= x2;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (y4 > y1) {
		if (y2 > y1) {
			if (y3 < y4) {
				if (y3 < y2) {
					y11 = y22 = y2;
					y11 -= y3;
				}
				else cout << "Не существует" << endl;
			}
			if (y4 < y3) {
				if (y4 < y2) {
					y11 = y22 = y2;
					y11 -= y4;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (y1 > y2) {
			if (y3 < y4) {
				if (y3 < y1) {
					y11 = y22 = y1;
					y11 -= y3;
				}
				else cout << "Не существует" << endl;
			}
			if (y4 < y3) {
				if (y4 < y1) {
					y11 = y22 = y1;
					y11 -= y4;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (y1 > y4) {
		if (y4 > y3) {
			if (y1 < y2) {
				if (y2 < y4) {
					y11 = y22 = y4;
					y11 -= y2;
				}
				else cout << "Не существует" << endl;
			}
			if (y2 < y1) {
				if (y1 < y4) {
					y11 = y22 = y4;
					y11 -= y1;
				}
				else cout << "Не существует" << endl;
			}
		}
		if (y3 > y4) {
			if (y1 < y2) {
				if (y1 < y3) {
					y11 = y22 = y3;
					y11 -= y1;
				}
				else cout << "Не существует" << endl;
			}
			if (y1 < y2) {
				if (y2 < y3) {
					y11 = y22 = y3;
					y11 -= y2;
				}
				else cout << "Не существует" << endl;
			}
		}
	}
	if (x11 != 0.5 && x22 != 0.5 && y11 != 0.5 && y22 != 0.5) {
		Rect IRect(x22-x11, x22, y22-y11, y22);
		IRect.Show();
	}
}
*/

Rect& Rect::operator++() {
	x1_++;
	x2_++;
	y1_++;
	y2_++;
	Rect newRect(x1_, x2_, y1_, y2_);
	return newRect;
}

Rect& Rect::operator--() {
	x1_--;
	x2_--;
	y1_--;
	y2_--;
	Rect newRect(x1_, x2_, y1_, y2_);
	return newRect;
}

Rect Rect::operator +(const Rect& other) {
	int y1, y2, x1, x2;
	if (this->x1_ <= other.x1_) {
		x1 = this->x1_;
	}
	else x1 = other.x1_;

	if (this->x2_ <= other.x2_) {
		x2 = other.x2_;
	}
	else x2 = this->x2_;

	if (this->y1_ <= other.y1_) {
		y1 = this->y1_;
	}
	else y1 = other.y1_;

	if (this->y2_ <= other.y2_) {
		y2 = other.y2_;
	}
	else y2 = this->y2_;

	Rect newRect(x1, x2, y1, y2);
	//newRect.Show();
	return newRect;
}

Rect Rect::operator +=(const Rect& other) {
	int y1, y2, x1, x2;

	if (this->x1_ <= other.x1_) {
		x1 = this->x1_;
	}
	else x1 = other.x1_;

	if (this->x2_ <= other.x2_) {
		x2 = other.x2_;
	}
	else x2 = this->x2_;

	if (this->y1_ <= other.y1_) {
		y1 = this->y1_;
	}
	else y1 = other.y1_;

	if (this->y2_ <= other.y2_) {
		y2 = other.y2_;
	}
	else y2 = this->y2_;

	this->x1_ = x1;
	this->x2_ = x2;
	this->y1_ = y1;
	this->y2_ = y2;

	return *this;
}

Rect Rect::operator -(const Rect& other){
	int X1, X2, Y1, Y2, x, xx, y, yy, i, j;

	vector <int> rect(0);

	for (x = this->x1_; x <= this->x2_; x++) {
		for (y = this->y1_; y <= this->y2_; y++) {
			for (xx = other.x1_; xx <= other.x2_; xx++) {
				for (yy = other.y1_; yy <= other.y2_; yy++) {

					X1 = x; X2 = xx; Y1 = y; Y2 = yy;

					if (X1 == X2 && Y1 == Y2) {
						rect.push_back(X1); rect.push_back(Y1);
					}
				}
			}
		}
	}

	X1 = rect[0];
	X2 = rect[1];
	Y1 = rect[2];
	Y2 = rect[3];

	for (i = 0; i < rect.size(); i = i + 2) {
		if (X1 > rect[i]) X1 = rect[i];
		if (X2 < rect[i]) X2 = rect[i];
	}
	for (j = 1; j < rect.size(); j = j + 2) {
		if (Y1 > rect[j]) Y1 = rect[j];
		if (Y2 < rect[j]) Y2 = rect[j];
	}

	Rect newRect(0, 0, 0, 0);

	if (X1 == X2 || Y1 == Y2) {
		return newRect;
	}
	else {
		newRect.def(X1, X2, Y1, Y2); return newRect;
	}
}

Rect Rect::operator -= (const Rect & other) {
	int X1, X2, Y1, Y2, x, xx, y, yy, i, j;

	vector <int> rect(0);

	for (x = this->x1_; x <= this->x2_; x++) {
		for (y = this->y1_; y <= this->y2_; y++) {
			for (xx = other.x1_; xx <= other.x2_; xx++) {
				for (yy = other.y1_; yy <= other.y2_; yy++) {

					X1 = x; X2 = xx; Y1 = y; Y2 = yy;

					if (X1 == X2 && Y1 == Y2) {
						rect.push_back(X1); rect.push_back(Y1);
					}
				}
			}
		}
	}

	X1 = rect[0];
	X2 = rect[1];
	Y1 = rect[2];
	Y2 = rect[3];

	for (i = 0; i < rect.size(); i = i + 2) {
		if (X1 > rect[i]) X1 = rect[i];
		if (X2 < rect[i]) X2 = rect[i];
	}
	for (j = 1; j < rect.size(); j = j + 2) {
		if (Y1 > rect[j]) Y1 = rect[j];
		if (Y2 < rect[j]) Y2 = rect[j];
	}

	if (X1 == X2 || Y1 == Y2) return *this;
	else {
		this->x1_ = X1;
		this->x2_ = X2;
		this->y1_ = Y1;
		this->y2_ = Y2;
		return *this;
	}
	
}

void Rect::operator=(const Rect& other)
{
	this->x1_ = other.x1_;
	this->x2_ = other.x2_;
	this->y1_ = other.y1_;
	this->y2_ = other.y2_;
}
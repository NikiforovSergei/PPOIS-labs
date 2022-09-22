#include "pch.h"
#include "C:\Users\Aleksandria\source\repos\ppois\lab1\realisation.cpp"

TEST(get, all) {
	Natural a(9, 153);  EXPECT_EQ(a.getNum(), 1); EXPECT_EQ(a.getDenom(), 17);
	Natural b(2, 4, 8); EXPECT_EQ(b.getInt(), 2);
	Natural c(2, 8, 4); EXPECT_EQ(c.getNum(), 4); EXPECT_EQ(c.getDenom(), 1);
}
TEST(addition, n_n) {
	Natural a(1, 5, 9); Natural b(8, 9, 15);
	Natural c = a + b;
	EXPECT_EQ(c.getNum(), 457); EXPECT_EQ(c.getDenom(), 45);
	Natural x(1, 5, 9); Natural y(8, 9, 15);
	x += y;
	EXPECT_EQ(x.getNum(), 457); EXPECT_EQ(x.getDenom(), 45);
}
TEST(addition, n_i) {
	Natural a(6, 5);
	Natural c = a + 4;
	EXPECT_EQ(c.getNum(), 26); EXPECT_EQ(c.getDenom(), 5);
	c = 4 + a;
	EXPECT_EQ(c.getNum(), 26); EXPECT_EQ(c.getDenom(), 5);
	c += 4;
	EXPECT_EQ(c.getNum(), 46); EXPECT_EQ(c.getDenom(), 5);
}
TEST(difference, n_n) {
	Natural a(18, 5); Natural b(14, 17);
	Natural c = a - b;
	EXPECT_EQ(c.getNum(), 236); EXPECT_EQ(c.getDenom(), 85);
	Natural x(1, 5, 9); Natural y(8, 9, 15);
	x -= y;
	EXPECT_EQ(x.getNum(), -317); EXPECT_EQ(x.getDenom(), 45);
}
TEST(difference, n_i) {
	Natural a(6, 5);
	Natural c = a - 4;
	EXPECT_EQ(c.getNum(), -14); EXPECT_EQ(c.getDenom(), 5);
	c -= 4;
	EXPECT_EQ(c.getNum(), -34); EXPECT_EQ(c.getDenom(), 5);
}
TEST(multiplication, n_n) {
	Natural a(18, 5); Natural b(14, 17);
	Natural c = a * b;
	EXPECT_EQ(c.getNum(), 252); EXPECT_EQ(c.getDenom(), 85);
	c = b * a;
	EXPECT_EQ(c.getNum(), 252); EXPECT_EQ(c.getDenom(), 85);
	Natural x(-1, 2, 3); Natural y(1, 3);
	x *= y;
	EXPECT_EQ(x.getNum(), -5); EXPECT_EQ(x.getDenom(), 9);
}
TEST(multiplication, n_i) {
	Natural a(6, 5);
	Natural c = a * 4;
	EXPECT_EQ(c.getNum(), 24); EXPECT_EQ(c.getDenom(), 5);
	c *= 4;
	EXPECT_EQ(c.getNum(), 96); EXPECT_EQ(c.getDenom(), 5);
}
TEST(division, n_n) {
	Natural a(12, 5); Natural b(2, 5);
	Natural c = a / b;
	EXPECT_EQ(c.getNum(), 6); EXPECT_EQ(c.getDenom(), 1);
	c = b / a;
	EXPECT_EQ(c.getNum(), 1); EXPECT_EQ(c.getDenom(), 6);
	Natural x(-1, 2, 3); Natural y(1, 3);
	x /= y;
	EXPECT_EQ(x.getNum(), -5); EXPECT_EQ(x.getDenom(), 1);
}
TEST(division, n_i) {
	Natural a(6, 5);
	Natural c = a / 6;
	EXPECT_EQ(c.getNum(), 1); EXPECT_EQ(c.getDenom(), 5);
	c /= 3;
	EXPECT_EQ(c.getNum(), 1); EXPECT_EQ(c.getDenom(), 15);
}
TEST(increment, n) {
	Natural a(6, 5), b = a++;
	EXPECT_EQ(b.getNum(), 6); EXPECT_EQ(b.getDenom(), 5);
	a++;
	EXPECT_EQ(a.getNum(), 16); EXPECT_EQ(a.getDenom(), 5);
	++a;
	EXPECT_EQ(a.getNum(), 21); EXPECT_EQ(a.getDenom(), 5);
}
TEST(decrement, n) {
	Natural a(6, 5), b = a--;
	EXPECT_EQ(b.getNum(), 6); EXPECT_EQ(b.getDenom(), 5);
	a--;
	EXPECT_EQ(a.getNum(), -4); EXPECT_EQ(a.getDenom(), 5);
	--a;
	EXPECT_EQ(a.getNum(), -9); EXPECT_EQ(a.getDenom(), 5);
}
TEST(bool, N_i) {
	Natural a(6, 5), b(1, 5);
	EXPECT_TRUE(a > 1);
	EXPECT_TRUE(a > b);
	EXPECT_FALSE(b > a);
}
TEST(bool, N__i) {
	Natural a(6, 5), b(1, 5), c(6, 5);
	EXPECT_TRUE(a >= 1);
	EXPECT_TRUE(c >= a);
	EXPECT_FALSE(b >= a);
}
TEST(bool, n_I) {
	Natural a(6, 5), b(1, 5);
	EXPECT_TRUE(b < a);
	EXPECT_TRUE(b < 1);
	EXPECT_FALSE(b > a);
}
TEST(bool, n__I) {
	Natural a(6, 5), b(1, 5), c(6, 5);
	EXPECT_TRUE(b <= 1);
	EXPECT_TRUE(c <= a);
	EXPECT_FALSE(b >= a);
}
TEST(double, n) {
	Natural a(1, 2), b(1, 5), c(6, 5), d(2, 4, 5), e(2);
	EXPECT_EQ(a.ntod(), 0.5);
	EXPECT_EQ(b.ntod(), 0.2);
	EXPECT_EQ(c.ntod(), 1.2);
	EXPECT_EQ(d.ntod(), 2.8);
	EXPECT_EQ(e.ntod(), 2);
}
TEST(equality, n) {
	Natural a(1, 2), b(1, 5), c(6, 5), d(2, 4, 5), e(2), f(6, 5);
	EXPECT_TRUE(a != b);
	EXPECT_TRUE(c == f);
	EXPECT_TRUE(d != e);
}
TEST(stream, n) {
	Natural a;
	cin >> a; cout << a;
}

TEST(throw, n) {
	EXPECT_ANY_THROW(Natural c(1, 0));
	EXPECT_ANY_THROW(Natural a(1, 0, 0));
	EXPECT_ANY_THROW(Natural g(7, 8, 0));
	EXPECT_ANY_THROW(Natural b(0));
	EXPECT_NO_THROW(Natural d(0, 1, 1));
}






























#include <bits/stdc++.h>

const int MAXN = 110;
typedef std::bitset<1440> B;
// 0
//1 2
// 3
//4 5
// 6
const int oy[] = {0, 5, 12, 17};
const int px[] = {0, 1, 1, 3, 4, 4, 6};
const int py[] = {1, 0, 3, 1, 0, 3, 1};
#define NU(A, B, C, D, E, F, G) \
	(A | (B << 1) | (C << 2) | (D << 3) | (E << 4) | (F << 5) | (G << 6))
const int nu[] = {
	NU(1, 1, 1, 0, 1, 1, 1),
	NU(0, 0, 1, 0, 0, 1, 0),
	NU(1, 0, 1, 1, 1, 0, 1),
	NU(1, 0, 1, 1, 0, 1, 1),
	NU(0, 1, 1, 1, 0, 1, 0),
	NU(1, 1, 0, 1, 0, 1, 1),
	NU(1, 1, 0, 1, 1, 1, 1),
	NU(1, 0, 1, 0, 0, 1, 0),
	NU(1, 1, 1, 1, 1, 1, 1),
	NU(1, 1, 1, 1, 0, 1, 1)
};
#undef NU
int sta[MAXN];
B eq[30], li[30], da[30];
int n;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n; std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int r = 0;
		static char buf[7][96];
		for (int i = 0; i < 7; ++i)
			std::cin >> buf[i];
		int cx = 0;
		for (int i = 0, t; i < 4; ++i)
			for (int j = 0; j < 7; ++j) {
				t = buf[px[j]][oy[i] + py[j]] == 'X';
				r |= t << cx++;
			}
		r |= (buf[2][10] == 'X') << cx++;
		r |= (buf[4][10] == 'X') << cx++;
		sta[i] = r;
	}
	{
		int A = -1, B = -1;
		for (int i = 0; i < n; ++i)
			A &= sta[i], B &= ~sta[i];
		for (int i = 0; i < 30; ++i) {
			if (A >> i & 1) li[i].set();
			if (B >> i & 1) da[i].set();
		}
	}
	for (int i = 0; i < 1440; ++i) {
		int ct = 0;
		for (int j = 0; j < n; ++j) {
			int ti = (i + j) % 1440;
			int h = ti / 60, m = ti % 60;
			int t = 3 << 28;
			if (h >= 10)
				t |= nu[h / 10];
			t |= nu[h % 10] << 7;
			t |= nu[m / 10] << 14;
			t |= nu[m % 10] << 21;
			ct |= sta[j] ^ t;
		}
		for (int j = 0; j != 30; ++j)
			if (!(ct >> j & 1))
				eq[j].set(i);
	}
	B al; al.set();
	for (int i = 0; i < 30; ++i)
		al &= eq[i] | li[i] | da[i];
	if (al.none()) {
		std::cout << "impossible" << std::endl;
		return 0;
	}
	static char ans[30];
	for (int i = 0; i < 30; ++i) {
		int a = (eq[i] & al).any();
		int b = (li[i] & al).any();
		int c = (da[i] & al).any();
		if (a + b + c > 1)
			ans[i] = '?';
		else {
			if (a) ans[i] = 'W';
			if (b) ans[i] = '1';
			if (c) ans[i] = '0';
		}
	}
	static char mat[7][22];
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 21; ++j)
			mat[i][j] = '.';
	int cx = 0;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 7; ++j) {
			int dx, dy;
			if (j % 3 == 0)
				dx = 0, dy = 1;
			else
				dx = 1, dy = 0;
			mat[px[j]][py[j] + oy[i]] = ans[cx];
			mat[px[j] + dx][py[j] + oy[i] + dy] = ans[cx];
			++cx;
		}
	mat[2][10] = ans[cx++];
	mat[4][10] = ans[cx++];
	for (int i = 0; i < 7; ++i)
		std::cout << mat[i] << '\n';
	return 0;
}

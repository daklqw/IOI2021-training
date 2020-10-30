#include <bits/stdc++.h>
#include "gomoku.h"

int A[20][20];
int stp, tc;
//void input(int & x, int & y) {
//	std::cin >> x >> y;
//}
//void output(int x, int y) {
//	std::cout << x << ' ' << y << '\n';
//	std::cout.flush();
//}
void _output(int x, int y) {
	static int flg = 0;
	if (flg) return ;
	A[x][y] = 2;
	output(x, y);
	input(x, y);
	if (x == -1 && y == -1) {
		flg = true;
	}
	A[x][y] = 1;
}

int in(int x) {
	return 1 <= x && x <= 19;
}
void defense() {
	const int dx[] = {1, 0, 1, 1};
	const int dy[] = {0, 1, 1, -1};
	for (int i = 4, x, y; i <= 15; ++i)
		for (int j = 4; j <= 15; ++j)
			for (int k = 0; k < 4; ++k) {
				bool can = true;
				for (int l = 0; l < 3; ++l)
					can &= A[i + dx[k] * l][j + dy[k] * l] == 1;
				if (can) {
					for (int co = -1; co <= 3; co += 4)
					if (!A[x = i + dx[k] * co][y = j + dy[k] * co]) {
						_output(x, y);
						return ;
					}
				}
			}
}
void work() {
	int x, y;
	input(x, y);
	A[x][y] = 1;
	_output(4, 5);
	_output(5, 4);
	defense();
	defense();
	if (!A[3][6]) {
		_output(3, 6);
		x = 4, y = 5;
	} else {
		_output(6, 3);
		x = 5, y = 4;
	}
	_output(x + 1, y + 1);
	_output(x - 1, y - 1);
	_output(x + 1, y);
	_output(x - 1, y);
	int sx, sy, tx, ty;
	if (A[x - 1][y + 2])
		_output(sx = x, sy = y + 2);
	else
		_output(sx = x, sy = y - 2);
	if (A[x + 2][y])
		_output(tx = x - 2, ty = y);
	else
		_output(tx = x + 2, ty = y);
	int dx = (tx - sx) / 2;
	int dy = (ty - sy) / 2;
	for (int i = 2; i; --i) {
		if (in(tx + dx * i) && in(ty + dy * i)) {
			bool can = true;
			for (int j = 1; j <= i; ++j)
				can &= !A[tx + dx * j][ty + dy * j];
			if (can) {
				_output(tx += dx, ty += dy);
				continue;
			}
		}
		_output(sx -= dx, sy -= dy);
	}
}


//int main() {
//	work();
//}

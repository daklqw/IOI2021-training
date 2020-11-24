#include <bits/stdc++.h>

const int MAXN = 21;
typedef long double db;
const db eps = 1e-8;
const db g = 9.80665;
int A[MAXN][MAXN];
int H, W, R, V;
int pw(int x) { return x * x; }
std::pair<db, db> normal(db a, db b) {
	db L = sqrtl(a * a + b * b);
	return std::make_pair(a / L, b / L);
}
bool judge(int sx, int sy, int dx, int dy) {
	db L = R * sqrtl(pw(sx - dx) + pw(sy - dy));
	db c = A[dx][dy] - A[sx][sy];
	db a = g * L * L / 2 / V / V;
	c += a;
	db b = -L;
	db dta = b * b - 4 * a * c;
	if (dta < -eps) return false;
	if (dta < 0) dta = 0;
	dta = sqrtl(dta);
	db vx, vy;
	std::tie(vx, vy) = normal(a * 2, -b + dta);
	vx *= V, vy *= V;
	db T = L / vx;
	int l = std::min(sx, dx);
	int r = std::max(sx, dx);
	for (int i = l; i < r; ++i) {
		db sc = (((i + 1) - (sx + 0.5)) / (dx - sx));
		db t = T * sc;
		db y = sc * (dy - sy) + sy + 0.5;
		db h = vy * t - g * t * t / 2 + A[sx][sy];
		int mh = 0;
		for (int j = (int) y - 1; j <= (int) y + 1; ++j)
			if (j - eps <= y && y <= j + 1 + eps)
				mh = std::max(mh, std::max(A[i][j], A[i + 1][j]));
		if (h < mh - eps) return false;
	}
	l = std::min(sy, dy);
	r = std::max(sy, dy);
	for (int i = l; i < r; ++i) {
		db sc = (((i + 1) - (sy + 0.5)) / (dy - sy));
		db t = T * sc;
		db x = sc * (dx - sx) + sx + 0.5;
		db h = vy * t - g * t * t / 2 + A[sx][sy];
		int mh = 0;
		for (int j = (int) x - 1; j <= (int) x + 1; ++j)
			if (j - eps <= x && x <= j + 1 + eps)
				mh = std::max(mh, std::max(A[j][i], A[j][i + 1]));
		if (h < mh - eps) return false;
	}
	return true;
}
int dis[MAXN][MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int sx, sy;
	std::cin >> W >> H >> R >> V >> sy >> sx;
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			std::cin >> A[i][j];
	memset(dis, -1, sizeof dis);
	dis[sx][sy] = 0;
	std::queue<std::pair<int, int> > que;
	que.emplace(sx, sy);
	while (!que.empty()) {
		int x, y;
		std::tie(x, y) = que.front();
		que.pop();
		for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= W; ++j)
				if (dis[i][j] == -1 && judge(x, y, i, j)) {
					dis[i][j] = dis[x][y] + 1;
					que.emplace(i, j);
				}
	}
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j) {
			if (dis[i][j] == -1)
				std::cout << 'X';
			else
				std::cout << dis[i][j];
			std::cout << (" \n" [j == W]);
		}
	return 0;
}

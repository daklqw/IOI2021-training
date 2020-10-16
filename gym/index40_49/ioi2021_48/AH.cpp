#include <bits/stdc++.h>

typedef long double db;
const int DTA = 23;
const int MAXN = DTA * 2;
const int MAXM = 1e4 + 10;

int H, W, N;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
db pr[4];
db mat[MAXM * MAXN][MAXN], co[MAXM * MAXN];
char buf[MAXM][MAXN];
inline int getID(int x, int y) {
	return x * W + y;
}
inline db & get(int x, int y) {
	return y == N ? co[x] : mat[x][y - x + DTA];
}

void adde(int u, int v, db pr) {
	get(v, u) += pr;
}

void gauss() {
	for (int i = 0; i < N; ++i) {
		const int ub = std::min(N, i + DTA);
		get(i, N) /= get(i, i);
		for (int j = ub - 1; j >= i; --j)
			get(i, j) /= get(i, i);
		for (int j = i + 1; j < ub; ++j) {
			const db V = get(j, i);
			for (int k = i; k < ub; ++k)
				get(j, k) -= V * get(i, k);
			get(j, N) -= V * get(i, N);
		}
	}
	for (int i = N - 1; ~i; --i) {
		const int ub = std::min(N, i + DTA);
		for (int j = i + 1; j < ub; ++j)
			get(i, N) -= get(j, N) * get(i, j);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> W >> H;
	for (int i = 0; i < 4; ++i)
		std::cin >> pr[i], pr[i] /= 100;
	for (int i = 0; i < H; ++i)
		std::cin >> buf[i];
	N = H * W;
	db tc = 1;
	tc /= std::count(buf[0], buf[0] + W, '.');
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			int u = getID(i, j);
			if (buf[i][j] != 'X')
				get(u, u) += -1;
			if (buf[i][j] == '.') {
				if (i == 0)
					get(u, N) -= tc;
				for (int k = 0; k < 4; ++k) {
					int x = i + dx[k], y = j + dy[k];
					bool over = false;
					if (x < 0 || y < 0 || x >= H || y >= W)
						over = true;
					else
						over = buf[x][y] == 'X';
					adde(u, over ? u : getID(x, y), pr[k]);
				}
			}
		}
	}
	gauss();
	std::cout << std::fixed << std::setprecision(10);
	for (int i = 0; i < H; ++i)
		for (int j = 0; j < W; ++j)
			if (buf[i][j] == 'T')
				std::cout << get(getID(i, j), N) << '\n';
	return 0;
}

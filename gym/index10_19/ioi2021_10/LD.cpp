#include <bits/stdc++.h>

const int MAXN = 2010;
int A[MAXN][MAXN];
int fa[MAXN][MAXN];

int n, m;
struct _ {
	int l, r;
} f[MAXN][MAXN];
_ operator + (_ a, _ b) {
}
int get(int x, int y) {
	int v = -1, at = 0;
	for (int i = -1; i <= 1; ++i) {
		int x = (y + i + m) % m;
		int t = A[(x + 1) % n][x];
		if (t > v) v = t, at = x;
	}
	return at;
}
void update(int x, int y) {
	int l = (x - 1 + n) % n;
	f[x][y] = (_) {-1, -1};
	for (int i = -1; i <= 1; ++i) {
		int p = (y + i + m) % m;
		if (fa[l][p] == y) {
			if (f[x][y].l == -1) f[x][y] = f[l][p];
			else f[x][y] = f[l][p] + f[x][y];
		}
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			std::cin >> A[i][j];
	for (int i = 0; i < n; ++i) f[i][0] = (_) {i, i};
	for (int j = 0; j < m; ++j)
		for (int i = 0; i < n; ++i)
			fa[i][j] = get(i, j);
	for (int j = 1; j < m; ++j)
		for (int i = 0; i < n; ++i)
			update(i, j);
	int Q; std::cin >> Q;
	while (Q --> 0) {
	}
	return 0;
}

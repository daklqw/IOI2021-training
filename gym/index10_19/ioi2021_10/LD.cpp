#include <bits/stdc++.h>

const int MAXN = 2010;
int A[MAXN][MAXN];
int fa[MAXN][MAXN];

int n, m;
struct _ {
	int l, r;
} f[MAXN][MAXN];
_ operator + (_ a, _ b) {
	if (b.r == a.l) return (_) {b.l, a.r};
	if (b.r == a.l + n) return (_) {b.l, a.r + n};
	if (a.r == b.l) return (_) {a.l, b.r};
	if (a.r == b.l + n) return (_) {a.l, b.r + n};
	std::cerr << "???" << std::endl;
	return (_) {-12243, 12243};
}
int get(int x, int y) {
	int v = -1, at = 0;
	for (int i = -1; i <= 1; ++i) {
		int p = (x + i + n) % n;
		int t = A[p][(y + 1) % m];
		if (t > v) v = t, at = p;
	}
	return at;
}
void update(int x, int y) {
	int l = (y - 1 + m) % m;
	f[x][y] = (_) {-1, -1};
	for (int i = -1; i <= 1; ++i) {
		int p = (x + i + n) % n;
		if (f[p][l].l != -1 && fa[p][l] == x) {
			if (f[x][y].l == -1) f[x][y] = f[p][l];
			else f[x][y] = f[p][l] + f[x][y];
		}
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			std::cin >> A[i][j];
	for (int i = 0; i < n; ++i) f[i][0] = (_) {i, i + 1};
	for (int j = 0; j < m; ++j)
		for (int i = 0; i < n; ++i)
			fa[i][j] = get(i, j);
	for (int j = 1; j < m; ++j)
		for (int i = 0; i < n; ++i)
			update(i, j);
	int Q; std::cin >> Q;
	int X = 0, Y = 0;
	while (Q --> 0) {
		char opt[10];
		std::cin >> opt;
		if (*opt == 'm') {
			int K; std::cin >> K;
			while (K && Y != 0)
				--K, X = fa[X][Y], Y = (Y + 1) % m;
			int turn = K / m;
			K -= turn * m;
			static int nxt[MAXN];
			for (int i = 0; i < n; ++i)
				for (int j = f[i][m - 1].l; j != f[i][m - 1].r; ++j)
					nxt[j % n] = fa[i][m - 1];
			int u = X, v = X, L = 0;
			while (turn) {
				--turn;
				u = nxt[u], v = nxt[nxt[v]];
				++L;
				if (u == v) break;
			}
			if (L) turn %= L;
			while (turn --> 0) u = nxt[u];
			X = u;
			while (K)
				--K, X = fa[X][Y], Y = (Y + 1) % m;
			std::cout << (X + 1) << ' '  << (Y + 1) << '\n';
		} else {
			int x, y, v;
			std::cin >> x >> y >> v; --x, --y;
			A[x][y] = v;
			int p = (y - 1 + m) % m;
			static int up[6];
			int bak = 0;
			for (int i = -1; i <= 1; ++i) {
				int q = (x + i + n) % n;
				up[bak++] = fa[q][p];
				fa[q][p] = get(q, p);
				up[bak++] = fa[q][p];
			}
			while (++p < m) {
				for (int i = 0; i < bak; ++i)
					update(up[i], p), up[i] = fa[up[i]][p];
			}
		}
	}
	return 0;
}

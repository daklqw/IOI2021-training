#include <bits/stdc++.h>

const int MAXN = 110;
inline int NU(int A, int B = 0, int C = 0, int D = 0, int E = 0) {
	return A | (B << 1) | (C << 2) | (D << 3) | (E << 4);
}
const int mid[] = {
	NU(1, 0, 1),
	NU(0, 0, 0),
	NU(1, 1, 1),
	NU(1, 1, 1),
	NU(0, 1, 0),
	NU(1, 1, 1),
	NU(1, 1, 1),
	NU(1, 0, 0),
	NU(1, 1, 1),
	NU(1, 1, 1)
};
const int left[] = {
	NU(1, 1),
	NU(0, 0),
	NU(0, 1),
	NU(0, 0),
	NU(1, 0),
	NU(1, 0),
	NU(1, 1),
	NU(0, 0),
	NU(1, 1),
	NU(1, 0)
};
const int right[] = {
	NU(1, 1),
	NU(1, 1),
	NU(1, 0),
	NU(1, 1),
	NU(1, 1),
	NU(0, 1),
	NU(0, 1),
	NU(1, 1),
	NU(1, 1),
	NU(1, 1)
};
#undef NU
int A[MAXN][9];
int n;
int vis[MAXN][1 << 4][2];
int ansl[3][MAXN];
bool dfs(int S, int mask, int b) {
	if (S == 0) {
		int v = NU(A[1][1], A[1][3], A[1][5], A[1][7]);
		return !b && v == mask;
	}
	if (vis[S][mask][b]) return false;
	vis[S][mask][b] = true;
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 10; ++j) {
			int k = (b + i + j) % 10;
			int tar = NU(A[S][0], A[S][2], A[S][4], A[S][6], A[S][8]);
			int now = NU(mid[i], mid[j], mid[k]);
			if (now != tar) continue;
			int T = S + 1;
			now = mask | NU(right[i], right[j], right[k]);
			tar = NU(A[T][1], A[T][3], A[T][5], A[T][7]);
			if (now != tar) continue;
			int nx = NU(left[i], left[j], left[k]);
			if (dfs(S - 1, nx, b + i + j > 9)) {
				ansl[0][S] = i;
				ansl[1][S] = j;
				ansl[2][S] = k;
				return true;
			}
		}
	return false;
}
int main() {
#define FILENAME "digital"
#ifdef FILENAME
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < 9; ++i)
		for (int j = 1; j <= n + (i & 1); ++j)
			std::cin >> A[j][i];
	if (!dfs(n, 0, 0)) {
		std::cout << "NO" << '\n';
	} else {
		for (int i = 0; i < 3; ++i, std::cout << '\n')
			for (int j = 1; j <= n; ++j)
				std::cout << ansl[i][j];
	}
	return 0;
}

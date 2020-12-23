#include <bits/stdc++.h>

const int MAXN = 4e4 + 10;
typedef std::pair<int, int> pi;
std::vector<int> hav[6][6];
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
int dp[10][10];
void move(int x, int y, int typ, int C) {
	std::cout << (6 - x) << ' ' << (6 - y) << ' ';
	if (typ == 0) std::cout << "D ";
	else std::cout << "R ";
	std::cout << C << '\n';
	VI li;
	while (C --> 0) {
		li.push_back(hav[x][y].back());
		hav[x][y].pop_back();
	}
	int dx = typ == 0 ? -1 : 0;
	int dy = typ == 1 ? -1 : 0;
	if (x + dx < 0 || y + dy < 0)
		abort();
	while (!li.empty()) {
		hav[x + dx][y + dy].push_back(li.back());
		li.pop_back();
	}
}
void solve(int x, int y, int L, int R, VVI bot) {
	if (!x && !y) return ;
	if (x + y == 1) {
		int p = bot[x][y];
		bool typ = hav[x][y][p] < hav[x][y][p + 1];
		int up = typ ? 1 : 2;
		if (L + 1 == R) up = 1, typ = 0;
		for (int i = 1; i <= up; ++i)
			move(x, y, y == 1, typ ? 2 : 1);
		return ;
	}
	std::map<int, pi> M;
	int cur = L;
	VVI bn = bot, dl(6, VI(6, 0)), dr = dl;
	for (int i = 0; i <= x; ++i)
		for (int j = 0; j <= y - (i == x); ++j) {
			int t = dp[i + 1][j + 1];
			dl[i][j] = cur;
			while (t > 0 && cur < R) {
				M[cur++] = pi(i, j);
				++bn[i][j];
				--t;
			}
			dr[i][j] = cur;
		}
	while ((int) hav[x][y].size() > bot[x][y]) {
		int v = hav[x][y].back();
		int ux = x, uy = y;
		while (ux > M[v].first)
			move(ux--, uy, 0, 1);
		while (uy > M[v].second)
			move(ux, uy--, 1, 1);
	}
	for (int i = 0; i <= x; ++i)
		for (int j = 0; j <= y - (i == x); ++j)
			if (dl[i][j] < dr[i][j]) {
				bn[i][j] = bot[i][j];
				solve(i, j, dl[i][j], dr[i][j], bn);
			}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	dp[1][1] = 1;
	dp[2][1] = dp[1][2] = 2;
	for (int i = 1; i <= 6; ++i)
		for (int j = 1; j <= 6; ++j) if (i + j > 3) {
			for (int k = 1; k <= i; ++k)
				for (int l = 1; l <= j - (k == i); ++l)
					dp[i][j] += dp[k][l];
		}
	VVI init(6, VI(6, 0));
	int n; std::cin >> n;
	for (int i = 1, t; i <= n; ++i) {
		std::cin >> t;
		hav[5][5].push_back(n - t + 1);
	}
	solve(5, 5, 1, n + 1, init);
	return 0;
}

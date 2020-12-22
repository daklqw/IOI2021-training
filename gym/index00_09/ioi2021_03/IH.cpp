#include <bits/stdc++.h>

const int MAXN = 10;
void bye() {
	std::cout << "No" << std::endl;
	exit(0);
}
char mat[MAXN][MAXN][MAXN];
int n, m, K;
bool vis[MAXN][MAXN][MAXN];
std::set<int> S;
void solve(int x, int y, int z, int a, int b, int c, int d) {
	if (x < 1 || y < 1 || z < 1) return ;
	if (x > n || y > m || z > K) return ;
	if (mat[x][y][z] != 'x') return ;
	if (vis[x][y][z]) return ;
	vis[x][y][z] = true;
	if (S.count(a)) bye();
	S.insert(a);
	solve(x - 1, y, z, b, -a, c, d);
	solve(x + 1, y, z, -b, a, c, d);
	solve(x, y - 1, z, c, b, -a, d);
	solve(x, y + 1, z, -c, b, a, d);
	solve(x, y, z - 1, d, b, c, -a);
	solve(x, y, z + 1, -d, b, c, a);
}
int main() {
#define FILENAME "hypercube"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> K >> m >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			std::cin >> (mat[i][j] + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			for (int k = 1; k <= K; ++k)
				if (mat[i][j][k] == 'x') {
					solve(i, j, k, 1, 2, 3, 4);
					std::cout << "Yes" << std::endl;
					return 0;
				}
	return 0;
}

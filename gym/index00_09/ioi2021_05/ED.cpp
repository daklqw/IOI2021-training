#include <bits/stdc++.h>

const int MAXN = 510;
typedef long double db;
int n, D, R;
db inv[MAXN], f[MAXN][MAXN], g[MAXN][MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> D >> R;
	inv[0] = 1;
	for (int i = 1; i <= n; ++i)
		inv[i] = inv[i - 1] / i;
	f[0][0] = 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= D; ++j) {
			for (int k = i == 0; i + k <= n && j + i <= D; ++k) {
				const db c = inv[k];
				const db co = f[i][j] * c;
				f[i + k][j + i] += co;
				g[i + k][j + i] += g[i][j] * c;
				g[i + k][j + i] += co * std::min(i, R);
			}
		}
	}
	std::cout << std::fixed << std::setprecision(10);
	std::cout << g[n][D] / f[n][D] + R << std::endl;
	return 0;
}

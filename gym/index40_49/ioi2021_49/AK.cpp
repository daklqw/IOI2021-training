#include <bits/stdc++.h>

const int MAXN = 2e6 + 10;
void gma(int & x, int y) { if (x < y) x = y; }
int R[21][MAXN];
int n, K;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> K;
	for (int i = 1, l, r; i <= K; ++i) {
		std::cin >> l >> r;
		if (l > r) gma(R[0][l], r + n);
		else gma(R[0][l], r), gma(R[0][l + n], r + n);
	}
	const int m = n << 1;
	for (int i = 1; i <= m; ++i)
		gma(R[0][i], R[0][i - 1]);
	for (int i = 1; i != 21; ++i)
		for (int j = 1; j <= m; ++j)
			R[i][j] = R[i - 1][std::min(R[i - 1][j] + 1, m)];
	int ans = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		int t = 0, u = i, T = i + n - 1;
		for (int j = 20; ~j; --j)
			if (R[j][u] < T)
				t |= 1 << j, u = R[j][u] + 1;
		if (R[0][u] >= T)
			ans = std::min(ans, t + 1);
	}
	if (ans == 0x3f3f3f3f)
		std::cout << "impossible" << std::endl;
	else
		std::cout << ans << std::endl;
	return 0;
}

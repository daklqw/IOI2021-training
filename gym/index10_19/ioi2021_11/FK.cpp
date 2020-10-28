#include <bits/stdc++.h>

const int MAXN = 100;
const int lim = 8 * 9 * 5 * 7;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
typedef long double db;
typedef std::bitset<MAXN> B;
int n;
B hav[MAXN][lim];
bool can[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	for (int i = 1; i < MAXN; ++i) can[i] = true;
	for (int i = 2; i < MAXN; ++i)
		for (int j = i + i; j < MAXN; j += i)
			can[j] = false;
	can[2] = can[3] = false;
	can[8] = can[9] = true;
	for (int i = 1; i < MAXN; ++i)
		if (can[i]) {
			for (int j = 0; j < lim; ++j)
				for (int k = 0; k < i; ++k)
					hav[i][j].set(k);
		}
	std::cin >> n;
	static db dp[510];
	for (int i = 1; i <= n; ++i) {
		int x, a, b;
		std::cin >> x >> a >> b;
		int T = a + b;
		x %= T;
		int g = gcd(T, lim);
		int r = T / g;
		if (r == 2 || r == 4) r = 8;
		if (r == 3) r = 9;
		for (int k = 0; k < r; ++k)
			for (int j = 0; j < lim; ++j) {
				if (x < a) hav[r][j].reset(k);
				x = x == T - 1 ? 0 : x + 1;
			}
		db & pr = dp[i] = 0;
		for (int j = 0; j < lim; ++j) {
			db tp = 1;
			for (int k = 1; k < MAXN; ++k)
				if (can[k])
					tp *= hav[k][j].count() / (db) k;
			pr += tp;
		}
		pr /= lim;
	}
	std::cout << std::fixed << std::setprecision(12);
	dp[0] = 1;
	for (int i = 1; i <= n + 1; ++i)
		std::cout << (dp[i - 1] - dp[i]) << '\n';
	return 0;
}

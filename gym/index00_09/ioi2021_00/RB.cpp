#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
void bye() {
	std::cout << "Impossible" << std::endl;
	exit(0);
}
int n, P, noB, noG, G1, G2, B1, B2, Gex, Bex;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> noB >> noG;
	noB = n - noB;
	noG = n - noG;
	if (noB == 0 && noG == n) {
		for (int i = 0; i < n; ++i) std::cout << 'B';
		std::cout << '\n';
		return 0;
	}
	if (noB == n && noG == 0) {
		for (int i = 0; i < n; ++i) std::cout << 'G';
		std::cout << '\n';
		return 0;
	}
	if (noB + noG > n || (n - noB - noG) % 2 != 0) bye();
	int g2b2 = (n - noB - noG) / 2;
	for (P = 1; P * 2 <= n; ++P) {
		int g1b1 = P * 2 - g2b2;
		int gexbex = noB + noG - g1b1;
		if (g1b1 < 0 || gexbex < 0) continue;
		bool can = false;
		for (int j = 0; j != 4; ++j) {
			int L = std::max(std::max(noG - gexbex, g1b1 - P), 0);
			int R = std::min(std::min(noG, g1b1), P);
			if (j & 1) {
				L = std::max(L, g1b1 - noB);
				R = std::min(R, g1b1 - noB);
			} else R = std::min(R, P - 1);
			if (j & 2) {
				L = std::max(L, noG);
				R = std::min(R, noG);
			} else L = std::max(L, g1b1 - P + 1);
			if (L <= R) {
				can = true;
				G1 = L, G2 = P - L;
				B1 = g1b1 - G1, B2 = P - B1;
				Bex = noG - G1;
				Gex = noB - B1;
				break;
			}
		}
		if (can) break;
	}
	if (P * 2 > n) bye();
	for (int i = 1; i <= P; ++i) {
		int c = i <= G2 ? 2 + (i == 1) * Gex : G1 > 0;
		while (c --> 0) std::cout << 'G';
		c = i <= B2 ? 2 + (i == 1) * Bex : B1 > 0;
		while (c --> 0) std::cout << 'B';
	}
	std::cout << '\n';
	return 0;
}

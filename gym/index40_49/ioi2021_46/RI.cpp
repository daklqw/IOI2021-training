#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;
typedef long long LL;
int x[MAXN], y[MAXN], z[MAXN];
int n;
int cross(int a, int b) {
	return (x[a] & y[b]) ^ (x[b] & y[a]);
}
int hav[2][2][2];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> x[i] >> y[i];
		x[i] &= 1, y[i] &= 1;
	}
	int sm = 0;
	for (int i = 0; i < n; ++i)
		z[i] = sm ^= cross(i, (i + 1) % n);
	LL ans = 0;
	for (int i = 1; i < n; ++i) {
		if (i == n - 1)
			--hav[x[0]][y[0]][0];
		int tc = 0;
		for (int k = 0; k < 2; ++k)
			for (int l = 0; l < 2; ++l) {
				int cr = (x[i] & l) ^ (y[i] & k);
				for (int a = 0; a < 2; ++a) {
					int b = (z[i - 1] ^ a), c = sm ^ b;
					if ((cr ^ b) == 0 && (c ^ cr) == 0) {
						tc += hav[k][l][a];
					}
				}
			}
		ans += tc;
		++hav[x[i - 1]][y[i - 1]][i == 1 ? 0 : z[i - 2]];
	}
	std::cout << ans << std::endl;
	return 0;
}

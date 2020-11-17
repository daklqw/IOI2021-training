#include <bits/stdc++.h>

#define FILENAME "PE"
std::mt19937 rd(time(0) + (unsigned long) new char);
const int R = 4;
template<typename T> T rnd(T l, T r) { return l + rd() % (r - l); }
const int MAXN = 2e5 + 10;
int rk[MAXN];

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	freopen(FILENAME ".in", "w", stdout);
	int T = 10;
	std::cout << T << '\n';
	while (T --> 0) {
		int n = rd() % R + 1, P = rd() % n + 1;
		std::cout << n << ' ' << P << '\n';
		for (int i = 1; i <= n; ++i) {
			rk[i] = i;
			int v = (int) rd() % R;
			if (i == 1) v = std::abs(v);
			std::cout << v << ' ';
		}
		std::cout << '\n';
		std::shuffle(rk + 1, rk + 1 + n, rd);
		for (int i = 1; i < n; ++i)
			std::cout << rk[rd() % i + 1] << ' ' << rk[i + 1] << '\n';
	}
	return 0;
}

#include <bits/stdc++.h>

#define FILENAME "OJ"
std::mt19937 rd(time(0) + (unsigned long) new char);
const int R = 5;
template<typename T> T rnd(T l, T r) { return l + rd() % (r - l); }

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	freopen(FILENAME ".in", "w", stdout);
	int T = 1;
	std::cout << T << '\n';
	while (T --> 0) {
		int n = rd() % R + 2, m = R;
		// n = 1000, m = 1e5;
		std::cout << n << ' ' << m << '\n';
		for (int i = 1; i <= m; ++i) {
			int x, y;
			do x = rd() % n + 1, y = rd() % n + 1; while (x == y);
			std::cout << x << ' ' << y << ' ' << rd() % R + 1 << '\n';
		}
		int Q = 0;
		std::cout << Q << '\n';
	}
	return 0;
}

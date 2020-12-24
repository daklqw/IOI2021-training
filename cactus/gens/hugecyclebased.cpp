#include <bits/stdc++.h>

unsigned seed = time(0) + (unsigned long) new char;
std::mt19937 rd(seed);
const int R = 100000;
template<typename T> T rnd(T l, T r) { return l + rd() % (r - l); }

const int MAXN = 1e5 + 10;
int rk[MAXN];
int main(int argc, char ** argv) {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cerr << "Generating by seed " << seed << std::endl;
	int n = argc >= 2 ? strtol(argv[1], 0, 10) : rnd(3, R + 1);
	int m = n;
	int K = argc >= 3 ? strtol(argv[2], 0, 10) : (rd() % 10 < 9 ? 1 : rd() % n + 1);
	for (int i = 1; i <= n; ++i) rk[i] = i;
	std::cout << n << ' ' << m << ' ' << K << '\n';
	std::cerr << n << ' ' << m << ' ' << K << '\n';
	std::shuffle(rk + 1, rk + 1 + n, rd);
	for (int i = 1; i <= K; ++i)
		std::cout << rk[i] << (" \n" [i == K]);
	std::shuffle(rk + 1, rk + 1 + n, rd);
	for (int i = 1; i <= n / 2; ++i)
		std::cout << rk[i] << ' ' << rk[i == n / 2 ? 1 : i + 1] << '\n';
	for (int i = n / 2 + 1; i <= n; ++i) {
		int u = i, v = rd() % (i - 1) + 1;
		std::cout << rk[u] << ' ' << rk[v] << '\n';
	}
	return 0;
}

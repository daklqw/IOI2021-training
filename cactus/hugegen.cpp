#include <bits/stdc++.h>

#define FILENAME "cactus"
unsigned seed = time(0) + (unsigned long) new char;
std::mt19937 rd(seed);
const int R = 500;
template<typename T> T rnd(T l, T r) { return l + rd() % (r - l); }

const int MAXN = 1e5 + 10;
int rk[MAXN];
int cnt;
std::vector<int> hav[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	freopen(FILENAME ".in", "w", stdout);
	std::cerr << "Generating by seed " << seed << std::endl;
	int n = rd() % R + 2, m = 0, K = rd() % n + 1;
	n = 1e5;
	if (rd() % 10 < 4) K = 1;
	for (int i = 1; i <= n; ++i) rk[i] = i;
	for (int i = 2; i <= n; ++i) {
		int typ = rd() % 2 + 1;
		if (!cnt) typ = 1;
		if (typ == 1) {
			int u = rd() % (i - 1) + 1;
			++cnt;
			hav[cnt].push_back(u);
			hav[cnt].push_back(i);
		} else {
			int u = rd() % cnt + 1;
			hav[u].push_back(i);
		}
	}
	for (int i = 1; i <= cnt; ++i)
		m += hav[i].size() == 2 ? 1 : hav[i].size();
	std::cout << n << ' ' << m << ' ' << K << '\n';
	std::cerr << n << ' ' << m << ' ' << K << '\n';
	std::shuffle(rk + 1, rk + 1 + n, rd);
	for (int i = 1; i <= K; ++i)
		std::cout << rk[i] << (" \n" [i == K]);
	std::shuffle(rk + 1, rk + 1 + n, rd);
	for (int i = 1; i <= cnt; ++i) {
		for (int j = hav[i].size() == 2; j < hav[i].size(); ++j) {
			int u = hav[i][j], v = hav[i][(j + 1) % hav[i].size()];
			u = rk[u];
			v = rk[v];
			std::cout << u << ' ' << v << '\n';
		}
	}
	return 0;
}

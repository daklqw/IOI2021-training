#include <bits/stdc++.h>

unsigned seed = time(0) + (unsigned long) new char;
std::mt19937 rd(seed);
const int R = 100000;
template<typename T> T rnd(T l, T r) { return l + rd() % (r - l); }

const int MAXN = 1e5 + 10;
int rk[MAXN];
int cnt, yes[MAXN];
std::vector<int> hav[MAXN], li;
int main(int argc, char ** argv) {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cerr << "Generating by seed " << seed << std::endl;
	int n = argc >= 2 ? strtol(argv[1], 0, 10) : 100000;
	int m = 0;
	int K = argc >= 3 ? strtol(argv[2], 0, 10) : rd() % n + 1;
	for (int i = 1; i <= n; ++i) rk[i] = i;
	for (int i = 2; i <= n; ++i) {
		if (i % 2 == 0) {
			int u = rd() % (i - 1) + 1;
			++cnt;
			hav[cnt].push_back(u);
			hav[cnt].push_back(i);
		} else
			hav[cnt].push_back(i);
	}
	for (int i = 1; i <= cnt; ++i) {
		m += hav[i].size() == 2 ? 1 : hav[i].size();
		if (hav[i].size() > 2) {
			int v = rd() % hav[i].size();
			yes[hav[i][v]] = true;
		}
	}
	for (int i = 1; i <= n; ++i)
		if (yes[i])
			li.push_back(i);
	if (li.empty()) li.push_back(rd() % n + 1);
	K = li.size();
	std::cout << n << ' ' << m << ' ' << K << '\n';
	std::cerr << n << ' ' << m << ' ' << K << '\n';
	std::shuffle(rk + 1, rk + 1 + n, rd);
	for (int i = 0; i < K; ++i)
		std::cout << rk[li[i]] << (" \n" [i == K - 1]);
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

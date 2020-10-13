#include <bits/stdc++.h>

const int MAXN = 20;
void solve(int * out, int * val, int n, int * li, int & bak) {
	const int U = 1 << n;
	static int dg[1 << MAXN], sm[1 << MAXN], cant[1 << MAXN];
	memset(dg, 0, U << 2);
	memset(sm, 0, U << 2);
	memset(cant, 0, U << 2);
	for (int i = 0; i != U; ++i) {
		if (i) {
			const int v = __builtin_ctz(i);
			dg[i] = dg[i & i - 1] | out[v];
			sm[i] = sm[i & i - 1] + val[v];
			if (__builtin_popcount(i) > __builtin_popcount(dg[i]))
				cant[i] = true;
		}
		if (cant[i]) {
			for (int j = 0; j < n; ++j)
				cant[i | 1 << j] = true;
			continue;
		}
		li[bak++] = sm[i];
	}
}
int os[MAXN], ot[MAXN];
int vs[MAXN], vt[MAXN];
int n, m;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		static char buf[MAXN + 10];
		std::cin >> buf;
		for (int j = 0; j < m; ++j)
			if (buf[j] == '1') {
				os[i] |= 1 << j;
				ot[j] |= 1 << i;
			}
	}
	for (int i = 0; i < n; ++i)
		std::cin >> vs[i];
	for (int i = 0; i < m; ++i)
		std::cin >> vt[i];
	int T; std::cin >> T;
	int lbak = 0, rbak = 0;
	static int lhs[1 << MAXN], rhs[1 << MAXN];
	solve(os, vs, n, lhs, lbak);
	solve(ot, vt, m, rhs, rbak);
	std::sort(lhs, lhs + lbak);
	std::sort(rhs, rhs + rbak);
	int rcur = rbak - 1;
	long long ans = 0;
	for (int i = 0; i < lbak; ++i) {
		while (rcur >= 0 && lhs[i] + rhs[rcur] >= T) --rcur;
		ans += rbak - rcur - 1;
	}
	std::cout << ans << std::endl;
	return 0;
}

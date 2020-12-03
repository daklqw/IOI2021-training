#include <bits/stdc++.h>

const int MAXN = 1e6 + 10;

int n, P, C, tar;
int f[MAXN], g[MAXN];
int A[MAXN], B[MAXN];
bool solve(int cho, int mt) {
	int tc = f[tar], mc = f[mt], oc = n - tc - mc;
	if (cho != tar) {
		if (cho == mt) --mc;
		else --oc;
		++tc;
	}
	for (int i = 1; i <= P; ++i) {
		if (B[i] == tar) {
			if (!tc) {
				if (!oc) --mc;
				else --oc;
				++tc;
			}
		} else if (B[i] == mt) {
			if (tc) --tc, ++mc;
			else if (oc) --oc, ++mc;
		} else {
			if (tc) --tc, ++oc;
			else if (!oc) --mc, ++oc;
		}
	}
	return tc > mc;
}
int main() {
#define FILENAME "kabaleo"
#ifdef FILENAME
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> P >> C >> tar;
	for (int i = 1; i <= n; ++i)
		std::cin >> A[i], ++f[A[i]];
	for (int i = 1; i <= P; ++i)
		std::cin >> B[i], ++g[B[i]];
	int fir = 0, sec = 0;
	for (int i = 1; i <= C; ++i) if (i != tar) {
		int v = f[i] + g[i];
		if (v >= fir) sec = fir, fir = v;
		else sec = std::max(sec, v);
	}
	bool fc = false, sc = false, ac = false;
	for (int i = 1; i <= C; ++i)
		if (i != tar && f[i] + g[i] == fir) {
			bool found = false;
			for (int j = 1; j <= C; ++j)
				if (j != i && j != tar && f[j] + g[j] == sec) {
					found = true;
					if (solve(i, i) && solve(i, j))
						fc = true;
					if (solve(j, i))
						sc = true;
					if (solve(tar, i))
						ac = true;
					break;
				}
			if (!found) {
				fc = solve(i, i);
				ac = solve(tar, i);
			}
			break;
		}
	static int li[MAXN];
	int bak = 0;
	for (int i = 1; i <= n; ++i) {
		int c = A[i];
		if (c == tar) {
			if (ac) li[++bak] = i;
		} else {
			if (f[c] + g[c] == fir) {
				if (fc) li[++bak] = i;
			} else if (sc) li[++bak] = i;
		}
	}
	std::cout << bak << '\n';
	for (int i = 1; i <= bak; ++i)
		std::cout << li[i] << (" \n" [i == bak]);
	return 0;
}

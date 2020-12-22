#include <bits/stdc++.h>

const int MAXN = 100;
typedef std::vector<int> VI;
VI ansl;
int sm;
#define ppc __builtin_popcount
int li[MAXN], pc[MAXN];
int calc(int x) {
	return (x & (x - 1)) == 0 ? __builtin_ctz(x) : 12243;
}
bool solve(int S) {
	if (li[S] == sm) {
		ansl = VI(li + 1, li + 1 + S);
		return true;
	}
	int ex = 0, lst = li[S];
	for (int t = li[S]; t < sm; t <<= 1, ++ex) lst = t;
	bool can = false;
	for (int i = 1; i <= S && !can; ++i)
		if ((sm - lst) % li[i] == 0)
			if (calc((sm - lst) / li[i]) < ex)
				can = true;
	if (!can) ++ex;
	if (S + ex >= (int) ansl.size()) return false;
	for (int j = S; j; --j) {
		int V = li[S] + li[j];
		if (V > sm) continue;
		pc[S + 1] = ppc(V);
		if (pc[S + 1] > 4) continue;
		if (pc[S + 1] != pc[S] + pc[j]) {
			if (!(li[j] <= 3 || li[S] - li[j] <= 3 || li[S] == li[j] * 2))
				continue;
		}
		li[S + 1] = V;
		if (solve(S + 1)) return true;
	}
	return false;
}
int main() {
#define FILENAME "dividing"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	li[1] = 1, li[2] = 2;
	pc[1] = pc[2] = 1;
	while (T --> 0) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		sm = (1 << a) + (1 << b) + (1 << c) + (1 << d);
		for (int i = 0; (1 << i) <= sm; ++i)
			ansl.push_back(1 << i);
		for (int i = sm; i & (i - 1); i &= i - 1)
			ansl.push_back(i);
		solve(2);
		std::sort(ansl.begin(), ansl.end());
		int E = (int) ansl.size() - 1;
		std::cout << E << '\n';
		for (int i = E; i; --i) {
			bool hav = false;
			for (int j = 0; j < i && !hav; ++j)
				for (int k = 0; k < i && !hav; ++k)
					if (ansl[j] + ansl[k] == ansl[i]) {
						std::cout << ansl[i] << ' ' << ansl[j] << ' ' << ansl[k] << '\n';
						hav = true;
					}
		}
		std::cout.flush();
		ansl.clear();
		std::cerr << "NOW " << T << ' ' << clock() / (double) CLOCKS_PER_SEC << std::endl;
	}
	return 0;
}

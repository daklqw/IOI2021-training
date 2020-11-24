#include <bits/stdc++.h>

const int MAXN = 510;
typedef long long LL;
typedef std::pair<int, int> pi;

int hav[MAXN]; LL sc[MAXN];
int n, m;
int lst[MAXN], ansl[MAXN];
pi calc(int L, int x, int y) {
	int R = std::min(lst[x], lst[y]);
	if (L >= R) return pi();
	// std::cout << "NOW " << L << ' ' << R << ' ' << x << ' ' << y << " : ";
	LL d = sc[y] - sc[x];
	int b = hav[x] - hav[y];
	if (!b) {
		if (d > 0) return pi(L, R);
		return pi();
	}
	if (b < 0) {
		b = -b, d = -d;
		LL at = d / b + 1;
		if (at > R) return pi();
		return pi((int)std::max<LL>(at, L), R);
	}
	LL at = d / b + (d % b != 0);
	if (at < L) return pi();
	return pi(L, (int)std::min<LL>(at, R));
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	std::vector<pi> A, V;
	for (int i = 1; i <= n; ++i)
		for (int j = 1, t; j <= m; ++j) {
			std::cin >> t;
			sc[i] += t;
			V.emplace_back(t, i);
		}
	V.emplace_back(0, 0);
	std::sort(V.begin(), V.end());
	static LL os[MAXN];
	memcpy(os, sc, n + 1 << 3);
	for (int i = 1; i <= n; ++i) {
		A.clear();
		for (int j = 1; j <= n; ++j)
			lst[j] = 1e9 + 1;
		memcpy(sc, os, n + 1 << 3);
		memset(hav, 0, n + 1 << 2);
		V[0].second = i;
		for (int T = (int) V.size() - 1; ~T; --T) {
			int x, d;
			std::tie(d, x) = V[T];
			int lb = x, ub = x;
			if (i == x) lb = 1, ub = n;
			for (int j = lb; j <= ub; ++j) if (j != i) {
				auto r = calc(std::max(d, 1), i, j);
				// std::cout << r.first << ' ' << r.second << std::endl;
				if (r.first >= r.second) continue;
				A.emplace_back(r.first, 1);
				A.emplace_back(r.second, -1);
			}
			sc[x] -= d;
			lst[x] = d;
			++hav[x];
		}
		std::sort(A.begin(), A.end());
		int lst = 0, val = 0;
		for (auto t : A) {
			if (t.first != lst)
				ansl[i] = std::max(ansl[i], val);
			lst = t.first;
			val += t.second;
		}
	}
	for (int i = 1; i <= n; ++i)
		std::cout << (n - ansl[i]) << '\n';
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 3e5 + 10;

struct _ {
	int x, y, v;
	bool operator < (_ b) const {
		return v < b.v;
	}
} es[MAXN];
int n, m;
int ansp[MAXN], anse[MAXN];
int fa[MAXN], val[MAXN];
int deg[MAXN];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i)
		std::cin >> es[i].x >> es[i].y >> es[i].v;
	std::sort(es + 1, es + 1 + m);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	int c2 = 0, cc = 0, cn = 0;
	for (int i = m; i; --i) {
		int x = es[i].x, y = es[i].y;
		cn += deg[x] == 0;
		if (x != y) cn += deg[y] == 0;
		c2 -= deg[x] == 2;
		c2 -= deg[y] == 2;
		int fx = find(x), fy = find(y);
		cc -= val[fx] == 1;
		if (fx != fy)
			cc -= val[fy] == 1;
		++deg[x], ++deg[y];
		c2 += deg[x] == 2;
		c2 += deg[y] == 2;
		if (fx == fy)
			++val[fx];
		else {
			val[fx] += val[fy];
			fa[fy] = fx;
		}
		if (deg[x] == 3)
			val[find(x)] = 12243;
		if (deg[y] == 3)
			val[find(y)] = 12243;
		cc += val[find(x)] == 1;
		ansp[i] = cn - c2 + cc;
		anse[i] = (m - i + 1) - c2 + cc;
	}
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int k; std::cin >> k;
		int l = 0, r = m + 1;
		while (l + 1 < r) {
			int mid = l + r >> 1;
			(es[mid].v >= k ? r : l) = mid;
		}
		std::cout << ansp[r] << ' ' << anse[r] << '\n';
	}
	return 0;
}

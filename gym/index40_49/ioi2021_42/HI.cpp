#include <bits/stdc++.h>

const int MAXN = 2.5e5 + 10;
typedef long long LL;
const LL INF = 2e12;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], vt[MAXN << 1], tot;
void adde(int b, int e, int v) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e; vt[tot] = v;
	nxt[++tot] = head[e]; to[head[e] = tot] = b; vt[tot] = v;
}
LL dep[MAXN];
const int MAXP = 2e6;
int ls[MAXP], rs[MAXP], idx; LL val[MAXP];
int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (val[x] > val[y]) std::swap(x, y);
	rs[x] = merge(rs[x], y);
	std::swap(ls[x], rs[x]);
	return x;
}
int rt1[MAXN], rt2[MAXN];
int cnt[MAXN];
int newnode(LL v) {
	val[++idx] = v; return idx;
}
LL ans;
void dfs(int u, int fa) {
	if (cnt[u] > 0) for (int i = 1; i <= cnt[u]; ++i)
		rt1[u] = merge(rt1[u], newnode(dep[u] - INF));
	else for (int i = 1; i <= -cnt[u]; ++i)
		rt2[u] = merge(rt2[u], newnode(dep[u]));
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa) {
			dep[to[i]] = dep[u] + vt[i];
			dfs(to[i], u);
			rt1[u] = merge(rt1[u], rt1[to[i]]);
			rt2[u] = merge(rt2[u], rt2[to[i]]);
		}
	while (rt1[u] && rt2[u]) {
		int x = rt1[u], y = rt2[u];
		LL tv = val[x] + val[y] - dep[u] * 2;
		if (tv < 0) {
			ans += tv;
			rt1[u] = merge(ls[x], rs[x]);
			rt2[u] = merge(ls[y], rs[y]);
			ls[x] = ls[y] = rs[x] = rs[y] = 0;
			val[x] -= tv; val[y] -= tv;
			rt1[u] = merge(rt1[u], x);
			rt2[u] = merge(rt2[u], y);
		} else break;
	}
}
int n;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, b, e, v; i < n; ++i)
		std::cin >> b >> e >> v, adde(b, e, v);
	int all = 0;
	for (int i = 1; i <= n; ++i) {
		int x, y; std::cin >> x >> y;
		all += std::max(cnt[i] = y - x, 0);
	}
	dfs(1, 0);
	ans += INF * all;
	std::cout << ans << std::endl;
	return 0;
}

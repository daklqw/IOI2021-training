#include <bits/stdc++.h>

const int MAXN = 2010;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int isc[MAXN][MAXN];
int forb;
int n, m;
int low[MAXN], dfn[MAXN], idx;
void tarjan(int u, int * tar, int fa) {
	low[u] = dfn[u] = ++idx;
	for (int i = head[u]; i; i = nxt[i])
		if ((i >> 1) != fa && (i >> 1) != forb) {
			if (!dfn[to[i]]) {
				tarjan(to[i], tar, i >> 1);
				low[u] = std::min(low[u], low[to[i]]);
				if (dfn[u] < low[to[i]])
					tar[i >> 1] = true;
			} else
				low[u] = std::min(low[u], dfn[to[i]]);
		}
}
int fa[MAXN], sz[MAXN];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1, b, e; i <= m; ++i)
		std::cin >> b >> e, adde(b, e);
	for (int i = 0; i <= m; ++i) {
		fa[i] = forb = i;
		memset(dfn, 0, n + 1 << 2);
		idx = 0;
		for (int j = 1; j <= n; ++j)
			if (!dfn[j])
				tarjan(j, isc[i], 0);
	}
	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= m; ++j)
			if (!isc[0][j] && isc[i][j])
				fa[find(i)] = find(j);
	for (int i = 1; i <= m; ++i)
		if (!isc[0][i])
			++sz[find(i)];
	int ans = 0;
	for (int i = 1; i <= m; ++i)
		ans = gcd(ans, sz[i]);
	for (int i = 1; i <= m; ++i)
		if (ans % i == 0)
			std::cout << i << (" \n" [i == ans]);
	return 0;
}

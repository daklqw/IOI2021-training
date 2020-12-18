#include <bits/stdc++.h>

const int MAXN = 1010;

int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int lca[MAXN][MAXN];
int dep[MAXN], fa[MAXN];
int LCA(int x, int y) {
	if (x == y) return x;
	if (lca[x][y]) return lca[x][y];
	return lca[x][y] = dep[x] <= dep[y] ? LCA(x, fa[y]) : LCA(fa[x], y);
}
void dfs(int u) {
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			fa[to[i]] = u;
			dep[to[i]] = dep[u] + 1;
			dfs(to[i]);
		}
}
typedef std::pair<int, int> pi;
std::vector<pi> hav[MAXN];
int tr[MAXN], bel[MAXN];
int n;
void gma(int & x, int y) {
	x < y ? x = y : 0;
}
int g[MAXN][1 << 10];
int deg[MAXN], rnk[MAXN];
inline int all(int x) {
	return g[x][(1 << deg[x]) - 1];
}
void predo(int u, int b, int s) {
	bel[u] = b;
	const int U = 1 << deg[u];
	tr[u] = s + g[u][U - 1];
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			int v = U - 1 - (1 << rnk[to[i]]);
			predo(to[i], b, s + g[u][v]);
		}
}
void solve(int u) {
	int cnt = 0;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			solve(to[i]);
			++cnt;
		}
	deg[u] = cnt;
	static int mat[MAXN][MAXN];
	for (int i = 0; i <= cnt; ++i)
		memset(mat[i], 0xc0, (cnt + 1) << 2);
	cnt = 0;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			gma(mat[cnt][cnt], all(to[i]));
			predo(to[i], rnk[to[i]] = cnt++, 0);
		}
	for (auto t : hav[u]) {
		int x = t.first, y = t.second;
		if (dep[x] < dep[y]) std::swap(x, y);
		int bx = bel[x], by = bel[y];
		if (y == u) {
			int v = tr[x] + 1;
			gma(mat[bx][bx], v);
		} else {
			int v = tr[x] + tr[y] + 1;
			gma(mat[bx][by], v);
			gma(mat[by][bx], v);
		}
	}
	const int U = 1 << cnt;
	int * f = g[u];
	memset(f, 0xcf, U << 2);
	f[0] = 0;
	for (int i = 0; i + 1 != U; ++i)
		for (int j = 0; j != cnt; ++j) if (!(i >> j & 1)) {
			for (int k = j; k != cnt; ++k) if (!(i >> k & 1))
				gma(f[i | 1 << j | 1 << k], f[i] + mat[j][k]);
		}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> n;
		for (int i = 1, b, e; i < n; ++i)
			std::cin >> b >> e, adde(b, e);
		for (int i = 1; i <= n; ++i)
			memset(lca[i], 0, (n + 1) << 2);
		dfs(1);
		int m; std::cin >> m;
		for (int i = 1, u, v; i <= m; ++i) {
			std::cin >> u >> v;
			hav[LCA(u, v)].emplace_back(u, v);
		}
		solve(1);
		std::cout << all(1) << '\n';
		for (int i = 1; i <= n; ++i) hav[i].clear();
		memset(fa, 0, (n + 1) << 2);
		tot = 0;
		memset(head, 0, (n + 1) << 2);
	}
	return 0;
}

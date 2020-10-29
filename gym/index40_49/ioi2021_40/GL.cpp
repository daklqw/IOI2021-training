#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
int tr[MAXN << 2];
int tag[MAXN << 2];
void mkset(int u, int v) {
	tr[u] = tag[u] = v;
}
int merge(int x, int y) {
	return x == y ? x : -1;
}
void pushdown(int u) {
	if (tag[u]) {
		mkset(u << 1, tag[u]);
		mkset(u << 1 | 1, tag[u]);
		tag[u] = 0;
	}
}

int all;
void mdf(int u, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) {
		if (all == 0)
			all = tr[u];
		else
			all = merge(all, tr[u]);
		return mkset(u, v);
	}
	int mid = l + r >> 1;
	pushdown(u);
	if (L <= mid) mdf(u << 1, l, mid, L, R, v);
	if (mid < R) mdf(u << 1 | 1, mid + 1, r, L, R, v);
	tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
}
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int fa[MAXN], sz[MAXN], top[MAXN], dep[MAXN], son[MAXN], dfn[MAXN];
void dfs(int u) {
	sz[u] = 1;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			fa[to[i]] = u;
			dep[to[i]] = dep[u] + 1;
			dfs(to[i]);
			sz[u] += sz[to[i]];
			if (sz[to[i]] > sz[son[u]])
				son[u] = to[i];
		}
}
void hld(int u) {
	static int idx;
	dfn[u] = ++idx;
	if (son[u]) {
		top[son[u]] = top[u];
		hld(son[u]);
	}
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u] && to[i] != son[u]) {
			top[to[i]] = to[i];
			hld(to[i]);
		}
}
int LCA(int x, int y) {
	while (top[x] != top[y])
		dep[top[x]] > dep[top[y]] ? x = fa[top[x]] : y = fa[top[y]];
	return dep[x] < dep[y] ? x : y;
}
int n, m;
void mdf(int x, int y, int v) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]])
			std::swap(x, y);
		mdf(1, 1, n, dfn[top[x]], dfn[x], v);
		x = fa[top[x]];
	}
	if (dep[x] < dep[y]) std::swap(x, y);
	mdf(1, 1, n, dfn[y], dfn[x], v);
}
struct _ {
	int x, y, L;
	bool operator < (_ b) const {
		return L > b.L;
	}
	void calc() {
		L = dep[x] + dep[y] - dep[LCA(x, y)] * 2;
	}
} es[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1, x, y; i < n; ++i) {
		std::cin >> x >> y;
		adde(x, y);
	}
	dfs(1);
	top[1] = 1;
	hld(1);
	for (int i = 1; i <= m; ++i) {
		std::cin >> es[i].x >> es[i].y;
		es[i].calc();
	}
	std::sort(es + 1, es + 1 + m);
	mkset(1, 114514);
	for (int i = 1; i <= m; ++i) {
		all = 0;
		mdf(es[i].x, es[i].y, i);
		if (all == -1) {
			std::cout << "No" << std::endl;
			return 0;
		}
	}
	std::cout << "Yes" << std::endl;
	return 0;
}

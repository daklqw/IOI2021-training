#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
struct _ {
	int v, d, tag, l, r;
} tr[MAXN];
void mkadd(int u, int v) {
	tr[u].v += v;
	tr[u].tag += v;
}
void pushdown(int u) {
	if (int & t = tr[u].tag) {
		if (tr[u].l) mkadd(tr[u].l, t);
		if (tr[u].r) mkadd(tr[u].r, t);
		t = 0;
	}
}
int merge(int a, int b) {
	if (!a || !b) return a | b;
	pushdown(a); pushdown(b);
	if (tr[a].v > tr[b].v) std::swap(a, b);
	tr[a].r = merge(tr[a].r, b);
	std::swap(tr[a].l, tr[a].r);
	return a;
}
int can[MAXN];
bool vis[MAXN];
int A[MAXN];
int fa[MAXN];
int dfs(int u, int dep = 0) {
	dep += A[u];
	int rt = 0;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			fa[to[i]] = u;
			rt = merge(rt, dfs(to[i], dep));
		}
	tr[u].d = dep;
	if (A[u] < 0) {
		mkadd(rt = merge(rt, u), -A[u]);
		while (rt && tr[rt].d < dep - A[u])
			rt = merge(tr[rt].l, tr[rt].r);
		can[u] = rt ? tr[rt].v : 0x3f3f3f3f;
	} else rt = u;
	return rt;
}
typedef std::pair<int, int> pi;
std::priority_queue<pi> que;
int all;
void add(int u) {
	std::cerr << "ADD " << u << std::endl;
	all += A[u];
	vis[u] = true;
	for (int i = head[u]; i; i = nxt[i])
		if (!vis[to[i]])
			que.emplace(-can[to[i]], to[i]);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int n, T;
		std::cin >> n >> T;
		for (int i = 1; i <= n; ++i)
			std::cin >> A[i];
		for (int i = 1, x, y; i < n; ++i)
			std::cin >> x >> y, adde(x, y);
		dfs(1);
		static int li[MAXN]; int bak = 0;
		while (T) li[++bak] = T, T = fa[T];
		while (bak) {
			int u = li[bak--];
			if (vis[u]) continue;
			add(u);
			if (all < 0) break;
			while (!que.empty()) {
				auto p = que.top();
				if (p.first + all < 0) break;
				que.pop();
				add(p.second);
			}
		}
		std::cout << (all >= 0 ? "escaped" : "trapped") << '\n';
		while (!que.empty()) que.pop();
		all = 0;
		memset(head, 0, n + 1 << 2);
		memset(fa, 0, n + 1 << 2);
		memset(can, 0, n + 1 << 2);
		memset(vis, 0, n + 1);
		memset(tr, 0, (n + 1) * sizeof(_));
		tot = 0;
	}
	return 0;
}

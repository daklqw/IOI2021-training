#include <bits/stdc++.h>

const int MAXN = 3010;
const int MAXM = 9010;
typedef unsigned long long LL;
int head[MAXN], nxt[MAXM], to[MAXM], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}

std::mt19937_64 rd(time(0));
int n, m;

int bel[MAXN];
int idx, cnt, forb;
int low[MAXN], dfn[MAXN], st[MAXN], top;
void tarjan(int u, int fa) {
	low[u] = dfn[u] = ++cnt;
	st[++top] = u;
	for (int i = head[u]; i; i = nxt[i])
		if ((i >> 1) != fa && (i >> 1) != forb) {
			if (!dfn[to[i]]) {
				tarjan(to[i], i >> 1);
				low[u] = std::min(low[u], low[to[i]]);
			} else low[u] = std::min(low[u], dfn[to[i]]);
		}
	if (low[u] == dfn[u]) {
		int v; ++idx;
		do bel[v = st[top--]] = idx; while (v != u);
	}
}
LL val[MAXN], func[MAXN];
void solve() {
	memset(dfn, 0, n + 1 << 2);
	idx = cnt = 0;
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i, 0);
	for (int i = 1; i <= idx; ++i)
		func[i] = rd();
	for (int i = 1; i <= n; ++i)
		val[i] ^= func[bel[i]];
}

int fa[MAXN];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
template<typename T>
int calc(T * li) {
	std::sort(li + 1, li + 1 + n);
	int res = 0;
	for (int l = 1, r; l <= n; l = r) {
		r = l;
		while (r <= n && li[r] == li[l]) ++r;
		res += (r - l) * (r - l - 1) / 2;
	}
	return res;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1, b, e; i <= m; ++i) {
		std::cin >> b >> e, adde(b, e);
		fa[find(b)] = find(e);
	}
	for (int i = 1; i <= n; ++i) find(i);
	for (int i = 1; i <= m; ++i)
		forb = i, solve();
	forb = 0;
	solve();
	int ans = calc(fa) + calc(val) + calc(bel);
	std::cout << ans << std::endl;
	return 0;
}

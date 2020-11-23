#include <bits/stdc++.h>

const int MAXN = 5e5 + 10;
const int MAXP = MAXN << 1;
typedef long long LL;

int head[MAXP], nxt[MAXP], val[MAXP];
void adde(int b, int e) {
	nxt[e] = head[b]; head[b] = e;
}
int fa[MAXP], son[MAXP], ansl[MAXP];
char buf[MAXN][12];
int n, m;
bool set[MAXP];
LL dp[MAXP], out[MAXP], li[MAXP];
int bak;
int lb(LL x) {
	return std::lower_bound(li + 1, li + 1 + bak, x) - li;
}
void dfs1(int u) {
	if (u > m) {
		out[u] = dp[u] = val[u];
		return ;
	}
	LL ma = 0, mi = 0x3f3f3f3f3f3f3f3fLL;
	for (int i = head[u]; i; i = nxt[i]) {
		dfs1(i);
		dp[u] = std::max(dp[i], dp[u]);
		if (dp[i] > ma) {
			ma = dp[i];
			son[u] = i;
		}
		mi = std::min(out[i], mi);
	}
	out[u] = mi + val[u];
	dp[u] = std::max(dp[u], out[u]);
}
int tr[MAXP];
void add(int x, int v) {
	for (; x; x &= x - 1)
		tr[x] += v;
}
int qry(int x) {
	int r = 0;
	for (; x <= bak; x += x & -x)
		r += tr[x];
	return r;
}
void dfs2(int u, LL sm) {
	sm += val[u];
	add(dp[u], -1);
	if (u > m) {
		int at = lb(sm + 1);
		ansl[u - m] = qry(at) + 1;
	} else {
		add(dp[son[u]], 1);
		for (int i = head[u]; i; i = nxt[i])
			dfs2(i, sm);
		add(dp[son[u]], -1);
	}
	add(dp[u], 1);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::cin >> buf[i] >> fa[i + m] >> val[i + m];
		adde(fa[i + m], i + m);
	}
	for (int i = 1; i <= m; ++i) {
		std::cin >> fa[i] >> val[i];
		adde(fa[i], i);
	}
	const int N = n + m;
	dfs1(0);
	std::copy(dp, dp + N + 1, li + 1);
	bak = N + 1;
	std::sort(li + 1, li + 1 + bak);
	bak = std::unique(li + 1, li + 1 + bak) - li - 1;
	for (int i = 0; i <= N; ++i) {
		dp[i] = lb(dp[i]);
		add(dp[i], 1);
	}
	for (int i = 0; i <= m; ++i)
		add(dp[son[i]], -1);
	dfs2(0, 0ll);
	for (int i = 1; i <= n; ++i)
		std::cout << buf[i] << ' ' << ansl[i] << '\n';
	return 0;
}

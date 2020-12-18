#include <bits/stdc++.h>

const int MAXN = 300010;
const int mod = 1e9 + 7;
void reduce(int & x) { x += x >> 31 & mod; }

void bye() {
	std::cout << 0 << std::endl;
	exit(0);
}

int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int n;
int dp[MAXN], dep[MAXN], fa[MAXN], len[MAXN];
int d2s[MAXN];
int deg[MAXN], son[MAXN][2];
int down(int u, int d) {
	while (d --> 0) u = son[u][0];
	return u;
}
int calc(int u, int v) {
	if (d2s[u]) std::swap(u, v);
	if (d2s[u]) return 0;
	if (d2s[v]) {
		int L = dep[d2s[v]] - dep[v];
		if (len[u] > L) return 0;
	} else if (len[u] >= len[v]) {
		std::swap(u, v);
		if (len[u] == len[v]) return 1;
	}
	return dp[down(v, len[u])];
}
void dfs(int u) {
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			fa[to[i]] = u;
			dep[to[i]] = dep[u] + 1;
			dfs(to[i]);
			if (++deg[u] > 2) bye();
			son[u][deg[u] - 1] = to[i];
			len[u] = std::max(len[u], len[to[i]]);
		}
	++len[u];
	if (!deg[u]) {
		dp[u] = 1;
		return ;
	}
	if (deg[u] == 2) {
		d2s[u] = u;
		for (int i = 0; i < 2; ++i) {
			int v = son[u][i], w = son[u][i ^ 1];
			if (len[v] > 1) {
				if (deg[v] == 1)
					reduce(dp[u] += calc(w, son[v][0]) - mod);
			} else {
				reduce(dp[u] += dp[w] - mod);
			}
		}
	} else {
		int v = son[u][0];
		d2s[u] = d2s[v];
		reduce(dp[u] += dp[v] - mod);
		if (deg[v] == 0) reduce(dp[u] += dp[v] - mod);
		else if (deg[v] == 1)
			reduce(dp[u] += dp[son[v][0]] - mod);
		if (d2s[v]) {
			int L = dep[d2s[v]] - dep[u];
			for (int i = 0; i < 2; ++i) {
				int p = son[d2s[v]][i], q = son[d2s[v]][i ^ 1];
				if (deg[p] == 1) {
					if (len[son[p][0]] == L && !d2s[son[p][0]])
						reduce(dp[u] += dp[q] - mod);
				} else if (deg[p] == 2) {
					for (int j = 0; j < 2; ++j) {
						int x = son[p][j], y = son[p][j ^ 1];
						if (len[x] == L && !d2s[x])
							reduce(dp[u] += calc(y, q) - mod);
					}
				}
			}
			for (int i = 0; i < 2; ++i) {
				int p = son[d2s[v]][i], q = son[d2s[v]][i ^ 1];
				if (len[p] == L - 1 && !d2s[p])
					reduce(dp[u] += dp[q] - mod);
			}
		} else if (len[u] % 2 == 0 && len[u] > 2)
			reduce(dp[u] += 1 - mod);
	}
	// std::cerr << "DP " << u << " : " << dp[u] << std::endl;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, b, e; i < n; ++i)
		std::cin >> b >> e, adde(b, e);
	dfs(1);
	std::cout << dp[1] << std::endl;
	return 0;
}

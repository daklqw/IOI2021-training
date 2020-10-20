#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
void bye() {
	std::cout << "There is no route, Karl!" << std::endl;
	exit(0);
}
std::vector<int> out[MAXN];
int n, m, _, S;
int bel[MAXN], fa[MAXN];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int ind[MAXN], oud[MAXN];
int bot[MAXN];
int vis[MAXN];
int st[50];
void dfs(int u, int d = 0) {
	vis[u] = true;
	st[d] = u;
	for (auto t : out[u]) {
		int v = find(t);
		if (t != bot[v]) continue;
		if (__builtin_expect(d == _ - 1 && v == S, 0)) {
			std::vector<int> V;
			for (int i = 0; i <= d; ++i) {
				int x = bot[st[i]];
				while (x) {
					V.push_back(x);
					x = bel[x];
				}
			}
			auto at = std::find(V.begin(), V.end(), 1);
			std::rotate(V.begin(), at, V.end());
			for (auto x : V)
				std::cout << x << ' ';
			std::cout << 1 << '\n';
			exit(0);
		}
		if (vis[v]) continue;
		dfs(v, d + 1);
	}
	vis[u] = false;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m; _ = n;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 1, x, y; i <= m; ++i) {
		std::cin >> x >> y;
		out[x].push_back(y);
		++ind[y], ++oud[x];
		fa[find(x)] = find(y);
	}
	for (int i = 1; i <= n; ++i)
		if (find(i) != find(1))
			bye();
	for (int i = 1; i <= n; ++i)
		bot[i] = fa[i] = i;
	for (int i = 1; i <= n; ++i)
		if (ind[i] == 1 && oud[i] == 1) {
			int v = out[i][0];
			if (find(v) != i) {
				if (bot[find(v)] != v) bye();
				bel[i] = v;
				fa[i] = find(v);
				bot[find(v)] = bot[i];
				--_;
			}
		}
	assert(_ <= 40);
	S = find(1);
	dfs(S);
	bye();
	return 0;
}

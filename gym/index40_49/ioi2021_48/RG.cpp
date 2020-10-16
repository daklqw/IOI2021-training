#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
int head[MAXN], nxt[MAXN], fa[MAXN], bel[MAXN], sz[MAXN];
int n, m;
int ST[18][MAXN << 1], bak, in[MAXN];
int gmi(int x, int y) {
	return in[x] < in[y] ? x : y;
}
void dfs(int u) {
	ST[0][++bak] = u, in[u] = bak;
	for (int i = head[u]; i; i = nxt[i]) {
		dfs(i);
		ST[0][++bak] = u;
		sz[u] += sz[i];
	}
	if (!sz[u]) sz[u] = 1;
}
int LCA(int x, int y) {
	if (x > y) std::swap(x, y);
	const int L = std::__lg(++y - x);
	return gmi(ST[L][x], ST[L][y - (1 << L)]);
}
std::set<int> hav[MAXN];
int lst[MAXN];
int ans, ansc;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 2; i <= n; ++i) {
		std::cin >> fa[i];
		nxt[i] = head[fa[i]], head[fa[i]] = i;
		if (fa[i] == 1) bel[i] = i;
		else bel[i] = bel[fa[i]];
	}
	dfs(1);
	for (int i = 1; i != 18; ++i)
		for (int j = 1; j + (1 << i) - 1 <= bak; ++j)
			ST[i][j] = gmi(ST[i - 1][j], ST[i - 1][j + (1 << i - 1)]);
	while (m --> 0) {
		static char opt[10]; int u;
		std::cin >> opt >> u;
		const int B = bel[u];
		if (hav[B].size())
			--ans, ansc -= sz[lst[B]] - hav[B].size();
		if (*opt == '+') hav[B].insert(in[u]);
		else hav[B].erase(in[u]);
		if (hav[B].size()) {
			lst[B] = LCA(*hav[B].begin(), *hav[B].rbegin());
			++ans, ansc += sz[lst[B]] - hav[B].size();
		}
		std::cout << ans << ' ' << ansc << '\n';
	}
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int n;
int dep[MAXN];
int istop[MAXN], isend[MAXN];
std::vector<std::string> ansl;
#define its std::to_string
void color(int u, int x, int y) {
	ansl.emplace_back("r " + its(u) + " " + its(x) + " " + its(y));
}
void link(int u, int x, int y) {
	ansl.emplace_back("c " + its(u) + " " + its(x) + " " + its(y));
}
void merge(int x, int y) {
	ansl.emplace_back("j " + its(x) + " " + its(y));
}
int st[MAXN], top;
int low[MAXN], dfn[MAXN];
std::vector<int> hav[MAXN], cir[MAXN];
int idx;
void tarjan(int u, int fa) {
	st[++top] = u;
	static int cnt;
	low[u] = dfn[u] = ++cnt;
	for (int i = head[u]; i; i = nxt[i])
		if ((i >> 1) != fa) {
			if (!dfn[to[i]]) {
				tarjan(to[i], i >> 1);
				low[u] = std::min(low[u], low[to[i]]);
				if (dfn[u] <= low[to[i]]) {
					int v; ++idx;
					cir[u].push_back(idx);
					do {
						v = st[top--];
						hav[idx].push_back(v);
					} while (v != to[i]);
				}
			} else
				low[u] = std::min(low[u], dfn[to[i]]);
		}
}
void solve(int u, bool spe = false) {
	color(u, 1, 3);
	for (auto x : cir[u]) {
		int lst = 0, sc = hav[x][0];
		if (hav[x].size() == 1) {
			solve(sc, false);
			merge(u, sc);
			continue;
		}
		for (auto v : hav[x]) {
			solve(v, v == sc);
			if (lst) {
				color(v, 2, 3);
				merge(lst, v);
				link(v, 3, lst == sc ? 4 : 2);
				color(v, 2, 1);
				color(v, 3, 2);
			}
			lst = v;
		}
		merge(lst, u);
	}
	link(u, 3, 2);
	link(u, 3, 4);
	color(u, 2, 1);
	color(u, 4, 1);
	color(u, 3, spe ? 4 : 2);
}
int main() {
#define FILENAME "cactus"
#ifdef FILENAME
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int m; std::cin >> n >> m;
	for (int i = 1, t, lst, p; i <= m; ++i)
		for (std::cin >> t, lst = 0; t; --t)
			std::cin >> p, lst ? adde(lst, p) : void(), lst = p;
	tarjan(1, 0);
	solve(1);
	std::cout << ansl.size() << '\n';
	for (auto t : ansl)
		std::cout << t << '\n';
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 100010;
typedef long long LL;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}

int n, m;
int fa[MAXN], fae[MAXN], dep[MAXN];
int bel[MAXN], sz[MAXN];
void dfs(int u) {
	sz[u] = 1;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			if (!dep[to[i]]) {
				fae[to[i]] = i;
				dep[to[i]] = dep[u] + 1;
				fa[to[i]] = u;
				dfs(to[i]);
				sz[u] += sz[to[i]];
			} else if (dep[u] > dep[to[i]]) {
				bel[i >> 1] = i >> 1;
				int now = u;
				while (now != to[i]) {
					bel[fae[now] >> 1] = i >> 1;
					now = fa[now];
				}
			}
		}
}
struct Dsu {
	int fa[MAXN];
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
} dsu;
int siz[MAXN];
std::vector<int> hav[MAXN];
LL C2(int x) {
	return (LL) x * (x - 1) / 2;
}
int main() {
#define FILENAME "cactus"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int t; std::cin >> t;
		int v = -1;
		for (int j = 1, u; j <= t; ++j) {
			std::cin >> u;
			if (j > 1) adde(u, v);
			v = u;
		}
	}
	dep[1] = 1; dfs(1);
	for (int i = 1; i <= n; ++i) dsu.fa[i] = i;
	LL ans = 0;
	for (int i = 2; i <= tot; i += 2)
		if (!bel[i >> 1]) {
			int x = to[i], y = to[i ^ 1];
			dsu.merge(x, y);
			if (dep[x] < dep[y]) std::swap(x, y);
			ans += (LL) sz[x] * (n - sz[x]);
		} else
			hav[bel[i >> 1]].push_back(i >> 1);
	for (int i = 1; i <= n; ++i) ++siz[dsu.find(i)];
	LL all = 0; int full = 0;
	for (int i = 1; i <= n; ++i)
		if (dsu.fa[i] == i) {
			all += C2(siz[i]);
			full += siz[i] - 1;
		}
	for (int i = 1; i <= tot / 2; ++i)
		if (hav[i].size()) {
			std::vector<int> li;
			for (auto t : hav[i]) {
				li.push_back(to[t * 2]);
				li.push_back(to[t * 2 + 1]);
			}
			std::sort(li.begin(), li.end());
			li.erase(std::unique(li.begin(), li.end()), li.end());
			LL way = all;
			int es = 0;
			for (auto t : li) {
				int s = siz[dsu.find(t)];
				way -= C2(s);
				es += s;
			}
			int ae = full + (int) li.size() - 1;
			ans += (way + C2(es) - ae) * li.size();
		}
	ans -= tot >> 1;
	std::cout << ans << std::endl;
	return 0;
}

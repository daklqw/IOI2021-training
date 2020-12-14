#include <bits/stdc++.h>

const int MAXN = 3e5 + 10;

struct _ {
	int x, y, id;
	bool operator < (_ b) const {
		return x < b.x;
	}
} ls[MAXN], ps[MAXN];
int fa[19][MAXN];
int head[MAXN], nxt[MAXN], ansl[MAXN];
void adde(int b, int e) {
	nxt[e] = head[b]; head[b] = e;
}
int n, m;
typedef std::pair<int, int> pi;
std::set<pi> S;
bool vis[MAXN];
void dfs(int u) {
	if (vis[u]) return ;
	vis[u] = true;
	for (int i = head[u]; i; i = nxt[i])
		dfs(i), ansl[u] += ansl[i];
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i)
		std::cin >> ls[i].x >> ls[i].y;
	std::sort(ls + 1, ls + 1 + n);
	std::cin >> m;
	for (int i = 1; i <= m; ++i) {
		std::cin >> ps[i].x >> ps[i].y;
		ps[i].id = i;
	}
	std::sort(ps + 1, ps + 1 + m);
	int cur = n;
	for (int it = m; ; --it) {
		int at = ps[it].x;
		while (cur && ls[cur].x > at) {
			auto ip = S.lower_bound(pi(ls[cur].y, 0));
			if (ip != S.end())
				++ansl[ip->second];
			--cur;
		}
		if (!it) break;
		auto t = pi(ps[it].y, ps[it].id);
		auto ip = S.lower_bound(t);
		if (ip != S.end()) {
			int u = ip->second, v = t.second;
			for (int i = 18; ~i; --i)
				if (fa[i][u] > v)
					u = fa[i][u];
			if (u > v) u = fa[0][u];
			if (u) adde(u, v);
			fa[0][v] = u;
			for (int j = 1; j < 19; ++j)
				fa[j][v] = fa[j - 1][fa[j - 1][v]];
		}
		while ((ip = S.lower_bound(t)) != S.begin()) {
			--ip;
			if (ip->second > t.second)
				S.erase(ip);
			else break;
		}
		S.insert(t);
	}
	for (int i = 1; i <= m; ++i) {
		if (!vis[i]) dfs(i);
		std::cout << ansl[i] << '\n';
	}
	return 0;
}

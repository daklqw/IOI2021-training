#include <bits/stdc++.h>

const int MAXN = 110;
const int MAXM = 5e4 + 10;
int n;
int typ[MAXN], to[MAXN][3];
int tot, cho[MAXM], nxt[MAXM][3];
int vis[MAXN][MAXM];
int get(int x, int y) { return (x - 1) * n + y; }
int gety(int x) { return (x - 1) % n + 1; }
int main() {
#define FILENAME "epic"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		static char buf[10];
		std::cin >> buf >> to[i][0] >> to[i][1] >> to[i][2];
		typ[i] = *buf == 'R' ? 0 : (*buf == 'P' ? 1 : 2);
	}
	tot = n * n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			int u = get(i, j);
			cho[u] = (typ[j] + 1) % 3;
			nxt[u][typ[j]] = get(i, to[j][cho[u]]);
		}
	for (int i = 2; i <= n; ++i) {
		memset(vis, 0, sizeof vis);
		int u = 1, v = i;
		while (true) {
			if (vis[v][u]) break;
			vis[v][u] = true;
			if (!nxt[u][typ[v]]) {
				nxt[u][typ[v]] = get(i, to[v][cho[u]]);
				break;
			}
			std::tie(u, v) = std::make_pair(nxt[u][typ[v]], to[v][cho[u]]);
		}
	}
	std::cout << tot << std::endl;
	for (int i = 1; i <= tot; ++i) {
		for (int j = 0; j < 3; ++j)
			if (!nxt[i][j])
				nxt[i][j] = 1;
		std::cout << ("RPS" [cho[i]]) << ' ' << nxt[i][0] << ' '
				  << nxt[i][1] << ' ' << nxt[i][2] << '\n';
	}
	return 0;
}


/*
#include <bits/stdc++.h>

const int MAXN = 110;
const int MAXM = 5e4 + 10;
int n;
int typ[MAXN], to[MAXN][3];
typedef std::vector<int> VI;
std::map<VI, int> M;
int tot, cho[MAXM], nxt[MAXM][3];
int dfs(VI now) {
	if (now.empty()) return 1;
	if (M.count(now)) return M[now];
	int u = M[now] = ++tot;
	VI li[3];
	int cho = -1;
	for (auto t : now)
		cho = typ[t] + 1;
	::cho[u] = cho = cho % 3;
	for (auto t : now)
		li[typ[t]].push_back(to[t][cho]);
	for (int i = 0; i < 3; ++i)
		nxt[u][i] = dfs(li[i]);
	return u;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		static char buf[10];
		std::cin >> buf >> to[i][0] >> to[i][1] >> to[i][2];
		typ[i] = *buf == 'R' ? 0 : (*buf == 'P' ? 1 : 2);
	}
	VI be;
	for (int i = 1; i <= n; ++i) be.push_back(i);
	dfs(be);
	std::cout << tot << std::endl;
	for (int i = 1; i <= tot; ++i) {
		std::cout << ("RPS" [cho[i]]) << ' ' << nxt[i][0] << ' '
				  << nxt[i][1] << ' ' << nxt[i][2] << '\n';
	}
	return 0;
}
*/

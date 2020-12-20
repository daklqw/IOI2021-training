#include <bits/stdc++.h>

const int MAXN = 60;
const int INF = 0x3f3f3f3f;
typedef std::pair<int, int> pi;
typedef std::vector<pi> V;
typedef std::vector<int> VI;
typedef std::string str;
void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
struct Graph {
	pi real[MAXN][MAXN];
	int val[MAXN][MAXN];
	int tar[MAXN], mat[MAXN];
	Graph() {
		memset(val, 0x3f, sizeof val);
		memset(real, -1, sizeof real);
		memset(tar, -1, sizeof tar);
	}
	V solve(int S, int n) {
		for (int i = 1; i <= n; ++i) if (i != S) {
			int & t = tar[i];
			for (int j = 1; j <= n; ++j)
				if (val[j][i] != INF) {
					if (t == -1 || val[t][i] > val[j][i])
						t = j;
				}
		}
		static int vis[MAXN];
		memset(vis, 0, (n + 1) << 2);
		std::vector<VI> cl;
		for (int i = 1; i <= n; ++i) if (i != S && !vis[i]) {
			int u = i, v;
			while (u != S && !vis[u])
				vis[u] = 1, u = tar[u];
			if (u != S && vis[u] == 1) {
				VI cy; v = u;
				do cy.push_back(v), v = tar[v]; while (u != v);
				cl.push_back(cy);
			}
			u = i;
			while (u != S && vis[u] != 2)
				vis[u] = 2, u = tar[u];
		}
		if (cl.empty()) {
			V res;
			for (int i = 1; i <= n; ++i) if (i != S)
				res.emplace_back(tar[i], i);
			return res;
		}
		Graph * nxt = new Graph;
		int m = 0;
		for (auto v : cl) {
			++m; for (auto t : v) mat[t] = m;
		}
		int cc = m;
		for (int i = 1; i <= n; ++i)
			if (!mat[i]) mat[i] = ++m;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (mat[i] != mat[j] && val[i][j] != INF) {
					int v = val[i][j];
					if (mat[tar[j]] == mat[j])
						v -= val[tar[j]][j];
					int & cv = nxt->val[mat[i]][mat[j]];
					if (v < cv) {
						real[mat[i]][mat[j]] = pi(i, j);
						cv = v;
					}
				}
		V es = nxt->solve(mat[S], m), res;
		delete nxt;
		for (auto t : es) {
			pi rt = real[t.first][t.second];
			res.push_back(rt);
			if (t.second <= cc) {
				for (auto t : cl[t.second - 1])
					if (t != rt.second)
						res.emplace_back(tar[t], t);
			}
		}
		return res;
	}
} ;
int n;
str buf[MAXN];
int be[MAXN][MAXN];
int idx;
int fa[MAXN * MAXN];
char up[MAXN * MAXN];
int upv[MAXN * MAXN];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int bel[MAXN][MAXN];
void merge(int x, int y) { fa[find(y)] = find(x); }
int main() {
#define FILENAME "dictionary"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i)
		std::cin >> buf[i];
	Graph * gr = new Graph;
	for (int i = 1; i <= n; ++i) {
		gr->val[n + 1][i] = 0;
		be[n + 1][i] = 0;
		for (int j = 1; j <= n; ++j) if (i != j) {
			const int L = std::min(buf[i].size(), buf[j].size());
			for (int k = L; k; --k) {
				bool can = false;
				for (int l = 0; l + k <= (int) buf[i].size(); ++l)
					if (buf[i].substr(l, k) == buf[j].substr(0, k)) {
						be[i][j] = l;
						can = true;
						gr->val[i][j] = -k;
						break;
					}
				if (can) break;
			}
		}
	}
	for (int i = 1; i <= n + 1; ++i)
		for (int j = 0; j <= (int) buf[i].size(); ++j) {
			bel[i][j] = ++idx;
			fa[idx] = idx;
			if (j > 0) {
				up[idx] = buf[i][j - 1];
				upv[idx] = bel[i][j - 1];
			}
		}
	V ans = gr->solve(n + 1, n + 1);
	for (auto i : ans) {
		int V = gr->val[i.first][i.second];
		int p = be[i.first][i.second];
		for (int j = 0; j <= -V; ++j)
			merge(bel[i.first][p + j], bel[i.second][j]);
	}
	static int rnk[MAXN * MAXN], bak;
	for (int i = 1; i <= idx; ++i)
		if (fa[i] == i) rnk[i] = ++bak;
	std::cout << bak << '\n';
	for (int i = 1; i <= idx; ++i)
		if (fa[i] == i) {
			std::cout << rnk[find(upv[i])];
			if (i != idx)
				std::cout << ' ' << up[i];
			std::cout << '\n';
		}
	return 0;
}

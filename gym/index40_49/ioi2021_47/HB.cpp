#include <bits/stdc++.h>

const int MAXN = 1e6 + 10;
const int MAXP = MAXN * 2 + MAXN * 2 + MAXN * 2;
const int MAXM = MAXP * 4;
namespace gr {
	int head[MAXP], nxt[MAXM], to[MAXM], tot;
	void adde(int b, int e) {
		if (!b || !e) return ;
		nxt[++tot] = head[b]; to[head[b] = tot] = e;
	}
	int dfn[MAXP], low[MAXP], bel[MAXP], ins[MAXP], st[MAXP], top;
	int all;
	void tarjan(int u) {
		static int idx;
		low[u] = dfn[u] = ++idx;
		ins[st[++top] = u] = true;
		for (int i = head[u]; i; i = nxt[i])
			if (!dfn[to[i]]) {
				tarjan(to[i]);
				low[u] = std::min(low[u], low[to[i]]);
			} else if (ins[to[i]])
				low[u] = std::min(low[u], dfn[to[i]]);
		if (low[u] == dfn[u]) {
			int v; ++all;
			do {
				bel[v = st[top--]] = all;
				ins[v] = false;
			} while (v != u);
		}
	}
	void solve(int n) {
		for (int i = 1; i <= n; ++i)
			if (!dfn[i])
				tarjan(i);
	}
}
using gr::adde;

int nxt[MAXN][2], idx = 1, fa[MAXN];
int ins(char * buf) {
	int u = 1;
	while (*buf) {
		int & nt = nxt[u][*buf++ - '0'];
		if (!nt) fa[nt = ++idx] = u;
		u = nt;
	}
	return u;
}
int end[MAXN][2], mat[MAXN][2];
typedef std::pair<int, int> pi;
int in[MAXN], out[MAXN], cnt;
bool hav[MAXN];
void dfs(int u) {
	int x = ++cnt, y = ++cnt;
	adde(x, in[u]);
	adde(out[u], y);
	for (int i = 0; i < 2; ++i)
		if (const int to = nxt[u][i]) {
			dfs(to);
			adde(out[to], in[u]);
			adde(out[u], in[to]);
			adde(x, in[to]);
			adde(out[to], y);
		}
	in[u] = x, out[u] = y;
}
int n;
void print(int u, int l = 0) {
	if (u != 1) print(fa[u], u);
	if (l) {
		for (int i = 0; i < 2; ++i)
			if (nxt[u][i] == l)
				std::cout << i;
	} else std::cout << '\n';
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		static char buf[MAXN];
		std::cin >> buf;
		char * at = strchr(buf, '?');
		int up = at == NULL ? 1 : 2;
		for (int j = 0; j < 2; ++j)
			mat[i][j] = ++cnt;
		if (at == NULL)
			adde(mat[i][1], mat[i][0]);
		for (int j = 0; j < up; ++j) {
			if (at != NULL) *at = '0' + j;
			int p = ins(buf);
			end[i][j] = p;
			adde(mat[i][j], in[p]);
			adde(out[p], mat[i][j ^ 1]);
			int x = ++cnt, y = ++cnt;
			adde(x, in[p]);
			adde(x, mat[i][j ^ 1]);
			adde(out[p], y);
			adde(mat[i][j], y);
			in[p] = x, out[p] = y;
		}
	}
	dfs(1);
	gr::solve(cnt);
	while (true);
	for (int i = 1; i <= n; ++i)
		if (gr::bel[mat[i][0]] == gr::bel[mat[i][1]]) {
			std::cout << "NO" << std::endl;
			return 0;
		}
	std::cout << "YES" << std::endl;
	for (int i = 1; i <= n; ++i)
		print(end[i][gr::bel[mat[i][0]] > gr::bel[mat[i][1]]]);
	return 0;
}

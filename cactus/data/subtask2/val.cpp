#include "ex_testlib.h"

const int MAXN = 1e5 + 10;
const int MAXM = 3e5 + 10;
int head[MAXN], nxt[MAXM], to[MAXM], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int dep[MAXN], idx, tag[MAXN];
void dfs1(int u, int fa) {
	++idx;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa) {
			if (!dep[to[i]]) {
				dep[to[i]] = dep[u] + 1;
				dfs1(to[i], u);
			} else {
				if (dep[to[i]] < dep[u])
					++tag[u], --tag[to[i]];
				to[i] = -1;
			}
		}
}
void dfs2(int u, int fa) {
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa && to[i] != -1) {
			dfs2(to[i], u);
			tag[u] += tag[to[i]];
		}
	inf.ensuref(tag[u] <= 0, "edge %d %d is covered at least once", u, fa);
}
int main(int argc, char ** argv) {
	registerValidation(argc, argv);
	int n = inf.readInt(2, 100000, "n");
	inf.readSpace();
	int m = inf.readInt(1, 150000, "m");
	inf.readSpace();
	int K = inf.readInt(1, n, "C");
	inf.readEoln();
	auto li = inf.readInts(K, 1, n, "c");
	std::sort(li.begin(), li.end());
	inf.ensuref(std::unique(li.begin(), li.end()) == li.end(), "same exit");
	inf.readEoln();
	std::set<std::pair<int, int> > S;
	for (int i = 1; i <= m; ++i) {
		int u = inf.readInt(1, n, "u" + vtos(i));
		inf.readSpace();
		int v = inf.readInt(1, n, "v" + vtos(i));
		inf.readEoln();
		inf.ensuref(u != v, "self loop %d", u);
		adde(u, v);
		if (u > v) std::swap(u, v);
		inf.ensuref(!S.count(std::make_pair(u, v)), "multi-edge %d %d", u, v);
		S.emplace(u, v);
	}
	inf.readEof();
	dep[1] = 1; dfs1(1, 0);
	inf.ensuref(idx == n, "graph not connected");
	dfs2(1, 0);
	return 0;
}

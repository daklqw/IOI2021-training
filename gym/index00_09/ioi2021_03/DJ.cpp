#include <bits/stdc++.h>

const int MAXN = 310;
const int MAXM = MAXN * MAXN * 10;
typedef long double db;
const db eps = 1e-6;
struct flow {
	int head[MAXN], nxt[MAXM], to[MAXM], tot = 1;
	db val[MAXM];
	void adde(int b, int e, db v, int bi = 1) {
		nxt[++tot] = head[b]; to[head[b] = tot] = e; val[tot] = v;
		nxt[++tot] = head[e]; to[head[e] = tot] = b; val[tot] = v * bi;
	}
	int S, T, idx;
	int dis[MAXN];
	std::queue<int> que;
	bool bfs() {
		memset(dis, 0, (idx + 1) << 2);
		dis[S] = 1; que.push(S);
		while (!que.empty()) {
			int t = que.front(); que.pop();
			for (int i = head[t]; i; i = nxt[i])
				if (!dis[to[i]] && std::abs(val[i]) > eps) {
					dis[to[i]] = dis[t] + 1;
					que.push(to[i]);
				}
		}
		return dis[T] > 0;
	}
	db dinic(int u, db minv) {
		if (u == T || std::abs(minv) < eps) return minv;
		db res = 0;
		for (int & i = head[u]; i; i = nxt[i])
			if (std::abs(val[i]) > eps && dis[to[i]] == dis[u] + 1) {
				db t = dinic(to[i], std::min(minv, val[i]));
				minv -= t;
				val[i] -= t;
				val[i ^ 1] += t;
				res += t;
			}
		return res;
	}
	db operator () () {
		db res = 0;
		static int th[MAXN];
		memcpy(th, head, (idx + 1) << 2);
		while (bfs()) {
			res += dinic(S, 1e9);
			memcpy(head, th, (idx + 1) << 2);
		}
		return res;
	}
} gf, gw, gfw, ga, gb;
int n, m;
db V, alpha;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m >> V >> alpha;
	for (int i = 1; i <= m; ++i) {
		int b, e, v;
		std::cin >> b >> e >> v;
		gf.adde(b, e, v);
		gw.adde(b, e, v);
		gfw.adde(b, e, v);
	}
	gf.idx = gw.idx = gfw.idx = gb.idx = n;
	gf.T = gw.T = gfw.T = gb.T = 3;
	gf.adde(0, 1, 1e9, 0);
	gw.adde(0, 2, 1e9, 0);
	ga = gfw;
	gfw.adde(0, 1, 1e9, 0);
	gfw.adde(0, 2, 1e9, 0);
	db F = gf(), W = gw(), FW = gfw();
	db fl = FW * alpha;
	fl = std::min(fl, F);
	fl = std::max(fl, FW - W);
	gfw = ga;
	gfw.adde(0, 1, fl, 0);
	gfw.adde(0, 2, FW - fl, 0);
	gfw();
	for (int i = 1; i <= m; ++i) {
		int u = gfw.to[i * 2 + 1], v = gfw.to[i * 2];
		db f = (gfw.val[i * 2 + 1] - gfw.val[i * 2]) / 2;
		if (f < 0) std::swap(u, v), f = -f;
		gb.adde(u, v, f, 0);
	}
	gb.adde(0, 1, fl, 0);
	gb();
	std::cout << std::fixed << std::setprecision(10);
	for (int i = 1; i <= m; ++i) {
		db lhs = gb.val[i * 2 + 1], rhs = gb.val[i * 2];
		if (gfw.to[i * 2] != gb.to[i * 2])
			lhs = -lhs, rhs = -rhs;
		std::cout << lhs / V << ' ' << rhs << '\n';
	}
	db ans = pow(fl / V, alpha) * pow(FW - fl, 1 - alpha);
	std::cout << ans << std::endl;
	return 0;
}

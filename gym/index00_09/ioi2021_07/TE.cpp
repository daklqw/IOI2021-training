#include <bits/stdc++.h>

const int MAXN = 10010;
const int MAXP = MAXN * 3;
const int INF = 0x3f3f3f3f;
struct _ { int in, out; } ;
typedef std::vector<_> V;
typedef std::vector<int> VI;
typedef std::string str;
int bkt[MAXN];
struct Automaton {
	VI nxt[MAXP][27]; int idx;
	void adde(int u, int v, int c) {
		// std::cout << "ADD " << u << ' ' << v << ' ' << c << std::endl;
		nxt[u][c].push_back(v);
	}
	_ parse(int l, int r, char * S) {
		std::vector<V> orlist;
		V now;
		for (int i = l; i < r; ++i) {
			if (S[i] == '(') {
				now.push_back(parse(i + 1, bkt[i], S));
				i = bkt[i];
			} else if (S[i] == '*') {
				if (now.empty()) continue;
				_ t = now.back();
				int in = ++idx, out = ++idx;
				adde(in, t.in, 26);
				adde(t.out, out, 26);
				adde(t.in, t.out, 26);
				adde(t.out, t.in, 26);
				now.back() = (_) {in, out};
			} else if (S[i] == '|') {
				orlist.push_back(std::move(now));
				now = V();
			} else {
				int in = ++idx, out = ++idx;
				if (S[i] == '.') {
					for (int i = 0; i < 26; ++i)
						adde(in, out, i);
				} else
					adde(in, out, S[i] - 'a');
				now.push_back((_) {in, out});
			}
		}
		orlist.push_back(std::move(now));
		int in = ++idx, out = ++idx, zero = false;
		for (auto t : orlist) {
			if (t.empty()) zero = true;
			else {
				for (int j = 1; j < (int) t.size(); ++j)
					adde(t[j - 1].out, t[j].in, 26);
				adde(in, t[0].in, 26);
				adde(t.back().out, out, 26);
			}
		}
		if (zero) adde(in, out, 26);
		return (_) {in, out};
	}
	void reverse(const Automaton & A) {
		idx = A.idx;
		for (int i = 1; i <= idx; ++i)
			for (int j = 0; j < 27; ++j)
				for (auto k : A.nxt[i][j])
					nxt[k][j].push_back(i);
	}
	int dis[MAXP], pre[MAXP], prec[MAXP];
	typedef std::pair<int, int> pi;
	std::priority_queue<pi> que;
	void relax(int x, int u, int v, int l) {
		if (v < dis[x]) {
			dis[x] = v;
			pre[x] = u;
			prec[x] = l;
			que.emplace(-dis[x], x);
		}
	}
	str print(int S, int u) {
		str r;
		while (u != S) {
			if (prec[u] < 26)
				r += (char) ('a' + prec[u]);
			u = pre[u];
		}
		return str(r.rbegin(), r.rend());
	}
	void dijkstra(int S) {
		static bool vis[MAXP];
		memset(vis, 0, sizeof vis);
		memset(dis, 0x3f, sizeof dis);
		que.emplace(dis[S] = 0, S);
		while (!que.empty()) {
			int t = que.top().second; que.pop();
			if (vis[t]) continue;
			vis[t] = true;
			for (int i = 0; i < 27; ++i)
				for (int v : nxt[t][i])
					relax(v, t, dis[t] + (i != 26), i);
		}
	}
} StoT, TtoS;
char S[MAXN], T[MAXN];
int dis[MAXP];
bool cmp(int x, int y) {
	return StoT.dis[x] < StoT.dis[y];
}
int main() {
#define FILENAME "expression"
#ifdef FILENAME
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> S >> T;
	int n = strlen(S);
	static int st[MAXN], top;
	for (int i = n - 1; ~i; --i) {
		if (S[i] == ')') st[++top] = i;
		else if (S[i] == '(') bkt[i] = st[top--];
	}
	int in, out;
	_ AM = StoT.parse(0, n, S);
	in = AM.in, out = AM.out;
	const int idx = StoT.idx;
	TtoS.reverse(StoT);
	StoT.dijkstra(in);
	TtoS.dijkstra(out);
	int m = strlen(T);
	static int rkat[MAXP];
	for (int i = 1; i <= idx; ++i) rkat[i] = i;
	std::sort(rkat + 1, rkat + 1 + idx, cmp);
	for (int i = 1; i <= idx; ++i) dis[rkat[i]] = i;
	for (int C = 0; C < m; ++C) {
		static int dt[MAXP], dh[MAXP];
		memset(dt, 0x3f, (idx + 1) << 2);
		for (int j = 1; j <= idx; ++j) {
			for (auto k : StoT.nxt[j][T[C] - 'a'])
				dt[k] = std::min(dt[k], dis[j]);
		}
		static int buc[MAXP], li[MAXP];
		memset(buc, 0, (idx + 1) << 2);
		for (int j = 1; j <= idx; ++j)
			if (dt[j] != INF) ++buc[dt[j]];
		for (int j = 1; j <= idx; ++j) buc[j] += buc[j - 1];
		const int SM = buc[idx];
		for (int j = 1; j <= idx; ++j)
			if (dt[j] != INF) li[buc[dt[j]]--] = j;
		memset(dh, 0, (idx + 1) << 2);
		for (int T = 1, top; T <= SM; ++T) {
			st[top = 1] = li[T];
			while (top) {
				int u = st[top--];
				if (dh[u]) continue;
				dh[u] = true;
				for (int i : StoT.nxt[u][26])
					if (dt[i] > dt[u]) {
						dt[i] = dt[u];
						st[++top] = i;
					}
			}
		}
		memcpy(dis, dt, (idx + 1) << 2);
	}
	int Su, Tu, ans = INF;
	for (int i = 1; i <= idx; ++i)
		if (dis[i] != INF) {
			int v = rkat[dis[i]];
			int c = StoT.dis[v] + TtoS.dis[i];
			if (c < ans) ans = c, Su = v, Tu = i;
		}
	if (ans == INF)
		return std::cout << "NO" << std::endl, 0;
	str A = StoT.print(in, Su);
	str B = TtoS.print(out, Tu);
	std::reverse(B.begin(), B.end());
	std::cout << A << T << B << '\n';
	return 0;
}

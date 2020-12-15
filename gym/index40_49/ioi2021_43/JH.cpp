#include <bits/stdc++.h>

const int MAXN = 3e4 + 10;
typedef long long LL;
int val[MAXN];
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
typedef std::vector<int> V;
struct BIT {
	V tr; int L;
	void init(int l) {
		tr.resize(l + 1);
		L = l;
	}
	void add(int x, int v) {
		for (++x; x <= L; x += x & -x)
			tr[x] += v;
	}
	int qry(int x) {
		int r = 0;
		for (++x; x; x &= x - 1)
			r += tr[x];
		return r;
	}
} ;
struct _ {
	V li; int dta;
	BIT tr[2];
	void set(int v) {
		dta = v; li.resize(v * 2 + 1);
		tr[0].init(v + 1);
		tr[1].init(v);
	}
	int qry(int i, int dt, bool all = false) {
		int at = std::min(-1 - i - 2 * (dt - dta), dta * 2);
		if (!all) at = std::min(at, i - 1);
		if ((at & 1) == (i & 1)) --at;
		return at < 0 ? 0 : tr[at & 1].qry(at / 2);
	}
	LL calc(int dt) {
		LL res = 0;
		for (int i = 0; i < dta * 2 + 1; ++i)
			res += (LL) li[i] * qry(i, dt);
		return res;
	}
	LL ins(int x, int v, int d1, int d2){ 
		x += dta;
		LL res = (LL) v * (qry(x, d1, true) - qry(x, d2, true));
		li[x] += v;
		tr[x & 1].add(x / 2, v);
		return res;
	}
} dp[MAXN];
typedef std::pair<int, int> pi;
pi li[MAXN];
int n;
int fa[MAXN], fae[MAXN];
LL sm = 0;
int depc[2], mad[MAXN];
void dfs(int u, int dep = 0) {
	++depc[dep & 1];
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa[u]) {
			fae[to[i]] = i >> 1;
			fa[to[i]] = u;
			dfs(to[i], dep + 1);
			mad[u] = std::max(mad[u], mad[to[i]]);
		}
	dp[u].set(mad[u]);
	++mad[u];
}
int main() {
#define FILENAME "hidden"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	memset(val, -1, sizeof val);
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i < n; ++i) {
		int b, e, v;
		std::cin >> b >> e >> v;
		adde(b, e);
		li[i] = pi(v, i);
	}
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		int v = 0, u = i;
		while (u) {
			dp[u].ins(v--, 1, 0, 0);
			u = fa[u];
		}
	}
	LL all = sm = (LL) depc[0] * depc[1];
	std::sort(li + 1, li + n);
	LL ans = 0;
	for (int T = 1; T < n; ++T) {
		ans += sm * (li[T].first - li[T - 1].first);
		const int id = li[T].second;
		int u = to[id * 2], v = to[id * 2 + 1];
		if (fa[u] == v) std::swap(u, v);
		val[id] = 1;
		sm += dp[v].calc(-1) - dp[v].calc(1);
		V li(dp[v].dta * 2 + 3, 0);
		for (int i = 0; i < dp[v].dta * 2 + 1; ++i) {
			li[i] -= dp[v].li[i];
			li[i + 2] += dp[v].li[i];
		}
		u = fa[v];
		int dt = dp[v].dta + 1;
		while (u) {
			for (int i = 0; i < dp[v].dta * 2 + 3; ++i) {
				int v = fa[u] ? val[fae[u]] : 1234567;
				sm += dp[u].ins(i - dt, li[i], 0, v);
			}
			dt -= val[fae[u]];
			u = fa[u];
		}
		// std::cerr << "NOW " << ::li[T].first << ' ' << sm << std::endl;
	}
	long double Ans = ans / (long double) all;
	std::cout << std::fixed << std::setprecision(12);
	std::cout << Ans;
	return 0;
}

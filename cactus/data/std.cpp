#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
const int MAXM = MAXN * 1.5;
const int mod = 998244353;
typedef long long LL;
typedef std::vector<int> VI;
void reduce(int & x) { x += x >> 31 & mod; }
int mul(int x, int y) { return (LL) x * y % mod; }
int pow(int a, int b, int r = 1) {
	for (; b; b >>= 1, a = mul(a, a))
		if (b & 1) r = mul(r, a);
	return r;
}
int inv[MAXN];

struct Poly {
	int x, b;
	Poly() { x = b = 0; }
	Poly(int _x, int _b) : x(_x), b(_b) { }
	int operator () (int v) const {
		return ((LL) x * v + b) % mod;
	}
} ;
Poly operator + (Poly a, Poly b) {
	reduce(a.x += b.x - mod);
	reduce(a.b += b.b - mod);
	return a;
}
Poly operator - (Poly a, Poly b) {
	reduce(a.x -= b.x);
	reduce(a.b -= b.b);
	return a;
}
Poly operator * (Poly a, int b) {
	return Poly(mul(a.x, b), mul(a.b, b));
}

int head[MAXN], nxt[MAXM << 1], to[MAXM << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
int deg[MAXN];
bool isExit[MAXN];

int dfn[MAXN], low[MAXN], st[MAXN], top;
VI hav[MAXN], cir[MAXN];

void tarjan(int u, int fa) {
	static int idx, cnt;
	low[u] = dfn[u] = ++idx;
	st[++top] = u;
	for (int i = head[u], v; i; i = nxt[i])
		if ((i >> 1) != fa && !isExit[to[i]]) {
			if (!dfn[to[i]]) {
				tarjan(to[i], i >> 1);
				low[u] = std::min(low[u], low[to[i]]);
				if (dfn[u] <= low[to[i]]) {
					hav[u].push_back(++cnt);
					do cir[cnt].push_back(v = st[top--]);
					while (v != to[i]);
				}
			} else low[u] = std::min(low[u], dfn[to[i]]);
		}
}

Poly f[MAXN];
struct _ {
	int fa;
	Poly b;
	_() { fa = 0; }
} g[MAXN];

_ solveCycle(VI li) {
	_ lst; lst.b = Poly(1, 0);
	for (int v : li) {
		_ now;
		int iv = (1 + (LL) (mod - f[v].x) * lst.fa) % mod;
		iv = pow(iv, mod - 2);
		now.fa = mul(f[v].x, iv);
		now.b = (Poly(0, f[v].b) + lst.b * f[v].x) * iv;
		lst = g[v] = now;
	}
	return lst;
}
_ solveSingle(int u) {
	_ lst; lst.b = f[u];
	return g[u] = lst;
}
void fromBottom(int u) {
	Poly sm;
	for (int r : hav[u]) {
		for (int v : cir[r])
			fromBottom(v);
		_ lhs, rhs;
		if (cir[r].size() > 1) {
			lhs = solveCycle(cir[r]);
			rhs = solveCycle(VI(cir[r].rbegin(), cir[r].rend()));
		} else lhs = solveSingle(cir[r][0]);
		sm = sm + lhs.b + rhs.b;
		reduce(sm.x += lhs.fa - mod);
		reduce(sm.x += rhs.fa - mod);
	}
	int iv = (1 + (LL) (mod - inv[deg[u]]) * sm.x) % mod;
	iv = pow(iv, mod - 2, inv[deg[u]]);
	f[u] = Poly(iv, mul(sm.b + deg[u], iv));
}

int pr[MAXN];
void fromTop(int u) {
	for (int r : hav[u]) {
		int lst = pr[u];
		for (auto t : cir[r]) {
			pr[t] = ((LL) g[t].fa * lst + g[t].b(pr[u])) % mod;
			lst = pr[t];
			fromTop(t);
		}
	}
}

void solve(int S) {
	top = 0;
	tarjan(S, 0);
	fromBottom(S);
	pr[S] = f[S].b;
	fromTop(S);
}

int main() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i != MAXN; ++i)
		inv[i] = mul(inv[mod % i], mod - mod / i);
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n, m, C;
	std::cin >> n >> m >> C;
	for (int i = 1, t; i <= C; ++i)
		std::cin >> t, isExit[t] = true;
	for (int i = 1, u, v; i <= m; ++i) {
		std::cin >> u >> v;
		adde(u, v);
		++deg[u], ++deg[v];
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i] && !isExit[i])
			solve(i);
	for (int i = 1; i <= n; ++i)
		std::cout << pr[i] << '\n';
	return 0;
}

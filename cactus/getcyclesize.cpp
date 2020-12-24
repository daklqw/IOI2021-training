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
int head[MAXN], nxt[MAXM << 1], to[MAXM << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
bool isExit[MAXN];

int dfn[MAXN], low[MAXN], st[MAXN], top;
VI hav[MAXN], cir[MAXN];

int ma = 0;
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
					ma = std::max(ma, (int) cir[cnt].size() + 1);
				}
			} else low[u] = std::min(low[u], dfn[to[i]]);
		}
}
void solve(int S) {
	top = 0;
	tarjan(S, 0);
}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n, m, C;
	std::cin >> n >> m >> C;
	for (int i = 1, t; i <= C; ++i)
		std::cin >> t, isExit[t] = true;
	for (int i = 1, u, v; i <= m; ++i) {
		std::cin >> u >> v;
		adde(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i] && !isExit[i])
			solve(i);
	std::cout << ma << std::endl;
	return 0;
}

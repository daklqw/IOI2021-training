#include <bits/stdc++.h>

const int MAXN = 5010;
const int MAXM = 1e5 + 10;
typedef long long LL;
int n;
void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
typedef std::pair<int, int> pi;
struct _ {
	int nxt, to, v;
} es[MAXM];
int tot;
void adde(int * head, int b, int e, int v) {
	es[++tot] = (_) {head[b], e, v};
	head[b] = tot;
}
std::priority_queue<pi> que;
void dijkstra(int S, int * dis, int * head) {
	static int vis[MAXN];
	memset(vis, 0, n + 1 << 2);
	memset(dis, 0x3f, n + 1 << 2);
	que.emplace(dis[S] = 0, S);
	while (!que.empty()) {
		int t = que.top().second;
		que.pop();
		if (vis[t]) continue;
		vis[t] = true;
		for (int i = head[t]; i; i = es[i].nxt) {
			int v = es[i].to, val = dis[t] + es[i].v;
			if (val < dis[v])
				que.emplace(-(dis[v] = val), v);
		}
	}
}
int gr[MAXN], igr[MAXN];
int f[MAXN], g[MAXN];
int B, S, R;
LL pre[MAXN];
const LL INFL = 0x3f3f3f3f3f3f3f3fLL;
LL dp[MAXN];
inline LL calc(int l, int r) {
	return l >= r ? INFL : (r - l - 1) * (pre[r] - pre[l]) + dp[l];
}
int at[MAXN << 1];
int cp[MAXN << 1], rp[MAXN << 1];
void smawk(int n, int * col, int m, int * row, int * tar) {
	static int _st[MAXN << 1], bak;
	int * st = _st + bak, top = 0;
	for (int i = 0; i < n; ++i) {
		while (top) {
			LL lhs = calc(col[st[top - 1]], row[top - 1]);
			LL rhs = calc(col[i], row[top - 1]);
			if (lhs <= rhs) break;
			--top;
		}
		if (top < m) st[top++] = i;
	}
	for (int i = 0; i < top; ++i)
		col[i] = col[st[i]];
	n = top;
	if (m == 1) return (void) (*tar = *st);
	bak += n;
	int * nc = col + n, * nr = row + m, nm = 0;
	for (int i = 0; i < m; i += 2)
		nr[nm++] = row[i];
	memcpy(col + n, col, n << 2);
	smawk(n, nc, nm, nr, tar + m);
	for (int i = 0; i < m; i += 2)
		tar[i] = tar[m + i / 2];
	for (int i = 1; i < m; i += 2) {
		int l = tar[i - 1], r = (i + 1 == m ? n - 1 : tar[i + 1]);
		LL nv = INFL; int at = 0;
		for (int j = l; j <= r; ++j) {
			LL t = calc(col[j], row[i]);
			if (t < nv) nv = t, at = j;
		}
		tar[i] = at;
	}
	for (int i = 0; i < m; ++i)
		tar[i] = st[tar[i]];
	bak -= n;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> B >> S >> R;
	for (int i = 1; i <= R; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		adde(gr, a, b, c);
		adde(igr, b, a, c);
	}
	dijkstra(B + 1, f, gr);
	dijkstra(B + 1, g, igr);
	for (int i = 1; i <= B; ++i)
		f[i] += g[i];
	std::sort(f + 1, f + 1 + B);
	for (int i = 1; i <= B; ++i)
		pre[i] = pre[i - 1] + f[i];
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for (int i = 1; i <= S; ++i) {
		for (int j = 0; j <= B; ++j)
			cp[j] = rp[j] = j;
		smawk(B + 1, cp, B + 1, rp, at);
		for (int j = B; ~j; --j)
			dp[j] = calc(at[j], j);
	}
	std::cout << dp[B] << std::endl;
	return 0;
}

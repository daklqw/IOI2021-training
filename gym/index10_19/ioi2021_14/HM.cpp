#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int val[MAXN];
int hav[MAXN];
typedef std::pair<int, int> pi;
pi mi[MAXN];
int n, Q;
void upd(int u) {
	if (!u) return ;
	mi[u] = pi(hav[u] ? 0 : INF, u);
	for (int t = 0, p; t < 2; ++t)
		if ((p = u << 1 | t) <= n) {
			pi x = mi[p];
			x.first += val[p] > 0 ? -1 : 1;
			mi[u] = std::min(mi[u], x);
		}
	upd(u >> 1);
}
void add(int u, int t, int v) {
	while (u != t) {
		val[u] += v;
		u >>= 1;
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> Q;
	for (int i = 1; i <= n; ++i)
		std::cin >> hav[i];
	for (int i = n; i; --i) upd(i);
	int ans = 0;
	for (int i = 1, u; i <= Q; ++i) {
		std::cin >> u;
		int t = u, sm = 0;
		pi b = pi(mi[u].first, u);
		while (t > 1) {
			sm += val[t] < 0 ? -1 : 1;
			t >>= 1;
			b = std::min(b, pi(sm + mi[t].first, t));
		}
		int x = mi[b.second].second, y = u;
		u = b.second;
		ans += b.first;
		--hav[x];
		add(x, u, -1);
		add(y, u, 1);
		upd(x);
		upd(y);
		std::cout << ans << (" \n" [i == Q]);
	}
	return 0;
}

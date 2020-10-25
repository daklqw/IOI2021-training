#include <bits/stdc++.h>

const int MAXN = 3010;
typedef long long LL;

int n, m, K;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot;
void adde(int b, int e, int v) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e; val[tot] = v;
	nxt[++tot] = head[e]; to[head[e] = tot] = b; val[tot] = v;
}
LL ans;
LL dis[MAXN];
bool vis[MAXN];
typedef std::pair<LL, int> pi;
std::priority_queue<pi> q;

void solve(int v) {
	memset(dis, 0x3f, n + 1 << 3);
	memset(vis, 0, n + 1);
	q.emplace(dis[1] = 0, 1);
	while (!q.empty()) {
		int t = q.top().second; q.pop();
		if (vis[t]) continue;
		vis[t] = true;
		for (int i = head[t]; i; i = nxt[i]) {
			LL l = dis[t] + std::max(val[i] - v, 0);
			if (dis[to[i]] > l)
				q.emplace(-(dis[to[i]] = l), to[i]);
		}
	}
	ans = std::min(ans, dis[n] + (LL) v * K);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m >> K;
	for (int i = 1, b, e, v; i <= m; ++i)
		std::cin >> b >> e >> v, adde(b, e, v);
	ans = 0x3f3f3f3f3f3f3f3f;
	solve(0);
	for (int i = 1; i < tot; i += 2) solve(val[i]);
	std::cout << ans << std::endl;
	return 0;
}

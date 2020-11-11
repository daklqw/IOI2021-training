#include <bits/stdc++.h>

const int MAXN = 1010;
const int MAXM = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef long long LL;
int head[MAXN], nxt[MAXM], to[MAXM], val[MAXM], cost[MAXM], tot = 1;
void adde(int b, int e, int v, int c) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	val[tot] = v; cost[tot] = c;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
	val[tot] = 0; cost[tot] = -c;
}
int S, T, idx;
LL dis[MAXN];
bool inq[MAXN];
std::queue<int> q;
const LL NINF = 0xc0c0c0c0c0c0c0c0ll;
bool bellmanford() {
	memset(dis, 0xc0, (idx + 1) << 3);
	dis[S] = 0; q.push(S);
	while (!q.empty()) {
		int t = q.front(); q.pop(); inq[t] = false;
		for (int i = head[t]; i; i = nxt[i])
			if (val[i] && dis[to[i]] < dis[t] + cost[i]) {
				dis[to[i]] = dis[t] + cost[i];
				if (!inq[to[i]]) {
					q.push(to[i]);
					inq[to[i]] = true;
				}
			}
	}
	return dis[T] != NINF;
}
int dinic(int u, int minv = INF) {
	if (u == T || !minv)
		return minv;
	int t, res = 0;
	inq[u] = true;
	for (int & i = head[u]; i; i = nxt[i])
		if (val[i] && !inq[to[i]] && dis[to[i]] == dis[u] + cost[i] &&
			(t = dinic(to[i], std::min(minv, val[i])))) {
			res += t;
			minv -= t;
			val[i] -= t;
			val[i ^ 1] += t;
			if (!minv) break;
		}
	inq[u] = false;
	if (!res) dis[u] = NINF;
	return res;
}
LL MCMF() {
	int fl = 0; LL v = 0;
	static int qh[MAXN];
	memcpy(qh, head, (idx + 1) << 2);
	while (bellmanford()) {
		int t = dinic(S, INF);
		memcpy(head, qh, (idx + 1) << 2);
		fl += t;
		v += t * dis[T];
	}
	return v;
}
int n, K, ms, me;
int A[MAXN], B[MAXN];
int ed[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> K >> ms >> me;
	for (int i = 1; i <= n; ++i)
		std::cin >> A[i];
	for (int i = 1; i <= n; ++i)
		std::cin >> B[i];
	S = 0, T = idx = n + 1;
	adde(S, 1, K - ms, 0);
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += A[i];
		adde(i, std::min(i + K, T), 1, B[i] - A[i]);
		ed[i] = tot;
		adde(i, i + 1, K - ms - me + std::max(K - i, 0), 0);
	}
	ans += MCMF();
	std::cout << ans << std::endl;
	for (int i = 1; i <= n; ++i)
		std::cout << ("SE" [val[ed[i]]]);
	std::cout << '\n';
	return 0;
}

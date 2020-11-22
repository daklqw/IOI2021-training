#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;

int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot = 1;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
}
bool vis[MAXN];
int n, m;
int as[MAXN], bs[MAXN], cs[MAXN];
int ind[MAXN];
std::vector<int> hav[MAXN];
int main() {
#define FILENAME "insider"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		std::cin >> as[i] >> bs[i] >> cs[i];
		adde(as[i], bs[i]);
		adde(cs[i], bs[i]);
		hav[as[i]].push_back(i);
		hav[bs[i]].push_back(i);
		hav[cs[i]].push_back(i);
		++ind[bs[i]];
	}
	static int que[MAXN], hd, tl;
	hd = tl = 1;
	for (int i = 1; i <= n; ++i)
		if (!ind[i])
			que[tl++] = i;
	while (hd < tl) {
		int t = que[hd++];
		for (int i = head[t]; i; i = nxt[i])
			if (!vis[i >> 1]) {
				vis[i >> 1] = true;
				if (!--ind[to[i]])
					que[tl++] = to[i];
			}
	}
	static int li[MAXN], at[MAXN];
	int lcur = 1, rcur = n;
	for (int i = 1; i <= n; ++i) {
		int u = que[i];
		int lc = 0, rc = 0;
		for (auto l : hav[u]) {
			if ((!!at[as[l]]) + (!!at[bs[l]]) + (!!at[cs[l]]) == 1) {
				if (u == bs[l])
					++((at[as[l]] | at[cs[l]]) < lcur ? lc : rc);
				else
					++(at[as[l] ^ cs[l] ^ u] < lcur ? rc : lc);
			}
		}
		li[at[u] = lc > rc ? lcur++ : rcur--] = u;
	}
	for (int i = 1; i <= n; ++i)
		std::cout << li[i] << (" \n" [i == n]);
	return 0;
}

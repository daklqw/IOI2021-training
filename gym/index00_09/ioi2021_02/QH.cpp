#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
int head[MAXN], nxt[MAXN], fa[MAXN];
typedef std::vector<int> VI;
int f[MAXN][2];
void dfs(int u) {
	for (int i = head[u]; i; i = nxt[i]) {
		dfs(i);
		int ma = std::max(f[i][0], f[i][1]);
		f[u][1] = std::max(f[u][0] + f[i][0] + 1, f[u][1] + ma);
		f[u][0] = ma + f[u][0];
	}
}
void get(int u, int b, VI & tar) {
	if (b == -1) {
		b = f[u][0] >= f[u][1] ? 0 : 1;
		if (!b) tar.push_back(u);
	}
	int mi = 0xc0c0c0c0, at = -1;
	if (b) for (int i = head[u]; i; i = nxt[i])
		if (f[i][0] - f[i][1] > mi)
			mi = f[i][0] - f[i][1], at = i;
	for (int i = head[u]; i; i = nxt[i])
		get(i, b ? (i == at ? 0 : -1) : -1, tar);
}
int n;
VI hav[MAXN];
int req[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 2; i <= n; ++i) {
		std::cin >> fa[i];
		nxt[i] = head[fa[i]];
		head[fa[i]] = i;
	}
	int sm = 0;
	VI li;
	for (int i = 1; i <= n; ++i)
		if (!fa[i]) {
			dfs(i);
			sm += std::max(f[i][0], f[i][1]);
			li.push_back(i);
			get(i, -1, hav[i]);
			if (f[i][0] + 1 > f[i][1])
				req[i] = true;
		}
	auto cmp = [] (int a, int b) {
		if (a == 1) return true;
		if (b == 1) return false;
		if (req[a] == 0 || req[b] == 0)
			return req[a] < req[b];
		return hav[a].size() > hav[b].size();
	};
	std::sort(li.begin(), li.end(), cmp);
	VI pool;
	for (int i : li) {
		if (req[i] && !pool.empty()) {
			fa[i] = pool.back();
			pool.pop_back();
			hav[i].erase(hav[i].begin());
			++sm;
		}
		pool.insert(pool.end(), hav[i].begin(), hav[i].end());
	}
	for (int i = 2; i <= n; ++i)
		if (!fa[i])
			fa[i] = 1;
	std::cout << sm << '\n';
	for (int i = 2; i <= n; ++i)
		std::cout << fa[i] << (" \n" [i == n]);
	return 0;
}

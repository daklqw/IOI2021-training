#include <bits/stdc++.h>

const int MAXN = 5010;
typedef std::string str;
typedef std::map<str, int> MT;
MT M[2];
int idx[2];
int get(int c, const str & x) {
	return M[c].count(x) ? M[c][x] : M[c][x] = ++idx[c];
}
int head[MAXN], nxt[MAXN], to[MAXN];
int n;
int match[MAXN];
int vis[MAXN];
int dfs(int u, bool typ = true) {
	if (vis[u]) return false;
	vis[u] = true;
	for (int i = head[u]; i; i = nxt[i])
		if (!match[to[i]] || dfs(match[to[i]], typ)) {
			if (typ)
				match[to[i]] = u;
			return true;
		}
	return false;
}
int used[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int K;
	std::cin >> n >> K;
	str buf;
	for (int i = 1; i <= n; ++i) {
		std::cin >> buf;
		int u = get(0, buf.substr(0, K));
		int v = get(1, buf.substr(buf.length() - K));
		nxt[i] = head[u];
		to[head[u] = i] = v;
	}
	int matching = 0;
	for (int i = 1; i <= idx[0]; ++i) {
		memset(vis, 0, idx[0] + 1 << 2);
		matching += dfs(i);
	}
	for (int i = 1; i <= idx[1]; ++i) if (match[i]) {
		memset(vis, 0, idx[0] + 1 << 2);
		used[match[i]] = dfs(match[i], false);
	}
	typedef std::vector<int> VI;
	std::map<int, VI> ans;
	for (int i = 1; i <= idx[0]; ++i)
		if (used[i]) {
			for (int j = head[i]; j; j = nxt[j])
				ans[-i].push_back(j);
		} else {
			for (int j = head[i]; j; j = nxt[j]) {
				assert(match[to[j]]);
				assert(!used[match[to[j]]]);
				ans[to[j]].push_back(j);
			}
		}
	std::cout << ans.size() << '\n';
	int call = 0;
	for (auto t : ans) {
		std::cout << t.second.size();
		call += t.second.size();
		for (auto x : t.second)
			std::cout << ' ' << x;
		std::cout << '\n';
	}
	assert(call == n);
	assert(ans.size() == matching);
	return 0;
}

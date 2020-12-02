#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;
typedef long long LL;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
}
struct _ {
	LL n, p;
	bool operator < (_ b) const {
		return n > b.n;
	}
	_ operator + (_ b) const {
		return (_) {std::min(n, p + b.n), p + b.p};
	}
} ;
LL A[MAXN];
int idx;
std::multiset<_> S[MAXN];
void reduce(int u, LL _v) {
	_ v = (_) {std::min(_v, 0ll), _v};
	while (!S[u].empty() && (!(v < *S[u].begin()) || v.p < 0)) {
		v = v + *S[u].begin();
		S[u].erase(S[u].begin());
	}
	if (S[u].empty() && v.p <= 0) return ;
	S[u].insert(v);
}
int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (S[x].size() > S[y].size()) std::swap(x, y);
	for (auto t : S[x]) S[y].insert(t);
	S[x].clear();
	return y;
}
int dfs(int u, int fa) {
	int r = 0;
	for (int i = head[u]; i; i = nxt[i])
		if (to[i] != fa)
			r = merge(r, dfs(to[i], u));
	if (!r) S[r = ++idx].clear();
	reduce(r, A[u]);
	return r;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int n, T;
		std::cin >> n >> T;
		for (int i = 1; i <= n; ++i)
			std::cin >> A[i];
		for (int i = 1, x, y; i < n; ++i)
			std::cin >> x >> y, adde(x, y);
		adde(T, n + 1); A[n + 1] = 0x3f3f3f3f3f3f3f3fll;
		int r = dfs(1, 0);
		LL sm = 0;
		for (auto t : S[r])
			if (sm + t.n >= 0) sm += t.p;
			else break;
		if (sm > 1e15)
			std::cout << "escaped\n";
		else
			std::cout << "trapped\n";
		memset(head, 0, n + 2 << 2);
		tot = 1; idx = 0;
	}
	return 0;
}

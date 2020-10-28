#include <bits/stdc++.h>

const int MAXN = 110;
int pw(int x) { return x * x; }
int xs[MAXN], ys[MAXN];
int n, D;
int hav(int i, int j) {
	return pw(xs[i] - xs[j]) + pw(ys[i] - ys[j]) <= pw(D);
}
typedef std::bitset<100> B;
B out[MAXN];
B dfs(B);
int fa[MAXN];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
B par(B now) {
	if (now.count() <= 1) return now;
	for (int i = 0; i != n; ++i)
		fa[i] = i;
	for (int i = 0; i != n; ++i) if (now.test(i)) {
		B t = (out[i] & now);
		for (int j = i + 1; j != n; ++j)
			if (now.test(j) && !t.test(j))
				fa[find(i)] = find(j);
	}
	std::map<int, B> M;
	for (int i = 0; i != n; ++i)
		if (now.test(i))
			M[find(i)].set(i);
	B r;
	for (auto t : M)
		r |= dfs(t.second);
	return r;
}
B dfs(B now) {
	int p = -1, cnt = 12243;
	for (int i = now._Find_first(); i != 100; i = now._Find_next(i)) {
		int c = (now & out[i]).count();
		if (c < cnt) {
			cnt = c;
			p = i;
		}
	}
	B res = par(now & out[p]);
	res.set(p);
	now.reset(p);
	B ret = par(now);
	if (ret.count() > res.count())
		res = ret;
	return res;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> D;
	for (int i = 0; i < n; ++i)
		std::cin >> xs[i] >> ys[i];
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (hav(i, j)) {
				out[i].set(j);
				out[j].set(i);
			}
	B tp;
	for (int i = 0; i < n; ++i) tp.set(i);
	B r = par(tp);
	std::cout << r.count() << '\n';
	for (int i = 0; i < n; ++i)
		if (r.test(i))
			std::cout << (i + 1) << ' ';
	std::cout << '\n';
	return 0;
}

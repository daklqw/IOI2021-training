#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::pair<int, int> pi;
std::map<pi, int> M;
int ask(int x, int y) {
	if (M.count(pi(x, y))) return M[pi(x, y)];
	char buf[3];
	std::cout << "? " << x << ' ' << y << std::endl;
	std::cin >> buf;
	return M[pi(x, y)] = (*buf == '>');
}
void answer(VI e, VI o) {
	std::cout << "!";
	for (auto t : e) std::cout << ' ' << t;
	for (auto t : o) std::cout << ' ' << t;
	std::cout << std::endl;
}
typedef std::vector<int> VI;
const int MAXN = 10010;
const int MAXP = MAXN << 1;
int ls[MAXP], rs[MAXP], L[MAXP], R[MAXP], tot, cnt;
int sz[MAXP];
VI hav[MAXN];
pi split(int p, int x) {
	VI a, b;
	for (auto t : hav[x])
		if (ask(p, t) == 1)
			a.push_back(t);
		else
			b.push_back(t);
	if (a.empty()) return pi(0, x);
	if (b.empty()) return pi(x, 0);
	++tot;
	hav[x] = a;
	hav[tot] = b;
	return pi(x, tot);
}
bool all(int p, int x, int v) {
	for (auto t : hav[x])
		if (ask(p, t) != v)
			return false;
	return true;
}
int qry(int u, int p) {
	int res = 0;
	if (L[u] == R[u]) {
		int x, y;
		std::tie(x, y) = split(p, L[u]);
		if (!x || !y) return hav[x].size();
		ls[u] = ++cnt;
		L[cnt] = R[cnt] = x;
		sz[cnt] = hav[x].size();
		res += sz[cnt];
		rs[u] = ++cnt;
		L[cnt] = R[cnt] = y;
		sz[cnt] = hav[y].size();
	} else {
		int x = R[ls[u]], y = L[rs[u]];
		if (hav[x].size() < hav[y].size()) {
			if (all(p, x, 1))
				res += qry(rs[u], p) + sz[ls[u]];
			else
				res += qry(ls[u], p);
		} else {
			if (all(p, y, 0))
				res += qry(ls[u], p);
			else
				res += qry(rs[u], p) + sz[ls[u]];
		}
	}
	L[u] = L[ls[u]];
	R[u] = R[rs[u]];
	sz[u] = sz[ls[u]] + sz[rs[u]];
	return res;
}
int rnk[MAXN];
VI lhs, rhs;
int deb = 1;
void dfs(int u) {
	if (L[u] == R[u]) {
		if (hav[L[u]].size()) {
			rhs[hav[L[u]][0] - 1] = deb;
			deb += 2;
		}
		return ;
	}
	dfs(ls[u]);
	dfs(rs[u]);
}
void work(int n) {
	const int x = n / 2, y = n - x;
	L[1] = R[1] = cnt = tot = 1;
	for (int i = 1; i <= y; ++i)
		hav[1].push_back(i);
	lhs.resize(x);
	rhs.resize(y);
	for (int i = 1; i <= x; ++i) {
		int r = qry(1, i);
		lhs[i - 1] = r * 2;
	}
	dfs(1);
	answer(lhs, rhs);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n;
	std::cin >> n;
	work(n);
	return 0;
}

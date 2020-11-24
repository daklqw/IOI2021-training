#include <bits/stdc++.h>

const int MAXN = 5e5 + 10;
void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
typedef std::vector<int> VI;
typedef std::pair<int, int> pi;
typedef std::vector<pi> VE;
std::mt19937 rd(114514);
int sm = 0, mad = 0;
double per;
struct info {
	info * s[2];
	VI dis[2], to[2];
	int X[2], Y[2];
	void build(int n, VE e, int Sx, int Sy, int dep = 0) {
		std::tie(X[0], X[1]) = std::tie(Sx, Sy);
		dis[0].resize(n);
		dis[1].resize(n);
		if (n <= 3) {
			assert(n == 3);
			for (int i = 0; i != 3; ++i)
				for (int j = 0; j < 2; ++j)
					dis[j][i] = i != X[j];
			return ;
		}
		s[0] = new info;
		s[1] = new info;
		to[0].resize(n, -1);
		to[1].resize(n, -1);
		int ax = 0x3f3f3f3f, id = 0;
		for (int i = 1; i <= 10; ++i) {
			int v = rd() % e.size();
			int x, y;
			std::tie(x, y) = e[v];
			if (x > y) std::swap(x, y);
			int lc = 0, rc = 0;
			for (int i = 0; i < n; ++i) {
				if (i <= x || i >= y) lc++;
				if (x <= i && i <= y) rc++;
			}
			lc = std::abs(lc - rc);
			if (lc < ax)
				ax = lc, id = v;
		}
		std::tie(Y[0], Y[1]) = e[id];
		if (Y[0] > Y[1]) std::swap(Y[0], Y[1]);
		int lc = 0, rc = 0;
		for (int i = 0; i < n; ++i) {
			if (i <= Y[0] || i >= Y[1])
				to[0][i] = lc++;
			if (Y[0] <= i && i <= Y[1])
				to[1][i] = rc++;
		}
		VE el, er;
		for (auto t : e) if (t != e[id]) {
			int b = bel(t.first) && bel(t.second);
			(b ? er : el).emplace_back(to[b][t.first], to[b][t.second]);
		}
		s[0]->build(lc, el, to[0][Y[0]], to[0][Y[1]], dep + 1);
		s[1]->build(rc, er, to[1][Y[0]], to[1][Y[1]], dep + 1);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < 2; ++j)
				dis[j][i] = _qry(X[j], i);
	}
	inline int bel(int x) {
		return to[1][x] != -1;
	}
	int _qry(int x, int y) {
		if (x == y) return 0;
		int bl = bel(x), br = bel(y);
		if (bl == br)
			return s[bl]->qry(to[bl][x], to[bl][y]);
		if (bl) std::swap(x, y);
		int res = 0x3f3f3f3f;
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j) {
				int l = s[0]->qry(to[0][x], to[0][Y[i]]);
				int r = s[1]->qry(to[1][y], to[1][Y[j]]);
				gmi(res, l + r + (i != j));
			}
		return res;
	}
	int qry(int x, int y) {
		for (int i = 0; i < 2; ++i)
			if (x == X[i] || y == X[i])
				return dis[i][x ^ y ^ X[i]];
		return _qry(x, y);
	}
} rt;
int main() {
#define FILENAME "distance"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n; std::cin >> n;
	VE es; es.reserve(n - 3);
	for (int i = 1, a, b; i <= n - 3; ++i) {
		std::cin >> a >> b;
		--a, --b;
		es.emplace_back(a, b);
	}
	rt.build(n, es, 0, n - 1);
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int x, y; std::cin >> x >> y;
		--x, --y;
		std::cout << rt.qry(x, y) << '\n';
	}
	return 0;
}

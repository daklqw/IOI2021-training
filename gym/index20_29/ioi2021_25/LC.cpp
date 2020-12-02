#include <bits/stdc++.h>

typedef long long LL;
typedef std::tuple<int, int, int> tp;
int K;

struct _ {
	LL x, b;
	_() { x = b = 0; }
	_(LL v, LL p) { x = v, b = p; }
	LL operator () (int v) { return x * v + b; }
	_ join(_ y) {
		return _(x * y.x, b + y.b * x);
	}
	_ operator + (_ y) {
		return _(x + y.x, b + y.b);
	}
} ;
std::map<tp, _> M[31][3];
_ solve(int k, int typ, int a, int d, int m) {
	if (m == 0) return _();
	tp ha(a, d, m);
	if (m > 1 && M[k][typ].count(ha)) return M[k][typ][ha];
	int lc = 1 << (k - 1);
	_ r;
	int at = std::max(lc - a + d - 1, 0) / d;
	if (a < lc) {
		r = r + solve(k - 1, 0, a, d, std::min(m, at)).join(_(2, 0));
	}
	int mp = typ == 2 ? lc : lc * 2 - 1;
	if ((mp - a) % d == 0) {
		int ax = (mp - a) / d;
		if (0 <= ax && ax < m)
			r = r + (typ == 2 ? _(4, 2) : _(1, -typ));
	}
	if (typ == 2) ++lc;
	at = std::max(lc - a + d - 1, 0) / d;
	int tp = a + (m - 1) * d;
	if (tp >= lc) {
		int nt = typ == 2 ? 2 : 1;
		int na = a + d * at - lc + 1;
		int nm = m - at - (typ != 2 && tp == mp);
		r = r + solve(k - 1, nt, na, d, nm).join(_(2, 1));
	}
	return m > 1 ? (M[k][typ][ha] = r) : r;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int Q; std::cin >> K >> Q;
	while (Q --> 0) {
		int a, d, m;
		std::cin >> a >> d >> m;
		LL ans = solve(K, 2, a, d, m)(1) / 2;
		for (int i = 1; i <= K; ++i)
			for (int j = 0; j < 3; ++j)
				M[i][j].clear();
		std::cout << ans << '\n';
	}
	return 0;
}

#include <bits/stdc++.h>

typedef long double db;
typedef long long LL;
const int MAXN = 1e5 + 10;
int xs[MAXN], vs[MAXN];

struct _ {
	db a, b, c;
	_() { a = b = c = 0; }
	_(db x, db y, db z) { a = x, b = y, c = z; }
	_ tr(int dta) {
		return _(a, b + 2 * a * dta, c + a * dta * dta + b * dta);
	}
	db operator () (int x) {
		return (a * x + b) * x + c;
	}
} ;
_ & operator += (_ & a, _ b) {
	a.a += b.a; a.b += b.b; a.c += b.c;
	return a;
}
_ & operator -= (_ & a, _ b) {
	a.a -= b.a; a.b -= b.b; a.c -= b.c;
	return a;
}
_ operator * (_ a, db v) {
	return _(a.a * v, a.b * v, a.c * v);
}
_ tri(db W, db H) {
	return _(-W / H / 2, W, 0);
}

std::map<int, _> li;
std::map<int, db> sum;
void add(int l, int r, _ x) {
	li[l] += x; li[r] -= x;
	li[r] += _(0, 0, x(r));
}
db inte(_ x, int at) {
	return (((x.a * at / 3) + x.b / 2) * at + x.c) * at;
}
db inte(_ x, int l, int r) {
	return inte(x, r) - inte(x, l);
}
db get(int x) {
	return std::prev(li.upper_bound(x))->second(x);
}
db inte(int l, int r) {
	auto lhs = li.upper_bound(l);
	auto rhs = li.upper_bound(r);
	if (lhs == rhs)
		return inte(std::prev(lhs)->second, l, r);
	db res = inte(std::prev(lhs)->second, l, lhs->first);
	--rhs;
	res += inte(rhs->second, rhs->first, r);
	res += sum[lhs->first] - sum[rhs->first];
	return res;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n; std::cin >> n;
	for (int i = 1; i <= n; ++i)
		std::cin >> xs[i] >> vs[i];
	for (int i = 1; i < n; ++i) {
		int a = vs[i], b = vs[i + 1];
		if (a > b) std::swap(a, b);
		add(0, a, _(0, xs[i + 1] - xs[i], 0));
		if (a != b)
		add(a, b, tri(xs[i + 1] - xs[i], b - a).tr(-a));
	}
	int ma = *std::max_element(vs + 1, vs + 1 + n);
	{
		_ sm;
		int lst = 0;
		for (auto & t : li) {
			if (t.first)
				sum[lst] = inte(sm, lst, t.first);
			lst = t.first;
			t.second = sm += t.second;
		}
	}
	{
		db sm = 0;
		for (auto it = sum.rbegin(); it != sum.rend(); ++it)
			it->second = sm += it->second;
	}
	std::cin >> n;
	for (int i = 1; i <= n; ++i)
		std::cin >> xs[i] >> vs[i];
	int mb = *std::max_element(vs + 1, vs + 1 + n);
	if (ma != mb) {
		std::cout << "Invalid plan" << std::endl;
		return 0;
	}
	db ans = 0;
	for (int i = 1; i < n; ++i) {
		int x = vs[i], y = vs[i + 1];
		if (x > y) std::swap(x, y);
		if (x == y) {
			ans += get(x) * (xs[i + 1] - xs[i]);
		} else {
			db sca = (xs[i + 1] - xs[i]) / (db) (y - x);
			ans += inte(x, y) * sca;
		}
	}
	std::cout << std::fixed << std::setprecision(10);
	std::cout << ans << std::endl;
	return 0;
}

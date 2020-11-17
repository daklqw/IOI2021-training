#include <bits/stdc++.h>

const int MAXN = 50010;
typedef long long LL;
typedef long double db;
typedef db VT;
struct vec {
	VT x, y;
	vec() { x = y = 0; }
	vec(VT a, VT b) { x = a, y = b; }
	VT operator ^ (vec b) const { return x * b.y - y * b.x; }
	VT operator * (vec b) const { return x * b.x + y * b.y; }
	VT norm2() const { return x * x + y * y; }
	db norm() const { return sqrt(x * x + y * y); }
	vec operator - (vec b) const { return vec(x - b.x, y - b.y); }
	vec operator + (vec b) const { return vec(x + b.x, y + b.y); }
	vec operator * (db k) const { return vec(x * k, y * k); }
	bool operator < (const vec & b) const {
		return x == b.x ? y < b.y : x < b.x;
	}
	friend std::ostream & operator << (std::ostream & out, vec x) {
		out << '(' << x.x << ',' << x.y << ')';
		return out;
	}
} xs[MAXN], ys[MAXN];
int n, m;
const db eps = 1e-10;
void go(int & cur, db & rest, vec & at, vec * li, int n) {
	while (cur < n && std::abs(rest) > eps) {
		db L = (li[cur] - at).norm();
		db nxt = std::min(L, rest);
		rest -= nxt;
		if (std::abs(nxt - L) < eps)
			at = li[cur++];
		else
			at = at + (li[cur] - at) * (nxt / L);
	}
}
bool judge(db lim) {
	int curl = 1, curr = 1;
	vec lhs = xs[0], rhs = ys[0];
	db restl = 0, restr = lim;
	while (true) {
		go(curl, restl, lhs, xs, n);
		go(curr, restr, rhs, ys, m);
		if ((rhs - lhs).norm() < lim + eps)
			return true;
		if (curl >= n || curr >= m) break;
		vec dx = xs[curl] - lhs, dy = ys[curr] - rhs;
		db nx = dx.norm(), ny = dy.norm();
		dx = dx * (1. / nx), dy = dy * (1. / ny);
		db L = std::min(nx, ny);
		db l = 0, r = L;
		do {
			db p1 = l + (r - l) / 3, p2 = p1 * 2 - l;
			db v1 = (lhs - rhs + (dx - dy) * p1).norm();
			db v2 = (lhs - rhs + (dx - dy) * p2).norm();
			if (v1 <= lim || v2 <= lim)
				return true;
			if (v1 < v2) r = p2;
			else l = p1;
		} while (std::abs(r - l) > 1e-8);
		restl += L;
		restr += L;
	}
	return false;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0, x, y; i < n; ++i)
		std::cin >> x >> y, xs[i].x = x, xs[i].y = y;
	std::cin >> m;
	for (int i = 0, x, y; i < m; ++i)
		std::cin >> x >> y, ys[i].x = x, ys[i].y = y;
	db B = 0;
	for (int i = 0; i + 1 < m; ++i)
		B += (ys[i + 1] - ys[i]).norm();
	db l = 0, r = B;
	db ans = judge(r) ? r : -1;
	for (int TT = 1; TT <= 40; ++TT) {
		db mid = (l + r) / 2;
		if (judge(mid)) {
			ans = mid;
			r = mid;
		} else {
			l = mid;
		}
	}
	std::cout << std::fixed << std::setprecision(10);
	if (ans < 0)
		std::cout << "impossible" << std::endl;
	else
		std::cout << ans << std::endl;
	return 0;
}

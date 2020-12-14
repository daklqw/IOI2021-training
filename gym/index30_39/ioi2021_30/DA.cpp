#include <bits/stdc++.h>

const int MAXN = 210;

typedef long long LL;
typedef long double db;

const db eps = 1e-6;
struct vec {
	LL x, y;
	vec() { x = y = 0; }
	vec(LL a, LL b) { x = a, y = b; }
	LL operator ^ (vec b) const { return x * b.y - y * b.x; }
	vec operator - (vec b) const { return vec(x - b.x, y - b.y); }
	vec operator + (vec b) const { return vec(x + b.x, y + b.y); }
	db norm() { return sqrtl(x * x + y * y); }
	db val() { return x / (db) y; }
	bool operator < (const vec & b) const {
		return (db) x * b.y + eps < (db) y * b.x;
	}
	bool operator == (const vec & b) const {
		return std::abs((db) x * b.y - (db) y * b.x) < eps;
	}
	friend std::istream & operator >> (std::istream & in, vec & x) {
		in >> x.x >> x.y;
		return in;
	}
} ps[MAXN];
inline LL cross(vec a, vec b, vec c) {
	return (b - a) ^ (c - a);
}
int n;
int C(LL x) { return x < 0 ? -1 : x > 0; }
int P(int x) { return x == 1 ? n : x - 1; }
int S(int x) { return x == n ? 1 : x + 1; }
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) std::cin >> ps[i];
	db ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = std::max(ans, (ps[i] - ps[S(i)]).norm());
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			vec a = ps[i], b = ps[j];
			typedef std::pair<vec, int> pi;
			static pi li[MAXN];
			int bak = 0;
			auto sgn = [a, b] (int x) { return C(cross(a, b, ps[x])); };
			auto its = [a, b] (int x, int y) {
				vec c1 = ps[x] - ps[y], c2 = b - a, d = b - ps[y];
				LL fr = c1 ^ c2, de = c1 ^ d;
				if (fr < 0) fr = -fr, de = -de;
				return vec(de, fr);
			};
			auto diff = [sgn] (int x, int y) {
				x = sgn(x), y = sgn(y);
				if (x == 0 || y == 0) return false;
				return x != y;
			};
			for (int k = 1; k <= n; ++k)
				if (sgn(k) == 0 && sgn(S(k)) == 0) {
					if (sgn(P(k)) != sgn(S(S(k)))) {
						li[++bak] = pi(its(P(k), k), 1);
						li[++bak] = pi(its(S(k), S(S(k))), 1);
					}
				}
			for (int k = 1; k <= n; ++k)
				if (sgn(k) == 0 && diff(P(k), S(k)))
					li[++bak] = pi(its(k, S(k)), 2);
			for (int k = 1; k <= n; ++k)
				if (diff(k, S(k)))
					li[++bak] = pi(its(k, S(k)), 2);
			std::sort(li + 1, li + 1 + bak);
			int sm = -1, dire = 1;
			int lst = 0;
			for (int k = 1; k <= bak; ++k) {
				sm += dire * li[k].second;
				if (std::abs(sm) == 1) dire = -dire;
				db dis = li[k].first.val() - li[lst + 1].first.val();
				db dl = (a - b).norm() * dis;
				ans = std::max(ans, dl);
				if (sm < 0) lst = k;
			}
		}
	std::cout << std::fixed << std::setprecision(10);
	std::cout << ans << '\n';
	return 0;
}

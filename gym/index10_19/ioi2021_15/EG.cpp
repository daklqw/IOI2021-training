#include <bits/stdc++.h>

const int MAXN = 2010;
typedef long double db;
const db eps = 1e-7;
const db scale = 1e6;
struct vec {
	db x, y, z; int id;
	vec() { x = y = z = 0; id = 0; }
	vec(db a, db b) { x = a, y = b; z = 0; id = 0; }
	vec(db a, db b, db c) { x = a, y = b, z = c; id = 0; }
	db operator ^ (vec b) const { return x * b.y - y * b.x; }
	db operator * (vec b) const { return x * b.x + y * b.y; }
	vec operator - (vec b) const { return vec(x - b.x, y - b.y); }
	vec operator + (vec b) const { return vec(x + b.x, y + b.y); }
	vec operator * (db k) const { return vec(x * k, y * k); }
	db norm() { return sqrtl(x * x + y * y); }
	db norm2() { return x * x + y * y; }
	bool operator < (vec b) const {
		return x == b.x ? y < b.y : x < b.x;
	}
	bool operator == (vec b) const {
		return std::abs(x - b.x) < eps && std::abs(y - b.y) < eps;
	}
	friend std::istream & operator >> (std::istream & in, vec & x) {
		int a, b;
		in >> a >> b;
		x.x = a, x.y = b;
		return in;
	}
} ps[MAXN];
inline db cross(vec a, vec b, vec c) {
	return (b - a) ^ (c - a);
}
bool colinear(vec x, vec y) {
	return std::abs(x ^ y) < eps;
}
int n;
vec intersection(vec x, vec y) {
	vec vx(x.x, y.x);
	vec vy(x.y, y.y);
	vec vz(-x.z, -y.z);
	db kx = (vz ^ vy) / (vx ^ vy);
	db ky = (vx ^ vz) / (vx ^ vy);
	return vec(kx, ky);
}
bool contain(vec x, vec y, vec t) {
	if (t == x || t == y) return true;
	if (!colinear(t - x, t - y)) return false;
	return (t - x) * (t - y) < eps;
}
bool inside(vec t) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		vec u = ps[i], v = ps[(i + 1) % n];
		if (contain(u, v, t)) return true;
		if (u.y > v.y) std::swap(u, v);
		if (u.y + eps > t.y || v.y + eps < t.y) continue;
		res ^= cross(t, u, v) > eps;
	}
	return res;
}
vec pgl[MAXN];
vec hp[MAXN << 1], li[MAXN << 1];
int bak;
void ins(vec x, int id) {
	db scl = scale / x.z;
	li[bak] = vec(x.x * scl, x.y * scl);
	hp[li[bak++].id = id] = x;
}
db ans = 0;
void chkans(vec t, int id) {
	ans = std::max(ans, (ps[id] - t).norm());
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n; ++i) std::cin >> ps[i];
	for (int i = 0; i < n; ++i) {
		vec u = ps[i], v = ps[(i + 1) % n];
		vec d = v - u, nor(-d.y, d.x);
		nor.z = -(nor * u);
		pgl[i] = nor;
	}
	for (int S = 0; S < n; ++S) {
		bak = 0;
		for (int j = 0; j < n; ++j) if (j != S) {
			vec v = ps[j] - ps[S];
			db c = v.norm2() / 2;
			ins(vec(-v.x, -v.y, c), j);
		}
		ins(vec(0, 1, 1e6), n);
		ins(vec(1, 0, 1e6), n + 1);
		ins(vec(0, -1, 1e6), n + 2);
		ins(vec(-1, 0, 1e6), n + 3);
		std::iter_swap(li, std::min_element(li, li + bak));
		auto cmp = [be = li[0]] (vec a, vec b) {
			a = a - be, b = b - be; db t = a ^ b;
			return std::abs(t) < eps ? a.norm2() < b.norm2() : t > 0;
		};
		std::sort(li + 1, li + bak, cmp);
		int T = 0;
		for (int i = 0; i < bak; ++i) {
			while (T > 1 && cross(li[T - 2], li[T - 1], li[i]) <= eps) --T;
			li[T++] = li[i];
		}
		static vec its[MAXN];
		for (int i = 0; i < T; ++i) {
			int x = li[i].id, y = li[(i + 1) % T].id;
			if (colinear(hp[x], hp[y])) continue;
			vec t = its[i] = intersection(hp[x], hp[y]) + ps[S];
			if (inside(t)) chkans(t, S);
		}
		for (int i = 0; i < T; ++i) {
			int nxt = (i + 1) % T;
			vec L = its[i], R = its[nxt];
			int id = li[nxt].id;
			for (int j = 0; j < n; ++j) {
				vec u = ps[j], v = ps[(j + 1) % n];
				if (colinear(hp[id], pgl[j])) continue;
				vec spe = hp[id];
				spe.z -= spe * ps[S];
				vec t = intersection(spe, pgl[j]);
				if (contain(u, v, t) && contain(L, R, t))
					chkans(t, S);
			}
		}
	}
	std::cout << std::fixed << std::setprecision(10);
	std::cout << ans << std::endl;
	return 0;
}

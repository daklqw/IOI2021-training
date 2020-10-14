#include <bits/stdc++.h>

typedef long double db;
const int MAXN = 1e5 + 10;

db R[510][510];
typedef long long LL;
typedef long double db;
typedef int VT;
struct vec {
	VT x, y;
	vec() { x = y = 0; }
	vec(VT a, VT b) { x = a, y = b; }
// WARN: modify following 4 functions if VT is int
// 1. A * B    2. return LL
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
	friend std::istream & operator >> (std::istream & in, vec & x) {
		in >> x.x >> x.y;
		return in;
	}
	friend std::ostream & operator << (std::ostream & out, vec x) {
		out << '(' << x.x << ',' << x.y << ')';
		return out;
	}
} ;
db dis(vec a, vec b, vec c) {
	return std::abs(((c - a) ^ (c - b)) / (b - a).norm());
}
int n;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	for (int i = 1; i <= 500; ++i)
		for (int j = 1; j <= 500; ++j)
			R[i][j] = -1;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x, y;
		std::cin >> x >> y;
		std::cin >> R[x][y];
	}
	int Q; std::cin >> Q;
	while (Q --> 0) {
		vec a, b; std::cin >> a >> b;
		if (a.x > b.x) std::swap(a, b);
		vec d = b - a;
		int L = a.y, R = b.y;
		if (L > R) std::swap(L, R);
		int ans = 0;
		for (int i = a.x; i <= b.x; ++i) {
			int v = a.x == b.x ? a.y : (a.y + (db) d.y / d.x * (i - a.x));
			for (int j = v - 1; j >= L; --j) {
				db dd = dis(a, b, vec(i, j));
				if (dd > 1) break;
				if (dd <= ::R[i][j])
					++ans;
			}
			for (int j = v + 1; j <= R; ++j) {
				db dd = dis(a, b, vec(i, j));
				if (dd > 1) break;
				if (dd <= ::R[i][j])
					++ans;
			}
			if (L <= v && v <= R)
				ans += dis(a, b, vec(i, v)) <= ::R[i][v];
		}
		std::cout << ans << std::endl;
	}
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 1e4 + 10;
typedef long long LL;
typedef long double db;
const db PI = acosl(-1);
typedef db VT;
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
		int a, b;
		in >> a >> b;
		x.x = a, x.y = b;
		return in;
	}
	friend std::ostream & operator << (std::ostream & out, vec x) {
		out << '(' << x.x << ',' << x.y << ')';
		return out;
	}
} ps[MAXN], qs[MAXN];
typedef std::vector<vec> VP;
vec rtt(vec x, db cs, db sn) {
	return vec(x.x * cs - x.y * sn, x.x * sn + x.y * cs);
}
int n, m;
db alpha;
struct _ {
	int h, id;
	bool operator < (_ b) const {
		return h < b.h;
	}
} H[MAXN];
db ansl[MAXN], L[MAXN];

int main() {
#define FILENAME "green"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> m >> n >> alpha;
	alpha = ((90 - alpha) / 360) * 2 * PI;
	for (int i = 1; i <= m; ++i)
		std::cin >> H[i].h, H[i].id = i;
	std::sort(H + 1, H + 1 + m);
	db cs = cosl(alpha), sn = -sinl(alpha);
	for (int i = 1; i <= n; ++i) {
		std::cin >> ps[i];
		qs[i] = rtt(ps[i], cs, sn);
	}
	db CL = cosl(PI / 2 - alpha);
	int at = -1;
	for (int i = 1; i <= m; ++i) {
		L[i] = CL * H[i].h;
		ansl[i] = ps[1].x;
	}
	db ans = 0, left = qs[1].x;
	int cur = 1;
	for (int i = 1; i <= n; ++i) {
		while (cur < m && qs[i].x > left) {
			db D = qs[i].x - qs[i - 1].x;
			if (std::abs(D) < 1e-6) {
				ansl[H[cur].id] = ps[i].x;
			} else {
				db scl = (left - qs[i - 1].x) / D;
				db d2 = ps[i].x - ps[i - 1].x;
				ansl[H[cur].id] = d2 * scl + ps[i - 1].x;
			}
			left += L[cur];
			++cur;
		}
		if (at == -1 || (qs[i].x > qs[at].x)) at = i;
	}
	ans = left - qs[1].x;
	ans += qs[at].x + L[m] - std::max<db>(qs[at].x, left);
	ans /= CL;
	ansl[H[m].id] = ps[at].x;
	std::cout << std::fixed << std::setprecision(10);
	std::cout << ans << '\n';
	for (int i = 1; i <= m; ++i)
		std::cout << ansl[i] << '\n';
	return 0;
}

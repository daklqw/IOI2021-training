#include <bits/stdc++.h>

const int MAXN = 2010;

typedef long long LL;
typedef long double db;
const db eps = 1e-6;
typedef db VT;
struct vec {
	VT x, y;
	vec() { x = y = 0; }
	vec(VT a, VT b) { x = a, y = b; }
	VT operator ^ (vec b) const { return x * b.y - y * b.x; }
	VT operator * (vec b) const { return x * b.x + y * b.y; }
	VT norm2() const { return x * x + y * y; }
	db norm() const { return sqrtl(x * x + y * y); }
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
} ps[MAXN];

vec rtt(vec v, db c, db s) {
	return vec(v.x * c - v.y * s, v.x * s + v.y * c);
}
int n, D, dp[MAXN];
void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
bool can[MAXN][MAXN];
int main() {
#define FILENAME "kingdom"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> D;
	for (int i = 1; i <= n; ++i) std::cin >> ps[i];
	memset(dp, 0x3f, sizeof dp);
	dp[1] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int T = 0; T < 2; ++T) {
			vec l, r; bool all = true;
			int _b = i + 1, _e = n + 1, _d = 1;
			if (T == 1)
				_b = i - 1, _e = 0, _d = -1;
			for (int j = _b; j != _e; j += _d) {
				vec qs = ps[j] - ps[i];
				if (all || ((l ^ qs) >= eps && (qs ^ r) >= eps))
					can[i][j] = true;
				if (qs.norm2() > (LL) D * D + eps) {
					vec x, y;
					db sn = D / qs.norm();
					db cs = sqrtl(std::max(1 - sn * sn, 0.L));
					x = rtt(qs, cs, sn);
					y = rtt(qs, cs, -sn);
					if ((x ^ y) < -eps) std::swap(x, y);
					if (all) {
						all = false, l = x, r = y;
					} else {
						if ((x ^ l) < -eps) {
							std::swap(x, l);
							std::swap(y, r);
						}
						if ((l ^ y) < -eps) break;
						if ((y ^ r) > eps)
							r = y;
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (can[i][j] && can[j][i]) {
				gmi(dp[j], dp[i] + 1);
			}
		}
	}
	std::cout << dp[n] << std::endl;
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
typedef long double db;
struct vec {
	int x, y;
	vec() { x = y = 0; }
	vec(int a, int b) { x = a, y = b; }
	vec operator - (vec b) const { return vec(x - b.x, y - b.y); }
	vec operator + (vec b) const { return vec(x + b.x, y + b.y); }
	bool operator < (const vec & b) const {
		return x == b.x ? y < b.y : x < b.x;
	}
} ps[MAXN];
typedef std::vector<vec> V;
typedef std::pair<db, db> pi;
V up, down;
int n;
int LL, RR;
db ans, ansl[4];
const int TT = 100;
const int MIN = 0;
const db eps = 1e-7;
db lb(const V & li, db x, int typ) {
	int l = 0, r = li.size();
	while (l + 1 < r) {
		int mid = l + r >> 1;
		if (li[mid].x + eps >= x) r = mid; else l = mid;
	}
	if (r == 0) ++r;
	if (li[r - 1].x == li[r].x) {
		if (typ == MIN) return std::min(li[r - 1].y, li[r].y);
		return std::max(li[r - 1].y, li[r].y);
	}
	vec D = li[r] - li[r - 1];
	db y = li[r - 1].y + D.y * ((x - li[r - 1].x) / D.x);
	return y;
}
pi get(db x) {
	return pi(lb(down, x, MIN), lb(up, x, !MIN));
}
db calc(db xl, db xr) {
	pi lhs = get(xl), rhs = get(xr);
	db yl = std::max(lhs.first, rhs.first);
	db yr = std::min(lhs.second, rhs.second);
	db area = (yr - yl) * (xr - xl);
	if (area > ans) {
		ans = area;
		ansl[0] = xl, ansl[1] = yl;
		ansl[2] = xr, ansl[3] = yr;
	}
	return area;
}
db solve(db L) {
	db l = LL, r = RR - L;
	db vm = -1e100;
	for (int i = 1; i <= TT; ++i) {
		db lm = (l * 2 + r) / 3, rm = (l + r * 2) / 3;
		db vl = calc(lm, lm + L), vr = calc(rm, rm + L);
		vm = std::max(vm, vl);
		vm = std::max(vm, vr);
		if (vl > vr) r = rm; else l = lm;
	}
	return vm;
}
int main() {
#define FILENAME "easy"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n; ++i)
		std::cin >> ps[i].x >> ps[i].y;
	int atl = -1, atr = -1;
	for (int i = 0; i < n; ++i) {
		if (atl == -1 || ps[i].x < ps[atl].x) atl = i;
		if (atr == -1 || ps[i].x > ps[atr].x) atr = i;
	}
	for (int i = atl, f = 1; f || i != (atr + 1) % n; i = (i + 1) % n)
		up.push_back(ps[i]), f = 0;
	for (int i = atr, f = 1; f || i != (atl + 1) % n; i = (i + 1) % n)
		down.push_back(ps[i]), f = 0;
	std::reverse(down.begin(), down.end());
	LL = ps[atl].x, RR = ps[atr].x;
	db l = 0, r = RR - LL;
	for (int i = 1; i <= TT; ++i) {
		db lm = (l * 2 + r) / 3, rm = (l + r * 2) / 3;
		db vl = solve(lm), vr = solve(rm);
		if (vl > vr) r = rm; else l = lm;
	}
	std::cout << std::fixed << std::setprecision(12);
	std::cerr << "ANS: " << ans << std::endl;
	std::cout << ansl[0] << ' ' << ansl[1] << ' ';
	std::cout << ansl[2] << ' ' << ansl[3] << '\n';
	return 0;
}

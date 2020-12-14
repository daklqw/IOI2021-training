#include <bits/stdc++.h>

typedef long double db;
db D, L, R, T, H;
db bL, slp;
db PI = acosl(-1);
db area(db l) {
	return l * sqrtl(1 - l * l) + PI - acosl(l);
}
db f(db x) {
	db r;
	if (x < 0 || x > L) {
		db t = (x < 0 ? -x : x - L) + bL;
		t = std::min(t, R);
		r = sqrtl(R * R - t * t);
	} else r = D;
	if (r < 1e-15) return 0;
	db hi = std::min(r, (L * H - T * x) / slp - D);
	if (hi < -r) return 0;
	return area(hi / r) * r * r;
}
db calc(db l, db r) {
	return (f(l) + f((l + r) / 2) * 4 + f(r)) / 6 * (r - l);
}
db simpson(db l, db r, db eps) {
	if (l > r) return 0;
	db mid = (l + r) / 2;
	db lv = calc(l, mid), rv = calc(mid, r), all = calc(l, r);
	if (std::abs(lv + rv - all) < eps || eps < 1e-15)
		return all;
	return simpson(l, mid, eps / 2) + simpson(mid, r, eps / 2);
}
int main() {
#define FILENAME "damage"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> D >> L >> R >> T >> H;
	D /= 2;
	slp = sqrtl(L * L - T * T);
	std::cout << std::fixed << std::setprecision(10);
	db t = R - (bL = sqrtl(R * R - D * D));
	db rg = L / T * H;
	db ans = simpson(-t, std::min<db>(0, rg), 1e-4);
	ans += simpson(0, std::min<db>(L, rg), 1e-4);
	ans += simpson(L, std::min<db>(L + t, rg), 1e-4);
	ans /= 1e6;
	std::cout << ans << std::endl;
	return 0;
}

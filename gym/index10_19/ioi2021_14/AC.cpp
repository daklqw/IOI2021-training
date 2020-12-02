#include <bits/stdc++.h>

const int MAXN = 110;
typedef long long LL;
void bye() {
	std::cout << "unstable" << std::endl;
	exit(0);
}
int xs[MAXN], ys[MAXN];
int n;
int cross(int x, int y, int z) {
	int x1 = xs[y] - xs[x], x2 = xs[z] - xs[y];
	int y1 = ys[y] - ys[x], y2 = ys[z] - ys[y];
	return x1 * y2 - x2 * y1;
}
LL up(LL x, LL y) {
	return (x + y - 1) / y;
}
LL down(LL x, LL y) {
	return x / y;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	LL L = 0x3f3f3f3f, R = (int) 0xc0c0c0c0;
	for (int i = 0; i < n; ++i) {
		std::cin >> xs[i] >> ys[i];
		if (ys[i] == 0) {
			L = std::min<LL>(L, xs[i]);
			R = std::max<LL>(R, xs[i]);
		}
	}
	LL all = 0, px = 0;
	for (int i = 0; i < n; ++i) {
		int x = n, y = i, z = (i + 1) % n;
		int v = cross(x, y, z);
		all += v;
		px += (LL) (xs[y] + xs[z]) * v;
	}
	all *= 3;
	if (all < 0) px = -px, all = -all;
	LL ax = xs[0];
	LL la = L * all - px, lm = ax - L;
	LL ra = px - all * R, rm = R - ax;
	if (lm == 0 && la > 0) bye();
	if (rm == 0 && ra > 0) bye();
	if (L <= ax && ax <= R) {
		LL lhs = lm == 0 ? 0 : down(la, lm * 6);
		LL rhs = rm == 0 ? 0 : down(ra, rm * 6);
		LL at = std::max(std::max(lhs, rhs), 0ll);
		std::cout << at << " .. inf\n";
	} else {
		LL l, r;
		if (ax < L)
			l = down(ra, rm * 6), r = up(-la, -lm * 6);
		else
			l = down(la, lm * 6), r = up(-ra, -rm * 6);
		l = std::max(l, 0ll);
		if (l > r) bye();
		std::cout << l << " .. " << r << '\n';
	}
	return 0;
}

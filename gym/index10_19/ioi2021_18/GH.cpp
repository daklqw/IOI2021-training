#include <bits/stdc++.h>

#include "hack.h"
std::mt19937_64 rd(114514);
typedef long long LL;
typedef long double db;
//LL query(LL n) {
//	std::cout << "? " << n << std::endl;
//	LL v; std::cin >> v;
//	return v;
//}
const int lim = 3e4;
int val(LL x) {
	++x;
	int r = std::__lg(x);
	if (x & (x - 1)) ++r;
	return r;
}
int cost(LL a, LL b) {
	return val(a) * val(b);
}
int mul(LL & a, LL b, LL mod) {
	int v = cost(a, b);
	LL r = a * b - (LL) ((db) a * b / mod + 0.5) * mod;
	r += r >> 63 & mod;
	a = r;
	return v;
}
int calc(LL a, LL d, LL n) {
	LL r = 1; int b = 0;
	for (int i = 0; i < 60; ++i) {
		if ((d >> i & 1))
			b += mul(r, a, n);
		b += mul(a, a, n);
	}
	return b;
}
int raw(LL a, LL n) {
	int b = 0;
	for (int i = 0; i < 60; ++i)
		b += mul(a, a, n);
	return b;
}
LL A[lim], R[lim];
int res[lim];
db cov(db * A, db * B) {
	db sa = 0, sb = 0;
	for (int i = 0; i < lim; ++i)
		sa += A[i], sb += B[i];
	sa /= lim, sb /= lim;
	db res = 0;
	for (int i = 0; i < lim; ++i)
		res += (A[i] - sa) * (B[i] - sb);
	return res / lim;
}
const int TC = 15;
db rnda(LL v, LL n) {
	int sm = 0;
	for (int i = 0; i < TC; ++i) {
		LL t = rd() % n;
		sm += cost(t, v);
	}
	return sm / (db) TC;
}
db mx[lim], am[lim], nm[lim], ori[lim];
// db tst1[lim];
LL solve(LL n) {
	for (int i = 0; i < lim; ++i) {
		res[i] = query(A[i] = rd() % n);
		res[i] -= raw(A[i], n);
		R[i] = 1;
	}
	LL ans = 0;
	for (int i = 0; i < 60; ++i) {
		int cho = 1;
		if (i > 0) {
			for (int j = 0; j < lim; ++j) {
				ori[j] = res[j];
				LL t = R[j];
				nm[j] = rnda(t, n);
				mx[j] = mul(t, A[j], n);
				am[j] = rnda(t, n) + mx[j];
				// tst1[j] = ori[j] - nm[j];
			}
			db tar = cov(ori, mx);
			db c0 = cov(nm, mx);
			db c1 = cov(am, mx);
		//	std::cerr << "GET " << tar << ' ' << c0 << ' ' << c1 << std::endl;
		//	std::cerr << "TEST: " << cov(tst1, mx) << std::endl;
			if (std::abs(tar - c0) < std::abs(tar - c1))
				cho = 0;
		}
		if (cho) {
			ans |= 1ll << i;
			for (int j = 0; j < lim; ++j)
				res[j] -= mul(R[j], A[j], n);
		}
		// std::cerr << "NOW " << i << " : " << cho << ' ' << ans << std::endl;
		for (int j = 0; j < lim; ++j)
			mul(A[j], A[j], n);
	}
	return ans;
}
//int main() {
//	LL n; std::cin >> n;
//	LL ans = solve(n);
//	std::cout << "! " << ans << std::endl;
//	return 0;
//}

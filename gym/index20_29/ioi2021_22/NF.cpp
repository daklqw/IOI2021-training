#include <bits/stdc++.h>

const int mod = 1e6 + 3;
typedef long long LL;
void reduce(int & x) { x += x >> 31 & mod; }
int mul(int a, int b) { return (LL) a * b % mod; }
const int MAXN = 2e5 + 10;
int pwA[MAXN], pwB[MAXN];
int fac[mod], inv[mod];
int C(int a, int b) {
	return (LL) fac[a] * inv[b] % mod * inv[a - b] % mod;
}
void fma(int & x, int y, int z) {
	x = ((LL) y * z + x) % mod;
}
void fms(int & x, int y, int z) {
	x = ((LL) (mod - y) * z + x) % mod;
}
int calc(int x, int y) {
	if (x < 0 || y < 0) return 0;
	return (LL) C(x + y, x) * pwA[x] % mod * pwB[y] % mod;
}
int n, A, B, D;
int main() {
	fac[0] = fac[1] = inv[0] = inv[1] = 1;
	for (int i = 2; i != mod; ++i) {
		fac[i] = mul(fac[i - 1], i);
		inv[i] = mul(inv[mod % i], mod - mod / i);
	}
	for (int i = 2; i != mod; ++i)
		inv[i] = mul(inv[i - 1], inv[i]);
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> B >> A >> D;
	for (int i = *pwA = 1; i <= n; ++i)
		pwA[i] = mul(pwA[i - 1], A);
	for (int i = *pwB = 1; i <= n; ++i)
		pwB[i] = mul(pwB[i - 1], B);
	static int li[MAXN];
	int ans = 0, Ans = 0;
	for (int i = 1; i <= n; ++i) {
		std::cin >> li[i];
		if (i > 1)
			fma(ans, mul(calc(n - i, n - 2), B), li[i]);
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> li[i];
		if (i > 1)
			fma(ans, mul(calc(n - 2, n - i), A), li[i]);
	}
	n -= 2;
	int L = 0, R = 0, v = Ans = calc(0, 0);
	for (int s = 1; s <= n + n; ++s) {
		v = mul(v, A + B);
		fms(v, calc(R, s - R - 1), A);
		fma(v, calc(L - 1, s - L), A);
		int l = std::max(0, s - n);
		int r = std::min(s, n);
		while (L > l)
			--L, reduce(v += calc(L, s - L) - mod);
		while (R < r)
			++R, reduce(v += calc(R, s - R) - mod);
		while (L < l)
			reduce(v -= calc(L, s - L)), ++L;
		while (R > r)
			reduce(v -= calc(R, s - R)), --R;
		reduce(Ans += v - mod);
	}
	fma(ans, Ans, D);
	std::cout << ans << std::endl;
	return 0;
}

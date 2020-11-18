#include <bits/stdc++.h>

const int MAXN = 4010;
typedef long long LL;
int mod;
void reduce(int & x) {
	x += x >> 31 & mod;
}
int n;
int fib[MAXN], f[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> n >> mod;
		fib[0] = 1, fib[1] = 2;
		memset(f, 0, n + 1 << 2);
		f[0] = 1;
		for (int i = 2; i < n; ++i)
			reduce(fib[i] = fib[i - 1] + fib[i - 2] - mod);
		for (int i = 0; i < n; ++i) {
			for (int j = n; ~j; --j) {
				f[j] = ((j ? f[j - 1] : 0) - (LL) f[j] * fib[i]) % mod;
				reduce(f[j]);
			}
		}
		int sm = 0;
		for (int i = 0, t; i < n; ++i) {
			std::cin >> t;
			sm = ((LL) t * f[i] + sm) % mod;
		}
		reduce(sm = -sm);
		std::cout << sm << '\n';
	}
	return 0;
}

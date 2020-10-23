#include <bits/stdc++.h>

const int MAXN = 64;
typedef unsigned long long LL;
int n;
LL A[MAXN], S;
namespace huge {
	void solve() {
		LL iv = 1, t = A[0];
		int dig = 0;
		while (!(t & 1)) t >>= 1, ++dig;
		for (int i = 0; i < 6; ++i)
			iv = iv * (2 - iv * t);
		for (int T = 0; T < (1 << dig); ++T) {
			for (int i = 1; i <= (1 << 23 - dig); i += 2) {
				static LL B[MAXN], T;
				T = S * i * iv;
				for (int j = 0; j < n; ++j)
					B[j] = A[j] * i * iv;
				bool can = B[0] > 0;
				for (int j = 1; j < n; ++j)
					can &= B[j] > B[j - 1];
				if (!can) continue;
				static int C[MAXN];
				for (int j = n - 1; ~j; --j) {
					C[j] = T / B[j];
					T %= B[j];
					can &= C[j] <= 1;
				}
				can &= T == 0;
				if (!can) continue;
				for (int j = 0; j < n; ++j)
					std::cout << C[j];
				std::cout << '\n';
				exit(0);
			}
			iv += 1ull << (64 - dig);
		}
	}
}
namespace small {
	LL lhs[1 << 21], rhs[1 << 21];
	int rkl[1 << 21], rkr[1 << 21];
	bool cmpl(int a, int b) {
		return lhs[a] < lhs[b];
	}
	bool cmpr(int a, int b) {
		return rhs[a] < rhs[b];
	}
	void solve() {
		const int L = n / 2, R = n - L;
		for (int i = 0; i != (1 << L); ++i) {
			rkl[i] = i;
			for (int j = 0; j != L; ++j)
				if (i >> j & 1)
					lhs[i] += A[j];
		}
		for (int i = 0; i != (1 << R); ++i) {
			rkr[i] = i;
			for (int j = 0; j != R; ++j)
				if (i >> j & 1)
					rhs[i] += A[j + L];
		}
		std::sort(rkl, rkl + (1 << L), cmpl);
		std::sort(rkr, rkr + (1 << R), cmpr);
		for (int i = 0; i != (1 << L); ++i) {
			LL tar = S - lhs[rkl[i]];
			int l = 0, r = (1 << R) - 1, at = -1;
			while (l <= r) {
				int mid = l + r >> 1;
				if (rhs[rkr[mid]] >= tar) at = mid, r = mid - 1;
				else l = mid + 1;
			}
			if (at != -1 && rhs[rkr[at]] == tar) {
				for (int j = 0; j != L; ++j)
					std::cout << (rkl[i] >> j & 1);
				for (int j = 0; j != R; ++j)
					std::cout << (rkr[at] >> j & 1);
				std::cout << '\n';
				exit(0);
			}
		}
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n; ++i)
		std::cin >> A[i];
	std::cin >> S;
	if (n <= 42) small::solve();
	else huge::solve();
	return 0;
}

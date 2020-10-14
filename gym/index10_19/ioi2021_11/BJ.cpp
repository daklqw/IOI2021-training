#include <bits/stdc++.h>

const int MAXN = 1 << 20;
const int N = 5e5;
const int mod = 998244353;
typedef long long LL;
void reduce(int & x) { x += x >> 31 & mod; }
int mul(int a, int b) { return (LL) a * b % mod; }
int pow(int a, int b, int res = 1) {
	for (; b; b >>= 1, a = mul(a, a)) if (b & 1) res = mul(res, a);
	return res;
}

int rev[MAXN], lim, wn[MAXN];
void NTT(int * A, int typ) {
	for (int i = 0; i < lim; ++i)
		if (i < rev[i])
			std::swap(A[i], A[rev[i]]);
	for (int mid = 1; mid < lim; mid <<= 1)
		for (int k = 0; k < lim; k += mid << 1)
			for (int l = 0; l < mid; ++l) {
				const int Y = mul(A[l + k + mid], wn[mid + l]);
				reduce(A[l + k + mid] = A[l + k] - Y);
				reduce(A[l + k] += Y - mod);
			}
	if (typ == -1) {
		const int liminv = pow(lim, mod - 2);
		for (int i = 0; i < lim; ++i)
			A[i] = mul(A[i], liminv);
		std::reverse(A + 1, A + lim);
	}
}
int A[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	for (int i = 1; i <= N; ++i)
		for (int j = i; j <= N; j += i)
			++A[j];
	int dig = -1; lim = 1;
	while (lim <= N + N) lim <<= 1, ++dig;
	for (int i = 1; i < lim; ++i)
		rev[i] = rev[i >> 1] >> 1 | (i & 1) << dig;
	for (int mid = 1; mid < lim; mid <<= 1) {
		const int Wn = pow(3, (mod - 1) / mid / 2);
		for (int i = 0, W = 1; i < mid; ++i)
			wn[mid + i] = W, W = mul(W, Wn);
	}
	NTT(A, 1);
	for (int i = 0; i != lim; ++i) A[i] = mul(A[i], A[i]);
	NTT(A, -1);
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int l, r; std::cin >> l >> r;
		int a = std::max_element(A + l, A + r + 1) - A;
		std::cout << a << ' ' << A[a] << '\n';
	}
	return 0;
}

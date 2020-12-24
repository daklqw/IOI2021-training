#include <bits/stdc++.h>

const int MAXN = 100010;
const int mod = 998244353;
typedef long long LL;
void reduce(int & x) { x += x >> 31 & mod; }
int mul(int a, int b) { return (LL) a * b % mod; }
int fastpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}
int head[MAXN], nxt[MAXN * 3], to[MAXN * 3], tot;
int deg[MAXN];
int n, prob[MAXN], m;
void addedge(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
	++deg[b], ++deg[e];
}
int A[510][510];
void guass(int n) {
	for (int i = 1; i <= n; ++i) {
		int at = 0;
		for (int j = i; j <= n; ++j)
			if (A[j][i]) { at = j; break; }
		std::swap(A[i], A[at]);
		const int IA = fastpow(A[i][i], mod - 2);
		for (int j = n + 1; j; --j) A[i][j] = mul(A[i][j], IA);
		for (int j = 1; j <= n; ++j) if (j != i) {
			for (int k = n + 1; k >= i; --k)
				reduce(A[j][k] -= mul(A[j][i], A[i][k]));
		}
	}
}
int C;
int main() {
	std::cin >> n >> m >> C;
	for (int i = 1, t; i <= C; ++i)
		std::cin >> t, prob[t] = 1;
	for (int i = 1, t1, t2; i <= m; ++i) {
		std::cin >> t1 >> t2;
		addedge(t1, t2);
	}
	for (int i = 1; i <= n; ++i) {
		int pb = mod + 1 - prob[i];
		A[i][i] = mod - 1;
		int id = fastpow(deg[i], mod - 2);
		id = mul(pb, id);
		for (int j = head[i]; j; j = nxt[j]) {
			reduce(A[i][to[j]] += id - mod);
			reduce(A[i][n + 1] -= id);
		}
	}
	guass(n);
	for (int i = 1; i <= n; ++i)
		std::cout << A[i][n + 1] << '\n';
	return 0;
}


#include <bits/stdc++.h>

const int mod = 1e9;
typedef long long LL;
void reduce(int & x) { x += x >> 31 & mod; }
int mul(int a, int b) { return (LL) a * b % mod; }
void fma(int & x, int y, int z) {
	x = ((LL) y * z + x) % mod;
}
const int MAXN = 1e5 + 10;
int n;
int match[MAXN];
int nxtop[MAXN];
char buf[MAXN];
struct poly {
	int A[11];
	void clear() { memset(A, 0, 44); }
	poly() { clear(); }
} ;
int co[11];
poly fold(poly x) {
	int sm = 0;
	for (int i = 0; i < 11; ++i)
		fma(sm, x.A[i], co[i]);
	x.clear();
	x.A[0] = sm;
	return x;
}
poly neg(poly x) {
	for (int i = 0; i < 11; ++i)
		reduce(x.A[i] = -x.A[i]);
	return x;
}
poly mul(poly x, poly y) {
	poly r;
	for (int i = 0; i < 11; ++i)
		for (int j = 0; j + i < 11; ++j)
			fma(r.A[i + j], x.A[i], y.A[j]);
	return r;
}
poly sqr(poly x) { return mul(x, x); }
poly inc(poly x, poly y) {
	for (int i = 0; i < 11; ++i)
		reduce(x.A[i] += y.A[i] - mod);
	return x;
}
poly dec(poly x, poly y) {
	for (int i = 0; i < 11; ++i)
		reduce(x.A[i] -= y.A[i]);
	return x;
}
poly single(int x, int y) {
	poly r;
	r.A[x] = y;
	return r;
}
poly solve(int l, int r) {
	if (buf[l] == '+') return fold(solve(l + 2, r));
	if (buf[l] == '-') return neg(solve(l + 1, r));
	if (buf[l] == '*') return sqr(solve(l + 2, r));
	int cur = l;
	if (match[l] != -1) cur = match[l];
	cur = nxtop[cur];
	if (cur < r) {
		if (buf[cur] == '+')
			return inc(solve(l, cur), solve(cur + 1, r));
		if (buf[cur] == '-')
			return dec(solve(l, cur), solve(cur + 1, r));
		if (buf[cur] == '*')
			return mul(solve(l, cur), solve(cur + 1, r));
		__builtin_unreachable();
	}
	if (buf[l] == '(')
		return solve(l + 1, r - 1);
	if (buf[l] == 'X') return single(1, 1);
	int v;
	if (buf[l] == 'N') v = n;
	else {
		v = 0;
		while (l < r)
			v = (v * 10 + buf[l++] - '0') % mod;
	}
	return single(0, v);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, t; i <= n; ++i) {
		std::cin >> t;
		int v = 1;
		for (int j = 0; j < 11; ++j) {
			reduce(co[j] += v - mod);
			v = mul(v, t);
		}
	}
	std::cin >> buf;
	const int L = strlen(buf);
	static int st[MAXN];
	int top = 0;
	memset(match, -1, sizeof match);
	for (int i = 0; i < L; ++i) {
		if (buf[i] == '(')
			st[++top] = i;
		else if (buf[i] == ')')
			match[st[top--]] = i;
	}
	for (int i = L - 1, lst = L; ~i; --i) {
		if (buf[i] == '+' || buf[i] == '-' || buf[i] == '*')
			lst = i;
		nxtop[i] = lst;
	}
	poly res = solve(0, L);
	std::cout << res.A[0] << std::endl;
	return 0;
}

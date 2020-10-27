#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 3e4 + 10;
LL A[MAXN], B[MAXN], C[MAXN];
int n, R;
int tr[MAXN];
LL li[MAXN];
void add(int x, int v) {
	for (; x <= n; x += x & -x)
		tr[x] += v;
}
int qry(int x) {
	int r = 0;
	for (; x; x &= x - 1)
		r += tr[x];
	return r;
}
int lb(LL x) {
	return std::lower_bound(li + 1, li + 1 + n, x) - li;
}
int ub(LL x) {
	return std::upper_bound(li + 1, li + 1 + n, x) - li;
}
LL getA(int x) {
	LL res = B[x + R - 1] - B[x - 1];
	res -= A[x + R - 1] - A[x - 1];
	return res;
}
LL getBR(int l) {
	int r = l + R - 1;
	LL res = B[r] + B[l - 1];
	res -= A[r] + C[l - 1];
	return res;
}
LL getBL(int l) {
	int r = l + R - 1;
	LL res = C[r] + A[l - 1];
	res -= B[r] + B[l - 1];
	return res;
}
LL solve(LL lim) {
	LL ans = 0;
	for (int i = 1; i <= n; ++i)
		li[i] = getA(i);
	std::sort(li + 1, li + 1 + n);
	memset(tr, 0, n + 1 << 2);
	for (int i = n; i; --i) {
		if (i + R <= n)
			add(lb(getA(i + R)), 1);
		LL v = lim - getA(i);
		ans += qry(ub(v) - 1);
	}
	for (int i = 1; i <= n; ++i)
		li[i] = getBR(i);
	std::sort(li + 1, li + 1 + n);
	memset(tr, 0, n + 1 << 2);
	for (int i = n; i; --i) {
		if (i + 1 <= n)
			add(lb(getBR(i + 1)), 1);
		if (i + R <= n)
			add(lb(getBR(i + R)), -1);
		LL v = lim - getBL(i);
		ans += qry(ub(v) - 1);
	}
	// std::cerr << "SOLVE " << lim << ' ' << ans << std::endl;
	return ans;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	LL K;
	std::cin >> n >> R >> K;
	for (int i = 1; i <= n; ++i)
		std::cin >> A[i], A[i] += A[i - 1];
	LL all = A[n];
	for (int i = 1; i <= n; ++i)
		std::cin >> B[i], B[i] += B[i - 1];
	for (int i = 1; i <= n; ++i)
		std::cin >> C[i], C[i] += C[i - 1];
	n = n - R + 1;
	LL l = all, r = 3e10 + 1, ans = -1;
	while (l <= r) {
		LL mid = l + r >> 1;
		if (solve(mid - all) >= K) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	std::cout << ans << std::endl;
	return 0;
}

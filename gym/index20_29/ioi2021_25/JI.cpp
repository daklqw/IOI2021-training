#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;

int A[MAXN], n;
int f[MAXN], g[MAXN];
void solve(int * f) {
	static int st[MAXN];
	memset(st, 0x3f, n << 2);
	int top = 0;
	for (int i = 1; i <= n; ++i) {
		int * at = std::upper_bound(st, st + top, A[i]);
		f[i] = (at - st) + 1;
		*at = std::min(*at, A[i]);
		top = std::max<int>(top, at - st + 1);
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, t; i <= n; ++i)
		std::cin >> t, A[t] = i;
	solve(f);
	std::reverse(A + 1, A + 1 + n);
	solve(g);
	int ans = 0;
	for (int i = 1; i <= n; ++i)
		ans = std::max(f[i] + g[n - i + 1] - 1, ans);
	std::cout << ans << std::endl;
	return 0;
}

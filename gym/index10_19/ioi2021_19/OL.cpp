#include <bits/stdc++.h>

const int MAXN = 310;
struct _ {
	int a, b, d;
} ps[MAXN];

int dp[MAXN][MAXN];
int n;
int calc(int l, int r) {
	if (dp[l][r] != -1) return dp[l][r];
	int at = -1, res = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i)
		if (l <= ps[i].a && ps[i].b <= r)
			if (at == -1) {
				at = i; break;
			}
	if (at == -1) return dp[l][r] = 0;
	for (int i = ps[at].a; i <= ps[at].b; ++i)
		res = std::min(res, calc(l, i - 1) + calc(i + 1, r));
	return dp[l][r] = res + ps[at].d;
}
int li[MAXN], bak;
bool cmp(_ a, _ b) { return a.d > b.d; }
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> n;
		bak = 0;
		for (int i = 1; i <= n; ++i) {
			std::cin >> ps[i].a >> ps[i].b >> ps[i].d;
			li[++bak] = ps[i].b;
		}
		std::sort(li + 1, li + 1 + bak);
		bak = std::unique(li + 1, li + 1 + bak) - li - 1;
		for (int i = 1; i <= n; ++i) {
			ps[i].a = std::lower_bound(li + 1, li + 1 + bak, ps[i].a) - li;
			ps[i].b = std::lower_bound(li + 1, li + 1 + bak, ps[i].b) - li;
		}
		std::sort(ps + 1, ps + 1 + n, cmp);
		for (int i = 0; i <= bak; ++i)
			memset(dp[i], -1, bak + 1 << 2);
		std::cout << calc(1, bak) << '\n';
	}
	return 0;
}

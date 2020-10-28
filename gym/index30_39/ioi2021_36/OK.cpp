#include <bits/stdc++.h>

const int MAXN = 150010;
int n, K;
struct _ {
	int v, c;
	bool operator < (_ b) const {
		return v < b.v;
	}
} ps[MAXN];
void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
int dp[10];
bool judge(int lim) {
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = K; ~j; --j)
			if (ps[i].v - (dp[j] + ps[i].c) >= lim) {
				if (j == K) return true;
				gmi(dp[j + 1], dp[j] + ps[i].c);
			}
	return false;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> n >> K;
		for (int i = 1; i <= n; ++i)
			std::cin >> ps[i].v >> ps[i].c;
		int l = 0, r = 1e6 + 1;
		std::sort(ps + 1, ps + 1 + n);
		while (l + 1 < r) {
			int mid = l + r >> 1;
			(judge(mid) ? l : r) = mid;
		}
		std::cout << l << '\n';
	}
	return 0;
}

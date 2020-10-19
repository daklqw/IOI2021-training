#include <bits/stdc++.h>

const int MAXN = 1010;
const int MAXK = 110;
const int MAXT = 260;
const int mod = 1e9 + 7;
typedef long long LL;
void reduce(int & x) { x += x >> 31 & mod; }
int mul(int a, int b) { return (LL) a * b % mod; }

int dp[MAXN][MAXK];
int n, T;
int f[2][MAXK][MAXT];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> T;
	int now = 0, lst = 1;
	f[0][0][0] = 1;
	const int U = (250 / (T + 1)) + 1;
	for (int _ = 1; _ <= n; ++_) {
		int L, R;
		std::cin >> R >> L;
		for (int DD = 1; DD <= R; ++DD) {
			std::swap(lst, now);
			for (int i = 0; i <= T; ++i)
				memset(f[now][i], 0, U + 1 << 2);
			for (int i = 0; i < T; ++i)
				for (int j = 0; j <= U; ++j)
					reduce(f[now][i][j] += f[lst][i + 1][j] - mod);
			for (int j = 1; j <= U; ++j)
				reduce(f[now][T][j] += f[lst][0][j - 1] - mod);
			for (int j = 0; j <= U; ++j)
				reduce(f[now][0][j] += f[lst][0][j] - mod);
		}
		std::swap(lst, now);
		for (int i = 0; i <= T; ++i)
			memset(f[now][i], 0, U + 1 << 2);
		for (int i = 0; i <= T; ++i)
			for (int j = 0; j <= U && j <= R - L; ++j)
				reduce(f[now][i][0] += f[lst][i][j] - mod);
	}
	int ans = 0;
	for (int i = 0; i <= T; ++i)
		reduce(ans += f[now][i][0] - mod);
	std::cout << ans << std::endl;
	return 0;
}

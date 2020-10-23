#include <bits/stdc++.h>

const int MAXN = 510;
typedef std::string str;
int get() {
	str mi, now;
	std::cin >> now;
	bool can = true;
	for (int i = 1; i <= 6; ++i)
		can &= now[i] == now[0];
	if (can) return -1;
	mi = now;
	int res = 0;
	for (int i = 1; i <= 6; ++i) {
		std::rotate(now.begin(), now.begin() + 1, now.end());
		if (now > mi) {
			res = i;
			mi = now;
		}
	}
	return res;
}
int n;
int C[7];
int dp[MAXN][MAXN][MAXN];
void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, lst = 0; i <= n; ++i) {
		int t = get();
		if (t != -1) {
			++C[(t - lst + 7) % 7];
			lst = t;
		}
	}
	int ans = 0;
	for (int i = 1; i <= 3; ++i) {
		int t = std::min(C[i], C[7 - i]);
		C[i] -= t;
		C[7 - i] -= t;
		ans += t;
	}
	static int rk[6];
	for (int i = 0; i < 6; ++i) rk[i] = i + 1;
	auto cmp = [] (int a, int b) {
		return C[a] > C[b];
	} ;
	std::sort(rk, rk + 6, cmp);
	static struct {
		int x, y, z, v;
	} li[8 * 8 * 8];
	int bak = 0;
	for (int i = 0; i <= 7 && i <= C[rk[0]]; ++i)
		for (int j = 0; j <= 7 && j <= C[rk[1]]; ++j)
			for (int k = 0; k <= 7 && k <= C[rk[2]]; ++k)
				if ((rk[0] * i + rk[1] * j + rk[2] * k) % 7 == 0) {
					if (!i && !j && !k) continue;
					li[bak].x = i;
					li[bak].y = j;
					li[bak].z = k;
					li[bak].v = i + j + k - 1;
					++bak;
				}
	memset(dp, 0x3f, sizeof dp);
	const int INF = 0x3f3f3f3f;
	dp[0][0][0] = 0;
	int tp = INF;
	int all = std::accumulate(C + 1, C + 7, 0);
	for (int i = 0; i <= C[rk[0]]; ++i)
		for (int j = 0; j <= C[rk[1]]; ++j)
			for (int k = 0; k <= C[rk[2]]; ++k)
				if (dp[i][j][k] != INF) {
					gmi(tp, dp[i][j][k] + all - i - j - k);
					for (int l = 0; l < bak; ++l) {
						gmi(dp[i + li[l].x][j + li[l].y][k + li[l].z], dp[i][j][k] + li[l].v);
					}
				}
	ans += tp;
	std::cout << ans << std::endl;
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 1e4 + 10;
typedef long long LL;
void gmi(LL & x, LL y) { x > y ? x = y : 0; }

int A, B;
int n, H;
int xs[MAXN], ys[MAXN];
LL dp[MAXN];
int sm[MAXN], rk[MAXN];
bool cmp(int x, int y) { return ys[x] < ys[y]; }
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> H >> A >> B;
	for (int i = 1; i <= n; ++i)
		std::cin >> xs[i] >> ys[i], ys[i] = H - ys[i], rk[i] = i;
	std::sort(rk + 1, rk + 1 + n, cmp);
	memset(dp, 0x3f, sizeof dp);
	dp[1] = A * ys[1];
	for (int i = 2; i <= n; ++i) {
		int L = 0, R = xs[i] - xs[1];
		auto add = [&L, &R, i] (int j) {
			int a = ys[j], b = xs[i] - xs[j];
			int p = std::sqrt((LL) 8 * a * b), q = (a + b) * 2;
			L = std::max(q - p, L);
			R = std::min(q + p, R);
		} ;
		int cur = 1;
		for (int j = i - 1; j; --j) {
			int D = xs[i] - xs[j];
			if (ys[j] * 2 < D) add(j);
			while (cur <= n && ys[rk[cur]] * 2 < D) {
				if (j < rk[cur] && rk[cur] <= i)
					add(rk[cur]);
				++cur;
			}
			if (L <= D && D <= R) {
				LL v = dp[j] + A * ys[i];
				v += (LL) D * D * B;
				gmi(dp[i], v);
			}
		}
	}
	if (dp[n] > 1e17) std::cout << "impossible" << std::endl;
	else std::cout << dp[n] << std::endl;
	return 0;
}

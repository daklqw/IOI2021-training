#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
int fail[MAXN], R[MAXN], nxt[MAXN][4], tot, lst;

void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
int getf(const char * P, int x) {
	while (*P != P[-R[x] - 1]) x = fail[x];
	return x;
}

int dp[MAXN], rec[MAXN];
int cur;
void ins(const char * P, int x) {
	int u = getf(P, lst);
	int & nt = nxt[u][x];
	bool pnew = !nt;
	if (pnew) {
		int f = nxt[getf(P, fail[u])][x];
		nt = ++tot;
		R[nt] = R[u] + 2;
		fail[nt] = f;
		dp[nt] = R[nt];
	}
	cur = nxt[getf(P, cur)][x];
	while (R[cur] * 2 > R[nt]) cur = fail[cur];
	if (pnew) {
		if (!(R[u] & 1)) {
			gmi(dp[nt], dp[u] + 1);
			gmi(dp[nt], R[nt] / 2 + rec[cur] + 1);
		}
		rec[nt] = std::min(rec[fail[nt]], dp[nt] - R[nt]);
	}
	lst = nt;
}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	static int mat[256];
	mat['A'] = 0, mat['C'] = 1, mat['G'] = 2, mat['T'] = 3;
	int T; std::cin >> T;
	while (T --> 0) {
		static char buf[MAXN];
		R[1] = -1, fail[0] = 1;
		tot = lst = 1;
		dp[0] = 1;
		cur = 1;
		std::cin >> buf + 1;
		int n = strlen(buf + 1);
		for (int i = 1; i <= n; ++i)
			ins(buf + i, mat[buf[i]]);
		int ans = n;
		for (int i = 2; i <= tot; ++i)
			gmi(ans, n - R[i] + dp[i]);
		std::cout << ans << '\n';
		const size_t SZ = tot + 1 << 2;
		memset(R, 0, SZ);
		memset(fail, 0, SZ);
		memset(dp, 0, SZ);
		memset(rec, 0, SZ);
		memset(nxt, 0, SZ << 2);
	}
	return 0;
}

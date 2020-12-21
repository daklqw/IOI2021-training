#include <bits/stdc++.h>

const int NN = 10, NM = NN + 2;
const int INF = 0x3f3f3f3f;
void gmi(int & x, int y) { x > y ? x = y : 0; }
typedef std::vector<int> VI;
VI S[NM];
int app[NM][NM];
int n;
int slen[NM][NM];
int dp[1 << NN][NM][NM][NM][NM];
int solve(int T, int lc, int llen, int rc, int rlen) {
	if (T + 1 == (1 << n) && lc == n && rlen == (int) S[rc].size())
		return 0;
	int & F = dp[T][lc + 1][llen + 1][rc + 1][rlen + 1];
	if (F != -1) return F;
	int ma = F = INF;
	if (llen == -1 && lc != n) {
		for (int i = 0; i < n; ++i) if (!(T >> i & 1))
			for (int j = slen[i][lc] - 1; j < (int) S[i].size(); ++j)
				gmi(ma, solve(T | 1 << i, i, j, rc, rlen));
		gmi(ma, solve(T, n, -1, rc, rlen));
	}
	for (int i = 0; i < n; ++i) if (!(T >> i & 1))
		if (rlen >= slen[rc][i])
			gmi(ma, solve(T | 1 << i, lc, llen, i, 0));
	for (int i = 1; i <= 9; ++i) {
		if (lc < n && (app[lc][i] == -1 || app[lc][i] > llen)) continue;
		if (rc < n && (app[rc][i] == -1 || app[rc][i] > rlen)) continue;
		int nl = lc < n && app[lc][i] == llen ? llen - 1 : llen;
		int nr = rc < n && app[rc][i] == rlen ? rlen + 1 : rlen;
		gmi(ma, solve(T, lc, nl, rc, nr) + 1);
		if (nl == llen - 1)
			gmi(ma, solve(T, lc, llen, rc, nr) + 1);
	}
	return F = ma;
}
bool incl(VI s, VI t) {
	for (auto x : t)
		if (std::find(s.begin(), s.end(), x) == s.end())
			return false;
	return true;
}
int main() {
	memset(dp, -1, sizeof dp);
	memset(app, -1, sizeof app);
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0, t; i < n; ++i) {
		while (std::cin >> t, t)
			S[i].push_back(t);
		for (int j = 0; j < (int) S[i].size(); ++j)
			app[i][S[i][j]] = j;
	}
	for (int i = 0; i < n; ++i)
		slen[i][n] = (int) S[i].size();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) if (i != j) {
			if (!incl(S[i], S[j])) {
				slen[i][j] = INF;
				continue;
			}
			const int sz = slen[i][j] = S[i].size();
			for (int k = 0; k < sz; ++k) {
				int cur = 0; bool can = true;
				for (int l = k; l < sz; ++l) {
					while (cur < (int) S[j].size() && S[j][cur] != S[i][l])
						++cur;
					if (cur++ == (int) S[j].size()) { can = false; break; }
				}
				if (can) { slen[i][j] = k; break; }
			}
			// std::cout << "TR: " << i << ' ' << j << " : " << slen[i][j] << '\n';
		}
	int ans = solve(0, n, -1, n, 0);
	for (int i = 0; i < n; ++i)
		gmi(ans, solve(1 << i, i, (int) S[i].size() - 1, n, 0));
	if (ans > 1e7) ans = -1;
	std::cout << ans << '\n';
	return 0;
}

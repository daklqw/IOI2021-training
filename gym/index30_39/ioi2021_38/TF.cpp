#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
int n, A[MAXN], cnt[MAXN], typ[MAXN];
int pre[MAXN];
int R[MAXN];
std::vector<int> hav[MAXN], dp[MAXN], frm[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int m = 0;
	int _n; std::cin >> _n;
	for (int i = 1, lst = -1, t; i <= _n; ++i) {
		std::cin >> t;
		m = std::max(m, t);
		if (t != lst) {
			++cnt[A[++n] = t];
			R[n] = i;
		} else ++R[n];
		lst = t;
	}
	for (int i = 1; i <= m; ++i)
		pre[i] = pre[i - 1] + cnt[i];
	for (int i = 1; i < n; ++i) {
		typ[i] = pre[A[i + 1] - 1] == pre[A[i]] ? A[i] : -1;
		if (typ[i] != -1)
			hav[typ[i]].push_back(i);
	}
	static bool forb[MAXN];
	for (int i = 2; i < n; ++i)
		if (cnt[A[i]] != 1) {
			if (typ[i - 1] != -1 && typ[i] != -1)
				forb[i] = true;
			}
	int lst = 0;
	hav[0].push_back(0);
	dp[0].push_back(0);
	for (int i = 1; i <= m; ++i) if (hav[i].size()) {
		hav[i].insert(hav[i].begin(), 0);
		static int pre[MAXN], suc[MAXN];
		const int LL = hav[lst].size();
		int at = 0;
		for (int j = 0; j < LL; ++j) {
			if (dp[lst][j] > dp[lst][at]) at = j;
			pre[j] = at;
		}
		at = LL - 1;
		for (int j = LL - 1; ~j; --j) {
			if (dp[lst][j] > dp[lst][at]) at = j;
			suc[j] = at;
		}
		const int L = hav[i].size();
		dp[i].resize(L);
		frm[i].resize(L);
		int cur = 0;
		for (int j = 0; j < L; ++j) {
			int t = hav[i][j];
			if (forb[t]) {
				while (hav[lst][cur] < t - 1) ++cur;
				assert(cur < LL);
				assert(hav[lst][cur] == t - 1);
				int x = pre[cur - 1];
				if (cur + 1 < LL) {
					int y = suc[cur + 1];
					if (dp[lst][y] > dp[lst][x])
						x = y;
				}
				frm[i][j] = x;
				dp[i][j] = dp[lst][x] + (t > 0);
			} else {
				frm[i][j] = pre[LL - 1];
				dp[i][j] = dp[lst][pre[LL - 1]] + (t > 0);
			}
		}
		lst = i;
	}
	int now = std::max_element(dp[lst].begin(), dp[lst].end()) - dp[lst].begin();
	for (int i = m; i; --i) if (hav[i].size()) {
		for (auto j : hav[i])
			if (j != hav[i][now])
				typ[j] = -1;
		now = frm[i][now];
	}
	typ[n] = -1;
	std::vector<int> ansl;
	lst = 0;
	for (int i = 1; i <= n; ++i)
		if (typ[i] == -1) {
			ansl.push_back(R[i] - R[lst]);
			lst = i;
		}
	std::cout << ansl.size() << '\n';
	for (auto t : ansl)
		std::cout << t << ' ';
	return 0;
}

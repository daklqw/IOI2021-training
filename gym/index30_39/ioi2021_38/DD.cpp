#include <bits/stdc++.h>

const int MAXN = 500010;
typedef long long LL;

struct ps {
	int t, d;
} A[MAXN], B[MAXN];

const LL INF = 0x3f3f3f3f3f3f3f3fLL;
LL calc(int a, int b) {
	if (B[b].t <= A[a].t && B[b].d < A[a].d) return -INF;
	return (LL) (B[b].t - A[a].t) * (B[b].d - A[a].d);
}
LL ans = 0;
int getbest(int u, int L, int R) {
	int at = -1; LL v = -INF - 1;
	for (int i = L; i <= R; ++i) {
		LL tv = calc(u, i);
		if (tv > v) v = tv, at = i;
	}
	ans = std::max(ans, v);
	return at;
}
void solve(int l, int r, int L, int R) {
	if (l > r || L > R) return ;
	int mid = l + r >> 1;
	int p = getbest(mid, L, R);
	solve(l, mid - 1, L, p);
	solve(mid + 1, r, p, R);
}
int n, m;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		std::cin >> A[i].d >> A[i].t;
	for (int i = 1; i <= m; ++i)
		std::cin >> B[i].d >> B[i].t;
	auto cmp = [] (ps a, ps b) {
		return a.t < b.t;
	};
	std::sort(A + 1, A + 1 + n, cmp);
	std::sort(B + 1, B + 1 + m, cmp);
	int tn = 0, tm = 0;
	for (int i = 1; i <= n; ++i) {
		if (tn && A[i].d >= A[tn].d) continue;
		A[++tn] = A[i];
	}
	for (int i = 1; i <= m; ++i) {
		while (tm && B[i].d >= B[tm].d) --tm;
		B[++tm] = B[i];
	}
	solve(1, tn, 1, tm);
	std::cout << ans << std::endl;
	return 0;
}

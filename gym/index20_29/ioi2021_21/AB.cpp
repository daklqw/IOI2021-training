#include <bits/stdc++.h>

const int MAXN = 1e4 + 10;
typedef long double db;
typedef long long LL;
const LL NINF = 0xc0c0c0c0c0c0c0c0ll;

inline db pw(db x) {
	return x * x;
}
LL pre[MAXN];
LL dp[MAXN];
int n, W;
struct _ {
	int v, d;
	bool operator < (_ b) const {
		return v > b.v;
	}
} li[260];
int bak;

LL f[MAXN], g[MAXN];
LL calc(int l, int r) {
	return f[l] == NINF ? NINF : f[l] + pre[r - l];
}
int getbest(int u, int l, int r) {
	r = std::min(r, u + 1);
	LL v = NINF;
	int at = l;
	for (int i = l; i < r; ++i) {
		LL t = calc(i, u);
		if (t > v) v = t, at = i;
	}
	g[u] = v;
	return at;
}
void solve(int l, int r, int ml, int mr) {
	if (l >= r || ml >= mr) return ;
	int mid = l + r >> 1;
	int p = getbest(mid, ml, mr);
	solve(l, mid, ml, p + 1);
	solve(mid + 1, r, p, mr);
}
db ws[260];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> W;
	memset(dp, 0xc0, sizeof dp);
	dp[0] = 0;
	for (int T = 1; T <= n; ++T) {
		static char buf[10];
		std::cin >> buf;
		if (*buf == 'D') {
			int w, a, b;
			std::cin >> w >> a >> b;
			for (int i = 1; i * w <= W; ++i)
				pre[i] = pre[i - 1] + (a - b * (i - 1));
			for (int i = 0; i < w; ++i) {
				int k = 0;
				for (int j = i; j <= W; j += w, ++k)
					f[k] = dp[j];
				solve(0, k, 0, k);
				k = 0;
				for (int j = i; j <= W; j += w, ++k)
					dp[j] = g[k];
			}
		} else {
			std::cin >> li[bak].v >> li[bak].d;
			++bak;
		}
	}
	if (dp[W] == NINF && !bak) {
		std::cout << "impossible" << std::endl;
		return 0;
	}
	std::sort(li, li + bak);
	db now = 0;
	for (int i = 1; i <= bak; ++i) {
		for (int j = 0; j < i; ++j)
			if (!li[j].d) {
				now = 1e100;
			} else {
				now += (li[i - 1].v - li[i].v) / (db) li[j].d;
			}
		ws[i] = now;
	}
	db ans = -1e100;
	for (int i = 0; i <= W; ++i) {
		int j = 1;
		while (j < bak && ws[j] <= i) ++j;
		db t = i - ws[j - 1], sm = 0, ti = 0;
		if (bak) {
			if (ws[j] < 1e99) {
				for (int k = 0; k < j; ++k)
					sm += 1 / (db) li[k].d;
				t = li[j - 1].v - t / sm;
			} else {
				ti += t * li[j - 1].v;
				t = li[j - 1].v;
			}
			for (int k = 0; k < j; ++k) if (li[k].d)
				ti += (pw(li[k].v) - pw(t)) / li[k].d / 2;
		} else ti = i == 0 ? 0. : -1e100;
		ans = std::max(ans, dp[W - i] + ti);
	}
	std::cout << std::fixed << std::setprecision(10);
	std::cout << ans << std::endl;
	return 0;
}

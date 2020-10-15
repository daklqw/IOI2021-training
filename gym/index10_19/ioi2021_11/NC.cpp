#include <bits/stdc++.h>

const int MAXN = 1e6 + 10;
const int MAXP = 2e5 + 10;
int tr[MAXN << 2];
int add[MAXN << 2], set[MAXN << 2];
void mkadd(int u, int v) {
	add[u] += v, tr[u] += v;
}
void mkset(int u, int v) {
	add[u] = 0, tr[u] = set[u] = v;
}
void pushdown(int u) {
	if (set[u] != -1) {
		mkset(u << 1, set[u]);
		mkset(u << 1 | 1, set[u]);
		set[u] = -1;
	}
	if (int & t = add[u]) {
		mkadd(u << 1, t);
		mkadd(u << 1 | 1, t);
		t = 0;
	}
}
int qry(int u, int l, int r, int tar) {
	if (l == r) return tr[u];
	int mid = l + r >> 1;
	pushdown(u);
	if (tar <= mid) return qry(u << 1, l, mid, tar);
	return qry(u << 1 | 1, mid + 1, r, tar);
}
void mdfset(int u, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) return mkset(u, v);
	int mid = l + r >> 1;
	pushdown(u);
	if (L <= mid) mdfset(u << 1, l, mid, L, R, v);
	if (mid < R) mdfset(u << 1 | 1, mid + 1, r, L, R, v);
}
void mdfadd(int u, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) return mkadd(u, v);
	int mid = l + r >> 1;
	pushdown(u);
	if (L <= mid) mdfadd(u << 1, l, mid, L, R, v);
	if (mid < R) mdfadd(u << 1 | 1, mid + 1, r, L, R, v);
}

std::vector<int> cow[MAXN], flo[MAXN], blo[MAXN];
const int R = 1e6 + 1;
int ys[MAXP], ansl[MAXP];
struct rect {
	int y1, y2;
} fs[MAXP];
int val[MAXP];
std::set<int> hav;
int get(int x) {
	auto it = hav.upper_bound(x);
	return it == hav.begin() ? 0 : *--it;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	memset(set, -1, sizeof set);
	memset(val, -1, sizeof val);
	int n;
	std::cin >> n;
	for (int i = 1, x1, x2; i <= n; ++i) {
		std::cin >> fs[i].y1 >> x1 >> fs[i].y2 >> x2;
		blo[x2].push_back(i);
		blo[x1 - 1].push_back(i);
	}
	std::cin >> n;
	for (int i = 1, x, y; i <= n; ++i) {
		std::cin >> y >> x;
		flo[x].push_back(y);
	}
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
		std::cin >> ys[i] >> x;
		cow[x].push_back(i);
	}
	auto cmp = [] (int a, int b) {
		return fs[a].y1 < fs[b].y1;
	} ;
	for (int i = R; i; --i) {
		std::sort(blo[i].begin(), blo[i].end(), cmp);
		const int L = blo[i].size();
		int lst = 0;
		for (int T = 0; T < L; ++T) {
			const int t = blo[i][T];
			rect p = fs[t];
			if (val[t] == -1) {
				val[t] = qry(1, 0, R, p.y2 + 1);
				hav.insert(p.y1);
				hav.insert(p.y2 + 1);
				mdfset(1, 0, R, p.y1, p.y2, 0);
			} else {
				hav.erase(p.y1);
				hav.erase(p.y2 + 1);
				int v = qry(1, 0, R, p.y2 + 1);
				mdfset(1, 0, R, p.y1, p.y2, v);
				int lst = get(p.y1);
				mdfadd(1, 0, R, lst, p.y1 - 1, v - val[t]);
			}
		}
		for (auto t : flo[i])
			mdfadd(1, 0, R, get(t), t, 1);
		for (auto t : cow[i])
			ansl[t] = qry(1, 0, R, ys[t]);
	}
	for (int i = 1; i <= n; ++i)
		std::cout << ansl[i] << '\n';
	return 0;
}

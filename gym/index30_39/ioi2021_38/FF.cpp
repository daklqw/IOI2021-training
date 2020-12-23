#include <bits/stdc++.h>

const int MAXN = 5e5 + 10;
const int MAXM = MAXN * 4;
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef long double db;
struct vec { int x, y; } ;
int cur;
struct seg {
	vec x, y; int id;
	LL getv() const {
		return (LL) x.y * (y.x - x.x) + (LL) (y.y - x.y) * (cur - x.x);
	}
	bool operator < (seg b) const {
		return (db) getv() * (b.y.x - b.x.x) > (db) b.getv() * (y.x - x.x);
	}
} ss[MAXN];
std::set<seg> S;
int head[MAXN], nxt[MAXM], to[MAXM], tot;
int ind[MAXN];
void adde(int b, int e) {
	// std::cerr << "ADDE " << b << ' ' << e << std::endl;
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	++ind[e];
}
int li[MAXN << 1], bak;
int n, DL, DR;
typedef std::pair<int, int> pi;
std::map<int, std::vector<pi>> mdf;
int lb(int x) {
	return std::lower_bound(li + 1, li + 1 + bak, x) - li;
}

struct _ {
	int mi, ma, pm, sm;
} tr[MAXN << 3];
int tagadd[MAXN << 3];
int tagset[MAXN << 3];
_ operator + (_ x, _ y) {
	_ r;
	r.mi = std::min(x.mi, y.mi);
	r.ma = std::max(x.ma, y.ma);
	r.pm = x.pm && y.pm && x.mi >= y.ma;
	r.sm = x.sm && y.sm && x.ma <= y.mi;
	return r;
}
void mkadd(int u, int v) {
	tr[u].mi += v;
	tr[u].ma += v;
	tagadd[u] += v;
}
void mkset(int u, int v) {
	tr[u].mi = tr[u].ma = v;
	tr[u].pm = tr[u].sm = true;
	tagadd[u] = 0;
	tagset[u] = v;
}
const int NONE = -12243;
void pushdown(int u) {
	if (tagset[u] != NONE) {
		mkset(u << 1, tagset[u]);
		mkset(u << 1 | 1, tagset[u]);
		tagset[u] = NONE;
	}
	if (int & t = tagadd[u]) {
		mkadd(u << 1, t);
		mkadd(u << 1 | 1, t);
		t = 0;
	}
}
void mkset(int u, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) return mkset(u, v);
	int mid = (l + r) >> 1;
	pushdown(u);
	if (L <= mid) mkset(u << 1, l, mid, L, R, v);
	if (mid < R) mkset(u << 1 | 1, mid + 1, r, L, R, v);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void mkadd(int u, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) return mkadd(u, v);
	int mid = (l + r) >> 1;
	pushdown(u);
	if (L <= mid) mkadd(u << 1, l, mid, L, R, v);
	if (mid < R) mkadd(u << 1 | 1, mid + 1, r, L, R, v);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
int minc;
void premin(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		_ tp = (_) {minc, minc, true, false};
		tp = tp + tr[u];
		if (!tp.pm) {
			if (minc <= tr[u].mi) { mkset(u, minc); return ; }
		} else { minc = tr[u].mi; return ; }
	}
	int mid = (l + r) >> 1;
	pushdown(u);
	if (L <= mid) premin(u << 1, l, mid, L, R);
	if (mid < R) premin(u << 1 | 1, mid + 1, r, L, R);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}
void sucmin(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		_ tp = (_) {minc, minc, false, true};
		tp = tr[u] + tp;
		if (!tp.sm) {
			if (minc <= tr[u].mi) { mkset(u, minc); return ; }
		} else { minc = tr[u].mi; return ; }
	}
	int mid = (l + r) >> 1;
	pushdown(u);
	if (mid < R) sucmin(u << 1 | 1, mid + 1, r, L, R);
	if (L <= mid) sucmin(u << 1, l, mid, L, R);
	tr[u] = tr[u << 1] + tr[u << 1 | 1];
}

int qry(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) return tr[u].mi;
	int mid = (l + r) >> 1, res = INF;
	pushdown(u);
	if (L <= mid) res = qry(u << 1, l, mid, L, R);
	if (mid < R) res = std::min(res, qry(u << 1 | 1, mid + 1, r, L, R));
	return res;
}
void debug() {
	for (int i = 1; i <= bak; ++i) {
		int v = qry(1, 1, bak, i, i);
		if (v >= 1e9)
			std::cout << "INF ";
		else std::cout << v << ' ';
	}
	std::cout << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> DL >> DR >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> ss[i].x.x >> ss[i].x.y;
		std::cin >> ss[i].y.x >> ss[i].y.y;
		if (ss[i].x.x > ss[i].y.x)
			std::swap(ss[i].x, ss[i].y);
		ss[i].id = i;
		mdf[li[++bak] = ss[i].x.x].emplace_back(1, i);
		mdf[li[++bak] = ss[i].y.x].emplace_back(-1, i);
	}
	li[++bak] = DL, li[++bak] = DR;
	std::sort(li + 1, li + 1 + bak);
	bak = std::unique(li + 1, li + 1 + bak) - li - 1;
	for (auto t : mdf) {
		auto & V = t.second;
		std::sort(V.begin(), V.end());
		cur = t.first;
		for (auto t : V) {
			int id = t.second;
			if (t.first == -1) S.erase(ss[id]);
			else {
				auto it = S.insert(ss[id]).first;
				if (it != S.begin())
					adde(std::prev(it)->id, id);
				if (std::next(it) != S.end())
					adde(id, std::next(it)->id);
			}
		}
	}
	static int que[MAXN], be = 1, tl = 1;
	for (int i = 1; i <= n; ++i)
		if (!ind[i])
			que[tl++] = i;
	while (be < tl) {
		int t = que[be++];
		for (int i = head[t]; i; i = nxt[i])
			if (!--ind[to[i]])
				que[tl++] = to[i];
	}
	mkset(1, 0x3f3f3f3f);
	mkset(1, 1, bak, lb(DL), lb(DR) - 1, 0);
	// debug();
	for (int T = n; T; --T) {
		const int i = que[T];
		int L = lb(ss[i].x.x), R = lb(ss[i].y.x);
		mkadd(1, 1, bak, L, R - 1, 1);
		minc = INF;
		if (ss[i].x.y > ss[i].y.y)
			sucmin(1, 1, bak, L, R);
		else premin(1, 1, bak, L - 1, R - 1);
		// debug();
	}
	int ans = qry(1, 1, bak, lb(DL), lb(DR));
	std::cout << ans << std::endl;
	return 0;
}


#include <bits/stdc++.h>

const int MAXM = 1e5 + 10;
const int MAXV = 1e6 + 10;
const int MAXP = 1e5 + 1010;
const int INF = 0x3f3f3f3f;
const int MAXD = MAXM * 2 * 21;
struct LCT {
	int fa[MAXP], son[MAXP][2], val[MAXP], mx[MAXP];
	int rev[MAXP];
	int gma(int x, int y) {
		return val[x] > val[y] ? x : y;
	}
	LCT() { val[0] = -INF; }
	void update(int x) {
		mx[x] = x;
		if (son[x][0])
			mx[x] = gma(mx[x], mx[son[x][0]]);
		if (son[x][1])
			mx[x] = gma(mx[x], mx[son[x][1]]);
	}
	void mkrev(int x) {
		rev[x] ^= 1;
		std::swap(son[x][0], son[x][1]);
	}
	void pushdown(int x) {
		if (rev[x]) {
			if (son[x][0]) mkrev(son[x][0]);
			if (son[x][1]) mkrev(son[x][1]);
			rev[x] = false;
		}
	}
	int get(int x, int b = 1) {
		return son[fa[x]][b] == x;
	}
	int isroot(int x) {
		return !get(x, 0) && !get(x, 1);
	}
	void rotate(int x) {
		int y = fa[x], z = fa[y];
		bool b = get(x);
		if (!isroot(y))
			son[z][get(y)] = x;
		son[y][b] = son[x][!b];
		son[x][!b] = y;
		fa[x] = z;
		fa[y] = x;
		if (son[y][b])
			fa[son[y][b]] = y;
		update(y);
	}
	void splay(int x) {
		static int st[MAXP], top;
		for (int y = st[top = 1] = x; !isroot(y); )
			st[++top] = y = fa[y];
		while (top)
			pushdown(st[top--]);
		for (; !isroot(x); rotate(x))
			if (!isroot(fa[x]))
				rotate(get(x) ^ get(fa[x]) ? x : fa[x]);
		update(x);
	}
	void access(int x) {
		int t = 0;
		while (x) {
			splay(x);
			son[x][1] = t;
			update(x);
			t = x;
			x = fa[x];
		}
	}
	void mkroot(int x) {
		access(x);
		splay(x);
		mkrev(x);
	}
	int split(int x, int y) {
		mkroot(x);
		access(y);
		splay(y);
		return y;
	}
	void link(int x, int y) {
		mkroot(x);
		fa[x] = y;
	}
	void cut(int x, int y) {
		split(x, y);
		fa[x] = son[y][0] = 0;
		update(y);
	}
	int conn(int x, int y) {
		split(x, y);
		while (son[y][0]) {
			pushdown(y);
			y = son[y][0];
		}
		splay(y);
		return x == y;
	}
	void init(int u, int v) {
		fa[u] = son[u][0] = son[u][1] = rev[u] = 0;
		mx[u] = u, val[u] = v;
	}
} lct;
int n, m;
struct _ {
	int x, y, v;
	bool operator < (_ b) const {
		return v > b.v;
	}
} es[MAXM];

struct SGT {
	int ls[MAXD], rs[MAXD], val[MAXD], tot;
	void clear() {
		memset(ls, 0, tot + 1 << 2);
		memset(rs, 0, tot + 1 << 2);
		memset(val, 0, tot + 1 << 2);
		tot = 0;
	}
	int add(int u, int l, int r, int tar, int v) {
		++tot;
		ls[tot] = ls[u];
		rs[tot] = rs[u];
		val[tot] = val[u] + v;
		u = tot;
		if (l == r) return u;
		int mid = l + r >> 1;
		if (tar <= mid)
			ls[u] = add(ls[u], l, mid, tar, v);
		else
			rs[u] = add(rs[u], mid + 1, r, tar, v);
		return u;
	}
	int qry(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R)
			return val[u];
		int mid = l + r >> 1;
		int res = 0;
		if (L <= mid)
			res += qry(ls[u], l, mid, L, R);
		if (mid < R)
			res += qry(rs[u], mid + 1, r, L, R);
		return res;
	}
} sg;
int rt[MAXV];

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T;
	std::cin >> T;
	while (T --> 0) {
		std::cin >> n >> m;
		for (int i = 1; i <= m; ++i)
			std::cin >> es[i].x >> es[i].y >> es[i].v;
		std::sort(es + 1, es + 1 + m);
		sg.clear();
		for (int i = 1; i <= n; ++i)
			lct.init(i, -INF);
		const int lim = 1e6;
		for (int i = 1; i <= m; ++i) {
			rt[i] = rt[i - 1];
			lct.init(i + n, es[i].v);
			if (lct.conn(es[i].x, es[i].y)) {
				int e = lct.mx[lct.split(es[i].x, es[i].y)] - n;
				lct.cut(es[e].x, e + n);
				lct.cut(es[e].y, e + n);
				rt[i] = sg.add(rt[i], 1, lim, es[e].v, -es[e].v);
			}
			lct.link(es[i].x, i + n);
			lct.link(es[i].y, i + n);
			rt[i] = sg.add(rt[i], 1, lim, es[i].v, es[i].v);
		}
		int Q;
		std::cin >> Q;
		int lans = 0;
		while (Q --> 0) {
			int l, r;
			std::cin >> l >> r;
			l -= lans, r -= lans;
			lans = 0;
			if (l <= r) {
				int L = 1, R = m + 1;
				while (L + 1 < R) {
					int mid = L + R >> 1;
					if (es[mid].v < l) R = mid;
					else L = mid;
				}
				lans = sg.qry(rt[L], 1, lim, l, r);
			}
			std::cout << lans << '\n';
		}
	}
	return 0;
}

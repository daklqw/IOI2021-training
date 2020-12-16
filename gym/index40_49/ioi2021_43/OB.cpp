#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;

typedef long long LL;
struct vec {
	int x, y;
	vec() { x = y = 0; }
	vec(LL a, LL b) { x = a, y = b; }
	LL operator ^ (vec b) const { return (LL) x * b.y - (LL) y * b.x; }
	LL operator * (vec b) const { return (LL) x * b.x + (LL) y * b.y; }
	vec operator - (vec b) const { return vec(x - b.x, y - b.y); }
	vec operator + (vec b) const { return vec(x + b.x, y + b.y); }
	bool operator < (const vec & b) const {
		return x == b.x ? y < b.y : x < b.x;
	}
} ps[MAXN];
typedef std::vector<vec> VP;
inline LL cross(vec a, vec b, vec c) {
	return (b - a) ^ (c - a);
}
VP convexhull(VP ps) {
	std::sort(ps.begin(), ps.end());
	static vec st[MAXN]; int top = 0;
	for (vec i : ps) {
		while (top > 1 && cross(st[top - 2], st[top - 1], i) >= 0) --top;
		st[top++] = i;
	}
	return VP(st, st + top);
}
int n;
VP tr[MAXN << 2];
void build(int u, int l, int r) {
	tr[u] = convexhull(VP(ps + l, ps + r + 1));
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
}
vec S, T, nor;
bool qry(const VP & li) {
	int l = 0, r = li.size();
	while (l + 1 < r) {
		int m = (l + r - 1) >> 1;
		LL vl = nor * li[m], vr = nor * li[m + 1];
		(vl >= vr ? r : l) = m + 1;
	}
	return cross(li[l], S, T) > 0;
}
int qry(int u, int l, int r) {
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (qry(tr[u << 1]))
		return qry(u << 1, l, mid);
	return qry(u << 1 | 1, mid + 1, r);
}
int qry(int u, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		if (qry(tr[u])) return qry(u, l, r);
		return 0;
	}
	int mid = (l + r) >> 1;
	if (L <= mid)
		if (int t = qry(u << 1, l, mid, L, R))
			return t;
	if (mid < R)
		if (int t = qry(u << 1 | 1, mid + 1, r, L, R))
			return t;
	return 0;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int Q; std::cin >> Q;
	while (Q --> 0) {
		std::cin >> n;
		for (int i = 1; i <= n; ++i)
			std::cin >> ps[i].x >> ps[i].y;
		build(1, 1, n);
		for (int i = 1; i < n; ++i) {
			S = ps[i], T = ps[i + 1];
			vec t = T - S;
			nor = vec(-t.y, t.x);
			int p = i + 1 == n ? 0 : qry(1, 1, n, i + 2, n);
			if (p) --p;
			std::cout << p << (" \n" [i == n - 1]);
		}
	}
	return 0;
}

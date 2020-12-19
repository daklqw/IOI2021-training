#include <bits/stdc++.h>

const int MAXN = 50010;
const int BLO = 100;
const int CNT = MAXN / BLO + 3;
typedef long long LL;
typedef std::pair<LL, int> pi;
struct vec {
	int x, y, id;
	vec() { x = y = 0; }
	vec(int a, int b) { x = a, y = b; }
	LL operator ^ (vec b) const { return (LL) x * b.y - (LL) y * b.x; }
	pi operator () (vec b) const {
		return pi((LL) x * b.x + (LL) y * b.y, id);
	}
	vec operator - (vec b) const { return vec(x - b.x, y - b.y); }
	vec operator + (vec b) const { return vec(x + b.x, y + b.y); }
	bool operator < (const vec & b) const {
		return x == b.x ? y > b.y : x < b.x;
	}
} arr[MAXN], qry[MAXN];
LL cross(vec a, vec b, vec c) {
	return (b - a) ^ (c - b);
}
int bel[MAXN];
int L[MAXN], R[MAXN], len[MAXN];
int n, m;
int P, N;
int A[MAXN];
vec tag[CNT];
void rebuild(int x) {
	vec * li = qry + L[x];
	std::copy(arr + L[x], arr + R[x] + 1, li);
	int & n = len[x] = R[x] - L[x] + 1;
	std::sort(li, li + n);
	int top = 0;
	for (int i = 0; i < n; ++i) {
		while (top > 1 && cross(li[top - 2], li[top - 1], li[i]) >= 0)
			--top;
		li[top++] = li[i];
	}
	n = top;
}
void mkadd(int x, vec v) {
	for (int i = x; i <= R[bel[x]]; ++i)
		arr[i] = arr[i] + v;
	rebuild(bel[x]);
	for (int i = bel[x] + 1; i <= bel[n]; ++i)
		tag[i] = tag[i] + v;
}
void gma(LL & x, LL y) {
	x < y ? x = y : 0;
}
const pi NINF(0xc0c0c0c0c0c0c0c0ll, -1);
int query() {
	pi ans = NINF;
	vec qs(-N, P);
	for (int i = 1; i <= bel[n]; ++i) {
		int l = L[i], r = l + len[i] - 1;
		LL bse = tag[i](qs).first;
		pi ma = NINF;
		while (l + 1 < r) {
			int mid = l + r >> 1;
			pi lp = qry[mid](qs);
			pi rp = qry[mid + 1](qs);
			ma = std::max(ma, std::max(lp, rp));
			if (lp >= rp) r = mid;
			else l = mid;
		}
		ma = std::max(ma, qry[l](qs));
		ma.first += bse;
		ans = std::max(ans, ma);
	}
	return -ans.second;
}
vec eff(int i, int v) {
	vec r;
	if (A[i] > 0) {
		P += v * A[i];
		r.x += v * A[i];
	} else {
		N += v * A[i];
		r.y += v * A[i];
	}
	return r;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::cin >> A[i];
		bel[i] = (i - 1) / BLO + 1;
		if (!L[bel[i]]) L[bel[i]] = i;
		R[bel[i]] = i;
		arr[i] = arr[i - 1] + eff(i, 1);
		arr[i].id = -i;
	}
	for (int i = 1; i <= bel[n]; ++i)
		rebuild(i);
	std::cout << query() << '\n';
	while (m --> 0) {
		int x, y;
		std::cin >> x >> y;
		vec dta = eff(x, -1);
		A[x] = y;
		dta = dta + eff(x, 1);
		mkadd(x, dta);
		std::cout << query() << '\n';
	}
	return 0;
}

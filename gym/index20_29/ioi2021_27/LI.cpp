#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;

int tr[MAXN << 2], tag[MAXN << 2];
void mkadd(int u, int v) {
	tr[u] += v, tag[u] += v;
}
void pushdown(int u) {
	if (int & t = tag[u]) {
		mkadd(u << 1, t);
		mkadd(u << 1 | 1, t);
		t = 0;
	}
}
void mdf(int u, int l, int r, int L, int R, int v) {
	if (L <= l && r <= R) return mkadd(u, v);
	int mid = l + r >> 1;
	pushdown(u);
	if (L <= mid) mdf(u << 1, l, mid, L, R, v);
	if (mid < R) mdf(u << 1 | 1, mid + 1, r, L, R, v);
	tr[u] = std::min(tr[u << 1], tr[u << 1 | 1]);
}
int left(int u, int l, int r, int R) {
	if (tr[u] != 0) return 0;
	if (l == r) return l;
	int mid = l + r >> 1;
	pushdown(u);
	if (mid < R)
		if (int t = left(u << 1 | 1, mid + 1, r, R))
			return t;
	return left(u << 1, l, mid, R);
}

int ls[MAXN], ansl[MAXN], ansr[MAXN];
std::vector<int> qs[MAXN];
struct info {
	int mi, to;
	bool operator < (info b) const {
		return mi < b.mi;
	}
};
std::priority_queue<info> que;
int n, m, A[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> A[i];
		mdf(1, 1, n, i, i, i);
	}
	std::cin >> m;
	for (int i = 1, r; i <= m; ++i) {
		std::cin >> ls[i] >> r;
		qs[r].push_back(i);
	}
	static info mi[MAXN], ma[MAXN];
	int tmi = 0, tma = 0;
	for (int i = 1; i <= n; ++i) {
		for (auto t : qs[i])
			que.push((info) {ls[t], t});
		while (tmi && A[i] < A[mi[tmi].mi])
			mdf(1, 1, n, mi[tmi].to, mi[tmi].mi, A[mi[tmi].mi]), --tmi;
		mdf(1, 1, n, mi[tmi].mi + 1, i, -A[i]);
		mi[tmi + 1] = (info) {i, mi[tmi].mi + 1}, ++tmi;
		while (tma && A[i] > A[ma[tma].mi])
			mdf(1, 1, n, ma[tma].to, ma[tma].mi, -A[ma[tma].mi]), --tma;
		mdf(1, 1, n, ma[tma].mi + 1, i, A[i]);
		ma[tma + 1] = (info) {i, ma[tma].mi + 1}, ++tma;
		mdf(1, 1, n, 1, n, -1);
		while (!que.empty()) {
			int t = que.top().to, v = que.top().mi;
			if (int lhs = left(1, 1, n, v)) {
				ansl[t] = lhs, ansr[t] = i;
				que.pop();
			} else break;
		}
	}
	for (int i = 1; i <= m; ++i)
		std::cout << ansl[i] << ' ' << ansr[i] << '\n';
	return 0;
}

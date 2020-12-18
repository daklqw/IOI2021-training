#include <bits/stdc++.h>

const int MAXN = 61;
struct rec {
	int x, y, l;
} ;
int ans;
typedef std::vector<rec> VI;
struct _ { int v, l; };
typedef std::vector<_> V;
VI ansl;
rec st[MAXN * MAXN];
int n, m;
int lim;
void dfs(int S, V A) {
	if (A.size() > lim) return ;
	if (S + A.size() - (A[0].v == m) >= ans) return ;
	if (A.size() == 1 && A[0].v == m) {
		ans = S;
		ansl = VI(st, st + S);
		return ;
	}
	if (A.size() > 1 && A.back().l == 1) {
		int sz = A.size();
		V t = A;
		st[S].x = n - 1;
		st[S].y = A[sz - 1].v;
		st[S].l = 1;
		if (A[sz - 1].v + 1 == A[sz - 2].v) {
			t.pop_back();
			++t.back().l;
		} else {
			++t.back().v;
		}
		dfs(S + 1, t);
		return ;
	}
	int sm = 0, lst = m;
	for (int i = 0; i < A.size(); ++i) {
		st[S].x = sm;
		st[S].y = A[i].v;
		const int L = std::min(A[i].l, lst - A[i].v);
		int down = 0;
		if (A.size() == 3) down = L - 1;
		for (int j = L; j > down; --j) {
			V t(A.begin(), A.begin() + i);
			st[S].l = j;
			if (!t.empty() && t.back().v == A[i].v + j)
				t.back().l += j;
			else
				t.push_back((_) {A[i].v + j, j});
			if (j != A[i].l)
				t.push_back((_) {A[i].v, A[i].l - j});
			t.insert(t.end(), A.begin() + i + 1, A.end());
			dfs(S + 1, t);
		}
		sm += A[i].l;
		lst = A[i].v;
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> n >> m;
		std::cerr << "NOW " << n << ' ' << m << std::endl;
		ans = 0x3f3f3f3f;
		for (lim = 1; lim <= 3; ++lim) {
			dfs(0, V({(_) {0, n}}));
		}
		std::cout << n << ' ' << m << '\n';
		std::cout << ansl.size() << '\n';
		for (auto t : ansl)
			std::cout << t.x << ' ' << t.y << ' ' << t.l << '\n';
		std::cout << '\n';
	}
	return 0;
}

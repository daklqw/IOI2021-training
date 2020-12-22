#include <bits/stdc++.h>

const int MAXN = 1e4 + 10;
void bye() {
	std::cout << "no\n";
	exit(0);
}
struct _ {
	int l, r;
	bool operator < (_ b) const { return l < b.l; }
} ls[MAXN];
int n, T;
void gmi(int & x, int y) { x > y ? x = y : 0; }
int lim[MAXN];
int R[MAXN], cur[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> T;
	for (int i = 1; i <= n; ++i) {
		std::cin >> ls[i].l >> ls[i].r;
		R[i] = ls[i].r;
	}
	std::sort(ls + 1, ls + 1 + n);
	for (int i = 1; i <= n; ++i)
		R[i] = ls[i].r, cur[i] = n;
	for (int l = n; l; --l) {
		lim[l] = ls[l].l;
		for (int r = 1; r <= n; ++r)
			if (ls[r].r >= ls[l].r) {
				R[r] -= T;
				int & c = cur[r];
				while (l <= c && R[r] < ls[c].l)
					gmi(R[r], lim[c--]);
				if (R[r] < ls[l].l) bye();
				gmi(lim[l], R[r] - T);
			}
	}
	std::cout << "yes\n";
	return 0;
}

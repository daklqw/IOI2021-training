#include <bits/stdc++.h>

const int MAXN = 2010;
void getLCP(char * x, char * y, int tar[][MAXN]) {
	const int L = strlen(x), R = strlen(y);
	for (int i = L - 1; ~i; --i)
		for (int j = R - 1; ~j; --j)
			tar[i][j] = x[i] == y[j] ? tar[i + 1][j + 1] + 1 : 0;
}
char lhs[MAXN], rhs[MAXN];
int n, m;
int AA[MAXN][MAXN], AB[MAXN][MAXN], BB[MAXN][MAXN];
int main() {
#define FILENAME "curiosity"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin.getline(lhs, MAXN);
	std::cin.getline(rhs, MAXN);
	n = strlen(lhs), m = strlen(rhs);
	getLCP(lhs, lhs, AA);
	getLCP(lhs, rhs, AB);
	getLCP(rhs, rhs, BB);
	int ansl = 0x3f3f3f3f, AL = -1, AR = -1, BL = -1, BR = -1;
	for (int l = 0; l < n; ++l) {
		int ma = 0;
		for (int j = 0; j < l; ++j)
			if (AA[j][l])
				ma = std::max(ma, AA[j][l]);
		static int buc[MAXN], rk[MAXN];
		memset(buc, 0, n + 1 << 2);
		for (int j = l; j < n; ++j)
			if (AA[j][l])
				++buc[AA[j][l]];
		for (int j = 1; j <= n; ++j)
			buc[j] += buc[j - 1];
		int all = buc[n];
		for (int j = n - 1; j >= l; --j)
			if (AA[j][l])
				rk[--buc[AA[j][l]]] = j;
		int cur = 0;
		for (int A = ma + 1; A + l <= n; ++A) {
			while (cur < all && AA[rk[cur]][l] < A)
				++cur;
			static int li[MAXN], bak;
			bak = 0;
			int lst = 0;
			for (int k = cur; k < all; ++k)
				li[bak++] = rk[k];
			std::sort(li, li + bak);
			int tb = 0;
			for (int k = 0; k < bak; ++k)
				if (li[k] >= lst) {
					li[tb++] = li[k];
					lst = li[k] + A;
				}
			bak = tb;
			if (li[0] != l);
				assert(li[0] == l);
			if ((m - n) % bak != 0) continue;
			int B = A + (m - n) / bak;
			if (B < 0) continue;
			if (A + B > ansl) continue;
			bool can = AB[0][0] >= li[0];
			for (int j = 0; j < bak && can; ++j) {
				int at = li[j] + (B - A) * j;
				can &= BB[li[0]][at] >= B;
				int nxt = j == bak - 1 ? n : li[j + 1];
				can &= AB[li[j] + A][at + B] >= nxt - li[j] - A;
			}
			if (can) {
				ansl = A + B;
				AL = BL = l;
				AR = l + A;
				BR = l + B;
			}
		}
	}
	std::cout << "s/" << std::string(lhs + AL, lhs + AR)
			  << "/" << std::string(rhs + BL, rhs + BR)
			  << "/g" << std::endl;
	return 0;
}

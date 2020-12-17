#include <bits/stdc++.h>

const int none = -1;
const int any = 114514;
int readCard() {
	char x; std::cin >> x;
	if (x == '-') return none;
	if (x == '*') return any;
	return x - 'A';
}

const int MASK = (1 << 21) - 1;
int n;
int pl[4];
int disa[4];
std::vector<int> opti[4];
int li[5000000], bak, steps;
void solve(int p, int S, int hav) {
	if (S == steps) {
		for (auto t : opti[p]) if (!(t & pl[p])) return ;
		return (void) (li[++bak] = pl[p]);
	}
	for (int x = (~(hav | disa[p])) & MASK; x; x &= x - 1) {
		int v = x & (-x);
		pl[p] ^= v;
		solve(p, S + 1, hav | v);
		pl[p] ^= v;
	}
	return ;
}
int only(int x) { return !(x & (x - 1)); }
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < 5; ++i)
		pl[0] |= 1 << readCard();
	for (int i = 0; i < n; ++i) {
		int now = 0;
		for (int j = 0; j < 3; ++j)
			now |= 1 << readCard();
		for (int j = 0, t; j < 3; ++j) {
			int p = (i + j + 1) % 4;
			if ((t = readCard()) >= 0) {
				if (t == any) opti[p].push_back(now);
				else pl[p] |= 1 << t;
				break;
			} else disa[p] |= now;
		}
	}
	int all = pl[0] | pl[1] | pl[2] | pl[3];
	static int ab[21], ba[21], idx;
	for (int i = 0; i != 21; ++i)
		if (!(pl[0] >> i & 1))
			ba[ab[i] = idx++] = i;
	auto trans = [] (int x, int * li) {
		int r = 0;
		for (int i = 0; i != 21; ++i)
			if (x >> i & 1)
				r |= 1 << li[i];
		return r;
	} ;
	static int f[1 << 16], g[1 << 16], h[1 << 16];
	const int U = 1 << 16;
	f[0] = 1;
	for (int i = 1; i < 4; ++i) {
		int s = 4 + (i == 1) - __builtin_popcount(pl[i]);
		steps = s; bak = 0;
		solve(i, 0, all);
		memset(g, 0, U << 2);
		memset(h, 0, U << 2);
		for (int j = 1; j <= bak; ++j) {
			g[trans(li[j], ab)] = true;
		}
		for (int j = 0; j != U; ++j) if (g[j]) {
			int S = U - j - 1;
			for (int k = S; ; k = (k - 1) & S) {
				h[j | k] |= f[k];
				if (!k) break;
			}
		}
		memcpy(f, h, U << 2);
	}
	int can[3] = {0, 0, 0};
	for (int i = 0; i < U; ++i) if (f[i]) {
		int S = trans(i, ba) | pl[0];
		for (int j = 0; j < 6; ++j) if (!(S >> j & 1))
			for (int k = 6; k < 12; ++k) if (!(S >> k & 1))
				for (int l = 12; l < 21; ++l) if (!(S >> l & 1)) {
					can[0] |= 1 << j;
					can[1] |= 1 << k;
					can[2] |= 1 << l;
				}
	}
	for (int i = 0; i < 3; ++i) {
		if (!only(can[i])) std::cout << '?';
		else std::cout << (char) ('A' + __builtin_ctz(can[i]));
	}
	std::cout << '\n';
	return 0;
}

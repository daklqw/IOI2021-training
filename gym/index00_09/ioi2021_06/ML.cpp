#include <bits/stdc++.h>

const int MAXN = 50;
int A[3][MAXN];
int val[MAXN];
int fir[8];
int n;
struct _ {
	int x, vx, y, vy;
} ;
std::vector<_> cond, ex;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < n; ++j)
			std::cin >> A[i][j];
	memset(fir, -1, sizeof fir);
	for (int i = 0; i < n; ++i) {
		int t = A[0][i] | (A[1][i] << 1) | (A[2][i] << 2);
		val[i] = t;
		if (fir[t] == -1)
			fir[t] = i;
		else {
			ex.push_back((_) {i, 0, fir[t], 0});
			ex.push_back((_) {i, 1, fir[t], 1});
		}
	}
	for (int i = 0; i < 8; ++i) if (fir[i] != -1)
		for (int j = 0; j < 8; ++j) if (fir[j] != -1 && j != i) {
			int vx[2] = {0, 0};
			for (int k = 0; k < 3; ++k)
				vx[i >> k & 1] |= 1 << (j >> k & 1);
			for (int k = 0; k < 2; ++k) {
				if (vx[k] == 0) {
					cond.push_back((_) {fir[i], k, fir[i], k ^ 1});
				} else if (vx[k] != 3) {
					int v = vx[k] == 2;
					cond.push_back((_) {fir[i], k, fir[j], v});
				}
			}
		}
	const int U = 1 << 8;
	int ans = 0;
	for (int i = 0; i != U; ++i) {
		bool can = true;
		for (int j = 0; j < 8; ++j)
			if (fir[j] == -1 && (i >> j & 1))
				can = false;
		for (auto t : cond)
			if ((i >> val[t.x] & 1) == t.vx)
				can &= (i >> val[t.y] & 1) == t.vy;
		ans += can;
	}
	if (ans != 3) {
		std::cout << -1 << std::endl;
		return 0;
	}
	cond.insert(cond.end(), ex.begin(), ex.end());
	std::cout << cond.size() << std::endl;
	for (auto t : cond) {
		if (!t.vx) std::cout << '!';
		std::cout << 'x' << t.x + 1;
		std::cout << " -> ";
		if (!t.vy) std::cout << '!';
		std::cout << 'x' << t.y + 1;
		std::cout << '\n';
	}
	return 0;
}

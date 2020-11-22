#include <bits/stdc++.h>

const int MAXN = 1010;
int pre[MAXN][1 << 13 | 1];
int n;
void print(int x, int y) {
	if (!x) return ;
	print(x - 1, pre[x][y] & ((1 << 30) - 1));
	std::cout << ("lr"[pre[x][y] >> 30]);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	memset(pre[0], -1, sizeof pre[0]);
	pre[0][0] = 0;
	while (T --> 0) {
		std::cin >> n;
		int sm = 0;
		for (int i = 1, t; i <= n; ++i) {
			memset(pre[i], -1, sizeof pre[i]);
			std::cin >> t;
			for (int j = i != 1; j <= sm; ++j)
				if (pre[i - 1][j] != -1) {
					if (i == 1 || t <= (j & -j))
						pre[i][j + t] = j;
					int r = sm - j;
					if (j == sm || t <= (r & -r)) {
						r += t;
						int x = j;
						if ((j ^ (j & (r - 1))) <= r)
							x += r;
						pre[i][x] = j | (1 << 30);
					}
				}
			sm += t;
		}
		if (!(sm & (sm - 1)) && pre[n][sm] != -1) {
			print(n, sm);
			std::cout << '\n';
		} else
			std::cout << "no\n";
	}
	return 0;
}

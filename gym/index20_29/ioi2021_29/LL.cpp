#include <bits/stdc++.h>

const int RAN = 3010;
const int DTA = 1505;

int n;

int A[RAN][RAN], B[RAN][RAN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	while (n --> 0) {
		static char typ[10];
		int x, y, d;
		std::cin >> typ >> x >> y >> d;
		x += DTA, y += DTA;
		d /= 2;
		if (*typ == 'A') {
			++A[x - d][y - d];
			++A[x + d][y + d];
			--A[x + d][y - d];
			--A[x - d][y + d];
		} else {
			++B[x - d][y];
			++B[x + d][y];
			--B[x][y - d];
			--B[x][y + d];
		}
	}
	for (int i = 2; i + 2 < RAN; ++i)
		for (int j = 2; j + 2 < RAN; ++j) {
			A[i][j] += A[i - 1][j];
			A[i][j] += A[i][j - 1];
			A[i][j] -= A[i - 1][j - 1];
			B[i][j] += B[i - 1][j - 1];
			B[i][j] += B[i - 1][j + 1];
			B[i][j] -= B[i - 2][j];
		}
	int ans = 0;
	for (int i = 2; i + 2 < RAN; ++i)
		for (int j = 2; j + 2 < RAN; ++j) {
			int a = A[i][j] ? 15 : 0;
			if (B[i - 1][j + 1]) a |= 3;
			if (B[i - 1][j]) a |= 6;
			if (B[i][j]) a |= 12;
			if (B[i][j + 1]) a |= 9;
			ans += __builtin_popcount(a);
		}
	const static char ls[][3] = {
		"00", "25", "50", "75"
	};
	std::cout << (ans / 4) << '.' << ls[ans % 4] << '\n';
	return 0;
}

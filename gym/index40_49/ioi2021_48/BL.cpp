#include <bits/stdc++.h>

typedef long long LL;
typedef long double db;
LL C[21][21];
int n;
db A[4];
typedef std::pair<db, LL> PI;
std::priority_queue<PI> que;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i <= 20; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
	for (int i = 0; i < 4; ++i)
		std::cin >> A[i];
	db sm = 0;
	for (int a = 0; a <= n; ++a)
		for (int b = 0; b + a <= n; ++b)
			for (int c = 0; c + a + b <= n; ++c) {
				int d = n - a - b - c;
				db pr = std::pow(A[0], a) *
						std::pow(A[1], b) *
						std::pow(A[2], c) *
						std::pow(A[3], d);
				LL cnt = C[n][a] * C[n - a][b] * C[n - a - b][c];
				sm += pr * cnt;
				que.emplace(-pr, cnt);
			}
	db ans = 0;
	while (!que.empty()) {
		PI lhs = que.top(); que.pop();
		ans -= lhs.first * lhs.second;
		if (lhs.second > 1)
			que.emplace(lhs.first * 2, lhs.second >> 1);
		lhs.second &= 1;
		if (lhs.second == 1) {
			if (que.empty()) break;
			PI rhs = que.top(); que.pop();
			ans -= rhs.first;
			--rhs.second;
			que.emplace(lhs.first + rhs.first, 1);
			if (rhs.second) que.push(rhs);
		}
	}
	std::cout << std::fixed << std::setprecision(10);
	std::cout << ans - 1 << std::endl;
	return 0;
}

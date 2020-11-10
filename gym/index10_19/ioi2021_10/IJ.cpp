#include <bits/stdc++.h>

const int MAXN = 1010;
typedef std::vector<int> VI;
int qry(VI t) {
	for (auto x : t)
		std::cout << x;
	std::cout << std::endl;
	int r; std::cin >> r;
	return r;
}
std::mt19937 rd(time(0));
void solve(int n) {
	VI q(n, 0), eq(n, 0);
	for (; ; ) {
		for (int i = 0; i < n; ++i)
			q[i] = rd() % 2;
		int v = qry(q);
		if (v == n) return ;
		if (v == n / 2) {
			q[0] ^= 1;
			for (int j = 1; j < n; ++j) {
				q[j] ^= 1;
				int r = qry(q);
				if (r == n) return ;
				eq[j] = r == n / 2;
				q[j] ^= 1;
			}
			q[0] ^= 1;
			for (int j = 0; j < n; ++j)
				eq[j] ^= q[j];
			if (qry(eq) != n) {
				for (int j = 0; j < n; ++j)
					eq[j] ^= 1;
				if (qry(eq) != n)
					abort();
			}
			break;
		}
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n; std::cin >> n;
	solve(n);
	return 0;
}

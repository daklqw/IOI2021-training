#include <bits/stdc++.h>

const int MAXN = 1 << 20 | 10;
typedef std::vector<int> VI;
typedef std::tuple<int, int, int> tp;
tp stp[MAXN], ansl[MAXN];
int best;
void solve(VI li, int S = 0) {
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		int sm = (1 << a) | (1 << b) | (1 << c) | (1 << d);
		best = 0x3f3f3f3f;
		solve(VI({sm}), 0);
	}
	return 0;
}

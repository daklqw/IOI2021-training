#include <bits/stdc++.h>

typedef long long LL;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int N, L, R, T, S;
		std::cin >> N >> L >> R >> T >> S;
		LL f = 1;
		int stp = 0;
		while (f > 0) {
			if (R - L <= f * T)  {
				std::cout << stp << '\n';
				stp = -1;
				break;
			}
			++stp;
			int k = std::max((R - N / stp / S + T - 1) / T - 1, 0);
			f = (f - k) * 2;
			R -= k * T;
		}
		if (stp != -1) std::cout << "impossible\n";
	}
	return 0;
}

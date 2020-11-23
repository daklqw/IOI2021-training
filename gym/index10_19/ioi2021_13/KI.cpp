#include <bits/stdc++.h>
#include "intercept.h"

typedef long long LL;
// bool check(int l, int r) {
// 	std::cout << "check " << l << ' ' << r << std::endl;
// 	static char buf[10];
// 	std::cin >> buf;
// 	return *buf == 'Y';
// }
const int MAXN = 1e5 + 10;
int ls[MAXN], rs[MAXN];
int intercept(int p, int v) {
	for (int i = 0; i <= v; ++i)
		ls[i] = 0, rs[i] = p;
	int TC = 0;
	while (true) {
		LL all = 0;
		int l = 0x3f3f3f3f, r = 0;
		for (int i = 0; i <= v; ++i)
			if (ls[i] <= rs[i]) {
				all += rs[i] - ls[i] + 1;
				l = std::min(l, ls[i] + i * TC);
				r = std::max(r, rs[i] + i * TC);
			}
		if (all == 1) return l;
		int ans = -1;
		while (l <= r) {
			int mid = l + r >> 1;
			LL sm = 0;
			for (int i = 0; i <= v; ++i)
				if (ls[i] <= rs[i]) {
					int t = mid - ls[i] - i * TC + 1;
					t = std::max(t, 0);
					t = std::min(t, rs[i] - ls[i] + 1);
					sm += t;
				}
			if (sm * 2 >= all)
				ans = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		bool yes = check(0, ans);
		for (int i = 0; i <= v; ++i)
			if (ls[i] <= rs[i]) {
				if (yes)
					rs[i] = std::min(rs[i], ans - i * TC);
				else
					ls[i] = std::max(ls[i], ans - i * TC + 1);
			}
		++TC;
	}
}
// int main() {
// 	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
// 	int p, v;
// 	std::cin >> p >> v;
// 	int r = intercept(p, v);
// 	std::cout << "answer " << r << std::endl;
// 	return 0;
// }

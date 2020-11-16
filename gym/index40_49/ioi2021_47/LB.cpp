#include <bits/stdc++.h>

const int MAXN = 3e5 + 10;

struct _ {
	int x, y, id;
} ps[MAXN], fs[MAXN];
int n, m;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		std::cin >> ps[i].x >> ps[i].y;
	for (int i = 1; i <= m; ++i) {
		std::cin >> fs[i].x >> fs[i].y;
		fs[i].id = i;
	}


	return 0;
}

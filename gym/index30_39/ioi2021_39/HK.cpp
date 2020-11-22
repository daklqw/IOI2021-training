#include <bits/stdc++.h>

const int MAXN = 1010;
typedef std::pair<int, int> pi;
typedef std::vector<pi> VI;

VI read() {
	int H, W;
	std::cin >> H >> W;
	VI li;
	for (int i = 0; i < H; ++i) { 
		static char buf[MAXN];
		std::cin >> buf;
		for (int j = 0; j < W; ++j)
			if (buf[j] == '*')
				li.emplace_back(i, j);
	}
	return li;
}

VI calc(VI a, VI b) {
	if (b.empty()) return a;
	if (a.empty()) return b;
	int dx = a[0].first - b[0].first;
	int dy = a[0].second - b[0].second;
	std::set<pi> S(a.begin(), a.end());
	for (auto t : b) {
		t.first += dx;
		t.second += dy;
		if (S.count(t)) S.erase(t);
		else S.insert(t);
	}
	return VI(S.begin(), S.end());
}
bool eq(VI a, VI b) {
	return calc(a, b).empty();
}
int main() {
#define FILENAME "kids"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	VI a, b, c;
	a = read(), b = read(), c = read();
	bool can = true;
	if (eq(calc(a, b), c)) {
	} else if (eq(calc(a, c), b)) {
		a = calc(a, c);
	} else if (eq(calc(b, c), a)) {
		b = calc(b, c);
	} else can = false;
	if (can) {
		std::cout << "YES" << std::endl;
		int y = a[0].first - b[0].first;
		int x = a[0].second - b[0].second;
		std::cout << x << ' ' << y << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
	return 0;
}

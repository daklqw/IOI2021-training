#include <bits/stdc++.h>

#define FILENAME "RH"
std::mt19937 rd(time(0) + (unsigned long) new char);
const int R = 10;
template<typename T> T rnd(T l, T r) { return l + rd() % (r - l); }

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	freopen(FILENAME ".in", "w", stdout);
	std::vector<std::pair<int, int> > ql;
	for (int i = 1; i <= 60; ++i)
		for (int j = i; j <= 60; ++j)
			ql.emplace_back(i, j);

	std::cout << ql.size() << '\n';
	for (auto t : ql)
		std::cout << t.first << ' ' << t.second << '\n';

	return 0;
}

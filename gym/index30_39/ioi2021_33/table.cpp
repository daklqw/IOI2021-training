#include <bits/stdc++.h>

typedef std::vector<int> VI;
typedef std::pair<VI, int> pi;

std::map<pi, VI> hav;
std::queue<pi> que;
void ins(pi x, VI stp) {
	if (hav.count(x)) return ;
	que.push(x);
	hav[x] = stp;
}
int main() {
	ins(pi(VI({1, 2, 3, 4}), 0), VI({}));
	while (!que.empty()) {
		VI s; int t;
		auto p = que.front();
		std::tie(s, t) = p;
		que.pop();
		VI stp = hav[p];
		std::swap(s[0], s[1]); t ^= 1;
		stp.push_back(0);
		ins(pi(s, t), stp);
		stp.pop_back();
		std::swap(s[0], s[1]); t ^= 1;

		std::swap(s[0], s[2]); t ^= 2;
		stp.push_back(1);
		ins(pi(s, t), stp);
		stp.pop_back();
		std::swap(s[0], s[2]); t ^= 2;

		std::swap(s[2], s[3]); t ^= 4;
		stp.push_back(2);
		ins(pi(s, t), stp);
		stp.pop_back();
		std::swap(s[2], s[3]); t ^= 4;

		std::swap(s[1], s[3]); t ^= 8;
		stp.push_back(3);
		ins(pi(s, t), stp);
		stp.pop_back();
		std::swap(s[1], s[3]); t ^= 8;
	}
	for (auto t : hav) {
		if (t.first.second == 0) {
			for (auto x : t.first.first)
				std::cout << x << ' ';
			std::cout << ": ";
			for (auto x : t.second)
				std::cout << x;
			std::cout << std::endl;
		}
	}
	return 0;
}

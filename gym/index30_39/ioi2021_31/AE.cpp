#include <bits/stdc++.h>

const int MAXN = 110;
typedef unsigned long long LL;
int n;
typedef std::vector<LL> VI;
VI out[MAXN];
LL rnd(LL x) {
	 x ^= x << 13;
	 x ^= x >> 7;
	 x ^= x << 17;
	 return x;
}
std::map<LL, VI> M;
std::vector<VI> ansl;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, t; i <= n; ++i) {
		std::cin >> t;
		out[i].resize(t);
		for (int j = 0; j < t; ++j)
			std::cin >> out[i][j];
	}
	static LL dp[2][MAXN][MAXN];
	for (int i = 1; i <= n; ++i)
		for (auto t : out[i])
			dp[0][i][t] = rnd(out[i].size() + 114514);
	auto calc = [] (VI x) {
		LL r = 0;
		for (auto t : x)
			r = rnd(r + t);
		return r;
	};
	auto getmi = [] (VI x) {
		const int L = x.size();
		VI v = x;
		for (int i = 0; i + 1 < L; ++i) {
			std::rotate(x.begin(), x.begin() + 1, x.end());
			if (x < v) v = x;
		}
		return v;
	};
	int now = 0, lst = 1;
	for (int T = 1; T <= n; ++T) {
		std::swap(now, lst);
		for (int i = 1; i <= n; ++i) {
			const int sz = out[i].size();
			VI t;
			t.reserve(sz);
			for (int j : out[i])
				t.push_back(dp[lst][j][i]);
			for (int j : out[i]) {
				std::rotate(t.begin(), t.begin() + 1, t.end());
				dp[now][i][j] = calc(t);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		VI t;
		for (auto j : out[i])
			t.push_back(dp[now][i][j]);
		M[calc(getmi(t))].push_back(i);
	}
	for (auto t : M)
		if (t.second.size() > 1) {
			std::sort(t.second.begin(), t.second.end());
			ansl.push_back(t.second);
		}
	std::sort(ansl.begin(), ansl.end());
	if (ansl.empty())
		std::cout << "none" << std::endl;
	for (auto t : ansl) {
		bool lst = false;
		for (auto x : t) {
			if (lst) std::cout << ' ';
			lst = true;
			std::cout << x;
		}
		std::cout << '\n';
	}
	return 0;
}

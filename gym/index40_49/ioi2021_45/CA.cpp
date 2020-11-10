#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
typedef long long LL;

int n, A[MAXN], hav[MAXN];
LL up(LL a, LL b) {
	return a / b + (a % b != 0);
}
int sm = 0;
LL get(int i) {
	return up((hav[i] + 1ll) * sm, A[i]);
}
typedef std::pair<LL, int> pi;
std::priority_queue<pi, std::vector<pi>, std::greater<pi>> que;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int K;
	std::cin >> n >> K;
	for (int i = 1; i <= n; ++i)
		std::cin >> A[i], sm += A[i];
	for (int i = 1, t; i <= K; ++i)
		std::cin >> t, ++hav[t];
	for (int i = 1; i <= n; ++i)
		que.emplace(get(i), i);
	for (int i = K + 1; i <= K + sm; ++i) {
		pi t = que.top();
		que.pop();
		if (t.first < i || (!que.empty() && que.top().first <= i)) {
			std::cout << (i - K - 1) << std::endl;
			return 0;
		}
		int u = t.second;
		++hav[u];
		que.emplace(get(u), u);
	}
	std::cout << "forever" << std::endl;
	return 0;
}

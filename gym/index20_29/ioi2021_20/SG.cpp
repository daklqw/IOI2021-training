#include <bits/stdc++.h>

const int MAXN = 100010;
int n, m, K;
int ind[MAXN];
std::vector<int> out[MAXN];
std::vector<std::pair<int, int> > anse;
void adde(int b, int e) {
	out[b].push_back(e);
	++ind[e];
}
std::set<int> S, T;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m >> K;
	for (int i = 1, b, e; i <= m; ++i)
		std::cin >> b >> e, adde(b, e);
	for (int i = 1; i <= n; ++i)
		if (!ind[i])
			S.insert(i);
	static int ansl[MAXN];
	int bak = 0;
	while (!S.empty()) {
		while (K && S.size() > 1) {
			T.insert(*S.begin());
			S.erase(S.begin());
			--K;
		}
		if (K && !T.empty() && *S.begin() < *T.rbegin()) {
			int p = *T.rbegin();
			T.insert(*S.begin());
			S.clear();
			S.insert(p);
			T.erase(p);
			--K;
			anse.emplace_back(ansl[bak], p);
		}
		int t = *S.begin(); S.erase(S.begin());
		ansl[++bak] = t;
		for (int i : out[t])
			if (!--ind[i])
				S.insert(i);
		if (S.empty() && !T.empty()) {
			int p = *T.rbegin();
			T.erase(p);
			S.insert(p);
			anse.emplace_back(t, p);
		}
	}
	for (int i = 1; i <= n; ++i)
		std::cout << ansl[i] << (" \n" [i == n]);
	std::cout << anse.size() << '\n';
	for (auto t : anse)
		std::cout << t.first << ' ' << t.second << std::endl;
	return 0;
}

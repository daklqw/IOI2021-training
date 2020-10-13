#include <bits/stdc++.h>

const int MAXN = 3e5 + 10;
const int LIM = 1e6;
int hav[LIM + 10], n;
typedef std::vector<int> VI;
VI la, lb;
int ansl[MAXN];
void gmi(int & x, int y) { x > y ? x = y : 0; }
void solve(VI & x, int dta) {
	std::sort(x.begin(), x.end());
	dta += x.size();
	int rest = 0, cur = 0;
	for (int i = 1; i <= n; ++i) {
		++rest;
		while (cur < x.size() && rest >= x[cur])
			rest -= x[cur++], --dta;
		gmi(ansl[i], dta);
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1, t; i <= n; ++i)
		std::cin >> t, ++hav[t];
	for (int i = 1; i <= LIM; ++i) if (hav[i]) {
		la.push_back(hav[i]);
		for (int j = i + i; j <= LIM; j += i)
			if (hav[j]) {
				lb.push_back(hav[i]);
				break;
			}
	}
	for (int i = 0; i <= n; ++i)
		ansl[i] = la.size();
	solve(la, 1);
	solve(lb, la.size() - lb.size());
	for (int i = 0; i <= n; ++i)
		std::cout << ansl[i] << (" \n" [i == n]);
	return 0;
}

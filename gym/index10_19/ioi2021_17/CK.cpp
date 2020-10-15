#include <bits/stdc++.h>

const int MAXN = 110;
int A[MAXN], B[MAXN], hav[MAXN][MAXN], n;
bool get(int * A, int ans) {
	int lst = ans + 1;
	for (int i = 1; i <= n; ++i) {
		int r = lst * (lst - 1) / 2;
		if (r <= A[i]) return true;
		if (int t = hav[A[i]][lst]) lst = t;
		else return false;
	}
	return false;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	int all = 0;
	for (int i = 1; i <= n; ++i)
		std::cin >> A[i], all += B[n - i + 1] = A[i];
	for (int i = 100; i; --i)
		for (int j = i, sm = i; j && sm <= 100; sm += --j)
			hav[sm][i + 1] = j;
	if (all % 2 == 0) for (int i = 100; i; --i) {
		int v = i * (i + 1) / 2;
		if (v * 2 > all) continue;
		if (get(A, i) && get(B, i)) {
			if (i == 1 && all > 2) break;
			std::cout << i << std::endl;
			return 0;
		}
	}
	std::cout << "no quotation" << std::endl;
	return 0;
}

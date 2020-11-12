#include <bits/stdc++.h>

const int MAXN = 110;
int n;
struct _ {
	int a[MAXN * 4];
	_() { memset(a, -1, sizeof a); }
	int & operator [] (int x) {
		return a[x + MAXN];
	}
} A;
void swap(int x, int y) {
	std::swap(A[x], A[y]);
	std::swap(A[x + 1], A[y + 1]);
}
std::vector<std::pair<int, int> > ansl;
typedef unsigned long long LL;
std::set<LL> M[MAXN];
inline LL gen(LL x) {
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}
LL getha() {
	LL ha = 0;
	for (int i = -2; i < n * 2; ++i)
		ha = gen(ha + 114514 + A[i]);
	return ha;
}

bool dfs(int S) {
	if (S == n) {
		for (int be = -(n * 2); be < 0; ++be) {
			bool can = true;
			for (int i = 0; i < n; ++i)
				can &= A[i + be] == 1;
			for (int i = n; i < n * 2; ++i)
				can &= A[i + be] == 0;
			if (can)
				return true;
		}
		return false;
	}
	LL hash = getha();
	if (M[S].count(hash))
		return false;
	M[S].insert(hash);
	for (int i = -(n * 2); i + 1 < n * 2; ++i)
		if (A[i] != -1 && A[i + 1] != -1) {
			for (int j = -(n * 2); j + 1 < n * 2; ++j)
				if (A[j] == -1 && A[j + 1] == -1) {
					swap(i, j);
					if (dfs(S + 1)) {
						ansl.emplace_back(j, i);
						return true;
					}
					swap(i, j);
				}
		}
	return false;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n * 2; ++i)
		A[i] = i & 1;
	dfs(0);
	std::reverse(ansl.begin(), ansl.end());
	for (auto t : ansl)
		std::cout << t.second + 1 << " to " << t.first + 1 << std::endl;
	return 0;
}

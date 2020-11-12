#include <bits/stdc++.h>

const int MAXN = 110;
//   ABABABABAB 1
//   0123456789 1
// 780123456  9-2
// 7801  456239-2
// 7801564  239-1
// 7  156480239-2
// 7391564802  -1
int n;
// 2n-1 -> 1
struct _ {
	int a[MAXN * 4];
	_() { memset(a, -1, sizeof a); }
	int & operator [] (int x) {
		return a[x + MAXN];
	}
} A;
int co(int x) {
	return A[x] != -1 && A[x + 1] != -1 && A[x] != A[x + 1];
}
int swap(int x, int y) {
	int r = 0;
	r -= co(x - 1) + co(x + 1);
	r -= co(y - 1) + co(y + 1);
	std::swap(A[x], A[y]);
	std::swap(A[x + 1], A[y + 1]);
	r += co(x - 1) + co(x + 1);
	r += co(y - 1) + co(y + 1);
	return r;
}
std::vector<std::pair<int, int> > ansl;
typedef unsigned long long LL;
std::set<LL> M[MAXN * 2][3];
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
bool dfs(int S, int lst, int c1) {
	if (S == n) {
		if (c1 != 2) return false;
		for (int i = -2; i < -2 + n; ++i)
			if (A[i] != 1)
				return false;
		for (int i = -2 + n; i < -2 + n * 2; ++i)
			if (A[i] != 0)
				return false;
		return true;
	}
	LL hash = getha();
	if (M[lst + 4][c1].count(hash))
		return false;
	M[lst + 4][c1].insert(hash);
	int tar = S == (n + 1) / 2 || S + 1 == n ? 1 : 2;
	std::vector<int> hav;
	for (int i = -1; i + 1 < n * 2; ++i)
		if (std::abs(i - lst) > 1) {
			int v = -swap(i, lst);
			swap(i, lst);
			if (v == tar)
				hav.push_back(i);
		}
	for (int j : hav) {
		swap(lst, j);
		if (dfs(S + 1, j, c1 + (tar == 1))) {
			ansl.emplace_back(lst, j);
			swap(lst, j);
			std::cout << tar << " :";
			for (int k = -2; k < n * 2; ++k) {
				if (A[k] == -1)
					std::cout << ' ' << '*';
				else
					std::cout << ' ' << A[k];
			}
			std::cout << '\n';
			return true;
		}
		swap(lst, j);
	}
	return false;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n * 2; ++i)
		A[i] = i & 1;
	for (int i = 0; i < n * 2 - 1; ++i) {
		int v = swap(-2, i);
		if (dfs(1, i, v == 1)) {
			ansl.emplace_back(-2, i);
			break;
		}
		swap(-2, i);
	}
	std::reverse(ansl.begin(), ansl.end());
	for (auto t : ansl)
		std::cout << t.second + 1 << " to " << t.first + 1 << std::endl;
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 3010;
typedef long long LL;

int n, m;
int getL(int x, int y) { return y - (x & 1); }
int getR(int x, int y) { return y + (x & 1 ^ 1); }
int R, C;
void conn(int & x, int y) {
	x = x ? x + y : 0;
}
int twodcount(int * L, int * R, int * M, int n) {
	static int tr[MAXN];
	memset(tr, 0, sizeof tr);
	typedef std::pair<int, int> pi;
	static pi li[MAXN];
	int res = 0;
	for (int _L = 1, _R; _L <= n; _L = _R + 1) {
		_R = _L;
		while (_R <= n && M[_R]) ++_R;
		int bak = 0, cur = 1;
		for (int j = _L; j <= _R; ++j)
			li[++bak] = pi(j - L[j], j);
		std::sort(li + 1, li + 1 + bak);
		for (int j = _L, x; j <= _R; ++j) {
			while (cur <= bak && li[cur].first <= j)
				for (x = li[cur++].second; x <= n; x += x & -x)
					++tr[x];
			for (x = std::min(n, j + R[j]); x; x &= x - 1)
				res += tr[x];
			res -= _R - j + 1;
		}
		for (int j = 1; j < cur; ++j)
			for (int x = li[j].second; x <= n; x += x & -x)
				tr[x] = 0;
	}
	return res;
}
typedef int mat[MAXN][MAXN];
mat DL, DR, M, UL, UR;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> R >> C;
	auto getnu = [] (int x) {
		return x & 1 ? C + 1 >> 1 : C >> 1;
	};
	static char buf[MAXN * 4];
	std::cin.getline(buf, MAXN * 4);
	for (int T = 1, i = 1; T <= R * 2 - 1; ++T) {
		std::cin.getline(buf, MAXN * 4);
		if (T & 1) {
			int A = getnu(i);
			for (int j = 1, p = i & 1 ? 2 : 4; j < A; ++j, p += 4)
				M[i][j] = buf[p] == '-';
		} else {
			int A = getnu(i);
			for (int j = 1, p = i & 1 ? -1 : 1; j <= A; ++j, p += 4) {
				if (j > (i & 1))
					UR[i + 1][getL(i, j)] = DL[i][j] = buf[p] == '/';
				UL[i + 1][getR(i, j)] = DR[i][j] = buf[p + 2] == '\\';
			}
			++i;
		}
	}
	for (int i = R; i; --i)
		for (int j = getnu(i); j; --j) {
			conn(DL[i][j], DL[i + 1][getL(i, j)]);
			conn(DR[i][j], DR[i + 1][getR(i, j)]);
		}
	for (int i = 1; i <= R; ++i)
		for (int j = getnu(i); j; --j) {
			conn(UL[i][j], UL[i - 1][getL(i, j)]);
			conn(UR[i][j], UR[i - 1][getR(i, j)]);
		}
	LL ans = 0;
	for (int i = 1; i <= R; ++i) {
		ans += twodcount(UL[i], UR[i], M[i], getnu(i));
		ans += twodcount(DL[i], DR[i], M[i], getnu(i));
	}
	std::cout << ans << std::endl;
	return 0;
}

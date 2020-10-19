#include <bits/stdc++.h>

const int MAXN = 310;
int H, W;
int A[MAXN][MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> W >> H;
	for (int i = 1; i <= H; ++i) {
		char buf[MAXN];
		std::cin >> buf;
		for (int j = 1; j <= W; ++j)
			A[i][j] = buf[j - 1] == '#';
	}
	while (W > 2 && H > 2) {
		static int tmp[MAXN][MAXN], mat[MAXN][MAXN];
		memset(tmp, -1, sizeof tmp);
		memcpy(mat, A, sizeof A);
		auto get = [] (int x, int y) {
			int r = mat[x][y];
			for (int i = x ? -1 : 0; i <= 1; ++i)
				for (int j = y ? -1 : 0; j <= 1; ++j)
					if (tmp[x + i][y + j] != -1)
						r ^= tmp[x + i][y + j];
			return r;
		} ;
		bool err = false;
		for (int i = 2; i < H; ++i) {
			for (int j = 2; j < W; ++j)
				tmp[i][j] = get(i - 1, j - 1);
			if (get(i - 1, W - 1) || get(i - 1, W)) {
				err = true;
				for (int k = 2; k < W; ++k) tmp[i][k] = -1;
				for (int j = H - 1; j > i; --j)
					for (int k = 2; k < W; ++k)
						tmp[j][k] = get(j + 1, k - 1);
				for (int j = 1; j <= W; ++j) {
					mat[i - 1][j] ^= 1;
					for (int k = 2; k < W; ++k) tmp[i][k] = -1;
					for (int k = 2; k < W; ++k)
						tmp[i][k] = get(i - 1, k - 1);
					bool can = true;
					for (int k = 1; k <= W; ++k)
						can &= get(i, k) == 0 && get(i + 1, k) == 0;
					for (int k = 1; k <= H; ++k)
						can &= get(k, W - 1) == 0 && get(k, W) == 0;
					if (can) break;
					mat[i - 1][j] ^= 1;
				}
				break;
			}
		}
		for (int i = H - 1; i <= H; ++i)
			for (int j = 1; j <= W && !err; ++j)
				if (get(i, j) != 0) {
					err = true;
					mat[i][j] ^= 1;
				}
		err = false;
		for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= W; ++j)
				err |= get(i, j) != 0;
		if (err) break;
		auto calc = [] (int l, int r, int L, int R) {
			for (int i = l; i <= r; ++i)
				for (int j = L; j <= R; ++j)
					if (tmp[i][j] > 0)
						return false;
			return true;
		} ;
		int lh = 1, uh = H, lw = 1, uw = W;
		if (calc(1, H, 1, W)) break;
		while (calc(lh, lh, lw, uw)) ++lh;
		while (calc(uh, uh, lw, uw)) --uh;
		while (calc(lh, uh, lw, lw)) ++lw;
		while (calc(lh, uh, uw, uw)) --uw;
		H = uh - lh + 1;
		W = uw - lw + 1;
		memset(A, 0, sizeof A);
		for (int i = lh; i <= uh; ++i)
			for (int j = lw; j <= uw; ++j)
				A[i - lh + 1][j - lw + 1] = tmp[i][j];
	}
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j)
			std::cout << (A[i][j] ? '#' : '.');
		std::cout << '\n';
	}
	return 0;
}

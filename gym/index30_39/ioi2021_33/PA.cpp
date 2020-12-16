#include <bits/stdc++.h>

const int MAXN = 110;
int A[MAXN][MAXN];
int vis[MAXN * MAXN];
int H, W;
int get(int x, int y) {
	return (x - 1) * W + y;
}
int col[MAXN], row[MAXN];
int ps[MAXN][MAXN];
typedef std::vector<int> VI;
typedef std::string str;
std::map<VI, str> opr = {
	{{1, 2, 3, 4}, ""},
	{{1, 3, 4, 2}, "3232"},
	{{1, 4, 2, 3}, "2323"},
	{{2, 1, 4, 3}, "013013"},
	{{2, 3, 1, 4}, "0101"},
	{{2, 4, 3, 1}, "3030"},
	{{3, 1, 2, 4}, "1010"},
	{{3, 2, 4, 1}, "2121"},
	{{3, 4, 1, 2}, "021021"},
	{{4, 1, 3, 2}, "0303"},
	{{4, 2, 1, 3}, "1212"},
	{{4, 3, 2, 1}, "010212"}
};
void ROW(int M) {
	for (int j = 1; j * 2 <= W + 1; ++j)
		std::swap(A[M][j], A[M][W - j + 1]);
}
void COL(int M) {
	for (int j = 1; j * 2 <= H + 1; ++j)
		std::swap(A[j][M], A[H - j + 1][M]);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> W >> H;
		const int N = H * W;
		memset(vis, 0, N + 1 << 2);
		bool can = true;
		for (int i = 1; i <= H; ++i)
			for (int j = 1; j <= W; ++j) {
				std::cin >> A[i][j];
				can &= 1 <= A[i][j] && A[i][j] <= N;
				can &= !vis[A[i][j]];
				vis[A[i][j]] = true;
				bool yes = false;
				yes |= A[i][j] == get(i, j);
				yes |= A[i][j] == get(i, W - j + 1);
				yes |= A[i][j] == get(H - i + 1, j);
				yes |= A[i][j] == get(H - i + 1, W - j + 1);
				can &= yes;
			}
		for (int i = 1; i * 2 <= H + 1; ++i)
			for (int j = 1; j * 2 <= W + 1; ++j) {
				if (i * 2 == H + 1) {
					ps[i][j] = A[i][j] > A[i][W - j + 1];
					continue;
				}
				if (j * 2 == W + 1) {
					ps[i][j] = A[i][j] > A[H - i + 1][j];
					continue;
				}
				int B[4];
				B[0] = A[i][j];
				B[1] = A[i][W - j + 1];
				B[2] = A[H - i + 1][j];
				B[3] = A[H - i + 1][W - j + 1];
				int & par = ps[i][j] = 0;
				for (int k = 0; k < 4; ++k)
					for (int l = k + 1; l < 4; ++l)
						par ^= B[k] > B[l];
			}
		row[1] = 0;
		if (W & 1) {
			int M = W + 1 >> 1;
			col[M] = ps[1][M];
			for (int i = 1; i * 2 < H + 1; ++i)
				can &= ps[i][M] == col[M];
		}
		if (H & 1) {
			int M = H + 1 >> 1;
			row[M] = ps[M][1];
			for (int i = 1; i * 2 < W + 1; ++i)
				can &= ps[M][i] == row[M];
		}
		for (int i = 2; i * 2 < H + 1; ++i)
			for (int j = 2; j * 2 < W + 1; ++j) {
				int sm = ps[i][j] ^ ps[i - 1][j];
				sm ^= ps[i][j - 1] ^ ps[i - 1][j - 1];
				can &= sm == 0;
			}
		if (can) {
			std::vector<std::pair<char, int>> ansl;
			for (int i = 1; i * 2 < W + 1; ++i)
				col[i] = ps[1][i];
			for (int i = 2; i * 2 < H + 1; ++i)
				row[i] = ps[i][1] ^ ps[1][1];
			for (int i = 1; i * 2 <= H + 1; ++i)
				if (row[i]) {
					ansl.emplace_back('R', i);
					ROW(i);
				}
			for (int i = 1; i * 2 <= W + 1; ++i)
				if (col[i]) {
					ansl.emplace_back('C', i);
					COL(i);
				}
			for (int i = 1; i * 2 < H + 1; ++i)
				for (int j = 1; j * 2 < W + 1; ++j) {
					int B[4], C[4];
					B[0] = A[i][j];
					B[1] = A[i][W - j + 1];
					B[2] = A[H - i + 1][j];
					B[3] = A[H - i + 1][W - j + 1];
					std::copy(B, B + 4, C);
					std::sort(C, C + 4);
					static int mat[MAXN * MAXN];
					for (int k = 0; k < 4; ++k)
						mat[C[k]] = k + 1;
					for (int k = 0; k < 4; ++k)
						B[k] = mat[B[k]];
					str opt = opr[VI(B, B + 4)];
					std::reverse(opt.begin(), opt.end());
					for (auto t : opt) {
						if (t == '0') {
							ansl.emplace_back('R', i);
							ROW(i);
						} else if (t == '1') {
							ansl.emplace_back('C', j);
							COL(j);
						} else if (t == '2') {
							ansl.emplace_back('R', H - i + 1);
							ROW(H - i + 1);
						} else {
							ansl.emplace_back('C', W - j + 1);
							COL(W - j + 1);
						}
					}
				}
			for (int i = 1; i <= H; ++i)
				for (int j = 1; j <= W; ++j)
					assert(A[i][j] == get(i, j));
			std::cout << "POSSIBLE " << ansl.size();
			for (auto t : ansl)
				std::cout << ' ' << t.first << t.second;
			std::cout << '\n';
		} else {
			std::cout << "IMPOSSIBLE" << std::endl;
		}
	}
	return 0;
}

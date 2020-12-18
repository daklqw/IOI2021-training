#include <bits/stdc++.h>

const int MAXN = 16;
int H, W, K, n;
enum dire { _L = 1, _U = 2, _R = 4, _D = 8 };
struct _ {
	char A[MAXN][MAXN];
	void read() {
		for (int i = 0; i < 3 * H - 2; ++i)
			std::cin >> A[i];
	}
	int typ() {
		const int bx = H - 1, by = W - 1;
		int r = 0;
		for (int i = 1; i + 1 < H; ++i) { // L
			r |= (A[bx + i][by - 1] != '.') << 0;
			r |= (A[bx + i][by] == '.') << 0;
		}
		for (int i = 1; i + 1 < W; ++i) { // U
			r |= (A[bx - 1][by + i] != '.') << 1;
			r |= (A[bx][by + i] == '.') << 1;
		}
		for (int i = 1; i + 1 < H; ++i) { // R 
			r |= (A[bx + i][by + W] != '.') << 2;
			r |= (A[bx + i][by + W - 1] == '.') << 2;
		}
		for (int i = 1; i + 1 < W; ++i) { // D
			r |= (A[bx + H][by + i] != '.') << 3;
			r |= (A[bx + H - 1][by + i] == '.') << 3;
		}
		return 15 ^ r;
	}
} tr[16];
std::vector<int> hav[1 << 4];
char mat[30][30], rec[30][30];
void put(int x, int y, int id) {
	for (int i = 0; i < H * 3 - 2; ++i)
		for (int j = 0; j < W * 3 - 2; ++j)
			if (tr[id].A[i][j] != '.') {
				int px = x * H + i - (H - 1);
				int py = y * W + j - (W - 1);
				if (px < 0 || px >= H * n) continue;
				if (py < 0 || py >= W * n) continue;
				mat[px][py] = tr[id].A[i][j];
			}
}
bool valid() {
	for (int i = 0; i < H * n; ++i)
		for (int j = 0; j < W * n; ++j)
			if (!mat[i][j])
				return false;
	return true;
}
void solve4() {
	for (int i1 = 0; i1 != 2; ++i1)
	for (int i2 = 0; i2 != 2; ++i2)
	for (int i3 = 0; i3 != 2; ++i3)
	for (int i4 = 0; i4 != 2; ++i4)
	for (int a = 0; a < 4; ++a)
	for (int b = 0; b < 4; ++b) if (b != a)
	for (int c = 0; c < 4; ++c) if (c != b && c != a)
	for (int d = 0; d < 4; ++d) if (d != c && d != b && d != a) {
		memcpy(rec, mat, sizeof mat);
		put(0, 1, hav[_U][i1]);
		put(0, 2, hav[_U][i1 ^ 1]);
		put(1, 0, hav[_L][i2]);
		put(2, 0, hav[_L][i2 ^ 1]);
		put(1, 3, hav[_R][i3]);
		put(2, 3, hav[_R][i3 ^ 1]);
		put(3, 1, hav[_D][i4]);
		put(3, 2, hav[_D][i4 ^ 1]);
		put(1, 1, hav[0][a]);
		put(1, 2, hav[0][b]);
		put(2, 1, hav[0][c]);
		put(2, 2, hav[0][d]);
		if (valid()) return ;
		memcpy(mat, rec, sizeof mat);
	}
}
int main() {
#define FILENAME "ascii"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> K >> W >> H;
	n = std::sqrt(K);
	for (int i = 0; i < K; ++i) tr[i].read();
	for (int i = 0; i < K; ++i) {
		// std::cout << "NOW " << i << " : " << tr[i].typ() << std::endl;
		hav[tr[i].typ()].push_back(i);
	}
	if (n == 1) put(0, 0, 0);
	else {
		put(0, 0, hav[_L | _U][0]);
		put(0, n - 1, hav[_R | _U][0]);
		put(n - 1, 0, hav[_L | _D][0]);
		put(n - 1, n - 1, hav[_R | _D][0]);
		if (n == 3) {
			put(1, 1, hav[0][0]);
			put(1, 0, hav[_L][0]);
			put(0, 1, hav[_U][0]);
			put(1, 2, hav[_R][0]);
			put(2, 1, hav[_D][0]);
		}
		if (n == 4) solve4();
	}
	std::cout << W * n << ' ' << H * n << '\n';
	for (int i = 0; i < H * n; ++i)
		std::cout << mat[i] << '\n';
	return 0;
}

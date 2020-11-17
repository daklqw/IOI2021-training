#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
typedef long long LL;
struct arr {
	int A[MAXN * 2];
	int & operator [] (int x) {
		return A[x + MAXN];
	}
} col, row;
typedef std::pair<int, int> pi;
std::map<pi, int> M;
int cnt;
const int mod1 = 998244353;
const int mod2 = 1004535809;
int pow(int a, int b, int mod) {
	int r = 1;
	for (; b; b >>= 1, a = (LL) a * a % mod)
		if (b & 1)
			r = (LL) r * a % mod;
	return r;
}
struct _ {
	int pw1[MAXN * 2][2], pw2[MAXN * 2][2];
	int ha1, ha2;
	_() {
		ha1 = ha2 = 0;
		pw1[0][0] = 114514;
		pw1[0][1] = 1919810;
		pw2[0][0] = 3145192;
		pw2[0][1] = 6535897;
		for (int i = 1; i != MAXN * 2; ++i) {
			pw1[i][0] = (LL) pw1[i - 1][0] * pw1[0][0] % mod1;
			pw1[i][1] = (LL) pw1[i - 1][1] * pw1[0][1] % mod1;
			pw2[i][0] = (LL) pw2[i - 1][0] * pw2[0][0] % mod2;
			pw2[i][1] = (LL) pw2[i - 1][1] * pw2[0][1] % mod2;
		}
	}
	void add(int x, int y, int v) {
		x += MAXN, y += MAXN;
		int v1 = (LL) pw1[x][0] * pw1[y][1] % mod1;
		int v2 = (LL) pw2[x][0] * pw2[y][1] % mod2;
		ha1 = ((LL) (v + mod1) * v1 + ha1) % mod1;
		ha2 = ((LL) (v + mod2) * v2 + ha2) % mod2;
	}
	LL calc(int x, int y) {
		x += MAXN, y += MAXN;
		int v1 = (LL) pw1[x][0] * pw1[y][1] % mod1;
		int v2 = (LL) pw2[x][0] * pw2[y][1] % mod2;
		int t1 = (LL) ha1 * pow(v1, mod1 - 2, mod1) % mod1;
		int t2 = (LL) ha2 * pow(v2, mod2 - 2, mod2) % mod2;
		return (LL) t1 * mod2 + t2;
	}
} hash;

int lx, ly;

void addp(pi x) {
	if (!M.count(x)) {
		if (!cnt++)
			std::tie(lx, ly) = x;
		hash.add(x.first, x.second, 1);
	}
	++M[x];
	++col[x.first];
	++row[x.second];
	while (col[lx - 1]) --lx;
	while (row[ly - 1]) --ly;
}
void delp(pi x) {
	if (!--M[x]) {
		M.erase(x);
		--cnt;
		hash.add(x.first, x.second, -1);
	}
	--col[x.first];
	--row[x.second];
	if (cnt) {
		while (!col[lx]) ++lx;
		while (!row[ly]) ++ly;
	}
}
LL getha() {
	return hash.calc(lx, ly);
}

int L;
char buf[MAXN], * mat[MAXN];
int H, W;
int main() {
#define FILENAME "easy"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> L;
	std::cin.getline(buf, MAXN);
	std::cin.getline(buf, MAXN);
	std::cin >> H >> W;
	int all = 0;
	for (int i = 0; i < H; ++i) {
		mat[i] = new char[W + 1];
		std::cin >> mat[i];
		for (int j = 0; j < W; ++j)
			if (mat[i][j] == 'X') {
				++all;
				addp(pi(i, j));
			}
	}
	LL ansha = getha();
	M.clear();
	hash.ha1 = hash.ha2 = cnt = 0;
	memset(&col, 0, sizeof col);
	memset(&row, 0, sizeof row);
	int cx = 0, cy = 0;
	static pi li[MAXN];
	for (int i = 0; i < L; ++i) {
		if (buf[i] == 'u') --cx;
		if (buf[i] == 'd') ++cx;
		if (buf[i] == 'l') --cy;
		if (buf[i] == 'r') ++cy;
		li[i] = pi(cx, cy);
	}
	addp(pi(0, 0));
	for (int l = 0, r = 0; l < L; ++l) {
		while (cnt < all && r < L)
			addp(li[r++]);
		if (getha() == ansha) {
			std::cout << "YES" << '\n';
			std::cout << l + 1 << ' ' << r << '\n';
			return 0;
		}
		delp(l ? li[l - 1] : pi(0, 0));
	}
	std::cout << "NO" << '\n';
	return 0;
}

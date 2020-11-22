#include <bits/stdc++.h>

const int MAXN = 1e6 + 10;
void gma(int & x, int y) {
	x < y ? x = y : 0;
}
char buf[MAXN];
int n;
bool mat[256];
int hav[19][19], trs[256];
int main() {
	mat['a'] = mat['e'] = mat['i'] = mat['o'] = mat['u'] = true;
	mat['w'] = mat['y'] = true;
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> buf; n = strlen(buf);
	for (int i = 'a', k = 0; i <= 'z'; ++i)
		if (!mat[i])
			trs[i] = k++;
	for (int i = 1; i < n; ++i) {
		int x = buf[i - 1], y = buf[i];
		if (x > y) std::swap(x, y);
		if (!mat[x] && !mat[y])
			++hav[trs[x]][trs[y]];
	}
	int ans = -1, anv = -1;
	for (int i = 0; i != (1 << 19); ++i) {
		int sm = 0;
		for (int j = 0; j < 19; ++j)
			for (int k = j + 1; k < 19; ++k)
				if ((i >> j & 1) != (i >> k & 1))
					sm += hav[j][k];
		if (sm > anv)
			ans = i, anv = sm;
	}
	for (int i = 0; i < n; ++i)
		if (mat[buf[i]])
			std::cout << buf[i];
		else {
			char ch = (ans >> trs[buf[i]] & 1) ? 'A' : 'a';
			ch += buf[i] - 'a';
			std::cout << ch;
		}
	std::cout << '\n';
	return 0;
}

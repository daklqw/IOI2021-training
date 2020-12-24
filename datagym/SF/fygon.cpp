#include <bits/stdc++.h>

typedef long long LL;
struct frac {
	LL a, b;
} ;
int sm[7];

int cnt[256];
int ch[10], de[10], top;
int dfs(int S) {
	if (S == top) return 1;
	int res = 0;
	for (int i = 0; i < cnt[de[S]]; ++i) {
		cnt[ch[S]] = i;
		res += dfs(S + 1);
	}
	return res;
}
int main() {
#define FILENAME "fygon"
#ifdef FILENAME
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	static char buf[12243];
	for (int i = 0; i < 10; ++i)
		cnt['0' + i] = i;
	while (true) {
		std::cin.getline(buf, 1024);
		if (!std::cin.good()) break;
		int cur = 0;
		while (buf[cur] == ' ')
			cur += 4;
		top = cur / 4;
		if (buf[cur] == 'l') {
			for (int i = 0; i < 7; ++i) {
				cnt['n'] = i;
				sm[i] += dfs(0);
			}
		} else {
			ch[top] = buf[cur + 4];
			de[top] = buf[cur + 15];
		}
	}
	for (int i = 0; i < 7; ++i)
		for (int j = 6; j > i; --j)
			sm[j] -= sm[j - 1];
	std::cout << sm[0];
	for (int i = 1; i < 7; ++i) {
		if (i != 1)
			std::cout << "+1/" << i << "*(n-" << (i - 1) << ")*";
		else
			std::cout << "+n*";
		if (i < 6) std::cout << "(";
		std::cout << sm[i];
	}
	for (int i = 1; i < 6; ++i)
		std::cout << ')';
	return 0;
}

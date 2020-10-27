#include <bits/stdc++.h>

typedef long long LL;
LL li[100];
int bak;
void get(LL x, LL pw) {
	if (!x) return ;
	if (x % 2 == 0)
		return get(x / 2, pw * 2);
	LL now = 1;
	while (now * 3 <= x) now *= 3;
	li[++bak] = pw * now;
	x -= now;
	get(x, pw);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		LL t; std::cin >> t;
		bak = 0;
		get(t, 1);
		std::cout << bak << '\n';
		for (int i = 1; i <= bak; ++i)
			std::cout << li[i] << (" \n" [i == bak]);
	}
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 100010;
const int MAXL = 164;
typedef std::bitset<MAXL> LL;
LL li[MAXN];
int bak;
LL pw[MAXL];
int L;
LL operator + (LL a, LL b) {
	LL t;
	while ((a & b).any()) {
		t = (a & b) << 1;
		a ^= b;
		b = t;
	}
	return a | b;
}
bool cmp(LL a, LL b) {
	for (int i = MAXL - 1; ~i; --i)
		if (a.test(i) != b.test(i))
			return a.test(i) < b.test(i);
	return false;
}
void dfs(int S, LL sm, LL v) {
	if (S == L) {
		li[++bak] = v;
		return ;
	}
	for (int i = S == L - 1; i < 2; ++i) {
		if (i) {
			v.set(S);
			sm = sm + pw[S];
		}
		if (sm.test(S) == i)
			dfs(S + 1, sm, v);
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	pw[0].set(0);
	for (int i = 1; i < MAXL; ++i)
		pw[i] = (pw[i - 1] << 1) + (pw[i - 1] << 3);
	for (L = 1; bak <= 10000; ++L) {
		dfs(0, LL(), LL());
	}
	std::sort(li + 1, li + 1 + bak, cmp);
	int n; std::cin >> n;
	int cur = MAXL - 1;
	while (!li[n].test(cur - 1)) --cur;
	while (cur) std::cout << li[n].test(--cur);
	std::cout << '\n';
	return 0;
}

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 2333;
bool npri[MAXN];
int pri[MAXN], tot;
int digl[MAXN];

const LL LIM = 1e18;
void add(LL & x, LL y) {
	x += y;
	x = std::min(x, LIM);
}
LL f[MAXN][MAXN], g[MAXN][MAXN];
int li[MAXN], bak;
int get(int i, int rest, int pre, LL K) {
	if (!rest) {
		return K;
	}
	LL lhs = K;
	lhs -= g[i + 1][rest - pri[i]];
	lhs -= (pre + digl[pri[i]] + 2) * f[i + 1][rest - pri[i]];
	if (lhs > 0)
		return get(i + 1, rest, pre, lhs);
	else {
		li[++bak] = pri[i];
		return get(i + 1, rest - pri[i], pre + digl[pri[i]] + 2, K);
	}
}
std::string ans;
int lim; LL pre;
void move(LL l) {
	while (pre + g[1][lim] <= l)
		pre += g[1][lim++];
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	for (int i = 2; i < MAXN; ++i) {
		if (!npri[i])
			pri[++tot] = i;
		for (int j = i + i; j < MAXN; j += i)
			npri[j] = true;
	}
	f[tot + 1][0] = 1; g[tot + 1][0] = 2;
	for (int j = tot; j; --j) {
		int dg = 0, t = pri[j];
		while (t)
			t /= 10, ++dg;
		digl[pri[j]] = dg;
		memcpy(f[j], f[j + 1], sizeof f[j]);
		memcpy(g[j], g[j + 1], sizeof g[j]);
		for (int i = MAXN - 1 - pri[j]; i >= 0; --i) {
			add(f[j][i + pri[j]], f[j][i]);
			add(g[j][i + pri[j]], g[j][i]);
			add(g[j][i + pri[j]], f[j][i] * (dg + 2));
		}
	}
	LL l, r;
	std::cin >> l >> r;
	l += 1, r += 1;
	move(l);
	LL tl = l;
	if (tl == pre) ++tl;
	tl -= get(1, lim, 0, tl - pre);
	LL bl = tl;
	lim = pre = 0;
	while (tl <= r) {
		bak = 0;
		move(tl);
		get(1, lim, 0, tl - pre + 1);
		std::string t;
		t += '[';
		bool lst = false;
		for (int i = 1; i <= bak; ++i) {
			if (lst) t += ", ";
			lst = true;
			t += std::to_string(li[i]);
		}
		t += "], ";
		tl += t.length();
		ans += t;
	}
	ans = ans.substr(l - bl, r - l + 1);
	std::cout << ans << std::endl;
	return 0;
}

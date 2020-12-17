#include <bits/stdc++.h>

const int MAXN = 1e6 + 10;
int W, H;
typedef std::pair<int, int> pi;
int get() {
	int x, y;
	std::cin >> x >> y;
	if (y == 0) return x;
	if (x == W) return y + W;
	if (y == H) return W + H + (W - x);
	if (x == 0) return W + H + W + (H - y);
	__builtin_unreachable();
}
pi operator + (pi a, pi b) {
	return pi(std::max(a.first, b.first), std::min(a.second, b.second));
}
typedef long double db;
void print(db x) {
	if (x <= W)
		std::cout << x << ' ' << 0;
	else if (x <= W + H)
		std::cout << W << ' ' << x - W;
	else if (x <= W + H + W)
		std::cout << (W + H + W - x) << ' ' << H;
	else
		std::cout << 0 << ' ' << (H * 2 + W * 2 - x);
}
void output(db x, db y) {
	print(x);
	std::cout << ' ';
	print(y);
	std::cout << '\n';
}
int n;
pi li[MAXN];
pi pre[MAXN], suc[MAXN];
int pma[MAXN], smi[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(2);
	std::cin >> n >> W >> H;
	for (int i = 1; i <= n; ++i) {
		int l = get(), r = get();
		if (l > r) std::swap(l, r);
		li[i] = pi(l, r);
	}
	std::sort(li + 1, li + 1 + n);
	pre[0] = suc[n + 1] = pi(0, H * 2 + W * 2);
	smi[n + 1] = 0x3f3f3f3f;
	for (int i = 1; i <= n; ++i) {
		pre[i] = pre[i - 1] + li[i];
		pma[i] = std::max(pma[i - 1], li[i].second);
	}
	for (int i = n; i; --i) {
		suc[i] = suc[i + 1] + li[i];
		smi[i] = std::min(smi[i + 1], li[i].first);
	}
	for (int i = 0; i <= n; ++i)
		if (pre[i].first <= pre[i].second)
		if (suc[i + 1].first <= suc[i + 1].second) {
			int l = pre[i].first, r = suc[i + 1].second;
			if (l < r && l < smi[i + 1] && r > pma[i]) {
				std::cout << 1 << '\n';
				output(l + 0.1, r - 0.1);
				return 0;
			}
		}
	std::cout << 2 << '\n';
	output(0.1, H + W + 0.1);
	output(W + 0.1, H + W * 2 + 0.1);
	return 0;
}

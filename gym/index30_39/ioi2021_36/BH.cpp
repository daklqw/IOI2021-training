#include <bits/stdc++.h>

const int MAXN = 1010;
typedef long double db;
db pw(db x) { return x * x; }
int W, H, n;
db X[MAXN], R[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> W >> H >> n; ++n;
	const db v = H / (db) W;
	db co = -pw(v) + pw(v - 1) / 2 + pw(v + 1) / 2;
	db V = ((1 - v) * (1 + v) / 2) / co;
	X[n] = W; R[1] = V;
	for (int i = 2; i < n; ++i)
		R[i] = V / (1 - R[i - 1] * V);
	for (int i = n - 1; i; --i)
		X[i] = X[i + 1] * R[i];
	std::cout << std::fixed << std::setprecision(10);
	db ans = 0;
	for (int i = 0; i < n; ++i)
		ans += pw((X[i + 1] - X[i] + v * (X[i + 1] + X[i])) / 2);
	for (int i = 1; i < n; ++i)
		ans -= pw(X[i] * v) / 2;
	std::cout << ans << '\n';
	for (int i = 1; i <= std::min(n - 1, 10); ++i)
		std::cout << X[i] << '\n';
	return 0;
}

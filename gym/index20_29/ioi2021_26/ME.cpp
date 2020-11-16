#include <bits/stdc++.h>

const int MAXN = 110;
typedef std::vector<int> VI;
VI operator + (VI a, VI b) {
	static int li[MAXN];
	memset(li, 0, sizeof li);
	for (int i = 0; i < a.size(); ++i)
		li[i] += a[i];
	for (int i = 0; i < b.size(); ++i)
		li[i] += b[i];
	for (int i = 0; i + 1 < MAXN; ++i)
		li[i + 1] += li[i] / 10, li[i] %= 10;
	int R = MAXN;
	while (R && !li[R - 1]) --R;
	return VI(li, li + R);
}
VI operator - (VI a, VI b) {
	static int li[MAXN];
	memset(li, 0, sizeof li);
	for (int i = 0; i < a.size(); ++i)
		li[i] += a[i];
	for (int i = 0; i < b.size(); ++i)
		li[i] -= b[i];
	for (int i = 0; i + 1 < MAXN; ++i)
		if (li[i] < 0) li[i] += 10, --li[i + 1];
	int R = MAXN;
	while (R && !li[R - 1]) --R;
	return VI(li, li + R);
}
VI operator * (VI a, int k) {
	static int li[MAXN];
	memset(li, 0, sizeof li);
	for (int i = 0; i < a.size(); ++i)
		li[i] = a[i] * k;
	for (int i = 0; i + 1 < MAXN; ++i)
		li[i + 1] += li[i] / 10, li[i] %= 10;
	int R = MAXN;
	while (R && !li[R - 1]) --R;
	return VI(li, li + R);
}
int n, K;
std::set<VI> S;
typedef std::tuple<VI, VI, VI> tp;
std::queue<tp> que;
void output(VI x) {
	std::reverse(x.begin(), x.end());
	for (auto t : x) putchar(t + 48);
}
int main() {
	scanf("%d%d", &K, &n);
	que.emplace(VI(), VI({1}), VI({1}) * K);
	while (!que.empty()) {
		VI a, b, c;
		std::tie(a, b, c) = que.front();
		que.pop();
		if (!a.empty() && !S.count(a) && !S.count(b) && !S.count(c)) {
			S.insert(a);
			S.insert(b);
			S.insert(c);
			output(a); putchar(32);
			output(b); putchar(32);
			output(c); putchar(10);
			if (!--n) break;
		}
		que.emplace(a, c, (a + c) * K - b);
		que.emplace(b, c, (b + c) * K - a);
	}
	return 0;
}

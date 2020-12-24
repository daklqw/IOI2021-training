#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;
const int MAXM = 4e5 + 10;
int head[MAXN], nxt[MAXM], to[MAXM], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
}
int n, m;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
	}

	return 0;
}

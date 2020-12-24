#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
const int MAXM = 2e5 + 10;
int head[MAXN], nxt[MAXM], to[MAXM], tot;
void adde(int b, int e) {
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
}
int n, m;
typedef std::pair<int, int> pi;
std::queue<pi> que;
int draw[MAXN][2];
void solvedraw() {
	static int ind[MAXN];
	for (int i = 1; i <= tot; ++i)
		++ind[to[i]];
	for (int i = 1; i <= n; ++i)
		if (!ind[i]) {
			que.emplace(i, 0);
			que.emplace(i, 1);
		} else {
			draw[i][0] = draw[i][1] = true;
		}
	while (!que.empty()) {
		pi _ = que.front(); que.pop();
		int t = _.first, b = _.second;
		for (int i = head[t]; i; i = nxt[i]) {
			if (!draw[to[i]][b ^ 1]) continue;
			bool ins = false;
			if (b == 0) ins = true;
			else ins = !--ind[to[i]];
			if (ins) {
				draw[to[i]][b ^ 1] = false;
				que.emplace(to[i], b ^ 1);
			}
		}
	}
}
int win[MAXN][2];
void solvewin() {
	static int ind[MAXN][2];
	for (int i = 1; i <= n; ++i)
		for (int j = head[i]; j; j = nxt[j])
			for (int b = 0; b < 2; ++b)
				if (!draw[i][b] && !draw[to[j]][b ^ 1])
					++ind[to[j]][b ^ 1];
	for (int i = 1; i <= n; ++i)
		for (int b = 0; b < 2; ++b)
			if (!ind[i][b])
				que.emplace(i, b);
	while (!que.empty()) {
		pi _ = que.front(); que.pop();
		int t = _.first, b = _.second;
		for (int i = head[t]; i; i = nxt[i]) {
			if (!draw[t][b] && !draw[to[i]][b ^ 1]) {
				if (win[to[i]][b ^ 1]) continue;
				bool ins = false;
				if (!win[t][b]) {
					win[to[i]][b ^ 1] = true;
					ins = true;
				} else {
					if (!--ind[to[i]][b ^ 1]) {
						win[to[i]][b ^ 1] = false;
						ins = true;
					}
				}
				if (ins) {
					que.emplace(to[i], b ^ 1);
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		if (ind[i][0])
			win[i][0] = true;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 1, b, e; i <= m; ++i)
		std::cin >> b >> e, adde(e, b);
	solvedraw();
	solvewin();
	for (int T = 0; T < 2; ++T) {
		for (int i = 1; i <= n; ++i) {
			if (draw[i][T]) std::cout << 'D';
			else std::cout << (win[i][T] ? "W" : "L");
		}
		std::cout << '\n';
	}
	return 0;
}

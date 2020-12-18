#include <bits/stdc++.h>

const int MAXN = 110;
typedef long long LL;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
struct _ { int x, y; } ;
std::queue<_> que;
int n, m;
int beln(int x) { x %= n; return x + (x >> 31 & n); }
int belm(int x) { x %= m; return x + (x >> 31 & m); }
char mat[MAXN][MAXN];
_ dir[MAXN][MAXN], dire;
bool vis[MAXN][MAXN];
int all;
void push(int x, int y) {
	// std::cout << "INS " << x << ' ' << y << std::endl;
	int bx = beln(x), by = belm(y);
	if (mat[bx][by] == '#') return ;
	int dx = (x - bx) / n;
	int dy = (y - by) / m;
	if (vis[bx][by]) {
		if (all) return ;
		_ & D = dir[bx][by];
		dx -= D.x, dy -= D.y;
		LL cr = (LL) dire.x * dy - (LL) dire.y * dx;
		if (cr) all = true;
		else if (dx || dy) {
			int g = gcd(dx, dy);
			dire = (_) {dx / g, dy / g};
		}
	} else {
		que.push((_) {x, y});
		vis[bx][by] = true;
		dir[bx][by] = (_) {dx, dy};
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for (int i = 0; i < n; ++i)
		std::cin >> mat[i];
	push(0, 0);
	while (!que.empty()) {
		_ t = que.front(); que.pop();
		const static int dx[4] = {1, 0, -1, 0};
		const static int dy[4] = {0, 1, 0, -1};
		for (int i = 0; i < 4; ++i) {
			int tx = t.x + dx[i];
			int ty = t.y + dy[i];
			push(tx, ty);
		}
	}
	int Q; std::cin >> Q;
	while (Q --> 0) {
		int x, y;
		std::cin >> x >> y;
		int bx = beln(x), by = belm(y);
		bool can = false;
		if (vis[bx][by]) {
			_ D = dir[bx][by];
			if (all) can = true;
			else if (dire.x || dire.y) {
				int dx = (bx - x) / n + D.x;
				int dy = (by - y) / m + D.y;
				LL cr = (LL) dx * dire.y - (LL) dy * dire.x;
				can = cr == 0;
			} else {
				int tx = D.x * n + bx;
				int ty = D.y * m + by;
				can = tx == bx && ty == by;
			}
		}
		std::cout << (can ? "yes" : "no") << '\n';
	}
	return 0;
}

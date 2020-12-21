#include <bits/stdc++.h>

const int MAXN = 257;
int Hlim, Wlim;
struct _ {
	int x, y, H, W;
} ws[MAXN];
int n;
int select(int x, int y) {
	for (int i = 1; i <= n; ++i)
		if (ws[i].x <= x && x < ws[i].x + ws[i].H)
			if (ws[i].y <= y && y < ws[i].y + ws[i].W)
				return i;
	return -1;
}
bool intersect(int l, int r, int L, int R) {
	return l < L ? L < r : l < R;
}
bool covered(_ a, int forb) {
	if (a.x < 0 || a.y < 0 || a.x + a.H > Hlim || a.y + a.W > Wlim)
		return true;
	for (int i = 1; i <= n; ++i)
		if (i != forb) {
			bool yes = true;
			yes &= intersect(a.x, a.x + a.H, ws[i].x, ws[i].x + ws[i].H);
			yes &= intersect(a.y, a.y + a.W, ws[i].y, ws[i].y + ws[i].W);
			if (yes) return true;
		}
	return false;
}
int shift(int id, int dx, int dy) {
	static int dis[MAXN][MAXN];
	memset(dis, 0x3f, sizeof dis);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (i != j) {
			if (dx != 0 && !intersect(ws[i].y, ws[i].y + ws[i].W,
									  ws[j].y, ws[j].y + ws[j].W)) continue;
			if (dy != 0 && !intersect(ws[i].x, ws[i].x + ws[i].H,
									  ws[j].x, ws[j].x + ws[j].H)) continue;
			int D = 0;
			if (dx > 0) D = ws[j].x - ws[i].x - ws[i].H;
			if (dx < 0) D = ws[i].x - ws[j].x - ws[j].H;
			if (dy > 0) D = ws[j].y - ws[i].y - ws[i].W;
			if (dy < 0) D = ws[i].y - ws[j].y - ws[j].W;
			if (D < 0) continue;
			dis[i][j] = D;
		}
	typedef std::pair<int, int> pi;
	std::priority_queue<pi> que;
	static int tim[MAXN];
	memset(tim, 0x3f, sizeof tim);
	const int INF = 0x3f3f3f3f;
	int lim = INF;
	que.emplace(0, id);
	while (!que.empty()) {
		auto _ = que.top(); que.pop();
		int u = _.second;
		if (tim[u] != INF) continue;
		tim[u] = -_.first;
		int dd = 0;
		if (dx < 0) dd = ws[u].x;
		if (dx > 0) dd = Hlim - ws[u].x - ws[u].H;
		if (dy < 0) dd = ws[u].y;
		if (dy > 0) dd = Wlim - ws[u].y - ws[u].W;
		lim = std::min(lim, tim[u] + dd);
		for (int i = 1; i <= n; ++i)
			if (dis[u][i] != INF && tim[i] == INF) {
				dd = dis[u][i] + tim[u];
				que.emplace(-dd, i);
			}
	}
	lim = std::min(lim, std::abs(dx + dy));
	if (dx) dx /= std::abs(dx);
	if (dy) dy /= std::abs(dy);
	for (int i = 1; i <= n; ++i) {
		int dta = std::max(lim - tim[i], 0);
		ws[i].x += dta * dx;
		ws[i].y += dta * dy;
	}
	return lim;
}
typedef std::string str;
str solve(str buf) {
	if (buf == "OPEN") {
		++n;
		std::cin >> ws[n].x >> ws[n].y >> ws[n].H >> ws[n].W;
		if (covered(ws[n], n)) {
			--n; return "window does not fit";
		}
		return "";
	}
	int x, y; std::cin >> x >> y;
	int id = select(x, y);
	if (id == -1) {
		if (buf != "CLOSE") std::cin >> x >> y;
		return "no window at given position";
	}
	if (buf == "CLOSE") {
		for (int i = id; i < n; ++i)
			ws[i] = ws[i + 1];
		--n;
	} else if (buf == "RESIZE") {
		int nh, nw;
		std::cin >> nh >> nw;
		_ t = ws[id];
		t.H = nh, t.W = nw;
		if (covered(t, id))
			return "window does not fit";
		ws[id] = t;
	} else {
		int dx, dy;
		std::cin >> dx >> dy;
		int r = std::abs(shift(id, dx, dy));
		dx = std::abs(dx + dy);
		if (r != dx) {
			static char buf[100];
			sprintf(buf, "moved %d instead of %d", r, dx);
			return buf;
		}
	}
	return "";
}

void output() {
	std::cout << n << " window(s):\n";
	for (int i = 1; i <= n; ++i)
		std::cout << ws[i].x << ' ' << ws[i].y << ' '
				  << ws[i].H << ' ' << ws[i].W << '\n';
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> Hlim >> Wlim;
	str buf;
	int optc = 0;
	while (std::cin >> buf) {
		++optc;
		str res = solve(buf);
		if (res != "") {
			std::cout << "Command " << optc << ": " << buf << " - ";
			std::cout << res << '\n';
		}
		// output();
	}
	output();
	return 0;
}

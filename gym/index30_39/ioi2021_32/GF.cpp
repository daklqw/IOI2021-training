#include <bits/stdc++.h>

const int MAXN = 3e5 + 10;

struct _ { int x, y; };
struct rect { _ x, y; };
typedef std::vector<rect> V;
int X, Y, L;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		std::cin >> X >> Y >> L;
		int x = 0, y = 0;
		V ansl;
		while (true) {
			bool ex = true;
			if (x != X && (x < X) == (X > 0)) ex = false;
			if (y != Y && (y < Y) == (Y > 0)) ex = false;
			if (ex) break;
			bool fir = x == 0 && y == 0;
			int dx = std::abs(X - x), dy = std::abs(Y - y);
			if (dx <= dy)
				dx = std::min(dx, L - 1), dy = L - fir;
			else
				dy = std::min(dy, L - 1), dx = L - fir;
			int cx = 0 < X ? 1 : -1, cy = 0 < Y ? 1 : -1;
			int tx = x + cx * dx, ty = y + cy * dy;
			int sx = tx - cx * (L - 1), sy = ty - cy * (L - 1);
			x = tx, y = ty;
			// std::cerr << "NOW " << x << ' ' << y << ' ' << dx << ' ' << dy << std::endl;
			ansl.push_back((rect) {(_) {sx, sy}, (_) {tx, ty}});
		}
		int swp = false;
		if (y != Y) swp = true;
		else if (x == X && ansl[0].x.x != 0) swp = true;
		if (swp) for (auto & t : ansl) std::swap(t.x, t.y);
		std::cout << ansl.size() << '\n';
		for (auto t : ansl) {
			std::cout << t.x.x << ' ' << t.x.y << ' ';
			std::cout << t.y.x << ' ' << t.y.y << '\n';
		}
	}
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 1e6 + 10;
struct _ {
	int x, y, z;
	_() { x = y = z = 0; }
	_(int a, int b, int c) {
		x = a, y = b, z = c;
	}
} ;
typedef std::pair<_, _> rect;

typedef std::vector<rect> VI;
VI hav[3]; int R;

void gmi(int & x, int y) {
	x > y ? x = y : 0;
}
void gma(int & x, int y) {
	x < y ? x = y : 0;
}
int solve(VI S, VI T, int C, int D) {
	if (C) {
		for (auto & t : S) {
			std::swap(t.first.x, t.first.y);
			std::swap(t.second.x, t.second.y);
		}
		for (auto & t : T) {
			std::swap(t.first.x, t.first.y);
			std::swap(t.second.x, t.second.y);
		}
	}
	int mi[3], ma[3];
	memset(mi, 0xc0, sizeof mi);
	memset(ma, 0x3f, sizeof ma);
	for (auto t : S) {
		gma(mi[0], t.first.x);
		gmi(ma[0], t.first.x + R);
		int l = t.first.y, r = t.second.y;
		if (l > r) std::swap(l, r);
		gma(mi[1], l);
		gmi(ma[1], r + (D == 1) * R);
		l = t.first.z, r = t.second.z;
		if (l > r) std::swap(l, r);
		gma(mi[2], l);
		gmi(ma[2], r + (D == 2) * R);
	}
	for (auto t : T) {
		int X = std::max(t.first.x, t.second.x);
		if (X < mi[0] || X > ma[0]) return 1;
		bool hav = false;
		int y = std::max(t.first.y, t.second.y);
		int z = std::max(t.first.z, t.second.z);
		if (mi[1] <= y && y <= ma[1])
			if (mi[2] <= z && z <= ma[2])
				hav = true;
		if (!hav) return 1;
	}
	return 0;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int T; std::cin >> T;
	while (T --> 0) {
		int n; std::cin >> n;
		for (int i = 0; i < 3; ++i)
			hav[i].clear();
		for (int i = 1; i <= n; ++i) {
			_ a, b;
			std::cin >> a.x >> a.y >> a.z;
			std::cin >> b.x >> b.y >> b.z;
			int typ = -1;
			if (a.x == b.x) typ = 0;
			if (a.y == b.y) typ = 1;
			if (a.z == b.z) typ = 2;
			hav[typ].emplace_back(a, b);
			if (typ == 0) R = std::abs(a.y - b.y);
			else R = std::abs(a.x - b.x);
		}
		int sm = 0;
		sm += solve(hav[0], hav[1], 0, 2);
		sm += solve(hav[0], hav[2], 0, 1);
		sm += solve(hav[1], hav[2], 1, 1);
		int all = 0;
		for (int i = 0; i < 3; ++i)
			all += hav[i].size() > 0;
		std::cout << (sm >= all - 1 ? "NO" : "YES") << '\n';
	}
	return 0;
}

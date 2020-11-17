#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;

void bye() {
	std::cout << "syntax error" << std::endl;
	exit(0);
}

struct _ {
	int x, y, typ, id;
} lhs[MAXN], rhs[MAXN];

typedef std::pair<int, int> pi;
int n, match[MAXN];
std::map<int, std::vector<_> > M;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> lhs[i].x >> lhs[i].y;
		lhs[i].typ = 1;
		lhs[i].id = i;
		M[lhs[i].x].push_back(lhs[i]);
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> rhs[i].x >> rhs[i].y;
		rhs[i].typ = -1;
		rhs[i].id = i;
		M[rhs[i].x].push_back(rhs[i]);
	}
	std::set<pi> S;
	for (auto i : M) {
		for (auto t : i.second) {
			if (t.typ == 1) {
				S.emplace(t.y, t.id);
			} else {
				auto it = S.upper_bound(pi(t.y, n + 1));
				if (it == S.begin()) bye();
				--it;
				match[it->second] = t.id;
				S.erase(it);
			}
		}
	}
	for (int C = 0; C < 2; ++C) {
		M.clear();
		std::set<int> T;
		for (int i = 1; i <= n; ++i) {
			const int v = match[i];
			_ t = (_) {lhs[i].y, rhs[v].y, 1, i};
			M[lhs[i].x].push_back(t);
			t.typ = -1;
			M[rhs[v].x].push_back(t);
		}
		for (auto i : M) {
			for (auto t : i.second) {
				if (t.typ == 1) {
					auto it = T.lower_bound(t.x);
					if (it != T.end() && *it <= t.y) bye();
					T.insert(t.x);
					T.insert(t.y);
				} else {
					T.erase(t.x);
					T.erase(t.y);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			std::swap(lhs[i].x, lhs[i].y);
			std::swap(rhs[i].x, rhs[i].y);
		}
	}
	for (int i = 1; i <= n; ++i)
		std::cout << match[i] << '\n';
	return 0;
}

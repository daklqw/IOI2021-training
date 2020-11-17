#include <bits/stdc++.h>

const int MAXN = 21;

void gma(int & x, int y) {
	x < y ? x = y : 0;
}
struct _ {
	int t, x;
};
std::queue<_> task[MAXN];
int ansl[MAXN], start[MAXN];
int n, R;
int bel[MAXN];
int bsepr[MAXN], respr[MAXN], dynpr[MAXN];
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> R;
	for (int i = 1; i <= n; ++i) {
		int t;
		std::cin >> start[i] >> bsepr[i] >> t;
		for (int j = 1; j <= t; ++j) {
			char x; int c;
			std::cin >> x >> c;
			if (x == 'C') {
				for (int k = 0; k < c; ++k)
					task[i].push((_) {1, 1});
			} else {
				task[i].push((_) {x == 'L' ? 2 : 3, c});
				gma(respr[c], bsepr[i]);
			}
		}
	}
	memset(ansl, -1, sizeof ansl);
	for (int TT = 1; ; ) {
		std::vector<int> li;
		bool hav = false;
		for (int i = 1; i <= n; ++i)
			if (ansl[i] == -1) {
				hav = true;
				if (TT >= start[i])
					li.push_back(i);
			}
		if (!hav) break;
		if (li.empty()) {
			++TT;
			continue;
		}
		memcpy(dynpr, bsepr, sizeof dynpr);
		bool need[21], blo[21];
		int tar[21];
		memset(need, 1, sizeof need);
		memset(blo, 0, sizeof blo);
		memset(tar, 0, sizeof tar);
		for (int i : li) {
			_ t = task[i].front();
			if (t.t == 2)
				tar[i] = t.x;
		}
		while (true) {
			int mi = 0x3f3f3f3f, at = -1;
			for (int i : li)
				if (need[i] && dynpr[i] < mi)
					mi = dynpr[i], at = i;
			if (at == -1) break;
			int tx = tar[at];
			blo[at] = false;
			if (tx && bel[tx] && bel[tx] != at)
				blo[at] = true;
			int ori = dynpr[at];
			dynpr[at] = bsepr[at];
			for (int i = 1; i <= R; ++i)
				if (bel[i] && bel[i] == at)
					for (auto j : li) if (j != at && tar[j])
						if (respr[i] >= dynpr[j])
							gma(dynpr[at], dynpr[j]);
			if (tx) for (int i = 1; i <= R && !blo[at]; ++i)
				if (bel[i] && bel[i] != at)
					if (respr[i] >= dynpr[at])
						blo[at] = true;
			if (ori != dynpr[at])
				memset(need, 1, sizeof need);
			need[at] = false;
		}
		int ma = 0xc0c0c0c0, u = -1;
		for (int i : li)
			if (!blo[i] && dynpr[i] > ma)
				ma = dynpr[i], u = i;
		_ t = task[u].front(); task[u].pop();
		if (t.t == 1) TT += t.x;
		else if (t.t == 2) bel[t.x] = u;
		else bel[t.x] = 0;
		if (task[u].empty())
			ansl[u] = TT;
	}
	for (int i = 1; i <= n; ++i)
		std::cout << ansl[i] << '\n';
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 210;
const int MAXC = MAXN * MAXN / 2;
const int MAXP = 404;

typedef std::bitset<MAXP> B;
typedef B GR[MAXP];

int n, bak;
struct _ {
	int x, y, v;
	bool operator < (_ b) const {
		return v < b.v;
	}
} es[MAXC];
GR grx[MAXC], gry[MAXC];
int get(int x, int b) {
	return x * 2 - 1 + b;
}
GR gr;
int dfn[MAXP], low[MAXP], st[MAXP], top, ins[MAXP], idx;
int bel[MAXP], cnt;
bool tarjan(int u) {
	dfn[u] = low[u] = ++idx;
	ins[st[++top] = u] = true;
	for (int i = gr[u]._Find_first(); i != MAXP; i = gr[u]._Find_next(i))
		if (!dfn[i]) {
			if (tarjan(i)) return true;
			low[u] = std::min(low[u], low[i]);
		} else if (ins[i])
			low[u] = std::min(low[u], dfn[i]);
	if (low[u] == dfn[u]) {
		int v; ++cnt;
		do {
			ins[v = st[top--]] = false;
			bel[v] = cnt;
			if (bel[((v + 1) ^ 1) - 1] == cnt)
				return true;
		} while (v != u);
	}
	return false;
}
int judge(int x, int y) {
	for (int i = 1; i <= n * 2; ++i)
		gr[i] = grx[x][i] | gry[y][i];
	memset(dfn, 0, (n * 2 + 1) << 2);
	memset(ins, 0, (n * 2 + 1) << 2);
	memset(bel, 0, (n * 2 + 1) << 2);
	top = cnt = idx = 0;
	for (int i = 1; i <= n * 2; ++i)
		if (!dfn[i])
			if (tarjan(i))
				return false;
	for (int i = 1; i <= n; ++i)
		if (bel[get(i, 0)] == bel[get(i, 1)])
			return false;
	return true;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j) {
			++bak;
			std::cin >> es[bak].v;
			es[bak].x = i;
			es[bak].y = j;
		}
	std::sort(es + 1, es + 1 + bak);
	static GR gx, gy;
	for (int i = bak; ~i; --i) {
		for (int j = 1; j <= n * 2; ++j) {
			grx[i][j] = gx[j];
			gry[i][j] = gy[j];
		}
		if (i) {
			gx[get(es[i].x, 0)].set(get(es[i].y, 1));
			gx[get(es[i].y, 0)].set(get(es[i].x, 1));
			gy[get(es[i].x, 1)].set(get(es[i].y, 0));
			gy[get(es[i].y, 1)].set(get(es[i].x, 0));
		}
	}
	int cur = bak;
	int ans = std::numeric_limits<int>::max();
	for (int i = 0; i <= cur; ++i) {
		while (cur >= i && judge(i, cur - 1))
			--cur;
		ans = std::min(ans, es[i].v + es[cur].v);
	}
	std::cout << ans << std::endl;
	return 0;
}

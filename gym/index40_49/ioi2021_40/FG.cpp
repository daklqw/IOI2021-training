#include <bits/stdc++.h>

const int MAXN = 2e6 + 10;
const int MAXP = 1e6 + 10;
int sz[MAXN];
namespace SAM {
	int nxt[MAXN][26], fail[MAXN], R[MAXN], lst, tot;
	int extend(int x, int lst) {
		int p, u, v, t;
		R[u = ++tot] = R[p = lst] + 1;
		sz[u] = 1;
		for (; p && !nxt[p][x]; p = fail[p])
			nxt[p][x] = u;
		if (!p) fail[u] = 1;
		else {
			t = nxt[p][x];
			if (R[t] == R[p] + 1)
				fail[u] = t;
			else {
				R[v = ++tot] = R[p] + 1;
				memcpy(nxt[v], nxt[t], 104);
				fail[v] = fail[t];
				fail[t] = fail[u] = v;
				for (; p && nxt[p][x] == t; p = fail[p])
					nxt[p][x] = v;
			}
		}
		return u;
	}
}
int head[MAXN], nxt[MAXN], val[MAXP];
int n, Q;
int rt[MAXP];
void dfs(int u) {
	for (int i = head[u]; i; i = nxt[i]) {
		dfs(i);
		sz[u] += sz[i];
	}
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> Q;
	for (int i = 1; i <= n; ++i) {
		static char buf[10];
		int fa;
		std::cin >> buf >> fa;
		nxt[i] = head[fa];
		head[fa] = i;
		val[i] = *buf - 'A';
	}
	static int que[MAXP];
	int hd = 0, tl = 1;
	que[0] = 0;
	rt[0] = SAM::tot = 1;
	while (hd < tl) {
		int t = que[hd++];
		for (int i = head[t]; i; i = nxt[i]) {
			rt[i] = SAM::extend(val[i], rt[t]);
			que[tl++] = i;
		}
	}
	memset(head, 0, sizeof head);
	for (int i = 2; i <= SAM::tot; ++i) {
		nxt[i] = head[SAM::fail[i]];
		head[SAM::fail[i]] = i;
	}
	dfs(1);
	while (Q --> 0) {
		static char buf[MAXN];
		std::cin >> buf;
		int now = 1;
		for (int i = (int) strlen(buf) - 1; ~i; --i)
			now = SAM::nxt[now][buf[i] - 'A'];
		std::cout << sz[now] << '\n';
	}
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 3e4 + 10;
char buf[MAXN]; int nxt[MAXN];

const int need[5] = {0, 4, 4, 3, 2};
struct _ {
	int typ, sm;
	_() { sm = typ = 0; }
	std::vector<_*> st;
	_ * add(_ * b) {
		st.push_back(b);
		const int T = st[0]->typ;
		if ((int) st.size() == need[T]) {
			_ * R;
			if (T == 1) {
				R = st[1]->add(st[2]->add(st[3]));
			} else if (T == 2) {
				R = st[1]->add(st[3])->add(st[2]);
			} else {
				R = st[1];
			}
			R->sm += this->sm + st[0]->sm + 1;
			return R;
		}
		return this;
	}
	int dfs() {
		if (typ) return 0;
		int r = sm;
		for (auto t : st) r += t->dfs();
		return r;
	}
} ;
_ * solve(int l, int r) {
	if (l + 1 == r) {
		_ * R = new _, * S = new _;
		if (buf[l] == 'B') S->typ = 1;
		if (buf[l] == 'C') S->typ = 2;
		if (buf[l] == 'K') S->typ = 3;
		if (buf[l] == 'I') S->typ = 4;
		R->st.push_back(S);
		return R;
	}
	_ * R = NULL;
	for (int i = l; i < r; ++i) {
		_ * tar;
		if (buf[i] == '(')
			tar = solve(i + 1, nxt[i]), i = nxt[i];
		else tar = solve(i, i + 1);
		if (R == NULL) R = tar;
		else R = R->add(tar);
	}
	return R;
}
int main() {
#define FILENAME "combinator"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> buf;
	int n = strlen(buf);
	static int st[MAXN], top;
	for (int i = 0; i < n; ++i) {
		if (buf[i] == '(') st[top++] = i;
		else if (buf[i] == ')') nxt[st[--top]] = i;
	}
	_ * rt = solve(0, n);
	int ans = rt->dfs();
	std::cout << ans << std::endl;
	return 0;
}

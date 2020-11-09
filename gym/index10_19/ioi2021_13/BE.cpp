#include <bits/stdc++.h>

const int MAXN = 4010;
void bye() {
	std::cout << "impossible" << std::endl;
	exit(0);
}
char buf[MAXN][MAXN];
int n;
int len[MAXN], rk[MAXN];
int incl(int x, int y) {
	if (len[x] <= len[y]) return false;
	char * l = buf[x], * r = buf[y];
	while (*r) {
		char * at = strchr(l, *r);
		if (at == NULL) return false;
		l = at + 1; ++r;
	}
	return true;
}
typedef std::vector<int> VI;
VI lhs, rhs, tmp;
void push(int tc) {
	auto & t = tc == 0 ? lhs : rhs;
	t.insert(t.end(), tmp.begin(), tmp.end());
	tmp.clear();
}
bool judge(const VI & x, int v) {
	return x.empty() || incl(v, x.back());
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i <= n; ++i) {
		std::cin >> buf[i];
		rk[i] = i;
		len[i] = strlen(buf[i]);
	}
	auto cmp = [] (int a, int b) {
		return len[a] < len[b];
	};
	std::sort(rk + 1, rk + n + 1, cmp);
	for (int T = 1; T <= n; ++T) {
		const int i = rk[T];
		int lc = judge(lhs, i);
		int rc = judge(rhs, i);
		if (!lc && !rc) bye();
		if (lc && rc) {
			int mc = judge(tmp, i);
			if (mc) tmp.push_back(i);
			else rc = 0;
		}
		if (lc + rc == 1) {
			(lc ? lhs : rhs).push_back(i);
			push(lc);
		}
	}
	push(0);
	if (!judge(lhs, 0) || !(judge(rhs, 0))) bye();
	std::cout << lhs.size() << ' ' << rhs.size() << '\n';
	for (auto t : lhs) std::cout << buf[t] << '\n';
	for (auto t : rhs) std::cout << buf[t] << '\n';
	return 0;
}

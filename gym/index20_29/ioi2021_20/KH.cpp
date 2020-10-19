#include <bits/stdc++.h>

const int MAXN = 1e5 + 10;
const int MAXP = MAXN * 32;
typedef long long LL;

int son[MAXP][2], val[MAXP], idx;
int add(int u, int v, int dig) {
	++idx;
	son[idx][0] = son[u][0];
	son[idx][1] = son[u][1];
	val[idx] = val[u] + 1;
	u = idx;
	if (dig == -1) return u;
	int t = v >> dig & 1;
	son[u][t] = add(son[u][t], v, dig - 1);
	return u;
}
int get(int l, int r, int v, int dig) {
	if (dig == -1) return val[r] - val[l];
	int t = v >> dig & 1;
	return get(son[l][t], son[r][t], v, dig - 1);
}

int rt[MAXN];
int n, A[MAXN], pr[MAXN];
typedef std::map<int, int> M;
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	const int DD = 30;
	M now;
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		std::cin >> A[i];
		pr[i] = pr[i - 1] ^ A[i];
		rt[i] = add(rt[i - 1], pr[i - 1], DD);
		M tmp;
		auto gmi = [&tmp] (int x, int y) {
			if (!tmp.count(x)) tmp[x] = y;
			else tmp[x] = std::min(tmp[x], y);
		};
		for (auto t : now)
			gmi(t.first & A[i], t.second);
		gmi(A[i], i);
		now = tmp;
		int lst = i;
		for (auto it = now.rbegin(); it != now.rend(); ++it) {
			ans += get(rt[it->second - 1], rt[lst], it->first ^ pr[i], DD);
			lst = it->second - 1;
		}
	}
	std::cout << ans << std::endl;
	return 0;
}

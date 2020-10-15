#include <bits/stdc++.h>

typedef long long LL;
LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}
struct frac {
	LL a, b;
	void reduce() {
		LL g = gcd(a, b);
		a /= g, b /= g;
	}
} ans;
typedef std::string str;
int n;
int gr[256], to[256], idx, rl[256], mat[30];
int get(int x) {
	return !to[x] ? to[x] = ++idx : to[x];
}
int fa[256];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	static char buf[12243];
	std::cin.getline(buf, 1024);
	n = strtol(buf, 0, 10);
	gr[get('1')] |= 1 << get('1');
	gr[get('n')] |= 1 << get('n');
	for (int T = 1; T <= n; ++T) {
		std::cin.getline(buf, 1024);
		int tc = 0;
		while (buf[tc] == ' ') ++tc;
		if (buf[tc] == 'l') {
			for (int i = 1; i <= idx; ++i) fa[i] = i;
			for (int i = 1; i <= idx; ++i)
				for (int j = 1; j <= idx; ++j)
					for (int k = 1; k <= idx; ++k)
						if (gr[j] >> k & 1)
							gr[j] |= gr[k];
			for (int i = 1; i <= idx; ++i)
				for (int j = 1; j <= idx; ++j)
					if ((gr[i] >> j & 1) && (gr[j] >> i & 1))
						fa[find(i)] = find(j);
			n = 0;
			memset(rl, -1, sizeof rl);
			for (int i = 1; i <= idx; ++i)
				if (fa[i] == i)
					rl[i] = n++;
			for (int i = 1; i <= idx; ++i)
				for (int j = 1; j <= idx; ++j)
					if (gr[i] >> j & 1)
						mat[rl[find(i)]] |= 1 << rl[find(j)];
			static LL dp[1 << 22];
			const int U = 1 << n;
			dp[0] = 1;
			for (int i = 0; i < U; ++i)
				for (int j = 0; j < n; ++j)
					if ((~i >> j & 1) && !(mat[j] & i))
						dp[i | 1 << j] += dp[i];
			ans.a = dp[U - 1];
			ans.b = 1;
			n -= 2;
			for (int i = 1; i <= n; ++i)
				ans.b *= i;
			ans.reduce();
			std::cout << n << ' ' << ans.a << '/' << ans.b << std::endl;
			return 0;
		} else {
			*strchr(buf, ',') = ' ';
			*strchr(buf, ')') = ' ';
			*strchr(buf, '(') = ' ';
			static char var[10], tmp[10], lhs[10], rhs[10];
			sscanf(buf, "%s %s %s %s %s %s", tmp, var, tmp, tmp, lhs, rhs);
			char v = *var, l = *lhs, r = *rhs;
			gr[get(v)] |= 1 << get(l);
			gr[get(r)] |= 1 << get(v);
		}
	}
	return 0;
}

#include <bits/stdc++.h>

const int MAXN = 10010;
typedef long long LL;
struct vec {
	int x, y, z;
	vec() { x = y = z = 0; }
	vec(int a, int b, int c) { x = a, y = b, z = c; }
	friend std::istream & operator >> (std::istream & in, vec & x) {
		in >> x.x >> x.y >> x.z;
		return in;
	}
	bool operator < (vec b) const {
		if (x != b.x) return x < b.x;
		if (y != b.y) return y < b.y;
		return z < b.z;
	}
	vec operator - (vec b) const {
		return vec(x - b.x, y - b.y, z - b.z);
	}
} S, T, pool[MAXN];
struct tri {
	vec A, B, C;
} ps[MAXN];
std::map<vec, int> M;
int idx;
int get(vec x) {
	if (M.count(x)) {
		return M[x];
	} else {
		pool[++idx] = x;
		return M[x] = idx;
	}
}
struct _ {
	int x, y, v;
	bool operator < (_ b) const {
		return v < b.v;
	}
} es[MAXN];
int bak;
int n;
void ins(vec x, vec y) {
	es[++bak] = (_) {get(x), get(y), std::max(x.z, y.z)};
}
int fa[MAXN];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], tot;
void adde(int b, int e) {
	// std::cout << "ADDE " << b << ' ' << e << std::endl;
	nxt[++tot] = head[b]; to[head[b] = tot] = e;
	nxt[++tot] = head[e]; to[head[e] = tot] = b;
	fa[find(b)] = find(e);
}
int vis[MAXN], pre[MAXN];
std::queue<int> que;
void bfs(int S) {
	que.push(S); vis[S] = true;
	while (!que.empty()) {
		int t = que.front(); que.pop();
		for (int i = head[t]; i; i = nxt[i])
			if (!vis[to[i]]) {
				vis[to[i]] = true;
				que.push(to[i]);
				pre[to[i]] = t;
			}
	}
}
LL cross(vec a, vec b, vec c) {
	LL res = 0;
	res += (LL) a.x * b.y * c.z;
	res += (LL) b.x * c.y * a.z;
	res += (LL) c.x * a.y * b.z;
	res -= (LL) a.x * c.y * b.z;
	res -= (LL) b.x * a.y * c.z;
	res -= (LL) c.x * b.y * a.z;
	return res;
}
LL cross(vec a, vec b) {
	return (LL) a.x * b.y - (LL) a.y * b.x;
}
void ins(vec x) {
	for (int i = 1; i <= n; ++i) {
		if (cross(ps[i].A - x, ps[i].B - x, ps[i].C - x) == 0) {
			LL ca = cross(ps[i].A - x, ps[i].B - x);
			LL cb = cross(ps[i].B - x, ps[i].C - x);
			LL cc = cross(ps[i].C - x, ps[i].A - x);
			bool can = false;
			can |= ca <= 0 && cb <= 0 && cc <= 0;
			can |= ca >= 0 && cb >= 0 && cc >= 0;
			if (!can) continue;
			// std::cout << "CALC BEL " << i << std::endl;
			ins(ps[i].A, x);
			ins(ps[i].B, x);
			ins(ps[i].C, x);
		}
	}
}
int main() {
#define FILENAME "hiking"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> ps[i].A >> ps[i].B >> ps[i].C;
		ins(ps[i].A, ps[i].B);
		ins(ps[i].A, ps[i].C);
		ins(ps[i].B, ps[i].C);
	}
	std::cin >> S >> T;
	ins(S); ins(T);
	int SS = get(S), TT = get(T);
	for (int i = 1; i <= idx; ++i) fa[i] = i;
	std::sort(es + 1, es + 1 + bak);
	// std::cerr << "NOW " << SS << ' ' << TT << std::endl;
	for (int i = 1; i <= bak; ++i) {
		adde(es[i].x, es[i].y);
		if (find(SS) == find(TT)) {
			bfs(SS);
			std::vector<int> ansl;
			int u = TT;
			while (u != SS)
				ansl.push_back(u), u = pre[u];
			ansl.push_back(SS);
			std::reverse(ansl.begin(), ansl.end());
			std::cout << ansl.size() << '\n';
			for (auto t : ansl) {
				vec x = pool[t];
				std::cout << x.x << ' ' << x.y << ' ' << x.z << '\n';
			}
			break;
		}
	}
	return 0;
}

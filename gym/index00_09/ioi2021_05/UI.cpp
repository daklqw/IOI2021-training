#include <bits/stdc++.h>

typedef unsigned long long LL;
LL xorshift(LL x) {
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return x;
}

std::unordered_map<LL, int> M[20];
struct _ {
	int A[9][9];
	void swap(int x, int y) {
		std::swap(A[x], A[y]);
	}
	_ operator ~() const {
		_ r;
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				r.A[i][j] = A[j][i];
		return r;
	}
	LL ha() const {
		LL r = 114514;
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				r = xorshift(r + A[i][j] * 3189012441317);
		return r;
	}
	void rename(int x, int y) {
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				if (A[i][j] == x) A[i][j] = y;
				else if (A[i][j] == y) A[i][j] = x;
	}
} ;
std::istream & operator >> (std::istream & in, _ & A) {
	static char buf[12];
	for (int i = 0; i < 9; ++i) {
		in >> buf;
		for (int j = 0; j < 9; ++j)
			A.A[i][j] = buf[j] == '.' ? 0 : buf[j] - '0';
	}
	return in;
}

struct info {
	char ch; int x, y;
};

typedef std::vector<info> VI;
typedef std::pair<int, int> pi;
typedef std::vector<pi> VP;
VP gettri(int v) {
	switch (v) {
		case 0: return {};
		case 1: return {pi(1, 2)};
		case 2: return {pi(0, 1)};
		case 3: return {pi(0, 1), pi(1, 2)};
		case 4: return {pi(0, 2), pi(1, 2)};
		case 5: return {pi(0, 2)};
	}
	return {pi(114514, 1919810)};
}
VI gene(int v) {
	VI r;
	if (v & 1) r.push_back((info) {'F', 0, 0});
	v /= 2;
	for (int i = 0; i < 3; ++i, v /= 6)
		for (auto a : gettri(v % 6))
			r.push_back((info) {'r', a.first + i * 3, a.second + i * 3});
	for (auto a : gettri(v))
		r.push_back((info) {'R', a.first, a.second});
	return r;
}
VI rename(_ x) {
	static int li[9];
	int bak = 0, vis = 0;
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			if (x.A[i][j] && !(vis >> (x.A[i][j] - 1) & 1)) {
				vis |= 1 << (x.A[i][j] - 1);
				li[bak++] = x.A[i][j];
			}
	for (int i = 0; i < 9; ++i)
		if (!(vis >> i & 1))
			li[bak++] = i + 1;
	VI r;
	for (int i = 0; i < bak; ++i)
		for (int j = 0; j + 1 < bak; ++j)
			if (li[j] > li[j + 1]) {
				std::swap(li[j], li[j + 1]);
				r.push_back((info) {'D', li[j], li[j + 1]});
			}
	return r;
}
_ perform(_ x, int v, bool rev, VI * tar = NULL) {
	VI tp = gene(v);
	if (rev) {
		info t = (info) {'F', 0, 0};
		tp.insert(tp.begin(), t);
		tp.insert(tp.end(), t);
	}
	if (tar != NULL)
		tar->insert(tar->end(), tp.begin(), tp.end());
	for (auto t : tp) {
		if (t.ch == 'F') x = ~x;
		else if (t.ch == 'r') x.swap(t.x, t.y);
		else {
			assert(t.ch == 'R');
			for (int i = 0; i < 3; ++i)
				x.swap(t.x * 3 + i, t.y * 3 + i);
		}
	}
	tp = rename(x);
	if (tar != NULL)
		tar->insert(tar->end(), tp.begin(), tp.end());
	for (auto t : tp)
		x.rename(t.x, t.y);
	return x;
}
int n;
_ A[20];
int ansl[20][20];
void output(int i, int j) {
	VI lhs, rhs;
	// std::cerr << "NOW " << ansl[i][j] << ' ' << ansl[j][i] << std::endl;
	perform(A[i], ansl[i][j], false, &lhs);
	perform(A[j], ansl[j][i], true, &rhs);
	lhs.insert(lhs.end(), rhs.rbegin(), rhs.rend());
	std::cout << lhs.size() << '\n';
	for (auto t : lhs) {
		if (t.ch == 'F') std::cout << "F\n";
		else {
			if (t.ch != 'D')
				++t.x, ++t.y;
			std::cout << t.ch << ' ' << t.x << ' ' << t.y << '\n';
		}
	}
}
int main() {
#define FILENAME "intellectual"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n; ++i)
		std::cin >> A[i];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 2592; ++j)
			M[i][perform(A[i], j, false).ha()] = j;
	memset(ansl, -1, sizeof ansl);
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < 2592; ++j) {
			LL v = (perform(A[i], j, true)).ha();
			for (int k = 0; k < i; ++k)
				if (ansl[k][i] == -1 && M[k].count(v)) {
					ansl[k][i] = M[k][v];
					ansl[i][k] = j;
				}
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			if (ansl[i][j] != -1) {
				std::cout << "Yes" << '\n';
				output(i, j);
			} else
				std::cout << "No" << '\n';
	return 0;
}

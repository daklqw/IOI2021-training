#include <bits/stdc++.h>

const int MAXN = 3e5 + 10;
typedef long long LL;
typedef std::pair<int, int> pi;
struct _ {
	std::vector<int> li;
	LL A[2][2];
	_() {
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				A[i][j] = 1e12;
	}
} ;
std::map<pi, _> MT;

int n, D, M;
void gmi(LL & x, LL y) {
	x > y ? x = y : 0;
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> D;
	for (int i = 1, lst = 0, t; i <= D; ++i) {
		std::cin >> t;
		if (lst) {
			int tr = lst > t;
			pi at(std::min(lst, t), std::max(lst, t));
			MT[at].li.push_back(tr);
		}
		lst = t;
	}
	std::cin >> M;
	for (int i = 1; i <= M; ++i) {
		static char typ[3];
		int x, y, v;
		std::cin >> x >> y >> typ >> v;
		pi at(std::min(x, y), std::max(x, y));
		gmi(MT[at].A[x > y][*typ == 'R'], v);
	}
	LL ans = 0;
	for (auto __ : MT) {
		_ & V = __.second;
		gmi(V.A[0][0], V.A[0][1]);
		gmi(V.A[1][0], V.A[1][1]);
		V.A[0][1] -= V.A[0][0] + V.A[1][0];
		V.A[1][1] -= V.A[0][0] + V.A[1][0];
		if (V.A[0][1] > V.A[1][1]) {
			std::swap(V.A[0][1], V.A[1][1]);
			std::swap(V.A[0][0], V.A[1][0]);
			for (auto & t : V.li) t ^= 1;
		}
		for (auto t : V.li)
			ans += V.A[t][0];
		for (int T = 0; T != 2; ++T)
			if (V.A[T][1] < 0) {
				const int L = V.li.size();
				static int st[MAXN]; int top = 0;
				for (int i = 0; i < L; ++i) 
					if (V.li[i] != -1) {
						if (V.li[i] == T)
							st[++top] = i;
						else if (top) {
							ans += V.A[T][1];
							V.li[st[top--]] = -1;
							V.li[i] = -1;
						}
					}
			}
	}
	std::cout << ans << std::endl;
	return 0;
}

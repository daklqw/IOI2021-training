#include <bits/stdc++.h>

const int MAXN = 50010;

enum TYPE { BUY = 1, SELL = 2 } ;
struct trade {
	int buyid, sellid, p, v;
	bool operator < (const trade & b) const {
		if (buyid == b.buyid)
			return sellid < b.sellid;
		return buyid < b.buyid;
	}
} ;
std::vector<trade> ansl;
struct order {
	int id, typ, p, v, tv, cv;
	void f5cv() {
		cv = std::min(v, tv);
	}
} ;
std::map<int, std::queue<order> > M[2];
inline int divup(int a, int b) {
	return a / b + (a % b != 0);
}
inline int modup(int a, int b) {
	return a % b == 0 ? b : a % b;
}
decltype(ansl) tmp;
void calc(order & A, std::queue<order> & que) {
	static order li[MAXN];
	static int ge[MAXN];
	int bak = 0, pre = 0;
	while (!que.empty() && A.v) {
		order t = que.front();
		int cost = std::min(A.v, t.cv);
		A.v -= cost;
		t.v -= cost;
		t.cv -= cost;
		if (!t.v) {
			trade d;
			d.buyid = A.id;
			d.sellid = t.id;
			if (A.typ == SELL)
				std::swap(d.buyid, d.sellid);
			d.p = t.p;
			d.v = cost;
			tmp.push_back(d);
		} else {
			ge[bak] += cost;
			bool hav = false;
			if (!t.cv) {
				t.f5cv();
				hav = true;
			}
			li[bak++] = t;
			pre += t.tv;
			if (!A.v) {
				if (!hav) {
					--bak;
					que.front() = t;
				} else
					que.pop();
				break;
			}
		}
		que.pop();
	}
	typedef std::pair<int, int> pi;
	static pi die[MAXN];
	for (int i = 0; i < bak; ++i) {
		die[i].second = i;
		die[i].first = divup(li[i].v, li[i].tv);
	}
	std::sort(die, die + bak);
	int pt = 0, cur = 0;
	while (pre) {
		int turn = A.v / pre;
		if (cur < bak)
			turn = std::min(turn, die[cur].first - pt);
		if (!turn) {
		   	if (cur < bak && die[cur].first - pt == 1) {
				int R = cur;
				int tp = pre;
				while (R < bak && die[R].first == die[cur].first) {
					int i = die[R].second;
					tp -= li[i].tv;
					tp += modup(li[i].v, li[i].tv);
					++R;
				}
				if (tp <= A.v) turn = 1;
			}
		}
		if (!turn) break;
		A.v -= (turn - 1) * pre;
		pt += turn;
		while (cur < bak && die[cur].first == pt) {
			int i = die[cur].second;
			A.v -= modup(li[i].v, li[i].tv);
			ge[i] += li[i].v;
			pre -= li[i].tv;
			++cur;
			li[i].v = 0;
		}
		A.v -= pre;
	}
	for (int i = 0; i < bak; ++i) if (li[i].v) {
		ge[i] += li[i].tv * pt;
		li[i].v -= li[i].tv * pt;
		li[i].f5cv();
	}
	for (int i = 0; i < bak; ++i) if (li[i].v) {
		int d = std::min(A.v, li[i].cv);
		bool hav = false;
		li[i].v -= d;
		if (!(li[i].cv -= d)) {
			li[i].f5cv();
			hav = true;
		}
		ge[i] += d;
		A.v -= d;
		if (!A.v) {
			int sp = i;
			if (hav) ++sp;
			for (int j = 0; j < bak; ++j)
				if (li[(sp + j) % bak].v)
					que.push(li[(sp + j) % bak]);
			break;
		}
	}
	for (int i = 0; i <= bak; ++i)
		if (ge[i]) {
			trade t;
			t.buyid = A.id;
			t.sellid = li[i].id;
			if (A.typ == SELL)
				std::swap(t.buyid, t.sellid);
			t.p = li[i].p;
			t.v = ge[i];
			tmp.push_back(t);
		}
	memset(ge, 0, (bak + 1) << 2);
}
int main() {
// #define FILENAME "iceberg"
// #ifdef ONLINE_JUDGE
// 	freopen(FILENAME ".in", "r", stdin);
// 	freopen(FILENAME ".out", "w", stdout);
// #endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		order t;
		std::cin >> t.id >> t.typ >> t.p >> t.v >> t.tv;
		const int b = (t.typ - 1) ^ 1;
		while (true) {
			decltype(M[b].begin()) it;
			if (t.typ == SELL) {
				it = M[b].end();
				if (it == M[b].begin()) break;
				--it;
				if (it->first < t.p) break;
			} else {
				it = M[b].begin();
				if (it == M[b].end()) break;
				if (it->first > t.p) break;
			}
			calc(t, it->second);
			if (it->second.empty())
				M[b].erase(it);
			if (!t.v) break;
		}
		if (t.v) {
			t.f5cv();
			M[b ^ 1][t.p].push(t);
		}
		std::sort(tmp.begin(), tmp.end());
		ansl.insert(ansl.end(), tmp.begin(), tmp.end());
		tmp.clear();
	}
	// std::sort(ansl.begin(), ansl.end());
	for (auto t : ansl)
		std::cout << t.buyid << ' ' << t.sellid << ' ' << t.p << ' ' << t.v << '\n';
	std::cout << '\n';
	for (auto t : M[1])
		M[0][t.first] = t.second;
	for (auto & a : M[0])
		while (!a.second.empty()) {
			order t = a.second.front();
			a.second.pop();
			std::cout << t.id << ' ' << t.typ << ' ' << t.p << ' '
					  << t.v << ' ' << t.tv << ' ' << t.cv << '\n';
		}
	return 0;
}

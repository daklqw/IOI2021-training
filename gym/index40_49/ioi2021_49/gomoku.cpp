#include <bits/stdc++.h>
#include <curses.h>
#include <unistd.h>

std::mt19937 rd(time(0));
typedef long long LL;
typedef std::pair<int, int> pi;
const int N = 19;
typedef std::vector<int> VI;
struct _ {
	int a[N][N];
/*
	LL calc(int x, int y, int dx, int dy) {
		int hav = 0, cnt = 0;
		for (int i = 0; i < 5; ++i) {
			cnt += a[x][y] > 0;
			hav |= 1 << a[x][y];
			x += dx, y += dy;
		}
		if (((hav & 2) && (hav & 4)) || !cnt)
			return 0;
		LL res = 1;
		cnt = cnt * 2 - 1;
		while (cnt --> 0) res *= 50;
		if (hav & 4) res = -res;
		return res;
	}
	LL calc() {
		LL res = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				if (i + 4 < N)
					res += calc(i, j, 1, 0);
				if (j + 4 < N)
					res += calc(i, j, 0, 1);
				if (i + 4 < N && j + 4 < N)
					res += calc(i, j, 1, 1);
			}
		return res;
	}
*/
} ;

class BadStrategy {
	const LL BASE = 50;
	LL score1[6], score2[6];

public:
	BadStrategy() {
		LL tmp = 1;
		for (int i = 1; i <= 5; ++i) {
			tmp *= BASE;
			score1[i] = tmp;
			tmp *= BASE;
			score2[i] = tmp;
		}
	}

	int getMove(int size, VI board) {
		assert(board.size() == size * size);
		int best;
		LL bestScore = std::numeric_limits<LL>::min();
		LL curScore = 0;
		for (int us = 0; us < board.size(); ++us) if (board[us] == 0) {
			board[us] = 1;
			LL worstScore = curScore + scoreDelta(us, size, board);
			worstScore += rd() % (50 * 50);
			board[us] = 0;
			if (worstScore > bestScore) {
				bestScore = worstScore;
				best = us;
			}
		}
		return best;
	}

private:
	LL scoreDelta(int pos, int size, VI board) {
		int r = pos / size;
		int c = pos % size;
		LL res = 0;
		for (int dr = 0; dr <= 1; ++dr) {
			for (int dc = (dr == 0 ? 1 : -1); dc <= 1; ++dc) {
				VI seq = VI(9, 3);
				// Arrays.fill(seq, 3);
				for (int delta = -4; delta <= 4; ++delta) {
					int pr = r + delta * dr;
					int pc = c + delta * dc;
					if (pr >= 0 && pr < size && pc >= 0 && pc < size) {
						seq[4 + delta] = board[pr * size + pc];
					}
				}
				res += scoreRowDelta(seq);
			}
		}
		return res;
	}

	LL scoreRowDelta(VI seq) {
		VI cntAfter(4, 0);
		VI cntBefore(4, 0);
		LL res = 0;
		for (int i = 0; i < 9; ++i) {
			if (seq[i] > 0) {
				++cntAfter[seq[i]];
				if (i != 4)
					++cntBefore[seq[i]];
			}
			if (i >= 5 && seq[i - 5] > 0) {
				--cntAfter[seq[i - 5]];
				--cntBefore[seq[i - 5]];
			}
			if (i >= 4) {
				res += scoreCnt(cntAfter);
				res -= scoreCnt(cntBefore);
			}
		}
		return res;
	}

	LL scoreCnt(VI cnt) {
		if ((cnt[1] == 0 ^ cnt[2] == 0) && cnt[3] == 0) {
			return score1[cnt[1]] - score2[cnt[2]];
		} else {
			return 0;
		}
	}
} solver;
pi play(_ now) {
	VI tmp(N * N, 0);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			tmp[i * N + j] = now.a[i][j];
	int t = solver.getMove(N, tmp);
	return pi(t / N, t % N);
}
/*
std::vector<pi> play(_ now) {
	LL v = -1e18;
	std::vector<pi> li;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) 
			if (now.a[i][j] == 0) {
				_ nxt = now;
				nxt.a[i][j] = 1;
				LL tv = nxt.calc();
				if (tv > v) {
					v = tv;
					li.clear();
				}
				if (v == tv)
					li.emplace_back(i, j);
			}
	return li;
}
*/

const int self = 1, opponent = 2;
int curx = 1, cury = 1;
void display(_ now) {
	clear();
	for (int i = 0; i <= N + 1; ++i)
		mvaddch(0, i, '%');
	for (int i = 1; i <= N; ++i) {
		mvaddch(i, 0, '%');
		for (int j = 1; j <= N; ++j) {
			char ch;
			if (i == curx && j == cury) {
				ch = '+';
			} else {
				switch (now.a[i - 1][j - 1]) {
					case self:
						ch = '@';
						break;
					case opponent:
						ch = '#';
						break;
					case 3:
						ch = '!';
						break;
					default:
						ch = ' ';
						break;
				}
			}
			mvaddch(i, j, ch);
		}
		mvaddch(i, N + 1, '%');
	}
	for (int i = 0; i <= N + 1; ++i)
		mvaddch(N + 1, i, '%');
	mvprintw(N + 2, 1, "(%d, %d)", curx, cury);
	refresh();
}
pi pl(_ now) {
	while (true) {
		display(now);
		char s = getch();
		bool put = false;
		switch (s) {
			case 'h':
				cury = std::max(cury - 1, 1);
				break;
			case 'j':
				curx = std::min(curx + 1, 19);
				break;
			case 'k':
				curx = std::max(curx - 1, 1);
				break;
			case 'l':
				cury = std::min(cury + 1, 19);
				break;
			case 'p':
				put = true;
				break;
			case 'q':
				return pi(-1, -1);
				break;
		}
		if (put && !now.a[curx - 1][cury - 1]) {
			return pi(curx - 1, cury - 1);
		}
	}
}
void solve(_ now, bool init = true) {
	while (true) {
		int x, y;
		std::tie(x, y) = pl(now);
		if (x == -1 && y == -1) {
			if (init) continue;
			return ;
		}
		now.a[x][y] = opponent;
		pi res = play(now);
		now.a[res.first][res.second] = self;
		solve(now, false);
		now.a[x][y] = 0;
		now.a[res.first][res.second] = 0;
	}
}
int main(){
	initscr();
	_ init;
	memset(&init, 0, sizeof init);
	init.a[N / 2][N / 2] = self;
	solve(init);
	endwin();
	return 0;
}

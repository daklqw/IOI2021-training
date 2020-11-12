#include <bits/stdc++.h>

const int MAXN = 110;
int n;
struct _ {
	int a[MAXN * 4];
	_() { memset(a, -1, sizeof a); }
	int & operator [] (int x) {
		return a[x + MAXN];
	}
} ;
_ A;
typedef std::pair<int, int> pi;
void swap(int x, int y) {
	std::cout << (y + 1) << " to " << (x + 1) << '\n';
	std::swap(A[x], A[y]);
	std::swap(A[x + 1], A[y + 1]);
}
std::map<pi, int> deg;
bool judge(_ A, _ B) {
	deg.clear();
	for (int i = -2; i + 1 < n * 2; ++i)
		if (A[i] != B[i]) {
			if (A[i + 1] == B[i + 1])
				return false;
			++deg[pi(A[i], A[i + 1])];
			--deg[pi(B[i], B[i + 1])];
			++i;
		}
	for (auto t : deg)
		if (t.second != 0)
			return false;
	return true;
}
void trans(_ B) {
	std::set<int> pos;
	int tar = -2;
	int u = -2;
	for (int i = -2; i + 1 < n * 2; ++i)
		if (A[i] != B[i]) {
			if (A[i] == -1) u = i;
			if (B[i] == -1) tar = i;
			else pos.insert(i);
			++i;
		}
	while (!pos.empty()) {
		pos.erase(u);
		for (int i : pos)
			if (A[i] == B[u] && A[i + 1] == B[u + 1]) {
				swap(u, i);
				u = i;
				break;
			}
	}
	swap(u, tar);
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for (int i = 0; i < n * 2; ++i)
		A[i] = i & 1;
	if (n == 3) {
		swap(-2, 1);
		swap(1, 4);
		swap(-4, 2);
		return 0;
	}
	int mid = -2 + n;
	_ B, C;
	B = A;
	const int lhs[] = {1, 0, 0, 1, 0, 0, 1, 1};
	const int rhs[] = {1, 1, 0, 0, 0, 1, 1, 0};
	for (int i = -2; i < mid; ++i)
		B[i] = lhs[(i + 2) % 8];
	for (int i = n * 2 - 1; i > mid; --i)
		B[i] = rhs[(n * 2 - 1 - i) % 8];
	for (int i = -2; i < mid; ++i)
		C[i] = 1, C[i + n] = 0;
	if (n % 4 == 1)
		B[mid - 1] = 1, B[mid] = B[mid + 1] = 0;
	if (n % 4 == 2) {
		if (n % 8 == 6)
			B[mid - 1] = B[mid - 2] = 1;
		else {
			for (int i = mid - 5, t = 0; i < mid + 4; ++i, ++t)
				B[i] = ("100110110"[t]) - '0';
		}
	}
	if (n % 4 == 3) {
		if (n == 7) {
			for (int i = mid - 2, t = 0; i < mid + 5; ++i, ++t)
				B[i] = ("1100011"[t]) - '0';
		} else {
			for (int i = mid - 5, t = 0; i < mid + 1; ++i, ++t)
				B[i] = ("001110"[t]) - '0';
		}
	}
	bool hav = false;
	for (int i = 0; i < n * 2 - 2; ++i) {
		_ t = B;
		t[i] = t[i + 1] = -1;
		if (judge(A, t) && judge(t, C)) {
			hav = true;
			B = t;
			break;
		}
	}
	trans(B);
	trans(C);
	return 0;
}

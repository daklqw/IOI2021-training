#include <bits/stdc++.h>

typedef long long LL;

const int MAXN = 1e5 + 10;
int n; LL K;
int A[MAXN], B[MAXN];
LL pre[MAXN];
int L[MAXN], R[MAXN];
void get(int * A, int * R, int v) {
	static int que[MAXN];
	int head = 0, tail = 0;
	for (int i = 1; i <= n; ++i) {
		while (head < tail && A[que[tail - 1]] < A[i]) --tail;
		que[tail++] = i;
		while (head + 1 < tail && A[que[head + 1]] >= v - i) ++head;
		if (head < tail && A[que[head]] >= v - i)
			R[i] = que[head];
		else R[i] = 0;
	}
}
LL calc(int l, int r) {
	return (LL) (l + r) * (r - l + 1) / 2;
}
LL calc(int up) {
	get(A, L, up);
	get(B, R, up);
	std::reverse(R + 1, R + 1 + n);
	for (int i = 1; i <= n; ++i)
		R[i] = n - R[i] + 1;
	LL res = 2e18;
	for (int i = 2; i < n; ++i)
		if (L[i] != 0 && R[i] != n + 1) {
			LL v = 0;
			v += calc(up - (i - L[i]) + 1, up);
			v += calc(up - (R[i] - i) + 1, up - 1);
			v -= pre[R[i] - 1] - pre[L[i]];
			res = std::min(res, v);
		}
	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> K;
	for (int i = 1; i <= n; ++i) {
		std::cin >> A[i];
		pre[i] = pre[i - 1] + A[i];
		B[n - i + 1] = A[i];
	}
	int l = *std::max_element(A + 1, A + 1 + n);
	int r = 2.5e5;
	for (int i = 1; i <= n; ++i) {
		A[i] -= i;
		B[i] -= i;
	}
	while (l + 1 < r) {
		LL mid = l + r >> 1;
		(calc(mid) <= K ? l : r) = mid;
	}
	std::cout << l << std::endl;
	return 0;
}

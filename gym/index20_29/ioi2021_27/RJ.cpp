#include <bits/stdc++.h>

int ansc;
int n;
const int A = 5;
char cur = 'a';
int main() {
#define FILENAME "java2016"
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	char min, max;
	char lst = '?', now;
	for (int i = 0; i < A; ++i) {
		now = cur++;
		printf("%c = %c min %c min %c\n", now, lst, lst, lst);
		lst = now;
	}
	min = lst;
	lst = '?';
	for (int i = 0; i < A; ++i) {
		now = cur++;
		printf("%c = %c max %c max %c\n", now, lst, lst, lst);
		lst = now;
	}
	max = lst;
	for (int i = 0; i < A; ++i) {
		now = cur++;
		if (i == 0) {
			printf("%c = %c - %c\n", now, min, max);
		} else {
			printf("%c = %c min %c min %c\n", now, lst, lst, lst);
		}
		lst = now;
	}
	char at[8];
	at[0] = lst;
	for (int i = 1; i < 8; ++i) {
		now = cur++;
		printf("%c = %c + %c\n", now, lst, lst);
		lst = now;
		if (i % 2 == 0) {
			now = cur++;
			printf("%c = %c min %c min %c\n", now, lst, lst, lst);
			lst = now;
		}
		at[i] = lst;
	}
	if (!n) {
		printf("%c / %c", min, max);
	} else {
		bool lst = false;
		for (int i = 0; i != 8; ++i) if (n >> i & 1) {
			if (lst) printf(" + ");
			lst = true;
			printf("%c", at[i]);
		}
	}
	putchar(10);
	return 0;
}

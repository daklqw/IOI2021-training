#include <bits/stdc++.h>

void output(int out) {
	if (out < 26) putchar(out + 'a');
	else if (out < 52) putchar(out - 26 + 'A');
	else putchar(out - 52 + '0');
}
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	int n = 60;
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; ++j) {
			int t;
			std::cin >> t >> t >> t;
			output(t);
			while (t --> 0) {
				int p;
				for (int j = 0; j < 3; ++j) {
					std::cin >> p;
					output(p);
				}
			}
		}
	return 0;
}

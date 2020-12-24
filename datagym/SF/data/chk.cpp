#include <bits/stdc++.h>
#include "testlib.h"

const int PRIMET = 128;
const int PERPRI = 128;
std::mt19937 rd(time(0));
bool ispri(int x) {
	for (int i = 2; i * i <= x; ++i)
		if (x % i == 0)
			return false;
	return x >= 2;
}
typedef long long LL;
int mod;
void reduce(int & x) {
	x += x >> 31 & mod;
}
int mul(int a, int b) {
	return (LL) a * b % mod;
}
int pow(int a, int b, int r = 1) {
	for (; b; b >>= 1, a = mul(a, a))
		if (b & 1)
			r = mul(r, a);
	return r;
}
typedef std::string str;
str removeSpace(str x) {
	const int L = x.size();
	str y;
	for (int i = 0; i < L; ++i)
		if (!isspace(x[i]))
			y += x[i];
	return y;
}
str getName(int x) {
	str r = "";
	if (x == -1)
		r = "EOF";
	else
		r += (char) x;
	return r;
}
class Parser {
	str buf;
	InStream * inf;
	int pos, N, zeroFlag;
	int current() {
		return pos < (int) buf.size() ? buf[pos] : -1;
	}
	void next() {
		++pos;
	}
	int parse() {
		int r = parseExpression();
		ensuref(pos >= (int) buf.size(),
					 "At %d: Extra characters after %d: '%s'",
					 pos,
					 pos,
					 getName(current()).c_str());
		assert(pos == (int) buf.size());
		return r;
	}
	int parseExpression() {
		int r = parseProduct();
		while (current() == '+' || current() == '-') {
			bool isPlus = current() == '+';
			next();
			int v = parseProduct();
			if (isPlus)
				reduce(r += v - mod);
			else
				reduce(r -= v);
		}
		return r;
	}
	int parseProduct() {
		int r = parseValue();
		while (current() == '*') {
			next();
			r = mul(r, parseValue());
		}
		return r;
	}
	int parseValue() {
		if (current() == 'n') {
			next();
			return N;
		} else if (current() == '-') {
			next();
			int r = parseValue();
			reduce(r = -r);
			return r;
		} else if (isdigit(current())) {
			int p = parseInteger();
			int q = 1;
			if (current() == '/') {
				next();
				q = parseInteger();
				if (zeroFlag) {
					inf->quitf(_fail,
							   "At %d: Division by zero",
							   pos);
				}
			}
			return pow(q, mod - 2, p);
		} else if (current() == '(') {
			next();
			int r = parseExpression();
			ensuref(current() == ')',
						 "%d: Unexpected %s instead of )",
						 pos,
						 getName(current()).c_str());
			next();
			return r;
		} else {
			inf->quitf(_fail,
					   "%d: Unexpected %s",
					   pos,
					   getName(current()).c_str());
		}
	}
	int parseInteger() {
		ensuref(isdigit(current()),
					 "%d: Unexpected %s instead of digit",
					 pos,
					 getName(current()).c_str());
		zeroFlag = true;
		int r = 0;
		do {
			zeroFlag &= current() == '0';
			r = ((LL) r * 10 + (current() - '0')) % mod;
			next();
		} while (isdigit(current()));
		return r;
	}
public:
	const char * toString() {
		return buf.c_str();
	}
	void parse(InStream * _inf) {
		inf = _inf;
		buf = removeSpace(inf->readLine());
		ensuref(buf.size() <= 100, "Too long");
	}
	int operator () (int v) {
		pos = 0;
		N = v;
		return parse();
	}
} lhs, rhs;
int main(int argc, char ** argv) {
	registerTestlibCmd(argc, argv);
	lhs.parse(&ouf);
	rhs.parse(&ans);
	for (int P = 0; P < PRIMET; ++P) {
		mod = rd() % 400000000 + 600000000;
		while (!ispri(mod)) ++mod;
		for (int T = 0; T < PERPRI; ++T) {
			int v = rd() % mod;
			int lv = lhs(v), rv = rhs(v);
			if (lv != rv) {
				quitf(_wa, "Excepted %s but %s found",
					  rhs.toString(),
					  lhs.toString());
			}
		}
	}
	quitf(_ok, "OK! %s", lhs.toString());
	return 0;
}

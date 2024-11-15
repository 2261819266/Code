#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P7075

using namespace std;

namespace Problem {
template <typename t>
ostream &operator<<(ostream &out, const vector<t> &A) {
    for (const t &i : A) out << i << spc;
    return out;
}

template <typename t>
void print(const t &x, int l = 0, int r = 0) {
    cout << x << spc;
}

template <typename t>
void print(const vector<t> &A, int l = 0, int r = 0) {
    for (int i = l; i < r; i++) {
    print(A[i], l, r);
    }
    cout << endl;
}

template <typename t>
istream &operator>>(istream &in, vector<t> &A) {
    for (t &i : A) in >> i;
    return in;
}

template<typename t>
void scan(t &x, int l = 0, int r = 0) {
    cin >> x;
}

template<typename t>
void scan(vector<t> &A, int l = 0, int r = 0) {
    for (int i = l; i < r; i++) {
    scan(A[i], l, r);
    }
}

template<typename it>
void assign(vector<int> &a, it p) {
    a.assign(*p, 0);
}

template<typename T, typename it>
void assign(vector<T> &a, it p) {
    T t;
    assign(t, p + 1);
    a.assign(*p, t);
}

template<typename T>
void assign(vector<T> &a, const vector<int> &p) {
    assign(a, p.begin());
}

const int zero = 1721424, y4 = 365 * 4 + 1, y0 = 4713, rrr = 578098 + zero, y400 = y4 * 100 - 3, y99 = 25 * y4 - 366, d1601 = zero + y4 * 400 - 10;
const int md[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int smd[13];

using PII = pair<int, int>;

PII getDay(int x, int f = 0) {
    PII ans = {0, 0};
    for (int i = 1; i <= 12; i++) {
        if (x < smd[i] + f * (i > 1)) return {i, x - smd[i - 1] - f * (i > 2) + 1};
    }
    return {-1, -1};
}

struct Day {
    int y, m, d;
};

ostream &operator<<(ostream &out, const Day &d) {
    return out << d.d << spc << d.m << spc << abs(d.y) << (d.y < 0 ? " BC" : "") << endl;
}

Day RRR(int x) {
	int y = x / y4 * 4 + 1;
	x -= y / 4 * y4;
	if (x < y4 - 1) {
		y += x / 365;
		x %= 365;
	} else {
		return {y + 3, 12, 31};
	}

	PII p = getDay(x, y % 4 == 0);
	return {y, p.first, p.second};
}

Day f(int x) {
	if (x < zero) {
        int y = x / y4 * 4;
        x -= y4 * y / 4;
        y = y0 - y;
        if (x >= 366) {
            y--, x -= 366;
            y -= x / 365;
            x %= 365;
        }
        PII p = getDay(x, y % 4 == 1);
        return {-y, p.first, p.second};
    }
    if (x < rrr) {
		return RRR(x - zero);
	} 
    if (x < d1601) {
        return RRR(x - 10);
    } else {
        x -= d1601;
        if (!x) return {1601, 1, 1};
        int y = x / y400 * 400;
        x -= y * y400 / 400;
        while (x >= y99 + 365 && y % 400 != 300) x -= y99 + 365, y += 100;
        if (y % 400 != 300 && x > y99) {
            x -= y99;
            PII p = getDay(x);
            return {y + 1700, p.first, p.second};
        }
        Day p = RRR(x);
        p.y += 1600 + y;
        return p;
    }
}

void init() {
    for (int i = 1; i <= 12; i++) smd[i] = smd[i - 1] + md[i];
}
 
void main() {
    int n;
    cin >> n;
    init();
    while (n--) {
        int x;
        cin >> x;
        cout << f(x);
    }
    // cout << smd[9];
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}
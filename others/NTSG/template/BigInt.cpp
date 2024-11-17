#ifndef __BigInt__
#define __BigInt__
#include <string>
#include <cmath>
#include <vector>
#include <ostream>
#include <algorithm>

#define int long long

// using namespace std;

class BigInt {
  private:

    using string = std::string;
    using istream = std::istream;
    using ostream = std::ostream;

    void update_zero() { while (!a.back()) a.pop_back(); }

  public:
    template<typename T> BigInt(const T &x) { *this = x; }
    BigInt(const string &x) { *this = x; }
    BigInt(const char *x) { *this = x; }
    BigInt(void) : sig(false), a() {}

    template<typename T>
    BigInt &operator=(const T &X) {
        T x = X;
        if ((sig = x < 0)) x = -x;
        do {
            a.push_back(x % MOD);
        } while (x /= MOD);
        return *this;
    }
    BigInt &operator=(const string &_s) {
        string s;
        if (_s.front() == '-') sig = 1, s = string(_s, 1);
        a.clear();
        int len = _s.size(), x = 0;
        int k;
        for (k = 0; k < len && _s[k] == '0'; k++);
        s = string(_s, k);
        len = s.size();
        if (!len) return *this;
        int y = len % BASE;
        for (int i = x = 0; i < y; i++) {
            (x *= 10) += s[i] - '0';
            // if (i == y - 1) a.push_back(x);
        }
        for (int i = y, j = BASE; ; i++, j++) {
            if (j == BASE) {
                j = 0;
                a.push_back(x);
                x = 0;
            }
            if (i == len) break;
            (x *= 10) += s[i] - '0';
        }
        std::reverse(a.begin(), a.end());
        return *this;
    }
    BigInt &operator=(const char *s) { return *this = s; }

    friend ostream &operator<<(ostream &out, const BigInt &x) { string s = x; return out << s; }
    friend istream &operator>>(istream &in, BigInt &x) {
        string s;
        in >> s;
        x = s;
        return in;
    }

    void clear() { sig = 0, a.clear(); }

    template<typename T>
    operator T() const {
        T x = 0;
        for (const T &i : a) (x *= MOD) += i;
        return x * (sig ? -1 : 1);
    }
    operator string() const {
        if (a.empty()) return "0";
        string S;
        if (sig) S = "-";
        int len = a.size();
        for(int i = len - 1; i >= 0; i--) {
            string s = std::to_string(a[i]);
            for (int j = s.size(); j < BASE && i < len - 1; j++) S += '0';
            S += s;
        }
        return S;
    }



  private:
    static const int BASE = 8;
    static const int MOD = 1e8;
    std::vector<int> a;
    bool sig;
};

#undef int
#endif

#include <iostream>
signed main() {
    using namespace std;
    BigInt x;
    cin >> x;
    cout << x;
}
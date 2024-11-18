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
    // using std::vector;

    BigInt update_zero() { while (!a.back()) a.pop_back(); return *this; }

    BigInt(std::vector<int> A, int SIG) : a(A), sig(SIG) {}

    int size() const { return a.size(); }

    int operator[](int x) const { return a[x]; }
    int &operator[](int x) { return a[x]; }
    bool empty() const { return a.empty(); }

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
        string s = _s;
        if (_s.front() == '-') sig = 1, s = string(_s, 1);
        a.clear();
        int len = _s.size(), x = 0;
        int k;
        for (k = 0; k < len && s[k] == '0'; k++);
        s = string(s, k);
        len = s.size();
        if (!len) return clear();
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

    BigInt &clear() { sig = 0, a.clear(); return *this; }


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

    operator bool() const { return !a.empty(); }
    bool operator!() const { return a.empty(); }

    bool operator<(const BigInt &b) const {
        bool ans;
        if (a.empty() && b.empty()) return false;
        if (a.empty()) return !b.sig;
        if (b.empty()) return sig;
        if (sig != b.sig && (!!*this || !!b)) return b.sig < sig;
        else if (a.size() != b.size()) ans = a.size() < b.size();
        else {
            int n = a.size();
            for (int i = n - 1; i >= 0; i--) {
                if (a[i] != b.a[i]) {
                    ans = a[i] < b.a[i];
                }
            }
        }
        return ans ^ sig;
    }
    bool operator==(const BigInt &b) const { return sig == b.sig && a == b.a; }
    bool operator!=(const BigInt &b) const { return !(*this == b); }
    bool operator<=(const BigInt &b) const { return !(b < *this); }
    bool operator>=(const BigInt &b) const { return !(*this < b); }
    bool operator>(const BigInt &b) const { return b < *this; }

    BigInt operator-() const { return {a, !sig}; }

    BigInt operator+(const BigInt &b) const {
        if (!*this && !b) return 0;
        if (sig != b.sig) return *this - -b;
        if (*this < b) return b + *this;
        BigInt ans(a, sig);
        int n = a.size(), m = b.size();
        ans.a.push_back(0);
        for (int i = 0, d = 0; i <= n; i++) {
            ans[i] += (i < m ? b[i] : 0) + d;
            d = ans[i] / MOD;
            ans[i] %= MOD;
        }
        return ans.update_zero();
    }

    BigInt operator-(const BigInt &b) const {

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
    BigInt a, b;
    cin >> a >> b;
    cout << (a + b);
}
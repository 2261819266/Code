#ifndef __BigInt__
#define __BigInt__
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#define int long long

class BigInt {
  private:

    using string = std::string;
    using istream = std::istream;
    using ostream = std::ostream;
    using vector = std::vector<int>;

    int operator[](int x) const { return a[x]; }
    int &operator[](int x) { return a[x]; }
    bool empty() const { return a.empty(); }
    size_t size() const { return a.size(); }
    BigInt update_zero() { while (!a.back()) a.pop_back(); return *this; }
    BigInt(vector A, int SIG) : a(A), sig(SIG) {}

    template<typename T> string to_string(const T &x) const { return std::to_string(x); }
    int stoi(const string &s) { return stoi(s, 0, s.size()); }
    int stoi(const string &s, int l, int r) { return std::stoi(string(s, l, r - l)); }

    template<typename T> BigInt &operator<<=(T x) { return *this = *this << x; }
    template<typename T> BigInt operator<<(T x) const {
        if (!*this) return 0;
        BigInt ans(vector(x, 0), sig);
        for (const int &i : a) ans.a.push_back(i);
        return ans.update_zero();
    }

    template<typename T> BigInt &operator>>=(T x) { return *this = *this >> x; }
    template<typename T> BigInt operator>>(T x) const { return x < size() ? (BigInt){vector(a.begin() + x, a.end()), sig}.update_zero() : (BigInt)0; }

  public:
    BigInt(void) : a(), sig(false) {}
    template<typename T> BigInt(const T &x) { *this = x; }
    BigInt(const string &x) { *this = x; }
    BigInt(const char *x) { *this = x; }

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
        int len = _s.size();
        int k;
        for (k = 0; k < len && s[k] == '0'; k++);
        s = string(s, k);
        len = s.size();
        if (!len) return clear();
        int y = len % BASE;
        if (!y) y = BASE;
        a.push_back(stoi(s, 0, y));
        for (int x = y; x < len; x += BASE) a.push_back(stoi(s, x, x + BASE));
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
        return x * (1 - 2 * sig);
    }
    operator string() const {
        if (a.empty()) return "0";
        string S;
        if (sig) S = "-";
        int len = a.size();
        for(int i = len - 1; i >= 0; i--) {
            string s = to_string(a[i]);
            for (int j = s.size(); j < BASE && i < len - 1; j++) S += '0';
            S += s;
        }
        return S;
    }
    operator bool() const { return !a.empty(); }
    bool operator!() const { return a.empty(); }

    bool operator<(const BigInt &b) const {
        if (*this == b) return false;
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
                    break;
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

    BigInt operator-() const { return {a, !*this ? 0 : !sig}; }

    BigInt abs() const { return sig ? -*this : *this; }

    template<typename T> BigInt operator+(const T &b) const { return *this + (BigInt)b; }
    template<typename T> BigInt &operator+=(const T &b) { return *this = *this + b; }
    BigInt operator+(const BigInt &b) const {
        if (!b) return *this;
        if (!*this) return b;
        if (sig != b.sig) return *this - (-b);
        if (*this < b) return b + *this;
        BigInt ans(*this);
        int n = a.size(), m = b.size();
        ans.a.push_back(0);
        for (int i = 0, d = 0; i <= n; i++) ans [i] -= MOD * (d = (ans[i] += (i < m ? b[i] : 0) + d) / MOD);
        return ans.update_zero();
    }

    template<typename T> BigInt operator-(const T &b) const { return *this - (BigInt)b; }
    template<typename T> BigInt &operator-=(const T &b) { return *this = *this - b; }
    BigInt operator-(const BigInt &b) const {
        if (!b) return *this;
        if (!*this) return -b;
        if (sig != b.sig) return *this + (-b);
        if (abs() < b.abs()) return -(b - *this);
        BigInt ans = *this;
        int n = a.size(), m = b.size();
        for (int i = 0, d = 1; i < n; i++) ans[i] -= MOD * (d = (ans[i] += MOD + d - 1 - (i < m ? b[i] : 0)) / MOD);
        return ans.update_zero();
    }

    template<typename T> BigInt operator*(const T &b) const { return *this * (BigInt)b; }
    template<typename T> BigInt &operator*=(const T &b) { return *this = *this * b; }
    BigInt operator*(const signed &b) const {
        if (!*this || !b) return 0;
        if (b < 0) return -(*this * (-b)); 
        int n = size();
        BigInt ans = *this;
        ans.a.resize(n + 2);
        for (int i = 0, d = 0; i < n || d; i++) 
            ans[i] -= (d = ((ans[i] *= b) += d) / MOD) * MOD; 
        return ans.update_zero();
    }
    BigInt operator*(const BigInt &b) const {
        if (!*this || !b) return 0;
        BigInt ans = 0;
        int n = b.size();
        for (int i = n - 1; i >= 0; i--) (ans <<= 1) += *this * (signed)b[i];
        ans.sig = sig ^ b.sig;
        return ans.update_zero();
    }

    BigInt operator/(const signed &b) const {
        if (!b) { std::cerr << "MATH ERROR!\n"; exit(-1); }
        if (!*this) return 0;
        if (b < 0) return -*this / (-b);
        BigInt ans = 0;
        int n = size();
        for (int i = n - 1, d = 0; i >= 0; i--) (ans <<= 1) += (a[i] + d * MOD) / b, d = (a[i] + d * MOD) % b;
        ans.sig = sig;
        return ans.update_zero();
	}

  private:
    static const int BASE = 8;
    static const int MOD = 1e8;
    vector a;
    bool sig;

};

template<> struct std::hash<BigInt> {
    int operator()(const BigInt &x) const {
        string s = x;
        return hash<string>{} (s);
    }
};

#undef int
#endif

#include <iostream>
signed main() {
    using namespace std;
    BigInt a, b;
    cin >> a;
    // cin >> a >> b;
    int x;
    cin >> x;
    cout << a / x;
}
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

    int operator[](int x) const { return data[x]; }
    int &operator[](int x) { return data[x]; }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
    BigInt update_zero() { while (!data.empty() && !data.back()) data.pop_back(); return *this; }
    BigInt(vector A, int SIG) : data(A), sig(SIG) {}

    template<typename T> string to_string(const T &x) const { return std::to_string(x); }
    int stoi(const string &s) { return stoi(s, 0, s.size()); }
    int stoi(const string &s, int l, int r) { return std::stoi(string(s, l, r - l)); }

    template<typename T> BigInt &operator<<=(T x) { return *this = *this << x; }
    template<typename T> BigInt operator<<(T x) const {
        if (!*this) return 0;
        BigInt ans(vector(x, 0), sig);
        for (const int &i : data) ans.data.push_back(i);
        return ans.update_zero();
    }

    template<typename T> BigInt &operator>>=(T x) { return *this = *this >> x; }
    template<typename T> BigInt operator>>(T x) const { return (size_t)x < size() ? (BigInt){vector(data.begin() + x, data.end()), sig}.update_zero() : (BigInt)0; }

    BigInt solve(const BigInt &b) {
        int x;
        while ((x = b.data.back() / (data.back() + 1))) {
            *this -= b * x;
        }
        while (*this >= b) *this -= b;
        return *this;
    }
  public:
    BigInt() = default;
    template<typename T> BigInt(const T &x) { *this = x; }
    BigInt(const string &x) { *this = x; }
    BigInt(const char *x) { *this = x; }

    template<typename T>
    BigInt &operator=(const T &X) {
        T x = X;
        if ((sig = x < 0)) x = -x;
        do {
            data.push_back(x % MOD);
        } while (x /= MOD);
        return *this = this->update_zero();
    }
    BigInt &operator=(const string &_s) {
        string s = _s;
        if (_s.front() == '-') sig = 1, s = string(_s, 1);
        data.clear();
        int len = _s.size();
        int k;
        for (k = 0; k < len && s[k] == '0'; k++);
        s = string(s, k);
        len = s.size();
        if (!len) return clear();
        int y = len % BASE;
        if (!y) y = BASE;
        data.push_back(stoi(s, 0, y));
        for (int x = y; x < len; x += BASE) data.push_back(stoi(s, x, x + BASE));
        std::reverse(data.begin(), data.end());
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

    BigInt &clear() { sig = 0, data.clear(); return *this; }

    template<typename T>
    operator T() const {
        T x = 0;
        for (const int &i : data) (x *= MOD) += i;
        return x * (1 - 2 * sig);
    }
    operator string() const {
        if (data.empty()) return "0";
        string S;
        if (sig) S = "-";
        int len = data.size();
        for(int i = len - 1; i >= 0; i--) {
            string s = to_string(data[i]);
            for (int j = s.size(); j < BASE && i < len - 1; j++) S += '0';
            S += s;
        }
        return S;
    }
    operator bool() const { return !data.empty(); }
    bool operator!() const { return data.empty(); }

    bool operator<(const BigInt &b) const {
        if (*this == b) return false;
        bool ans;
        if (data.empty() && b.empty()) return false;
        if (data.empty()) return !b.sig;
        if (b.empty()) return sig;
        if (sig != b.sig && (!!*this || !!b)) return b.sig < sig;
        else if (data.size() != b.size()) ans = data.size() < b.size();
        else {
            int n = data.size();
            for (int i = n - 1; i >= 0; i--) {
                if (data[i] != b.data[i]) {
                    ans = data[i] < b.data[i];
                    break;
                }
            }
        }
        return ans ^ sig;
    }
    bool operator==(const BigInt &b) const { return sig == b.sig && data == b.data; }
    bool operator!=(const BigInt &b) const { return !(*this == b); }
    bool operator<=(const BigInt &b) const { return !(b < *this); }
    bool operator>=(const BigInt &b) const { return !(*this < b); }
    bool operator>(const BigInt &b) const { return b < *this; }

    BigInt operator-() const { return {data, !*this ? 0 : !sig}; }

    BigInt abs() const { return sig ? -*this : *this; }

    template<typename T> BigInt operator+(const T &b) const { return *this + (BigInt)b; }
    template<typename T> BigInt &operator+=(const T &b) { return *this = *this + b; }
    BigInt operator+(const BigInt &b) const {
        if (!b) return *this;
        if (!*this) return b;
        if (sig != b.sig) return *this - (-b);
        if (*this < b) return b + *this;
        BigInt ans(*this);
        int n = data.size(), m = b.size();
        ans.data.push_back(0);
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
        int n = data.size(), m = b.size();
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
        ans.data.resize(n + 2);
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
    
    template<typename T> BigInt operator/(const T &b) const { return *this / (BigInt)b; }
    template<typename T> BigInt &operator/=(const T &b) { return *this = *this / b; }
    BigInt operator/(const signed &b) const {
        if (!b) { std::cerr << "MATH ERROR!\n"; exit(-1); }
        if (!*this) return 0;
        if (b < 0) return -*this / (-b);
        BigInt ans = 0;
        int n = size();
        for (int i = n - 1, d = 0; i >= 0; i--) (ans <<= 1) += (data[i] + d * MOD) / b, d = (data[i] + d * MOD) % b;
        ans.sig = sig;
        return ans.update_zero();
	}
    BigInt operator/(const BigInt &_b) const {
        if (!_b) { std::cerr << "MATH ERROR!\n"; exit(-1); }
        if (!*this) return 0;
        // if (b.size() <= 1) return *this / (signed)b;
        if (sig & _b.sig) return (-*this) / (-_b);
        if (sig ^ _b.sig) return -(abs() / _b.abs());
        if (*this < _b) return 0;
        BigInt ans, a = *this, b = _b;
        if (b.data.back() >= 10) {
            int t = 1, x = b.data.back();
            while (x < MOD) t *= 10, x *= 10;
            b *= t;
            a *= t;
        }
        int e = size() - b.size() + 1;
        BigInt c = b << e;
        ans.data.assign(e + 1, 0);
        int X = b.data.back();
        while (true) {
            while (a >= b && a.size() > c.size()) 
                a -= c * (MOD / 10), ans[e] += MOD / 10;
            if (a < b) break;
            int x = 0;
            while (a.size() == c.size() && (x = a.data.back() / (X + 1))) 
                a -= c * x, ans[e] += x;
            while (a >= c) 
                a -= c, ans[e]++;
            c >>= 1;
            e--;
        }
        return ans.update_zero();
    }

    template<typename T> BigInt operator%(const T &x) const { return *this - *this / x * x; }
    template<typename T> BigInt operator%=(const T &x) { return *this -= *this / x * x; }

  private:
    static const int BASE = 8;
    static const int MOD = 1e8;
    vector data;
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

// #include <iostream>
// signed main() {
//     using namespace std;
//     BigInt a, b;
//     cin >> a >> b;
//     // cout << a - BigInt(0) * b;
//     cout << a + b << endl << a - b << endl << a * b << endl << a / b << endl << a % b;
// }
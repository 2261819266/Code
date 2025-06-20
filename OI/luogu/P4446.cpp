#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P4446
#define fop fo(P4446)

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

using PII = pair<int, int>;

istream &operator>>(istream &in, PII &a) {
    return in >> a.first >> a.second;
}

ostream &operator<<(ostream &out, const PII &a) {
    return out << a.first << spc << a.second << spc;
}

template<typename T> vector<T> operator+(const vector<T> &A, const vector<T> &B) {
    int n = A.size(), m = B.size(), k = max(m, n);
    vector<T> C(k, 0);
    for (int i = 0; i < k; i++) {
        if (i < n) C[i] += A[i];
        if (i < m) C[i] += B[i];
    }
    return C;
}

template<typename T> vector<T> operator+=(vector<T> &A, const vector<T> &B) { return A = A + B; }

int tri(int x) { return x * x * x; }

int rec(int x) { return x * x * x * x; }

int fiv(int x) { return x * x * x * x * x;}

void main() {
    int n;
    cin >> n;
    vector<int> a, b, v(1e6 + 8, 1);
    for (int i = 2; i <= 1e3; i++) {
        if (!v[i]) continue;
        for (int j = 2; j * i <= 1e6; j++) {
            v[i * j] = false;
        }
    }
    for (int i = 2; i <= 1e6; i++) {
        if (v[i]) a.push_back(i), b.push_back(i * i * i);
    }
    // for (int i = a.size() - 1; i >= 0; i--) {
    //     if (a[i] * a[i] <= 1e9) {
    //         cout << a[i] << spc << rec(a[i]) << endl;
    //         break;
    //     }
    // }
    // cout << a.back() << spc << b.back() << endl;;
    while (n--) {
        int x;
        cin >> x;
        int ans = 1;
        int t = 1;
        for (size_t i = 0; b[i] <= x && i < a.size(); i++) {
            if (t) {
                int y = (int)pow(x, 1.0 / 3) - 1;
                while (tri(y + 1) <= x) y++;
                if (tri(y) == x) ans *= y, x /= tri(y);
                t = 0;
                // int z = (int)pow(x, 1.0 / 4) - 1;
                // while (rec(z + 1) <= x) z++;
                // if (rec(z) == x) ans *= z, x /= rec(z);

                // int w = (int)pow(x, 1.0 / 5) - 1;
                // while (fiv(w + 1) <= x) w++;
                // if (fiv(w) == x) ans *= w, x /= fiv(w);
            }
            while (x % b[i] == 0) ans *= a[i], x /= b[i], t++;
            while (x % a[i] == 0) x /= a[i], t++;
            // if (t) {
                int y = (int)pow(x, 1.0 / 3) - 1;
                while (tri(y + 1) <= x) y++;
                if (tri(y) == x) ans *= y, x /= tri(y);
                t = 0;
                // int z = (int)pow(x, 1.0 / 4) - 1;
                // while (rec(z + 1) <= x) z++;
                // if (rec(z) == x) ans *= z, x /= rec(z);

                // int w = (int)pow(x, 1.0 / 5) - 1;
                // while (fiv(w + 1) <= x) w++;
                // if (fiv(w) == x) ans *= w, x /= fiv(w);
            // }
            if (a[i] * a
            [i] > sqrt(x)) break;

        }
        cout << ans << endl;
    }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}
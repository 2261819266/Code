#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define spc " " 
#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define Problem P11232

using namespace std;

namespace Problem {
template <typename P, typename Q> 
ostream &operator<<(ostream &out, const pair<P, Q> &p) {
    return out << p.first << " " << p.second;
}

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

int sqr(int x) { return x * x; }
#define ceil(x, y) ((x) / (y) + (bool)((x) % (y)))

using PII = pair<int, int>;

const PII NONE = {0, -1};

struct Car {
    int d, v, a;
    friend istream &operator>>(istream &in, Car &car) {
        return in >> car.d >> car.v >> car.a;
    } 

    bool check(const vector<int> &p, int V) const {
        if (p.back() < d) return false;
        if (a == 0) return v > V;
        if (a < 0) {
            if (v <= V) return false;
            int nxt = lower_bound(p.begin(), p.end(), d) - p.begin();
            int D = p[nxt] - d;
            return sqr(v) + 2 * a * D > sqr(V);
        }
        int D = p.back() - d;
        return sqr(v) + 2 * a * D > sqr(V);
    }

    PII get(const vector<int> &p, int V) const {
        int l = lower_bound(p.begin(), p.end(), d) - p.begin(), r = p.size() - 1;
        if (a == 0) {
            if (v > V) return {l, r};
            else return NONE;
        } 
        if (a > 0) {
            int s = d + 1 + (sqr(V) - sqr(v)) / (2 * a);
            if (s > p.back()) return NONE;
            int L = lower_bound(p.begin(), p.end(), s) - p.begin();
            return {L, r};
        }
        if (v <= V) return NONE;
        int s = d - 1 + ceil(sqr(V) - sqr(v), 2 * a);
        int R = upper_bound(p.begin(), p.end(), s) - p.begin() - 1;
        return {l, R};
    }
};

void solve() {
    int n, m, L, V;
    cin >> n >> m >> L >> V;
    vector<Car> car(n);
    cin >> car;
    vector<int> p(m);
    cin >> p;
    
    int num = 0;
    for (const Car &i : car) num += i.check(p, V);
    // cout << num << endl;

    vector<PII> c;
    for (const Car &i : car) {
        PII q = i.get(p, V);
        if (q.first <= q.second) c.push_back(q);
        // cout << q << endl;
    }

    sort(c.begin(), c.end(), [](const PII &X, const PII &Y) { return Y.second < X.second; });
    // for (PII i : c) cout << i << endl;

    int ans = 1;
    if (!c.size()) {
        cout << num << spc << m << endl;
        return;
    }
    int l = c.front().first;
    for (int i = 1; i < c.size(); i++) {
        if (c[i].second < l) {
            ans++;
            l = c[i].first;
        } else if (c[i].first > l) l = c[i].first;
    }
    cout << num << spc << m - ans << endl;
}

void main() {
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Problem::main();
    return 0;
}
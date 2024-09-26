#include <iostream>
#include <ostream>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::vector;
using std::ostream;
using std::set;

typedef long long ll;

vector<int> d2x(int x, int p) {
    vector<int> a, b;
    if (!x) return {0};
    while (x) {
        b.push_back(x % p);
        x /= p;
    }
    a.assign(b.size(), 0);
    for (int i = 0; i < b.size(); i++) {
        a[i] = b[b.size() - i - 1];
    }
    return a;
}

ll x2d(const vector<int> &a, int p) {
    ll x = 0;
    for (int i : a) {
        x = x * p + i;
    }
    return x;
}

ostream &operator<<(ostream &out, const vector<int> &v) {
    for (int i : v) cout << i << " ";
    return out;
}

bool check(const vector<int> &a) {
    if (a.size() > 1 && a[0] == a[1]) return false;
    if (a.size() <= 2) return true;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != a[i % 2]) return false;
    }
    return true;
}

bool check(int x, int l, int r, int k) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        if (check(d2x(x, i))) ans++;
        if (ans > k) return false;
    }
    return ans == k;
}

int l, r, L, R, k;
set<int> ans;
vector<int> as;

void update(int x) {
    if (check(x, l, r, k)) ans.insert(x);
}

int len(int x) {
    return d2x(x, 10).size();
}

int main() {
    cin >> l >> r >> L >> R >> k;
    as.assign(R + 1, 0);

    for (int i = l; i <= r; i++) {
        for (int p = 1; p < i; p++) {
            for (int q = 0; q < i; q++) {
                if (p == q) continue;
                if (x2d({p}, i) >= L) update(x2d({p}, i));
                vector<int> a = {p, q};
                while (x2d(a, i) <= R) {
                    // if (check(x2d(a, i), l, r, k) && ans.find(x2d(a, i)) == ans.end())
                    //     as[x2d(a, i)] = i;
                    if (x2d(a, i) >= L) update(x2d(a, i));
                    a.push_back(a[a.size() % 2]);
                }
            }
        }
    }

    // int y = 0;
    // for (int i = L; i <= R; i++) {
    //     // if (check(i, l, r, k)) cout << i << "\n";
    //     if (check(i, l, r, k)) y++;
    // }
    // if (ans.size() != y) cout << -1;

    // cout << *ans.begin();
    // auto it = ans.begin();
    // it++;
    // cout << k;
    for (int i : ans) {
        if (i >= L) {
            cout << i << "\n";
            // cout << d2x(i, 2);
            // cout << i << "\n";
            // for (int j = l; j <= r; j++) {
            //     if (check(d2x(i, j))) {
            //         cout << j << ":" << d2x(i, j) << "    ";
            //     }
            // }
            // cout << "\n";
        }
    }
}

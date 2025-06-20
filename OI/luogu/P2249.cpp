#include <bits/stdc++.h>
#define Problem P2249
#define int long long
#define endl "\n"
#define space " "

using namespace std;

namespace Problem {

struct Array {
#define lowbit(x) (x & -(x))
    vector<int> a;
    int n;
    void assign(int N, int X = 0) {
        n = N;
        a.assign(n + 1, X);
    }

    void assign(const vector<int> &A) { build(A); }
 
    Array() {}

    Array(int N, int X = 0) { assign(N, X); }

    Array operator=(const vector<int> &A) {
        build(A);
        return *this;
    }

    Array(const vector<int> &A) { build(A); }

    void build(const vector<int> &A) {
        assign(A.size() - 1);
        for (int i = 1; i <= n; i++) {
            a[i] += A[i];
            if (i + lowbit(i) <= n) a[i + lowbit(i)] += a[i];
        }
    }

    int lower_bound(int X) {
        int ans = 0, sum = 0;
        for (int i = (1 << (int)log2(n)); i; i >>= 1) {
            if (ans + i <= n && sum + a[ans + i] < X) ans += i, sum += a[ans];
        }
        return ans + 1;
    }

    int query(int R) {
        int ans = 0;
        if (R > n) R = n;
        if (R <= 0) return 0;
        while (R) {
            ans += a[R];
            R -= lowbit(R);
        }
        return ans;
    }

    int operator()(int R) { return query(R); }
};

struct Array2 {
    Array a, b;
    int n;
    void assign(int N, int X = 0) {
        n = N;
        a.assign(N, X);
        b.assign(N, X);
    }

    Array2(int N, int X = 0) : n(N), a(N, X), b(N, X) {}
    Array2() {}

    void build(const vector<int> X) {
        assign(X.size() - 1);
        vector<int> A(n + 1), B(n + 1);
        for (int i = 1; i <= n; i++) {
            A[i] = X[i] - X[i - 1];
            B[i] = A[i] * i;
        }
        a = A;
        b = B;
    }

    int query(int R) {
        return (R + 1) * a(R) - b(R);
    }

    int lower_bound(int X) {

        
    }
};

void main() {
    int n, m;
    cin >> n >> m;
    vector<int> A(n + 1, 0);
    vector<int> B(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        B[i] = A[i] - A[i - 1];
    }
    Array a(B);
    while (m--) {
        int x;
        cin >> x;
        int y = a.lower_bound(x);
        if (a.query(y) == x) cout << y;
        else cout << -1;
        cout << space;
    }
}
}

signed main() {
    Problem::main();
    return 0;
}

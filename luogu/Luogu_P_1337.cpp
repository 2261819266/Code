#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#define int long long
#define endl "\n"

using namespace std;

template<typename T>
void assign(int n, vector<T> &x) {
    x.assign(n, T());
}

template<typename T, typename ...Args>
void assign(int n, vector<T> &x, vector<Args> &...y) {
    assign(n, x);
    assign(n, y...);
}

inline void init() {
    return;
}

using value_t = double;



struct Force {
    value_t x = 0, y = 0;
    Force operator+(const Force &f) const { return {x + f.x, y + f.y}; };
    Force operator-(const Force &f) const { return {x - f.x, y - f.y}; };
    Force operator*(value_t k) const { return {x * k, y * k}; };
    value_t operator*() const { return sqrt(x * x + y * y); }
    Force operator()(value_t w) const { 
        value_t l = **this;
        if (abs(l) < 1e-8) return {0, 0};
        return {x / l * w, y / l * w};
    }
};

struct Item {
    value_t x, y, w;
    operator Force() const { return {x, y}; }  
};

Force getmergeforce(const vector<Item> &a, const Force &x) {
    Force f;
    for (const auto &i : a) f = f + ((Force)i - x)(i.w);
    return f;
}

vector<Item> a;
value_t dis;
Force ans;

value_t calc(const Force &x) {
    value_t ret = 0;
    for (const auto &i : a) ret += i.w **(x - Force(i));
    if (dis > ret) dis = ret, ans = x;
    return ret;
}

value_t double_rand() {
    return (double)rand() / RAND_MAX;
}

Force Force_rand() {
    return {double_rand() * 2 - 1, double_rand() * 2 - 1};
}

void solve() {
    int n;
    cin >> n;
    a.assign(n, {});
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].w; 
        ans.x = a[i].x, ans.y = a[i].y;
    }
    ans.x /= n, ans.y /= n;
    dis = calc(ans);
    Force now = ans;
    value_t t;
    for (t = 100000; t > 0.00000001; t *= 0.9999) {
        if ((double)clock() / CLOCKS_PER_SEC > 0.9) break;
        // Force f = getmergeforce(a, ans)(1);
        // // if (*f < 1e-6) break;
        // ans = ans + f * t;
        Force nxt = now + Force_rand() * t;
        value_t delta = calc(nxt) - calc(now);
        if (exp(-delta / t) > double_rand()) now = nxt;
    }
    for (int i = 0; i < 10000; i++) {
        Force nxt = now + Force_rand() * t;
        calc(nxt);
    }
    fixed(cout).precision(3);
    cout << ans.x << " " << ans.y << endl;
}

signed main() {
    cin.tie()->sync_with_stdio(0);
    init();
    srand(0);

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
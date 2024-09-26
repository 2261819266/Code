#include <iostream>
#include <istream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::istream;

struct Plane {
    int h, l, r;
};

istream &operator>>(istream &in, Plane &x) {
    return in >> x.h >> x.l >> x.r;
}

int main() {
    int n;
    cin >> n;
    vector<Plane> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        int x = 0, y = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j].h < a[i].h && a[j].l < a[i].l && a[j].r > a[i].l && a[j].h > a[x].h) {
                x = j;
            }
        }
        for (int j = 1; j <= n; j++) {
            if (a[j].h < a[i].h && a[j].l < a[i].r && a[j].r > a[i].r && a[j].h > a[y].h) {
                y = j;
            }
        }
        cout << x << " " << y << "\n";
    }
}
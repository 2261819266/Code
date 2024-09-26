#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cin;
using std::cout;

const string S = "yizhong";

bool f(int x, int n) {
    return x >= 0 && x < n;
}

bool check(const vector<string> &a, int x, int y, int fx, int fy) {
    int m = S.size();
    int n = a.size();
    for (int i = 0; i < m; i++, x += fx, y += fy) {
        if (f(x, n) && f(y, n)) {
            if (a[x][y] != S[i]) return false;
        } else return false;
    }
    return true;
}

void change(vector<string> &a, int x, int y, int fx, int fy) {
    int m = S.size();
    int n = a.size();
    for (int i = 0; i < m; i++, x += fx, y += fy) {
        a[x][y] = S[i];
    }
}

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    vector<string> b(n);
    for (string &i : a) {
        cin >> i;
    }
    for (string &i : b) {
        i.assign(n, '*');
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == l & l == 0) continue;
                    if (check(a, i, j, k, l)) {
                        change(b, i, j, k, l);
                    }
                }
            }
        }
    }
    for (string i : b) {
        cout << i << "\n";
    }
}
#include <bits/stdc++.h>
#include <vector>
using namespace std;

template<typename T>
void assign(int n, T &x) {
    x.assign(n, {});
}

template<typename T, typename ...Args>
void assign(int n, T &x, Args &...y) {
    assign(n, x);
    assign(n, y...);
}

int main() {
    vector<int> a, b;
    vector<vector<int>> e;
    assign(3, a, b, e);
}
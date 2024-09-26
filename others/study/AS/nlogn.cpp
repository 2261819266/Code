#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::sort;
using std::vector;
using std::string;

// template<typename T>
// void tsort(vector<T> &a, int mx) {
//     vector<int> t(mx + 1, 0);
//     for (T i : a) t[(int)i]++;
//     a.clear();
//     for (int i = 0; i <= mx; i++) {
//         for (int j = 0; j < t[i]; j++) {
//             a.push_back(i);
//         }
//     }
// }

// void tsort(vector<vector<int>> a, int mx) {
//     vector<int> t(mx + 1, 0), s = t;
//     for (int i = 0; i < a.size(); i++) {

//     }
// }

vector<vector<int>> _B;
struct Data {
    vector<int> a;
    int i;
    int &operator[](int x) {
        return a[x];
    }
};
vector<Data> _C, _A;
vector<int> _rank;

vector<int> getRank(vector<vector<int>> a, int mx) {
    int n = a.size(), m = a[0].size();
    
    vector<Data> &A = _A;
    A.clear();
    for (int i = 0; i < n; i++) {
        A.push_back({a[i], i});
    }
    for (int i = m - 1; i >= 0; i--) {
        vector<vector<int>> &B = _B;
        B.assign(mx + 1, vector<int>());
        vector<Data> &C = _C;
        C.clear();
        for (int j = 0; j < n; j++) {
            B[A[j][i]].push_back(j);
        }
        for (int j = 0; j <= mx; j++) {
            for (int k : B[j]) C.push_back(A[k]);
        }
        A = C;
    }
    vector<int> &rank = _rank;
    rank.assign(n, 0);
    for (int i = 0, j = 0; i < n; i++) {
        rank[A[i].i] = j;
        if (A[i].a != A[i + 1].a) j++;
    }
    return rank;
}

vector<int> getRank(vector<int> a, int mx) {
    vector<vector<int>> A;
    for (int i : a) A.push_back(vector<int>(1, i));
    return getRank(A, mx);
}

int main() {
    int n;
    string s;
    cin >> s;
    n = s.size();
    vector<int> a;
    for (int i : s) a.push_back(i);
    a = getRank(a, 256);
    vector<vector<int>> B;
    for (int i = 1; i < n; i *= 2) {
        B.assign(n, vector<int>());
        for (int j = 0; j < n; j++) {
            B[j].push_back(a[j]);
            B[j].push_back(i + j < n ? a[j + i] : 0);
        }
        a = getRank(B, n);
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[a[i]] = i;
    }
    for (int i : b) cout << i + 1 << " ";
}
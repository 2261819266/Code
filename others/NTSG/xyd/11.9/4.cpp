#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
long long T, n, k;
long long a[MAXN];
string s;
bool flag;

int main()
{
    
#ifndef LOCAL
    fo(seq)
#endif
    // freopen("seq.in", "r", stdin);
    // freopen("seq.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while (T --)
    {
        flag = true;
        cin >> n >> k;
        for (int i = 1; i <= n; i ++){
            int cnt = 1;
            a[i] = 0;
            cin >> s;
            if (s[0] == '?')
                a[i] = 1e10;
            else{
                for (int j = s.length() - 1; j >= 0; j --){
                    if (s[j] == '-'){
                        a[i] *= -1;
                        break;
                    }
                    a[i] += cnt * (s[j] - '0');
                    cnt *= 10;
                }
            }
        }
        int t = 1;
        for (int i = 1; i <= k; i ++){
            if (a[i] == 1e10){
                a[i] = a[i + k] - 1;
                if (a[i + k] > 0)
                    a[i] = 0;
            }
        }
        for (int i = k + 1; i <= n; i ++)
        {
            if (a[i] == 1e10){
                if (a[i + k] - 1 < 0) t = -1;
                a[i] = min(abs(a[i - k] + 1), abs(a[i + k] - 1));
                a[i] *= t;
                if (a[i - k] < 0 && a[i + k] > 0)
                    a[i] = 0;
            }
            if (a[i] <= a[i - k]){
                cout << "Incorrect sequence" << endl;
                flag = false;
                break;
            }
        }
        if (flag)
            for (int i = 1; i <= n; i ++)
                cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}
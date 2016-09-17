#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define pr(x) cout << #x << ": " << x << "  " 
#define pl(x) cout << #x << ": " << x << endl;
typedef long long LL;
const int maxn = 3e3 + 15;

struct jibancanyang {
    int n, A[maxn], B[maxn];
    LL dp[maxn][maxn];

    void fun() {
        cin >> n; 
        for (int i = 1; i <= n; ++i) cin >> A[i], A[i] -= i, B[i] = A[i];
        sort(B + 1, B + 1 + n);
        for(int i = 1; i <= n; i++) {
            LL temp = dp[i - 1][1];
            for(int j = 1; j <= n; j++) {
                temp = min(temp, dp[i - 1][j]);
                dp[i][j] = abs(A[i] - B[j]) + temp;
            }
        }
        LL ans = LL(1e18);
        for(int i = 1; i <= n; i++) ans = min(ans, dp[n][i]);
        cout << ans << endl; 
    }

}ac;

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    ac.fun();
    return 0;
}

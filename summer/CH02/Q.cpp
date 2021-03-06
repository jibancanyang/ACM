/**********************jibancanyang**************************
 *Author*        :jibancanyang
 *Created Time*  : 三  7/ 6 14:07:06 2016
**Problem**:
**Analyse**:
经典的区间dp，首先从1开始枚举区间的长度L，然后枚举左端点i，右端点j为i + L。
然后当前区间的值要么通过小区间扩展而来，要么通过小区间合并而来。
**Get**:
**Code**:
***********************1599664856@qq.com**********************/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
#define pr(x) cout << #x << ": " << x << "  " 
#define pl(x) cout << #x << ": " << x << endl;
#define pri(a) printf("%d\n",(a))
#define xx first
#define yy second
#define sa(n) scanf("%d", &(n))
#define sal(n) scanf("%lld", &(n))
#define sai(n) scanf("%I64d", &(n))
#define vep(c) for(decltype((c).begin() ) it = (c).begin(); it != (c).end(); it++) 
const int mod = int(1e9) + 7, INF = 0x3f3f3f3f;
const int maxn = 1e5 + 13;
int dp[111][111];



int main(void)
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    string str;
    while (cin >> str, str != "end") {
        int n = str.size();
        memset(dp, 0, sizeof(dp));
        for (int L = 1; L <= n; L++) {
            for (int i = 0; i < n; i++) {
                int j = i + L;
                if (j >= n) break;
                if ((str[i] == '[' && str[j] == ']') || (str[i] == '(' && str[j] == ')')) {
                    dp[i][j] = max((j - i > 2 ? dp[i + 1][j - 1]  : 0) + 2, dp[i][j]);
                }
                for (int k = i ; k < j; k++) dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
        pri(dp[0][n - 1]);
    }
    return 0;
}

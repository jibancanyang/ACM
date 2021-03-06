/**********************jibancanyang**************************
 *Author*        :jibancanyang
 *Created Time*  : 五  7/ 8 11:43:36 2016
**Problem**:
**Analyse**:
显然二分半径来解决该问题。
然后建立一个m*n列的矩阵，判断是否可以选择不多于k行，让n列都至少被覆盖一次。
DLX可重复覆盖模板套上即可。
**Get**:
DLX可以解决精确覆盖，可重复覆盖等问题，而且可以限制选的行数。在限制的时候可以用A*算来进一步剪枝。
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
int n, m;

int k; //最多选择k列
const int maxnode = 3000;
const int maxm = 55;
const int maxn = 55;

struct DLX{
    int n,m,len;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[maxn];//行头结点
    int S[maxm];//每列有多少个结点
    int ansd,ans[maxn];//如果有答案，则选了ansd行，具体是哪几行放在ans[]数组里面,ans[0~ansd-1]

    void init(int _n,int _m){
        n = _n;m = _m;
        for(int i = 0; i <= m; i++){
            S[i] = 0;
            U[i] = D[i] = i;//初始状态时，上下都指向自己
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0,L[0] = m;
        len = m;//编号，每列都有一个头结点，编号1~m
        for(int i = 1; i <= n; i++)
            H[i] = -1;//每一行的头结点
    }

    void link(int r,int c){//第r行，第c列
        ++S[Col[++len]=c];//第len个节点所在的列为c,当前列的结点数++
        Row[len] = r;//第len个结点行位置为r
        D[len] = D[c];
        U[D[c]] = len;
        U[len] = c;
        D[c] = len;
        if(H[r] < 0)
            H[r] = L[len] = R[len] = len;
        else{
            R[len] = R[H[r]];
            L[R[H[r]]] = len;
            L[len] = H[r];
            R[H[r]] = len;
        }
    }

    void del(int c){
        for(int i = D[c]; i != c; i = D[i]){
            L[R[i]] = L[i];
            R[L[i]] = R[i];
        }
    }

    void resume(int c){
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[maxnode];
    int f(){
        int ret = 0;
        for(int c = R[0]; c != 0; c = R[c])
            v[c] = true;
        for(int c = R[0]; c != 0; c = R[c]){
            if(v[c]){
                ret++;
                v[c] = false;
                for(int i = D[c]; i != c; i = D[i]){
                    for(int j = R[i]; j != i; j = R[j]){
                        v[Col[j]] = false;
                    }
                }
            }
        }
        return ret;
    }
    bool dance(int d){//递归深度
        if(d + f() > k) //A*算法来解决最多选择k列
            return false;
        if(R[0] == 0)
            return d <= k;

        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i]){
            if(S[i] < S[c])
                c = i;
        }
        for(int i = D[c]; i != c; i = D[i]){
            del(i);
            ans[d] = Row[i];//列头节点下面的一个节点
            for(int j = R[i]; j != i; j = R[j])
                del(j);
            if(dance(d+1))
                return true;
            for(int j = L[i]; j != i; j = L[j])
                resume(j);
            resume(i);
        }
        return false;
    }
}head;


struct point {
    double x, y;
    point(){}
    point(double X, double Y): x(X), y(Y) {}
}city[55], radar[55];

double dist2(point &a, point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}


int main(void)
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    int T; sa(T);
    while (T--) {
        sa(n), sa(m), sa(k);
        for (int i = 0; i < n; i++) scanf("%lf %lf", &city[i].x, &city[i].y);
        for (int i = 0; i < m; i++) scanf("%lf %lf", &radar[i].x, &radar[i].y);
        double l = 0, r = 2000;
        while (l < r) {
            double mid = (l + r) / 2;
            head.init(m, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dist2(radar[j], city[i]) <= mid * mid)
                        head.link(j + 1, i + 1);
                }
            }
            if (head.dance(0)) r = mid - 1e-8;
            else l = mid + 1e-8;
        }
        printf("%.6f\n", l);
    }
    return 0;
}

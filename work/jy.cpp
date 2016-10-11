#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define pr(x) cout << #x << ": " << x << "  " 
#define pl(x) cout << #x << ": " << x << endl;

struct Solution 
{
    int n, m, S[1001], sons[1001];
    vector<int> G[1001];
    int dp[1001][101][2][2];

    int dfs(int cur, int x, bool f, bool t, int par) {
        if (cur == 0 || x == 0) return 0;
        //if (dp[cur][x][f][t]) pr(cur), pr(x), pr(f), pr(t), pl(dp[cur][x][f][t]);
        if (dp[cur][x][f][t]) return dp[cur][x][f][t];

        int l = 0, r = 0;
        for (int i = 0; i < (int)G[cur].size(); ++i) {
            if (G[cur][i] != par) {
                if (l) r = G[cur][i];
                else l = G[cur][i];
            }
        }

        if (l == 0 && r == 0) {
            if (f) return S[cur];
            return 0;
        }

        if (f && t)
            for (int i = 0; i <= min(sons[l], x - 1); ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        int temp = 0;
                        if (j == 1 || k == 1) continue;
                        if (j == 0) temp += S[l];
                        if (k == 0) temp += S[r];
                        dp[cur][x][1][1] = max(dp[cur][x][1][1], temp + dfs(l, i, j & 1, (j >> 1) & 1, cur) + dfs(r, x - 1 - i, k & 1, (k >> 1) & 1, cur) + S[cur]);
                    }
                }
            }
        else if(!f && t)
            for (int i = 0; i <= min(sons[l], x); ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        if (j == 1 || k == 1) continue;
                        if ( (l && j == 3 && i) || (r && k == 3 && (x - i)) )  {
                            dp[cur][x][0][1] = max(dp[cur][x][0][1], dfs(l, i, j & 1, (j >> 1) & 1, cur) + dfs(r, x - i, k & 1, (k >> 1) & 1, cur) + S[cur]);
                        }
                    }
                }
            }
        else
            for (int i = 0; i <= min(sons[l], x); ++i) {
                for (int j = 0; j < 4; ++j) {
                    for (int k = 0; k < 4; ++k) {
                        if (j == 1 || j == 3 || k == 1 || k == 3) continue;
                        dp[cur][x][0][0] = max(dp[cur][x][0][0], dfs(l, i, j & 1, (j >> 1) & 1, cur) + dfs(r, x - i, k & 1, (k >> 1) & 1, cur));
                    }
                }
            }
        return dp[cur][x][f][t];
    }


    int getSons(int cur, int par) {
        sons[cur] = 1;
        for (int i = 0; i < (int)G[cur].size(); ++i) {
            if (G[cur][i] == par) continue;
            sons[cur] += getSons(G[cur][i], cur);
        }
        return sons[cur];
    }

    void work() {
        S[0] = 0;
        while (~scanf("%d%d", &n, &m)) {
            memset(dp, 0, sizeof(dp));
            for (int i = 1; i <= n; ++i) scanf("%d", &S[i]), G[i].clear();
            for (int i = 1; i < n; ++i) {
                int x, y;
                scanf("%d%d", &x, &y);
                G[x].push_back(y);
                G[y].push_back(x);
            }

            //find root
            int root = 1;
            for (int i = 1; i <= n; ++i) {
                if (G[i].size() == 1) {
                    root = i;
                    break;
                }
            } 

            getSons(root, -1);

            int ans = 0;
            ans = max(dfs(root, m, true, true, -1), ans);
            ans = max(dfs(root, m, false, true, -1), ans);
            ans = max(dfs(root, m, false, false, -1), ans);
            printf("%d\n", ans);
        }
    }
}now;

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
#endif
    now.work();
    return 0;
}

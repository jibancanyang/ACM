#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define pr(x) cout << #x << ": " << x << "  " 
#define pl(x) cout << #x << ": " << x << endl;
const int INF = int(1e9);


////////////////////////最大流开始//////////////////////////////////////
typedef int cap_type;
#define MAX_V 200 + 30 + 16
 
// 用于表示边的结构体（终点、容量、反向边）
struct edge
{
    int to, rev;
	cap_type cap;
 
	edge(int to, cap_type cap, int rev) : to(to), cap(cap), rev(rev)
	{}
};
 
vector <edge> G[MAX_V];   // 图的邻接表表示
int level[MAX_V];      // 顶点到源点的距离标号
int iter[MAX_V];       // 当前弧，在其之前的边已经没有用了
 
// 向图中加入一条从from到to的容量为cap的边
void add_edge(int from, int to, int cap)
{
	G[from].push_back(edge(to, cap, G[to].size()));
	G[to].push_back(edge(from, 0, G[from].size() - 1));
}
 
// 通过BFS计算从源点出发的距离标号
void bfs(int s)
{
	memset(level, -1, sizeof(level));
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty())
	{
		int v = que.front();
		que.pop();
		for (int i = 0; i < (int)G[v].size(); ++i)
		{
			edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0)
			{
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}
 
// 通过DFS寻找增广路
cap_type dfs(int v, int t, cap_type f)
{
	if (v == t)
	{
		return f;
	}
	for (int &i = iter[v]; i < (int)G[v].size(); ++i)
	{
		edge &e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to])
		{
			cap_type d = dfs(e.to, t, min(f, e.cap));
			if (d > 0)
			{
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
 
	return 0;
}
 
// 求解从s到t的最大流
cap_type max_flow(int s, int t)
{
	cap_type flow = 0;
	for (;;)
	{
		bfs(s);
		if (level[t] < 0)
		{
			return flow;
		}
		memset(iter, 0, sizeof(iter));
		cap_type f;
		while ((f = dfs(s, t, 0x3f3f3f3f) > 0))
		{
			flow += f;
		}
	}
}
 
///////////////////////////////最大流结束/////////////////////////////////////

struct jibancanyang
{
    int K, C, M, Ga[234][234];

    void floyd_warshall() {
        for (int i = 0; i < K + C; ++i) {
            for (int j = 0; j < K + C; ++j) {
                for (int k = 0; k < K + C; ++k) {
                    Ga[j][k] = min(Ga[j][i] + Ga[i][k], Ga[j][k]);
                }
            }
        }
    }

    bool judge(int mid) {
        int s = C + K, t = s + 1;
        for (int i = 0; i <= t; ++i) G[i].clear();
        for (int i = 0; i < K; ++i) add_edge(i, t, M);
        for (int i = K; i < K + C; ++i) add_edge(s, i, 1);
        for (int i = 0; i < K; ++i) {
            for (int j = K; j < K + C; ++j) {
                if (Ga[i][j] <= mid) add_edge(j, i, 1);
            }
        }
        return max_flow(s, t) == C;
    }

    int binary_search() {
        floyd_warshall();
        int l = 0, r = 200 * (K + C);
        while (l < r) {
            int mid = (r - l) / 2 + l;
            if (judge(mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }

    void fun() {
        scanf("%d%d%d", &K, &C, &M);
        for (int i = 0; i < K + C; ++i) {
            for (int j = 0; j < K + C; ++j) {
                scanf("%d", &Ga[i][j]);
                Ga[i][j] = Ga[i][j] ? Ga[i][j] : INF;
            }
        }
        printf("%d\n", binary_search());
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

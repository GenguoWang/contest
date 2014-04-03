#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define NUM 202
#define MAXINT 0x3fffffff
int flowMap[NUM][NUM];
int d[NUM];
vector<int> node[NUM];
bool bfs(int s,int t)
{
    memset((void*)d,-1,sizeof(d));
    queue<int> q; int now; q.push(s); d[s]=0; int e;
    while(!q.empty())
    {
        now = q.front();q.pop();
        for(int i=0;i<node[now].size(); ++i)
        {
            e = node[now][i];
            if(d[e]==-1 && flowMap[now][e]>0)
            {
                d[e] = d[now]+1; q.push(e);
            }
        }
    }
    return d[t] != -1;
}
int dfs(int x, int t,int flow)
{
    //cout << "dfs" << x <<' ' << t << ' ' << flow << endl;
    if(x==t || !flow) return flow;
    int e,u,sum=0;
    for(int i=0; i <node[x].size();++i)
    {
        e = node[x][i];
        if(d[e] == d[x]+1)
        {
            u = dfs(e,t,min(flow,flowMap[x][e]));
            if(u>0)
            {
                sum += u; flowMap[x][e] -= u; flowMap[e][x] += u;
                flow -= u;
                if(!flow) break;
            }
        }
    }
    return sum;
}
int maxflow(int s,int t)
{
    int sum=0;
    while(bfs(s,t)) { sum += dfs(s,t,MAXINT); }
    return sum;
}
int main()
{
    int T,n,m,x,y,w,c;
    cin >> T;
    for(int caseNumber=1;caseNumber<=T;++caseNumber)
    {
        cout << "Case #" << caseNumber << ":\n";
        cin >> n >> m;
        for(int i=1;i<=m;++i)
        {
            cin >> x >> y >> w;
            flowMap[x-1][y-1] = w;
            flowMap[y-1][x-1] = w;
            node[x-1].push_back(y-1);
            node[y-1].push_back(x-1);
            c = maxflow(0,n-1);
            if(c>0) cout << i << ' ' << c << '\n';
        }
        for(int i=0;i<n;++i) node[i].clear();
    }
    return 0;
}

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define REP(i,s,n) for(int i=s;i<n;i++)
int N, Q;
vector<int> node[10001];
int level[10001];
int p[10001];
long long w[10001];
int u, l, r;
long long delta;
void dfsInit(int index)
{
    for (int i = 0; i < node[index].size(); ++i)
    {
        int next = node[index][i];
        if (level[next] == 0)
        {
            level[next] = level[index] + 1;
            dfsInit(next);
        }
    }
}
void handle(int index)
{
    //cout << "handle" << index <<' '<<level[index]<<endl;
    if (level[index] >= l && level[index] <= r) w[index] += delta;
    if (level[index] < r)
    {
        for (int i = 0; i < node[index].size(); ++i)
        {
            handle(node[index][i]);
        }
    }
}
long long MOD = 1000000007;
long long MAGIC = 12347;
long long getAns()
{
    long long Hash = 0;
    for (int i = 1; i <= N; ++i)
    {
        Hash = (Hash * MAGIC + w[i]) % MOD;
    }
    return Hash;
}
int main()
{
    int T;
    cin >> T;
    int a;
    REP(caseNumber, 1, T + 1)
    {
        cin >> N;
        p[1] = 0;
        level[1] = 1;
        REP(i, 2, N + 1)
        {
            cin >> a;
            node[a].push_back(i);
            p[i] = a;
        }
        dfsInit(1);
        cin >> Q;
        while (Q--)
        {
            cin >> u >> l >> r >> delta;
            handle(u);
        }
        cout << "Case " << caseNumber << ": " <<getAns()<< "\n";//find out whether need #
        memset((void*)w, 0, sizeof(w));
        memset((void*)level, 0, sizeof(level));
        REP(i, 1, N)
        {
            node[i].clear();
        }
    }
    return 0;
}



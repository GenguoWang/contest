#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX_N 100001
int nodes[2*MAX_N][3];
int indexOfNode[MAX_N];
int level[MAX_N];
int farest[MAX_N];
int parent[MAX_N];
int weight[MAX_N];
int N;
void init()
{
    for(int i=0;i<=N;++i)
    {
        indexOfNode[i] = 0;
        level[i] = 0;
    }
}
void dfs(int currentNode,int currentFarest,int currentLevel)
{
    farest[currentNode] = currentFarest;
    level[currentNode] = currentLevel;
    int degree,nextNode;
    for(int i=indexOfNode[currentNode];i!=0;i=nodes[i][2])degree++;
    if(currentNode!=1)degree--;
    for(int i=indexOfNode[currentNode];i!=0;i=nodes[i][2])
    {
        nextNode = nodes[i][0];
        if(level[nextNode]>0)continue;
        parent[nextNode] = currentNode;
        weight[nextNode] = nodes[i][1];
        if(degree==1)
        {
            dfs(nextNode,currentFarest,currentLevel+1);
        }
        else
        {
            dfs(nextNode,nextNode,currentLevel+1);
        }
    }
}
int main()
{
    int T;
    cin >> T;
    for(int caseNumber=1; caseNumber <= T; ++caseNumber)
    {
        cin >> N;
        init();
        int x,y,w;
        int cnt=0;
        for(int i=0;i<N-1;++i)
        {
            cin >> x >> y >> w;
            nodes[++cnt][0] = y;
            nodes[cnt][1] = w;
            nodes[cnt][2] = indexOfNode[x];
            indexOfNode[x] = cnt;

            nodes[++cnt][0] = x;
            nodes[cnt][1] = w;
            nodes[cnt][2] = indexOfNode[y];
            indexOfNode[y] = cnt;
        }
        dfs(1,1,1);
        cout << "Case #" << caseNumber << ":" << endl;
        int M;
        cin >> M;
        while(M--)
        {
            cin >> x >> y;
            int dist=0,tx=x,ty=y;
            while(farest[tx] != farest[ty])
            {
                if(level[tx] < level[ty]) swap(tx,ty);
                dist += level[tx]-level[farest[tx]]+1;
                tx = parent[farest[tx]];
            }
            dist += abs(level[tx]-level[ty]);
            bool canMake = false;
            if(dist > 50)
            {
                canMake = true;
            }
            else
            {
                vector<int> weights;
                if(level[x] < level[y])
                {
                    swap(x,y);
                }
                int levelToUp = level[x] - level[y];
                while(levelToUp--)
                {
                    weights.push_back(weight[x]);
                    x = parent[x];
                }
                while(x!=y)
                {
                    weights.push_back(weight[x]);
                    x = parent[x];
                    weights.push_back(weight[y]);
                    y = parent[y];
                }
                sort(weights.begin(),weights.end());
                for(int i=0;i+2<weights.size();++i)
                {
                    if(weights[i]+weights[i+1]>weights[i+2])
                    {
                        canMake = true;
                        break;
                    }
                }
            }
            if(canMake)
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
    }
    return 0;
}

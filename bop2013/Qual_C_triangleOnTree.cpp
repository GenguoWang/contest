#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
#define MAX_N 100001
int nodes[2*MAX_N][3];
int indexOfNode[MAX_N];
int questions[2*MAX_N][2];
int indexOfQuestions[MAX_N];
int level[MAX_N];
int parent[MAX_N];
int weight[MAX_N];
int set[MAX_N];
int rank[MAX_N];
int col[MAX_N];
int anc[MAX_N];
bool ans[MAX_N];
int N;
void init()
{
    for(int i=0;i<=N;++i)
    {
        indexOfNode[i] = 0;
        indexOfQuestions[i] = 0;

        level[i] = 0;
        col[i] = 0;

        set[i] = i;
        rank[i] = 0;
    }
}
int findSet(int ind)
{
    int j,k,t;
    for(k=ind; set[k]!=k;k=set[k]);
    for(j=ind; j!=k; j=t){t=set[j];set[j] = k;}
    return k;
}
void joinSet(int i, int j)
{
    i = findSet(i);
    j = findSet(j);
    if(i==j)return;
    if(rank[i]<=rank[j])
    {
        set[i] = j;
        if(rank[i]==rank[j])rank[j]++;
    }
    else set[j] =i;
}
void dfs(int currentNode,int currentLevel)
{
    level[currentNode] = currentLevel;
    anc[findSet(currentNode)] = currentNode;
    int nextNode;
    for(int i=indexOfNode[currentNode];i!=0;i=nodes[i][2])
    {
        nextNode = nodes[i][0];
        if(level[nextNode]>0)continue;
        parent[nextNode] = currentNode;
        weight[nextNode] = nodes[i][1];
        dfs(nextNode,currentLevel+1);
        joinSet(currentNode,nextNode);
        anc[findSet(currentNode)] = currentNode;
    }
    col[currentNode] = 1;
    int anotherNode,ancNode,dist;
    for(int i=indexOfQuestions[currentNode];i!=0;i=questions[i][1])
    {
        anotherNode = questions[i][0];
        if(col[anotherNode])
        {
            ancNode = anc[findSet(anotherNode)];
            dist = level[currentNode]-level[ancNode]+level[anotherNode]-level[ancNode];
            if(dist>50) ans[(i+1)/2] = true;
            else
            {
                vector<int> weights;
                for(int iNode=currentNode;iNode!=ancNode;)
                {
                    weights.push_back(weight[iNode]);
                    iNode = parent[iNode];
                }
                for(int iNode=anotherNode;iNode!=ancNode;)
                {
                    weights.push_back(weight[iNode]);
                    iNode = parent[iNode];
                }
                sort(weights.begin(),weights.end());
                ans[(i+1)/2] = false;
                for(int j=0;j+2<weights.size();++j)
                {
                    if(weights[j]+weights[j+1]>weights[j+2])
                    {
                        ans[(i+1)/2] = true;
                        break;
                    }
                }
            }
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
        int M;
        cin >> M;
        cnt = 0;
        for(int i=0;i<M;++i)
        {
            cin >> x >> y;
            questions[++cnt][0] = y;
            questions[cnt][1] = indexOfQuestions[x];
            indexOfQuestions[x] = cnt;
            questions[++cnt][0] = x;
            questions[cnt][1] = indexOfQuestions[y];
            indexOfQuestions[y] = cnt;
        }
        dfs(1,1);
        cout << "Case #" << caseNumber << ":" << endl;
        for(int i=1;i<=M;++i)
        {
            if(ans[i]) cout<< "Yes\n";
            else cout << "No\n";
        }
    }
    return 0;
}

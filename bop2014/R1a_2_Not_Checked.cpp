#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define NUM 100001
#define REP(i,s,n) for(int i=s;i<n;i++)
int N, Q;
vector<int> node[NUM];
int level[NUM];
long long w[NUM];
struct Delta
{
    int l, r;
    long long delta;
    Delta(int l, int r, long long delta) :l(l), r(r), delta(delta)
    {}
    Delta(){}
};
struct SegNode
{
    int l, r, mid;
    long long value;
    SegNode * pl, *pr;
    SegNode() :pl(NULL), pr(NULL),value(0){}
    SegNode(int l,int r) :l(l),r(r),pl(NULL), pr(NULL),value(0){}
};
class SegTree
{
public:
    SegNode * root;
    long long rD;
    vector<SegNode *> rN;
    void build(SegNode *&p, int l, int r)
    {
        p = new SegNode(l, r);
        if (r > l)
        {
            p->mid = (l + r) / 2;
            build(p->pl, l, p->mid);
            build(p->pr, p->mid + 1, r);
        }
    }
    SegTree(int n)
    {
        build(root, 1, n);
    }
    void insert(int l, int r, long long delta)
    {
        insert(root, l, r, delta);
    }
    void insert(SegNode *node, int l, int r, long long delta)
    {
        if (l == node->l&&r == node->r)
        {
            node->value += delta;
        }
        else
        {
            if (r <= node->mid)
            {
                insert(node->pl, l, r, delta);
            }
            else if (l > node->mid)
            {
                insert(node->pr, l, r, delta);
            }
            else
            {
                insert(node->pl, l, node->mid, delta);
                insert(node->pr, node->mid+1, r, delta);
            }
        }
    }
    void revert()
    {
        for (int i = 0; i < rN.size(); ++i) rN[i]->value -= rD;
        rN.clear();
    }
    void remove(int l, int r, long long delta)
    {
        remove(root, l, r, delta);
    }
    void remove(SegNode * node, int l, int r, long long delta)
    {
        if (l == node->l&&r == node->r)
        {
            node->value -= delta;
        }
        else
        {
            if (r <= node->mid)
            {
                remove(node->pl, l, r, delta);
            }
            else if (l > node->mid)
            {
                remove(node->pr, l, r, delta);
            }
            else
            {
                remove(node->pl, l, node->mid, delta);
                remove(node->pr, node->mid + 1, r, delta);
            }
        }
    }
    long long getValue(int l)
    {
        return getValue(root, l);
    }
    long long getValue(SegNode * node, int l)
    {
        if (node->pl != NULL)
        {
            if (l <= node->mid) return node->value + getValue(node->pl, l);
            else return node->value + getValue(node->pr, l);
        }
        else
        {
            return node->value;
        }
    }
};
vector<Delta> todo[NUM];
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
long long currentAdd[NUM];
SegTree * tree;
void handle(int index)
{
    //cout << "handle" << index << endl;
    Delta d;
    for (int i = 0; i < todo[index].size(); ++i)
    {
        d = todo[index][i];
        tree->insert(d.l, d.r, d.delta);
    }
    w[index] += tree->getValue(level[index]);
    for (int i = 0; i < node[index].size(); ++i)
    {
        handle(node[index][i]);
    }
    for (int i = 0; i < todo[index].size(); ++i)
    {
        d = todo[index][i];
        tree->remove(d.l, d.r, d.delta);
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
        level[1] = 1;
        tree = new SegTree(N);
        REP(i, 2, N + 1)
        {
            cin >> a;
            node[a].push_back(i);
        }
        dfsInit(1);
        cin >> Q;
        while (Q--)
        {
            cin >> u >> l >> r >> delta;
            todo[u].push_back(Delta(l, r, delta));
        }
        handle(1);
        cout << "Case " << caseNumber << ": " << getAns() << "\n";//find out whether need #
        memset((void*)w, 0, sizeof(w));
        memset((void*)level, 0, sizeof(level));
        memset((void*)currentAdd, 0, sizeof(level));
        REP(i, 1, N)
        {
            node[i].clear();
            todo[i].clear();
        }
    }
    return 0;
}



#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

struct Node {
    int lNumber,mNumber,rNumber;
    int trueLeft,trueRight;
    bool hasLeft,hasRight;
    Node *left,*right;
    Node(int l,int r):lNumber(l),rNumber(r),left(NULL),right(NULL)
    {
        trueLeft = -1;
        trueRight = -1;
        hasLeft = false;
        hasRight = false;
    }
    Node(int l,int r,int trueLeft, int trueRight):lNumber(l),rNumber(r),left(NULL),right(NULL)
    {
        this->trueLeft = trueLeft;
        this->trueRight = trueRight;
        hasLeft = false;
        hasRight = false;
    }
};
class SegTree
{
    public:
        Node *root;
        SegTree(int l,int r)
        {
            root = new Node(l,r);
            root->trueLeft = l;
            root->trueRight = r;
            root->hasLeft = true;
            root->hasRight = true;
        }
        void find(int num,int&l,int&r)
        {
            Node*node = root;
            while(node->left != NULL)
            {
                //cout << "\tfind:" << node->lNumber << ' ' << node->rNumber << endl;
                //cout << "\ttrue:" << node->trueLeft << ' ' << node->trueRight << endl;
                //cout << "\tnow:" << l << ' ' << r << endl;
                if(num > node->mNumber)
                {
                    if(node->trueLeft>=0) l = node->trueLeft;
                    if(node->hasRight)  r = node->rNumber;
                    node = node->right;
                }
                else
                {
                    if(node->trueRight>=0) r = node->trueRight;
                    if(node->hasLeft)  l = node->lNumber;
                    node = node->left;
                }
            }
            //cout << "\tfind:" << node->lNumber << ' ' << node->rNumber << endl;
            //cout << "\ttrue:" << node->trueLeft << ' ' << node->trueRight << endl;
            //cout << "\tnow:" << l << ' ' << r << endl;
            //cout << "\tbool:" << node->hasLeft << ' ' << node->hasRight << endl;
            if(node->hasLeft)  l = node->lNumber;
            if(node->hasRight)  r = node->rNumber;
            //if(node->trueLeft>=0) l = node->trueLeft;
            //if(node->trueRight>=0) r = node->trueRight;
        }
        void insert(int num)
        {
            Node *p = root;
            while(p->left != NULL)
            {
                if(num > p->mNumber)
                {
                    if(p->trueRight==-1||num < p->trueRight)
                    {
                        p->trueRight = num;
                    }
                    p = p->right;
                }
                else
                {
                    if(p->trueLeft==-1||num > p->trueLeft)
                    {
                        p->trueLeft = num;
                    }
                    p = p->left;
                }
            }
            if(p->lNumber == num)
            {
                p->trueLeft = num;
                p->hasLeft = true;
                return;
            }
            if(p->rNumber == num)
            {
                p->trueRight = num;
                p->hasRight = true;
                return;
            }
            int temp=(p->lNumber+p->rNumber)/2;
            while(temp != num)
            {
                p->mNumber = temp;
                p->left = new Node(p->lNumber,temp);
                p->right = new Node(temp,p->rNumber);
                if(num<temp)
                {
                    if(p->trueLeft==-1||num > p->trueLeft)
                    {
                        p->trueLeft = num;
                    }
                    p = p->left;   
                }
                else{
                    if(p->trueRight==-1||num < p->trueRight)
                    {
                        p->trueRight = num;
                    }
                    p = p->right;
                }
                temp=(p->lNumber+p->rNumber)/2;
            }
            p->mNumber = num;
            p->trueLeft = num;
            p->trueRight = num;
            p->left = new Node(p->lNumber,num);
            p->left->hasRight = true;
            p->right = new Node(num,p->rNumber);
            p->right->hasLeft = true;
        }
};
int count[500002];
int one[500002];
void testSegTree()
{
    int pos[10001];
    memset((void*)pos,0,sizeof(pos));
    pos[0] = 1;
    pos[10000] = 1;
    SegTree st(0,10000);
    int tests = 1000,l,r;
    while(tests--)
    {
        int num = rand()%9000+1;
        if(pos[num]) continue;
        //cout << "find     " << num << endl;
        st.find(num,l,r);
        int ll = num,rr=num;
        while(pos[ll]==0)ll--;
        while(pos[rr]==0)rr++;
        st.insert(num);
        pos[num] = 1;
        //cout << l <<' ' << r << endl;
        //cout << ll <<' ' << rr << endl;
        assert(l==ll&&r==rr);
    }
}
int main()
{
    //testSegTree();
    int T,N,a,totalCount,totalOne,l,r;
    cin >> T;
    for(int caseNumber=1; caseNumber <= T; ++caseNumber)
    {
        SegTree st(0,500001);
        count[0] = 1;one[0] = 0;
        count[500001] = 1;
        one[500001] = 1;
        totalCount = 2;
        totalOne = 1;
        cin >> N;
        while(N--)
        {
            cin >> a;
            st.find(a,l,r);
            //cout << "lr" << l << ' ' << r << endl;
            if(count[l]>=count[r])
            {
                count[a] = count[l]+1;
                one[a] = one[l]+1;
            }
            else
            {
                count[a] = count[r]+1;
                one[a] = one[r];
            }
            totalCount += count[a];
            totalOne += one[a];
            st.insert(a);
        }
        cout << "Case #"<<caseNumber<<": " << totalCount << ' ' << totalOne <<'\n';
    }
    return 0;    
}



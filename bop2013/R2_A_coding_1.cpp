#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

struct Node {
    //if have left right
    //mNumber = left->rNumber, right->lNumber = mNumber+1
    int lNumber,mNumber,rNumber;
    int trueLeft,trueRight;
    Node *left,*right;
    Node(int l,int r):lNumber(l),rNumber(r),left(NULL),right(NULL)
    {
        trueLeft = -1;
        trueRight = -1;
    }
    Node(int l,int r,int trueLeft, int trueRight):lNumber(l),rNumber(r),left(NULL),right(NULL)
    {
        this->trueLeft = trueLeft;
        this->trueRight = trueRight;
    }
};
class SegTree
{
    public:
        Node *root;
        SegTree(int l,int r)
        {
            root = new Node(l,r);
        }
        void find(int num,int&l,int&r)
        {
            Node*node = root;
            while(node->left != NULL)
            {
                if(num > node->mNumber)
                {
                    if(node->trueLeft>=0) l = node->trueLeft;
                    node = node->right;
                }
                else
                {
                    if(node->trueRight>=0) r = node->trueRight;
                    node = node->left;
                }
            }
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
            int temp=(p->lNumber+p->rNumber)/2;
            while(p->lNumber != num||p->rNumber != num)
            {
                p->mNumber = temp;
                p->left = new Node(p->lNumber,temp);
                p->right = new Node(temp+1,p->rNumber);
                if(num<=temp)
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
        }
        ~SegTree()
        {
            destroy(root);
        }
        private:
        void destroy(Node* node)
        {
            if(node==NULL) return;
            destroy(node->left);
            destroy(node->right);
            delete node;
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
    st.insert(0);
    st.insert(10000);
    int tests = 1000,l,r;
    while(tests--)
    {
        int num = rand()%9000+1;
        if(pos[num]) continue;
        cout << "find     " << num << endl;
        st.find(num,l,r);
        cout << "find     " << num << endl;
        int ll = num,rr=num;
        while(pos[ll]==0)ll--;
        while(pos[rr]==0)rr++;
        st.insert(num);
        pos[num] = 1;
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
        st.insert(0);
        st.insert(500001);
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



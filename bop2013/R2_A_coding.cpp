#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct Node {
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
            root->trueLeft = l;
            root->trueRight = r;
        }
        void find(int num,int&l,int&r)
        {
            Node*node = root;
            while(node->left != NULL)
            {
                //cout << "find:" << node->lNumber << ' ' << node->rNumber << endl;
                //cout << "true:" << node->trueLeft << ' ' << node->trueRight << endl;
                //cout << "now:" << l << ' ' << r << endl;
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
            //cout << "find:" << node->lNumber << ' ' << node->rNumber << endl;
            //cout << "true:" << node->trueLeft << ' ' << node->trueRight << endl;
            //cout << "now:" << l << ' ' << r << endl;
            if(node->trueLeft>=0) l = node->trueLeft;
            if(node->trueRight>=0) r = node->trueRight;
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
                return;
            }
            if(p->rNumber == num)
            {
                p->trueRight = num;
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
            p->right = new Node(num,p->rNumber);
        }
};
int count[500002];
int one[500002];
int main()
{
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



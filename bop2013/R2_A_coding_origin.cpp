#include <iostream>
#include <cstring>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <map>
using namespace std;
unsigned long long t[50010];
unsigned long long a[50010];
class RBTree
{
    public:
        typedef int DataType;
        enum COLOR { RED,BLACK };
        struct node
        {
            DataType weight;
            node *left;
            node *right;
            node *parent;
            int color;
            node()
            {
                left = NULL;
                right = NULL;
                parent = NULL;
                color = BLACK;
            }
        };
        node NILNODE;
        node *NIL;
   private:
        node * mRoot;
        int mTotal;
        void myAssert(bool flag)
        {

        }
    public:
        RBTree()
        {
            NIL = &NILNODE;
            mRoot = NIL;
        }
        void turnLeft(node * x)
        {
            myAssert(x!=NIL);
            node * y = x->right;
            myAssert(y!=NIL);
            x->right = y->left;
            x->right->parent = x;
            y->left = x;
            if(x->parent==NIL) mRoot=y;
            else if(x==x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
            y->parent = x->parent;
            x->parent = y;
        }
        void turnRight(node * x)
        {
            myAssert(x!=NIL);
            node * y = x->left;
            myAssert(y!=NIL);
            x->left = y->right;
            x->left->parent = x;
            y->right = x;
            if(x->parent==NIL) mRoot=y;
            else if(x==x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
            y->parent = x->parent;
            x->parent = y;
        }
        void insert(DataType number)
        {
            node * pNode = mRoot,*preNode = NIL;
            while(pNode != NIL)
            {
                preNode = pNode;
                if(pNode->weight > number) pNode = pNode->left;
                else pNode = pNode->right;
            }
            node *cNode = new node();
            cNode->parent = preNode;
            cNode->weight = number;
            cNode->left = NIL;
            cNode->right = NIL;
            if(preNode == NIL)
            {
                cNode->color = BLACK;
                mRoot = cNode;
            }
            else if(number > preNode->weight)
            {
                cNode->color = RED;
                preNode->right = cNode;
                fixUp(cNode);
            }
            else
            {
                cNode->color = RED;
                preNode->left = cNode;
                fixUp(cNode);
            }
        }
        void fixUp(node * pNode)
        {
            node *p,*pp;
            while(pNode->parent->color == RED)//color for NIl is BLACK
            {
                p = pNode->parent;
                pp = p->parent;
                if(p == pp->left)
                {
                    if(pp->right->color==BLACK)
                    {
                        if(pNode==p->right)
                        {
                            pNode = p;// to terminal the while loop
                            turnLeft(p);
                        }
                        pp->color = RED;
                        pp->left->color = BLACK;
                        turnRight(pp);
                    }
                    else
                    {
                        pp->left->color = BLACK;
                        pp->right->color = BLACK;
                        pp->color = RED;
                        pNode = pp;
                    }
                }
                else
                {
                    if(pp->left->color==BLACK)
                    {
                        if(pNode==p->left)
                        {
                            pNode = p;
                            turnRight(p);
                        }
                        pp->color = RED;
                        pp->right->color = BLACK;
                        turnLeft(pp);
                    }
                    else
                    {
                        pp->left->color = BLACK;
                        pp->right->color = BLACK;
                        pp->color = RED;
                        pNode = pp;
                    }
                }
            }
            //if(pNode->parent == NIL)
            //{
               // mRoot = p;
              //  pNode->color = BLACK;
            //}
            // or just always make it
            mRoot->color = BLACK;
        }
        node* search(DataType number)
        {
            return search(mRoot,number);
        }
        node* search(node * pNode, DataType number)
        {
            while(pNode != NIL && pNode->weight != number)
            {
                if(number < pNode->weight) pNode = pNode->left;
                else pNode = pNode->right;
            }
            return pNode;
        }
        node* find(DataType number,node* &p1,node*&p2)
        {
            return find(mRoot,number,p1,p2);
        }
        node* find(node * pNode, DataType number,node* &p1,node*&p2)
        {
            p1 = NIL;
            p2 = NIL;
            while(pNode != NIL)
            {
                if(number < pNode->weight)
                {
                    p2 = pNode;
                    pNode = pNode->left;
                }
                else
                {
                    p1 = pNode;
                    pNode = pNode->right;
                }
            }
            return pNode;
        }
        node * min()
        {
            return min(mRoot);
        }
        node * max()
        {
            return max(mRoot);
        }
        node* min(node* pNode)
        {
            while(pNode != NIL && pNode->left != NIL) pNode = pNode->left;
            return pNode;
        }
        node* max(node* pNode)
        {
            while(pNode != NIL && pNode->right != NIL) pNode = pNode->right;
            return pNode;
        }
        node* nextNode(node* pNode)
        {
            if(pNode->right != NIL) return min(pNode->right);
            node * p = pNode->parent;
            while(p!=NIL && pNode == p->right)
            {
                pNode = p;
                p = p->parent;
            }
            return p;
        }
        ~RBTree()
        {
            clear(mRoot);
        }
        void clear(node * pNode)
        {
            if(pNode == NIL) return;
            clear(pNode->left);
            clear(pNode->right);
            delete pNode;
        }
        void walkMid()
        {
            node *temp[1000];
            node *p;
            int top = 0;
            if(mRoot == NIL) return;
            p = mRoot;
            while(p != NIL) {
                temp[top++] = p;
                p = p->left;
            }
            while(top > 0)
            {
                p = temp[--top];
                visit(p);
                p = p->right;
                while(p != NIL)
                {
                    temp[top++] = p;
                    p = p->left;
                }
            }
        }
        void visit(node * p)
        {
            cout << p->weight << endl;
        }
        void transplant(node *oldNode,node * newNode)
        {
            if(oldNode->parent == NIL) mRoot = newNode;
            else if(oldNode == oldNode->parent->left)
            {
                oldNode->parent->left = newNode;
            }
            else
            {
                oldNode->parent->right = newNode;
            }
            //the line below is wrong
            //if(newNode != NIL) newNode->parent = oldNode->parent;
            //must unconditionally,used in remove
            newNode->parent = oldNode->parent;
        }
        void remove(node *pNode)
        {
            int oldColor = pNode->color;
            node * x = pNode;
            if(pNode->left == NIL)
            {
                x = pNode->right;
                transplant(pNode,pNode->right);
            }
            else if(pNode->right == NIL)
            {
                x = pNode->left;
                transplant(pNode,pNode->left);
            }
            else
            {
                node *p = min(pNode->right);
                x = p->right;
                oldColor = p->color;
                if(p->parent == pNode)
                {
                    x->parent = p;
                }
                else
                {
                    transplant(p,p->right);
                    p->right = pNode->right;
                    p->right->parent = p;
                }
                transplant(pNode,p);
                p->left = pNode->left;
                p->left->parent = p;
                p->color = pNode->color;
            }
            if(oldColor == BLACK)
            {
                removeFix(x);
            }
            delete pNode;
        }
        void removeFix(node * x)
        {
            node * p,*w;
            while(x != mRoot && x->color == BLACK)
            {
                p = x->parent;
                if(x == p->left)
                {
                    w = p->right;
                    if(w->color == RED)
                    {
                        turnLeft(p);
                        p->color = RED;
                        w->color = BLACK;
                        w = p->right;
                    }
                    if(w->left->color == BLACK && w->right->color == BLACK)
                    {
                        w->color = RED;
                        x = p;
                    }
                    else
                    {
                        if(w->right->color == BLACK)
                        {
                            w->left->color = BLACK;
                            w->color = RED;
                            turnRight(w);
                            w = p->right;
                        }
                        w->color = p->color;
                        p->color = BLACK;
                        w->right->color = BLACK;
                        turnLeft(p);
                        x = mRoot;
                    }
                }
                else
                {
                    w = p->left;
                    if(w->color == RED)
                    {
                        turnRight(p);
                        p->color = RED;
                        w->color = BLACK;
                        w = p->left;
                    }
                    if(w->left->color == BLACK && w->right->color == BLACK)
                    {
                        w->color = RED;
                        x = p;
                    }
                    else
                    {
                        if(w->left->color == BLACK)
                        {
                            w->right->color = BLACK;
                            w->color = RED;
                            turnLeft(w);
                            w = p->left;
                        }
                        w->color = p->color;
                        p->color = BLACK;
                        w->left->color = BLACK;
                        turnRight(p);
                        x = mRoot;
                    }
                }
            }
            x->color = BLACK;
        }
        bool checkRB()
        {
            mTotal = 0;
            if(mRoot == NIL) return true;
            if(mRoot->color != BLACK) return false;
            return checkRB(mRoot,0,BLACK);
        }
        bool checkRB(node * pNode,int count,int color)
        {
            if(pNode == NIL) 
            {
                if(mTotal > 0)
                {
                    if(mTotal == count) return true;
                    else return false;
                }
                else
                {
                    mTotal = count;
                    return true;
                }
            }
            if(pNode->left != NIL && pNode->left->weight > pNode->weight) return false;
            if(pNode->right != NIL && pNode->right->weight < pNode->weight) return false;
            if(pNode->color == BLACK)
            {
                return checkRB(pNode->left,count+1,BLACK) && checkRB(pNode->right,count+1,BLACK);
            }
            else
            {
                if(color == RED) return false;
                else return checkRB(pNode->left,count,RED) && checkRB(pNode->right,count,RED);
            }
        }
        
};
int pos[500010];
int visited[500010];
int main(int argc, char* argv[])
{
    int T;
    cin >> T;
    int N,temp,ind;
    int curMax = 0;
    RBTree::node *p1,*p2;
    int pos1,pos2;
    long long total,total1;
    for(int iCase = 1; iCase <= T;++iCase)
    {
        RBTree bt;
        //map<int,int> pos;
        //map<int,int> visited;

        memset((void*)visited,0,sizeof(visited));
        pos[0] = 0;
        t[0] = 1;
        a[0] = 0;
        bt.insert(0);
        cin >> N;
        for(int i=1;i<=N;++i)
        {
            cin >> temp;
            pos[temp] = i;
            bt.find(temp,p1,p2);
            if(p2==bt.NIL)
            {
                t[i] = t[pos[p1->weight]]+1;
                a[i] = a[pos[p1->weight]]+1;
            }
            else
            {
                pos1 = pos[p1->weight];
                pos2 = pos[p2->weight];
                if(visited[pos2])
                {
                    t[i] = t[pos1]+1;
                    a[i] = a[pos1]+1;
                }
                else
                {
                    visited[pos2] = 1;
                    t[i] = t[pos2]+1;
                    a[i] = a[pos2];
                }
            }
            bt.insert(temp);
        }
        total = 1;
        total1 = 1;
        for(int i=0;i<=N;++i)
        {
            total += t[i];
            total1 += a[i];
        }
        cout << "Case #" << iCase <<":"; //记得冒号后面的空格
        cout << " " << total << " " <<total1<< endl;
    }
    return 0;
}


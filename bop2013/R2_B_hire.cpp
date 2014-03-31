#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#define REP(i,s,n) for(int i=s;i<n;i++)
#define TR(i,x) for(typeof(x.begin()) i=x.begin();i!=x.end();i++)
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))

using namespace std;

const double eps = 1e-8;

#define PB push_back
#define MP make_pair

typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<long double> VD;
typedef pair<int,int> PII;
typedef long long int64;
typedef long long ll;
typedef unsigned int UI;
typedef long double LD;
typedef unsigned long long ULL;
bool gg(const pair<double,double> &a,const pair<double,double> &b)
{
    return a.second > b.second;
}
int main()
{
    int T,n,n1,n2;
    double f[501][501];
    double r,temp;
    double left,right;
    int value[501][4];
    vector<pair<double,double> > qq(501);
    cin >> T;
    REP(caseNumber,1,T+1)
    {
        cin >> n >> n1 >> n2;
        REP(i,1,n+1)
        {
            REP(j,0,4)cin >> value[i][j];
        }
        left = 1.0/50.0;
        right = 2000.0/1.0;
        while(right-left> 1e-8)
        {
            r=(right+left)/2;
            //cout << "t"<<r << endl;
            REP(i,1,n+1)
            {
                qq[i].first = value[i][0]-r*value[i][1];
                qq[i].second = value[i][2]-r*value[i][3];
            }
            sort(qq.begin()+1,qq.begin()+n+1,gg);
            f[0][0] = 0;
            REP(num,1,n+1)
            {
                REP(i,0,n1+1)
                {
                    if(i>num)
                    {
                        break;
                    }
                    f[num][i] = -1e8;
                    if(i<num)
                    {
                        f[num][i] = f[num-1][i];
                        if(num-i<=n2) f[num][i]+=qq[num].second;
                    }
                    if(i>0)
                    {
                        if(f[num-1][i-1]+qq[num].first > f[num][i])
                        {
                            f[num][i] = f[num-1][i-1]+qq[num].first;
                        }
                    }
                }
            }
            if(f[n][n1]>0)
            {
                left = r;
            }
            else
            {
                right = r;
            }
        }
        cout.precision(6);
        cout << "Case #" <<fixed<< caseNumber << ": " << (left+right)/2 << "\n";
    }
    return 0;
}

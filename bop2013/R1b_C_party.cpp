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
double dist(double x1,double y1,double x2,double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main()
{
    int T;
    int N;
    double x[50000];
    double y[50000];
    double left,right,middle;
    double maxLeft,maxRight,temp;
    cin >> T;
    REP(caseNumber,1,T+1)
    {
        cin >> N;
        REP(i,0,N) cin >> x[i] >> y[i];
        left = -10000.0;
        right = 10000.0;
        while(right-left>1e-8)
        {
            middle = (right+left)/2;
            maxRight = 0;
            maxLeft = 0;
            REP(i,0,N)
            {
                temp = dist(x[i],y[i],middle,0);
                if(x[i]<middle && temp>maxLeft)
                {
                    maxLeft = temp;
                }
                else if(x[i]>=middle && temp>maxRight)
                {
                    maxRight = temp;
                }
            }
            if(maxRight>maxLeft)
            {
                left = middle;
            }
            else
            {
                right = middle;
            }
        }

        cout.precision(6);
        cout << "Case #" <<caseNumber<<": "<<fixed <<middle << "\n";
    }
    return 0;
}

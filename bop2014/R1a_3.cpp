nclude <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define REP(i,s,n) for(int i=s;i<n;i++)
vector<double> px, py;
int N;
double getDist(double x)
{
    double dx, dy;
    double dist = 0;
    REP(i, 0, N)
    {
        dx = px[i] - x;
        dy = py[i];
        dist += sqrt(dx*dx + dy*dy);
    }
    return dist;
}
double getDD(double x)
{
    double dd = 0;
    double dx, dy;
    REP(i, 0, N)
    {
        dx = x-px[i];
        dy = py[i];
        if(dx!=0)dd += dx / sqrt(dx*dx + dy*dy);
    }
    return dd;

}
int main()
{
    int T;
    cin >> T;
    double minD,x,y,lx,rx,mx,tempD,dx,dy;
    double x0, x1, dd,step,d0,d1;
    REP(caseNumber, 1, T + 1)
    {
        cin >> N;
        lx = 1e9; rx = -1e9;
        REP(i, 0, N)
        {
            cin >> x >> y;
            lx = min(lx, x);
            rx = max(rx, x);
            px.push_back(x);
            py.push_back(y);
        }
        step = 1e5;
        x0 = rx;
        x1 = lx;
        //cout << rx << lx << endl;
        while (rx-lx > 1e-7)
        {
            mx = (rx + lx) / 2;
            dd = getDD(mx);
            if (dd > 0)
            {
                rx = mx;
            }
            else
            {
                lx = mx;
            }
        }
        cout.precision(6);
        cout << "Case " << caseNumber << ": " <<fixed<< mx << "\n";//find out whether need #
        px.clear(); py.clear();
    }
    return 0;
}



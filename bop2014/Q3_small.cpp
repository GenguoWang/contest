#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define REP(i,s,n) for(int i=s;i<n;i++)
//10^9+7
#define MOD 1000000007
          //1000000007
int m,n;
int mat[101][101];
int isSetM[101];
int isSetN[101];
void init()
{
    for (int i = 0; i < m; ++i)
    {
            isSetM[i] = 0;
    }
    for (int i = 0; i < n; ++i)
    {
            isSetN[i] = 0;
    }
}
int minValue;
void work(int iM, int iN,int value,int markM,int markN)
{
    if (iN >= n)
    {
        iM++;
        iN -= n;
    }
    if (iM < m && iN < n)
    {
        if (markM&(1 << iM) && markN&(1 << iN))
        {
            work(iM, iN + 1, value, markM, markN);
        }
        else
        {
            work(iM, iN + 1, value, markM, markN);
            work(iM, iN + 1, value + mat[iM][iN], markM | (1 << iM), markN | (1 << iN));
        }
    }
    else
    {
        if (value < minValue)
        {
            int mbits = (1 << m) - 1;
            int nbits = (1 << n) - 1;
            if ((markM&mbits) == mbits && (markN&nbits) == nbits)
            {
                minValue = value;
            }
        }
    }
}
int main()
{
    int T;
    cin >> T;
    REP(caseNumber, 1, T + 1)
    {
        cin >> m >> n;
        REP(i, 0, m)
        {
            REP(j, 0, n)
            {
                cin >> mat[i][j];
            }
        }
        minValue = 99999999;
        work(0, 0,0,0,0);
        cout << "Case " << caseNumber << ": "<<minValue << "\n";
    }
    return 0;
}

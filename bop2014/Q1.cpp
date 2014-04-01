#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define REP(i,s,n) for(int i=s;i<n;i++)
//10^9+7
#define MOD 1000000007ll
//1000000007
int tn[1000007];
int tm[1000007];
int main()
{
    int T;
    cin >> T;
    int N, M;
    bool res;
    int maxM, maxN;
    int x, y;
    REP(caseNumber, 1, T + 1)
    {
        cin >> N;
        REP(i, 1, N + 1)
        {
            tn[i] = 0;
        }
        REP(i, 1, N)
        {
            cin >> x >> y;
            tn[x]++;
            tn[y]++;
        }
        cin >> M;
        REP(i, 1, M + 1)
        {
            tm[i] = 0;
        }
        REP(i, 1, M)
        {
            cin >> x >> y;
            tm[x]++;
            tm[y]++;
        }
        res = false;
        maxM = 0;
        REP(i, 1, M + 1)
        {
            if (tm[i] > 1 && maxM > 1)
            {
                res = true;
                break;
            }
            if (tm[i] > maxM) maxM = tm[i];
        }
        if (!res)
        {
            maxN = 0;
            REP(i, 1, N + 1)
            {
                if (tn[i] > maxN) maxN = tn[i];
            }
            if (maxN >= maxM * 2 - 1) res = false;
            else res = true;
        }
        if (res)
            cout << "Case " << caseNumber << ": " << "YES" << "\n";
        else
            cout << "Case " << caseNumber << ": " << "NO" << "\n";

    }
    return 0;
}


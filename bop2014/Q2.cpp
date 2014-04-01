#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define REP(i,s,n) for(int i=s;i<n;i++)
//10^9+7
#define MOD 1000000007ll
//1000000007
int main()
{
    int T;
    unsigned long long n;
    unsigned long long res, sumn, sumtt, sumn2, sumn3;
    cin >> T;
    REP(caseNumber, 1, T + 1)
    {
        cin >> n;
        n = n%MOD;
        sumn = n*(n + 1) / 2 % MOD;
        sumn2 = sumn*sumn % MOD;
        sumn3 = sumn2*sumn % MOD;
        res = MOD + sumn3 + 3ll * sumn2 - sumn2*((2ll * n + 1ll) % MOD) % MOD;
        res = res % MOD;

        cout << "Case " << caseNumber << ": " << res << "\n";
    }
    return 0;
}


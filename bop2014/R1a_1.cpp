#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define REP(i,s,n) for(int i=s;i<n;i++)
int main()
{
    int T;
    cin >> T;
    double iW, FE, cW;
    string uW, uE, uP;
    REP(caseNumber, 1, T + 1)
    {
        cin >> FE >> uE >> cW >> uP >> iW >> uW;
        //cout << FE << uE << cW << uP << iW << uW;
        if (uE == "m")
        {
            FE *= 1000.0;
        }
        else if (uE == "dm")
        {
            FE *= 100.0;
        }
        else if (uE == "cm")
        {
            FE *= 10.0;
        }
        else if (uE == "um")
        {
            FE *= 1 / 1000.0;
        }
        else if (uE == "nm")
        {
            FE *= 1 / 1000000.0;
        }

        if (uP == "m")
        {
            cW *= 1000.0;
        }
        else if (uP == "dm")
        {
            cW *= 100.0;
        }
        else if (uP == "cm")
        {
            cW *= 10.0;
        }
        else if (uP == "um")
        {
            cW *= 1 / 1000.0;
        }
        else if (uP == "nm")
        {
            cW *= 1 / 1000000.0;
        }
        cout.precision(2);
        cout << "Case " << caseNumber << ": " << fixed << (iW*FE / cW) << "px\n";//find out whether need #
    }
    return 0;
}



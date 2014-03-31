//http://hihocoder.com/contest/msbop2014warmup/problem/2
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int T,K,N,M;
    int temp;
    unsigned long long result;
    unsigned long long tempResult;
    unsigned long long cols,rows,others;
    cin >> T;
    for(int caseNumber=1; caseNumber <= T;++caseNumber)
    {
        cin >> N >> M >> K;
        if(N < M)swap(N,M);
        result = 0;
        for(int i=2;i<=M;++i)
        {
            cols = K/i;
            others = K % i;
            rows = i;
            if(cols>=N)
            {
                cols = N;
                tempResult = cols*(cols-1)*rows*(rows-1)/4;
                if(tempResult > result) result = tempResult;
            }
            else
            {
                tempResult = cols*(cols-1)*rows*(rows-1)/4+others*(others-1)*cols/2;
                if(tempResult > result) result = tempResult;
            }
        }
        cout << "Case #" << caseNumber <<": " << result << endl;
    }
    return 0;
}

#include <iostream>
#include <algorithm>
#include <string>
#define REP(i,s,n) for(int i=s;i<n;i++)
using namespace std;
int main()
{
	int num[34][34];
	num[1][0] = 1;
	num[0][1] = 1;
	for (int step = 2; step <= 33; ++step)
	{
		for (int i = 0; i <= step; ++i)
		{
			if (i == 0)num[i][step - i] = 1;
			else if (i == step)num[i][step - i] = 1;
			else num[i][step - i] = num[i - 1][step - i] + num[i][step - i - 1];
		}
	}
	//cout << num[2][2] << endl;
	int t,n,m,k;
	cin >> t;
	while (t--)
	{
		cin >> n >> m >> k;
		if (k > num[n][m])
		{
			cout << "Impossible" << '\n';
		}
		else
		{
			string res="";
			while (k > 1)
			{
				if (k > num[n - 1][m])
				{
					res = res+'1';
					k -= num[n-1][m];
					m--;
				}
				else
				{
					res = res + '0';
					n--;
				}
			}
			REP(i, 0, n) res = res + '0';
			REP(i, 0, m)res = res + '1';
			cout << res << '\n';
		}
	}
	return 0;
}
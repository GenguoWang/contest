#include <iostream>
#include <algorithm>
#include <string>
#define REP(i,s,n) for(int i=s;i<n;i++)
using namespace std;
char toChar(int i)
{
	if (i >= 0 && i <= 9)
	{
		return (char)(i + '0');
	}
	else return (char)(i - 10 + 'a');
}
int indexOf(char c)
{
	if (c >= '0'&&c <= '9') return c - '0';
	else if (c >= 'a' && c <= 'z') return c - 'a' + 10;
	else return -1;
}
int main()
{
	string str;
	int count[36];
	int ind;
	while (getline(cin,str))
	{
		REP(i, 0, 36)
		{
			count[i] = 0;
		}
		bool isValid = true;
		for (int i = 0; i < str.size(); ++i)
		{
			ind = indexOf(str[i]);
			if (ind < 0)
			{
				isValid = false;
				break;
			}
			count[ind]++;
		}
		if (!isValid)
		{
			cout << "<invalid input string>" << '\n';
		}
		else
		{
			bool hasValue=true;
			while (hasValue)
			{
				hasValue = false;
				REP(i, 0, 36)
				{
					if (count[i] > 0)
					{
						cout << toChar(i);
						count[i]--;
						hasValue = true;
					}
				}
			}
			cout << '\n';
		}
	}
	return 0;
}
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#define REP(i,s,n) for(int i=s;i<n;i++)
using namespace std;
int dist[257][257];
int p1[257];
int p2[257];
string getDistance(string str1, string str2)
{
	int size1 = str1.size();
	int size2 = str2.size();
	dist[0][0] = 0;
	dist[1][0] = 1;
	dist[0][1] = 1;
	for (int i = 1; i <= size1; ++i)
	{
		for (int j = 1; j <= size2; ++j)
		{
			if (str1[i - 1] == str2[j - 1])
			{
				dist[i][j] = dist[i - 1][j - 1];
			}
			else
			{
				dist[i][j] = min(dist[i - 1][j] + 1, dist[i][j - 1] + 1);
				dist[i][j] = min(dist[i - 1][j - 1] + 1, dist[i][j]);
			}
		}
	}
	if (dist[size1][size2] > 5)return "";
	int i = size1;
	int j = size2;
	while (i > 0 && j > 0)
	{
		if (str1[i - 1] == str2[j - 1])
		{
			p1[i] = 1;
			p2[j] = 1;
			i--;
			j--;
		}
		else if (dist[i][j] == dist[i - 1][j - 1] + 1)
		{
			p1[i] = 0;
			p2[j] = 0;
			i--;
			j--;
		}
		else if (dist[i][j] == dist[i][j - 1] + 1)
		{
			p2[j] = 0;
			j--;
		}
		else if (dist[i][j] == dist[i - 1][j] + 1)
		{
			p1[i] = 0;
			i--;
		}
	}
	//cout << str1 << endl;
	//REP(i, 1, size1 + 1) cout << p1[i];
	//cout << endl;
	//cout << str2 << endl;
	//REP(i, 1, size2 + 1) cout << p2[i];
	//cout << endl;
	int begin=0, maxCount = 0,tmpCount=0,tmpBegin=0;
	for (int i = 1; i <= size1; ++i)
	{
		if (p1[i])
		{
			if (tmpBegin<0) tmpBegin = i - 1;
			tmpCount++;
		}
		else
		{
			if (tmpCount > maxCount)
			{
				maxCount = tmpCount;
				begin = tmpBegin;
			}
			tmpBegin = -1;
			tmpCount = 0;
		}
	}
	if (tmpCount > maxCount)
	{
		maxCount = tmpCount;
		begin = tmpBegin;
	}
	int strink = maxCount / 4;
	maxCount -= 2 * strink;
	begin += strink;
	return str1.substr(begin, maxCount);
}
struct pattern
{
	string str;
	int count;
	string pp;
	bool match(string str2)
	{
		if (pp != "")
		{
			if (str2.find(pp) != string::npos)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			pp = getDistance(str, str2);
			if (pp != "") return true;
			else return false;
		}

	}
};
int main()
{
	string str1, str2;
	string str;
	//getline(cin, str1);
	//getline(cin, str2);
	str1 = "Module ABC has completed its job";
	str2 = "Module XYZ has completed its job";
	vector<pattern> pList;
	bool isMatched;
	while (getline(cin, str))
	{
		isMatched = false;
		for (int i = 0; i < pList.size(); ++i)
		{
			if (pList[i].match(str))
			{
				pList[i].count++;
				isMatched = true;
			}
		}
		if (!isMatched)
		{
			pattern pn;
			pn.str = str;
			pn.count = 1;
			pn.pp = "";
			pList.push_back(pn);
			//cout << "add:" << str << endl;
		}
	}
	int maxCount = 0;
	for (int i = 0; i < pList.size(); ++i)
	{
		if (pList[i].count > maxCount)
		{
			maxCount = pList[i].count;
		}
	}
	cout << maxCount << endl;
	return 0;
}
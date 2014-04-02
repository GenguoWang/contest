#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#define REP(i,s,n) for(int i=s;i<n;i++)
using namespace std;
vector<int> splitIntoIntegers(string str)
{
	vector<int> res;
	string::size_type pos = 0, prePos = 0;
	while ((pos=str.find(',',pos)) != string::npos)
	{
		string numStr = str.substr(prePos, pos-prePos);
		res.push_back(atoi(numStr.c_str()));
		pos += 1;
		prePos = pos;
	}
	string numStr = str.substr(prePos);
	res.push_back(atoi(numStr.c_str()));
	return res;
}
int numOfReduce(vector<int>& intList, int i, int j)
{
	//i must less than j
	if (intList[i] < intList[j]) return -1;
	int count=0;
	if (intList[i]>intList[j])count++;
	for (int k = i + 1; k < j; ++k)
	{
		if (intList[k] > intList[j]) count++;
		if (intList[k] < intList[i]) count++;
		if (intList[k] < intList[j]) count--;
		if (intList[k] > intList[i]) count--;
	}
	return count;
}
int reduceOfList(vector<int>& intList)
{
	int count = 0;
	for (int i = 0; i < intList.size(); ++i)
	{
		for (int j = i + 1; j < intList.size(); ++j)
		{
			if (intList[i]>intList[j]) count++;
		}
	}
	return count;
}
int main()
{
	string str;
	int tempReduce,maxReduce;
	while (getline(cin, str))
	{
		vector<int> intList = splitIntoIntegers(str);
		maxReduce = 0;
		for (int i = 0; i < intList.size(); ++i)
		{
			for (int j = i + 1; j < intList.size(); ++j)
			{
				tempReduce = numOfReduce(intList, i, j);
				if (tempReduce > maxReduce) maxReduce = tempReduce;
			}
		}
		cout << reduceOfList(intList) - maxReduce << '\n';
	}
	return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;
int main()
{
    int T;
    cin >> T;
    for(int caseNumber=1; caseNumber <= T; ++caseNumber)
    {
        int N,M;
        map<string,string> convertList;
        string str1,str2;
        cin >> N >> M;
        while(M--)
        {
            cin >> str1 >> str2;
            convertList[str1] = str2;
        }
        map<string,string> lastList;
        for(map<string,string>::iterator it = convertList.begin();
            it != convertList.end();++it)
        {
            str1=it->first;
            str2=it->second;
            for(int i=1;i<=N-2;++i)
            {
                map<string,string>::iterator findIt = convertList.find(str2);
                if(findIt==convertList.end())
                {
                    break;
                }
                str2 = findIt->second;
            }
            lastList[str1] = str2;
        }
        getline(cin,str1);
        getline(cin,str1);
        istringstream istr(str1);
        vector<string> result;
        while(istr>>str2)
        {
            if(lastList.find(str2)!=lastList.end())
            {
                result.push_back(lastList[str2]);
            }
            else
            {
                result.push_back(str2);
            }
        }
        cout << "Case #" << caseNumber << ":";
        for(int i=0;i<result.size();++i)
        {
            cout << " " << result[i];
        }
        cout << endl;
    }
    return 0;
}

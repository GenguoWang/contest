#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX_S 10000007
#define MOD 100000007 
struct dpNode
{
    unsigned state;
    int count;
};
int dpIndex;
dpNode dpState[2][MAX_S];
map<unsigned int,int> stateToIndex;
unsigned int encode(int m,int boardType[],int perimeter)
{
    unsigned int result=0;
    int dict[9];
    for(int i=2;i<=8;++i)dict[i]=-1;
    dict[0] = 0;
    dict[1] = 1;
    int typeCnt=1;
    for(int i=0;i<m;++i)
    {
        if(dict[boardType[i]]==-1)dict[boardType[i]] = ++typeCnt; 
        result = (result<<3)+dict[boardType[i]];
    }
    return (result<<8)+perimeter;
}
void decode(int m,unsigned int state,int boardType[],int & perimeter)
{
    perimeter = state & 0xff;
    state = state>>8;
    for(int i=m-1;i>=0;--i)
    {
        boardType[i] = state&0x7;
        state = state>>3;
    }
}
void insertDpState(int index,unsigned int state,int count)
{
    if(stateToIndex.find(state)==stateToIndex.end())
    {
        stateToIndex[state] = dpIndex;
        dpState[index][dpIndex].state = state;
        if(count>MOD) count -= MOD;
        dpState[index][dpIndex].count = count;
        dpIndex++;
    }
    else
    {
        int stateIndex = stateToIndex[state];
        dpState[index][stateIndex].count += count;
        if(dpState[index][stateIndex].count > MOD)
        {
            dpState[index][stateIndex].count -= MOD;
        }
    }
}
int main()
{
    int T,N,M,cnt,preCnt,preDPCount,state,count,perimeter,tempCode;
    int typeForNewNode,up,left,newType;
    bool ok;
    int boardType[8];
    char board[8][8];
    int answer[256];
    /*
    decode(1,0,boardType,perimeter);
    boardType[0]=1;
    state = encode(1,boardType,4);
    decode(1,state,boardType,perimeter);
    cout << state << boardType[0];
    return 0;
    */
    cin >> T;
    for(int caseNumber=1; caseNumber <= T; ++caseNumber)
    {
        cin>>N>>M;
        for(int i=0;i<N;++i) cin >> board[i];
        dpIndex=0;
        cnt=0;
        stateToIndex.clear();
        insertDpState(cnt,0,1);
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<M;++j)
            {
                preDPCount = dpIndex;
                stateToIndex.clear();
                dpIndex = 0;
                preCnt = cnt;
                cnt = (cnt+1)&1;
                for(int k=0;k<preDPCount;++k)
                {
                    state = dpState[preCnt][k].state;
                    count = dpState[preCnt][k].count;
                    decode(M,state,boardType,perimeter);
                    //cout << "state" << state <<' '<<boardType[0]<<' '<<perimeter<< endl;
                    {
                        ok = false;
                        if(boardType[j]==0||boardType[j]==1) ok = true;
                        else
                        {
                            for(int iB = 0;iB<M;++iB)
                            {
                                if(iB!=j && boardType[iB]==boardType[j])
                                {
                                    ok = true;
                                    break;
                                }
                            }
                        }
                        if(ok)
                        {
                            tempCode = boardType[j];
                            boardType[j] = 0;
                            insertDpState(cnt,encode(M,boardType,perimeter),count);
                            boardType[j] = tempCode;
                        }
                    }
                    if(board[i][j]=='T')continue;
                    up = boardType[j];
                    left = j?boardType[j-1]:0;
                    if(board[i][j]=='X')boardType[j] = 1;
                    else boardType[j] = 8;
                    if(up && left)
                    {
                        //cout << "upleft:" <<up<<" " <<boardType[j]<< endl;
                        //cout <<i<<j<<endl;
                        newType = min(up,left);
                        newType = min(newType,boardType[j]);
                        for(int iB = 0;iB<M;++iB)
                        {
                            if(boardType[iB]==up||boardType[iB]==left||boardType[iB]==boardType[j]) boardType[iB] = newType;
                        }
                        insertDpState(cnt,encode(M,boardType,perimeter),count);
                    }
                    else if(up)
                    {
                        newType = min(up,boardType[j]);
                        //cout << "up:" <<up<<" " <<boardType[j]<< endl;
                        //cout <<i<<j<<endl;
                        //cout << perimeter<< endl;
                        for(int iB = 0;iB<M;++iB)
                        {
                            if(boardType[iB]==up||boardType[iB]==boardType[j]) boardType[iB] = newType;
                        }
                        insertDpState(cnt,encode(M,boardType,perimeter+2),count);
                    }
                    else if(left)
                    {
                        //cout << "left:" <<up<<" " <<boardType[j]<< endl;
                        //cout <<i<<j<<endl;
                        newType = min(left,boardType[j]);
                        for(int iB = 0;iB<M;++iB)
                        {
                            if(boardType[iB]==left||boardType[iB]==boardType[j]) boardType[iB] = newType;
                        }
                        insertDpState(cnt,encode(M,boardType,perimeter+2),count);
                    }
                    else
                    {
                        //cout << "none:" <<up<<" " <<boardType[j]<< endl;
                        //cout <<i<<j<<endl;
                        insertDpState(cnt,encode(M,boardType,perimeter+4),count);
                    }
                }
            }
        }
        for(int i=0;i<256;++i) answer[i]=-1;
        cout << "Case #" << caseNumber << ":\n";
        for(int i=0;i<dpIndex;++i)
        {
            ok=true;
            decode(M,dpState[cnt][i].state,boardType,perimeter);
            for(int j=0;j<M;++j)
            {
                if(boardType[j]>1)
                {
                    ok=false;
                    break;
                }
            }
            if(!ok)continue;
            if(answer[perimeter]==-1)answer[perimeter]=0;
            answer[perimeter] += dpState[cnt][i].count;
            if(answer[perimeter]>MOD) answer[perimeter] -= MOD;
        }
        for(int i=1;i<256;++i){
            if(answer[i]>=0) cout << i << " " << answer[i] << "\n";
        }
    }
    return 0;
}

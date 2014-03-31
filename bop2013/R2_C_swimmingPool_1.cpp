#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define TR(i,x) for(typeof(x.begin()) i=x.begin();i!=x.end();i++)
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))

using namespace std;

const double eps = 1e-8;

#define PB push_back
#define MP make_pair

typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<long double> VD;
typedef pair<int,int> PII;
typedef long long int64;
typedef long long ll;
typedef unsigned int UI;
typedef long double LD;
typedef unsigned long long ULL;

const int MAXH = 30007, MAXS = 1000007;
const int MOD = 100000007;

typedef deque<pair<long long, int> > LPII;

int last;
pair<long long, int> dp[2][MAXS];

const int table_size = 27777;
const int max_states = 1077777;

struct HashMap {

    long long states[max_states];
    int nextState[max_states];
    int values[max_states];

    int used;

    int firstPos[table_size];

    void clear() {
        memset(firstPos, -1, sizeof(firstPos));
        used = 0;
    }

    int &operator[](const long long &s) {
        unsigned hash = (s % table_size);
        int ptr = firstPos[hash];
        while (~ptr && !(states[ptr] == s)) {
            ptr = nextState[ptr];
        }
        if (ptr < 0) {
            ptr = used ++;
            states[ptr] = s;
            nextState[ptr] = firstPos[hash];
            values[ptr] = -1;
            firstPos[hash] = ptr;
        }
        return values[ptr];
    }
} hash;

int tmp[11], dict[11];

void decode(int n, long long x, int y[], int &length, int &mask)
{
    mask = x & 1023ll;
    x >>= 10ll;
    length = x & 1023ll;
    x >>= 10ll;
    REP(i, n)
    {
        y[i] = x & 7ll;
        x >>= 3ll;
    }
}

long long encode(int n, int tmp[], int mask, int length)
{
    REP(i, 10) dict[i] = -1;
    dict[0] = 0;
    long long ret = 0;
    int tot = 0;
    int newmask = 0;
    for (int i = n-1; i >= 0; --i)
    {
        if (-1 == dict[tmp[i]]) {
            dict[tmp[i]] = ++tot;
            if (mask & (1 << tmp[i])) {
                newmask |= 1 << tot;
            }
        }
        ret = (ret << 3ll) + dict[tmp[i]];
    }
    return (((ret << 10ll) + length) << 10ll) + newmask;
}

void update(int d, long long x, int add)
{
    if (add >= MOD) add -= MOD;
    if (hash[x] == -1) {
        hash[x] = last;
        dp[d][last++] = MP(x, add);
        return;
    }
    int y = hash[x];
    dp[d][y].second += add;
    if (dp[d][y].second >= MOD) dp[d][y].second -= MOD;
    return;

}

int n, m;
char mat[55][55];

int ans[5555];

int main() {
    int T;
    cin >> T;
    for (int nowCase = 1; nowCase <= T; ++nowCase) {
        cin >> n >> m;
        REP(i, n) cin >> mat[i];
        last = 0;
        // REP(i, MAXH) hash[i].clear();
        hash.clear();
        update(0, 0, 1);
        int cnt = 0;
        REP(i, n) REP(j, m)
        {
            int now = cnt++ & 1, next = now ^ 1;
            hash.clear();
            int prev = last;
            last = 0;
            REP(k, prev)
            {
                long long state = dp[now][k].first;
                int length, mask;
                int value = dp[now][k].second;

                decode(m, state, tmp, length, mask);

                // cout << "mask is " << mask << endl;

                {
                    bool ok = false;
                    if (!tmp[j]) ok = true; 
                    else {
                        int total = 0;
                        REP(t, m) if (tmp[j] == tmp[t]) ++total;
                        if (total > 1) ok = true;
                        else {
                            if (mask & (1 << tmp[j])) {
                                ok = true;
                            }
                        }
                    }
                    if (ok) {
                        int count = tmp[j];
                        tmp[j] = 0;
                        update(next, encode(m, tmp, mask, length), value);
                        tmp[j] = count;
                    }
                }

                if (mat[i][j] == 'T') continue;
                int tree = 0;
                if (mat[i][j] == 'X') tree = 1;

                int left = j ? tmp[j-1] : 0,
                    up = tmp[j];
                if (!left && !up)
                {
                    tmp[j] = 8;
                    update(next, encode(m, tmp, mask | (tree << 8), length + 4), value);
                }
                else
                {
                    if (left && up)
                    {
                        if (left == up)
                            update(next, encode(m, tmp, mask | (tree << up), length), value);
                        else
                        {
                            REP(r, m)
                                if (tmp[r] == left)
                                    tmp[r] = up;
                            if (mask & (1 << left)) mask |= 1 << up;
                            
                            update(next, encode(m, tmp, mask | (tree << up), length), value);
                        }
                    }
                    else
                    {
                        tmp[j] += left;
                        update(next, encode(m, tmp, mask | (tree << tmp[j]), length + 2), value);
                    }
                }
            }
        }
        FILL(ans, -1);
        REP(k, last) {
            long long state = dp[cnt&1][k].first;
            int length, mask;
            int value = dp[cnt&1][k].second;

            decode(m, state, tmp, length, mask);
            bool good = true;
            REP(i, m) {
                if (tmp[i]) {
                    if (!(mask & (1 << tmp[i]))) {
                        good = false;
                    }
                }
            }

            if (good) {
                if (ans[length] == -1) ans[length] = 0;
                ans[length] += value;
            }
            if (ans[length] >= MOD) ans[length] -= MOD;
        }
        cout << "Case #" << nowCase << ":\n";
        REP(i, 5000) {
            if (!i || -1 == ans[i]) continue;
            printf("%d %d\n", i, ans[i]);
        }
    }
    return 0;
}

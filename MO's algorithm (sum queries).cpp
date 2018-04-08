#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <utility>
#include <cassert>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

const long long me = 100025;
const int BLOCK_SIZE = 325;

struct query{
    int l, r;
    int id;
    query() {}
    query(int l, int r, int id) : l(l), r(r), id(id) {}
    bool operator < (const query other) const{
        if(l / BLOCK_SIZE != other.l / BLOCK_SIZE)
            return l / BLOCK_SIZE < other.l / BLOCK_SIZE;
        return r < other.r;
    }
};
struct fenwick{
    long long *ft;
    int sz;
    fenwick() {}
    fenwick(int size) : sz(size), ft(new long long [size + 1]) {
        fill(ft, ft + sz, 0);
    }
    void add(int pos, int value){
        for( ; pos < sz; pos += (pos & -pos))
            ft[pos] += value;
    }
    long long get(int pos){
        long long sum = 0;
        for( ; pos > 0; pos -= (pos & -pos))
            sum += ft[pos];
        return sum;
    }
    long long get(int l, int r){
        return get(r) - get(l - 1);
    }
};

int n, m, k;
long long sum;
int a[me], lb[me], rb[me];
long long ans[me];
fenwick ft;
vector<int> values;
vector<query> q;

void add(int w){
    sum += ft.get(lb[w], rb[w]);
    ft.add(a[w], 1);
}
void remove(int w){
    ft.add(a[w], -1);
    sum -= ft.get(lb[w], rb[w]);
}

/*
 6 6
 3 2 0 5 4 1
 3 6
 2 2
 4 5
 1 4
 1 6
 1 1
 */

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for(int i = 0; i < m; i ++){
        int l, r;
        scanf("%d%d", &l, &r);
        if(l == r){
            ans[i] = 0;
        }
        else{
            q.push_back(query(l + 1, r + 1, i));
        }
    }
    sort(q.begin(), q.end());
    for(int i = 1; i <= n; i ++){
        values.push_back(a[i]);
    }
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for(int i = 1; i <= n; i ++){
        lb[i] = (int)(lower_bound(values.begin(), values.end(), a[i] - k) - values.begin()) + 1;
        rb[i] = (int)(upper_bound(values.begin(), values.end(), a[i] + k) - values.begin());
        a[i] = (int)(lower_bound(values.begin(), values.end(), a[i]) - values.begin()) + 1;
    }
    ft = (fenwick)(me);
    int L = 1, R = 0;
    for(int i = 0; i < (int)q.size(); i ++){
        while(L > q[i].l)
            add(-- L);
        while(L < q[i].l)
            remove(L ++);
        while(R < q[i].r)
            add(++R);
        while(R > q[i].r)
            remove(R --);
        ans[q[i].id] = sum;
    }
    for(int i = 0; i < m; i ++)
        printf("%lld\n", ans[i]);
    
    return 0;
}

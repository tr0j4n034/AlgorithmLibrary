#include <bits/stdc++.h>

// Surely, the solution can be adapted to larger dimensions.

using namespace std;

const int me = 100025;

struct point{
    vector<int> x;
    point() {}
    point(vector<int> x) : x(x) {}
    
    bool operator ==(const point other) const{
        return x == other.x;
    }
    bool operator <(const point other) const{
        return x < other.x;
    }
    int dis(const point other){
        int d = 0;
        for(int i = 0; i < x.size(); i ++)
            d += abs(x[i] - other.x[i]);
        return d;
    }
};

int n, m, ans;
point a[me];
set<point> best;

int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i ++){
        a[i].x.resize(m);
        for(int j = 0; j < m; j ++)
            scanf("%d", &a[i].x[j]);
    }
    for(int i = 0; i < (1 << m); i ++){
        int far_d = 0, near_d = 0;
        int far_i = 0, near_i = 0;
        for(int j = 0; j < n; j ++){
            int s = 0;
            for(int k = 0; k < m; k ++){
                if(i & (1 << k))
                    s += a[j].x[k];
                else s -= a[j].x[k];
            }
            if(s > far_d){
                far_d = s;
                far_i = j;
            }
            if(s < near_d){
                near_d = s;
                near_i = j;
            }
        }
        best.insert(a[far_i]);
        best.insert(a[near_i]);
    }
    for(int i = 0; i < n; i ++)
        for(auto j : best)
            ans = max(ans, a[i].dis(j));
    cout << ans << endl;
    
    return 0;
}

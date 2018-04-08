#include <bits/stdc++.h>

using namespace std;

const int me = 50025;

struct point{
    double x, y;
    int pos;
    point() {}
    point(double x, double y, int pos) : x(x), y(y), pos(pos) {}
    bool operator <(const point other) const{
        return x < other.x
        || (x == other.x && y < other.y);
    }
    double dis(const point other){
        return sqrt(1. * (x - other.x) * (x - other.x) + 1. * (y - other.y) * (y - other.y));
    }
};

int n, p1, p2;
point p[me];
double ans = 1.e30;

void get(int low, int high){
    if(low >= high)
        return;
    if(low + 1 == high){
        double d = p[low].dis(p[low + 1]);
        if(d < ans){
            ans = d;
            p1 = p[low].pos;
            p2 = p[low + 1].pos;
        }
        return;
    }
    int mid = (low + high + 1) >> 1;
    get(low, mid);
    get(mid + 1, high);
    
    vector<point> v;
    for(int i = low; i <= high; i ++)
        if(fabs(p[i].x - p[mid].x) <= ans || fabs(p[i].y - p[mid].x) <= ans)
            v.push_back(p[i]);
    for(int i = 0; i < v.size(); i ++)
        for(int j = 0; j < i; j ++)
            if(v[i].dis(v[j]) < ans){
                ans = v[i].dis(v[j]);
                p1 = v[i].pos;
                p2 = v[j].pos;
            }
}

int main()
{
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        scanf("%lf%lf", &p[i].x, &p[i].y);
        p[i].pos = i;
    }
    sort(p, p + n);
    get(0, n - 1);
    
    if(p1 > p2)
        swap(p1, p2);
    printf("%d %d %.6f\n", p1, p2, ans);
    
    return 0;
}

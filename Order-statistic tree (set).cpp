#define _CRT_SECURE_NO_WARNINGS
//#pragma comment(linker, "/STACK:100000000")

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define y1 lalalalalala
#define index lalalalalalala
#define show(a, i) cout << "a[" << i << "] = " << a[i] << endl;
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define pii pair<int, int>
#define ll long long


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

const int INF = 1e9 + 1;

int getint()
{
    char ch;
    int neg = 1;
    int val = 0;
    
    while(ch = getchar())
    {
        if(ch == '-')   neg = -1;
        else if(ch > 57 || ch < 48)  break;
        else val = 10 * val + ch - 48;
    }
    val = val * neg;
    return val;
}

typedef
tree<
int,
null_type,
greater<int>,
rb_tree_tag,

tree_order_statistics_node_update>
set_t;

set_t s;
int main()
{
    int n, f, x;
    
    cin >> n;
    while(n --)
    {
        cin >> f;
        cin >> x;
        if(f == 1) s.insert(x);
        else if(f == -1) s.erase(x);
        else cout << *(s.find_by_order(x - 1)) << endl;
    }
    
    return 0;
}

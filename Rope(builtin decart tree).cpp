#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

const int me = 25;

rope<int> r;
int n, m, a, b;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        r.push_back(x);
    }
    for(int i : r)
        cout << i << ", ";
    cout << endl;
    
    while(m --){
        cin >> a >> b;
        a --, b --;
        rope<int> s = r.substr(a, b - a + 1);
        r.erase(a, b - a + 1);
        r.insert(r.mutable_begin(), s);
        for(int i : r)
            cout << i << ", ";
        cout << endl;
    }
    
    return 0;
}

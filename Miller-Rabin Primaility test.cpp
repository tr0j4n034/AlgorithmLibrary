#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define y1 lalalalalala
#define index lalalalalalala
#define show(a, i) cout << "a[" << i << "] = " << a[i] << endl;
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define ll unsigned long long

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

const int cs = 1e5 + 1;

ll n;
vector<ll>p;

void getprimes()
{
    int up = (int)sqrt(1.e9 + 1);
    vector<int>u(up + 1, 0);
    
    for(int i = 2 ; i <= (int)sqrt(up) ; i ++)
        if(!u[i])
            for(int j = i * i ; j < up ; j += i)
                u[j] = 1;
    
    for(int i = 2 ; i < up ; i ++)
        if(!u[i])
            p.pb(i);
}

ll mul(ll a, ll b, ll c)
{
    if(b == 0)
        return 0;
    
    ll temp = mul(a, b >> 1, c);
    temp = temp << 1;
    temp %= c;
    if(b & 1)
    {
        temp += a;
        temp %= c;
    }
    return temp;
}
ll modpow(ll a, ll b, ll c)
{
    if(b == 0)
        return 1;
    
    ll temp = modpow(a, b >> 1, c);
    
    temp = mul(temp, temp, c);
    
    if(b & 1)
        temp = mul(temp, a, c);
    
    return temp;
}

bool pseudoprime(ll n)
{
    return modpow(2, n - 1, n) == 1;
}

int Tries(ll n)
{
    /// returns how many numbers will be checked as a witness
    /// if it is big, error rate will so little...
    return (int)log2(n) + 1;
}

bool Witness(ll r, ll n)
{
    ll m = n - 1;
    
    int s = 0;
    while(!(m & 1))
    {
        s ++;
        m = m >> 1;
    }
    
    vector<ll>x(s + 1, 0);
    
    x[0] = modpow(r, m, n);
    
    for(int i = 1 ; i <= s ; i ++)
    {
        x[i] = mul(x[i - 1], x[i - 1], n);
        
        if(x[i] == 1 && x[i - 1] != 1 && x[i - 1] != n - 1)
            return true;
    }
    if(x[s] != 1)
        return true;
    return false;
}

bool solve_small(ll n)
{
    if(n == 1)
        return false;
    int up = (int)sqrt(n);
    for(auto i : p)
    {
        if(i > up)
            break;
        if(n % i == 0)
            return false;
    }
    return true;
}

bool Miller_Rabin(ll n)
{
    if(n < (1 << 30))
        return solve_small(n);
    
    if(!pseudoprime(n))
        return false;
    
    int s = Tries(n);
    
    for(int i = 0 ; i < s ; i ++)
    {
        ll r = p[i];
        
        if(r >= n)
            break;
        
        if(n % r == 0 || Witness(r, n) == true)
            return false;
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(false);
    
    getprimes();
    
    
    int t;
    
    cin >> t;
    
    while(t --)
    {
        cin >> n;
        
        if(Miller_Rabin(n) == true)
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    ///cerr << "Elapsed time: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}

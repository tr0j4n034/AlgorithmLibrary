#include <bits/stdc++.h>

/// Jonhson's Algorithm
/// All pair's shortest path problem
/// Complexity: O(V^2 * log(V) + V * E)

using namespace std;

#define mp make_pair
#define pb push_back
#define y1 lalalalalala
#define index lalalalalalala
#define show(a, i) cout << "a[" << i << "] = " << a[i] << endl;
#define all(x) x.begin(), x.end()
#define vi vector<int>
#define ll long long

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

struct edge
{
    int to;
    int w;
    edge () {
        
    }
};

struct c_edge
{
    int from;
    int to;
    int w;
    c_edge () {
        
    }
};

struct node
{
    int d;
    int vertex;
};

struct cmp
{
    bool operator()(node A, node B)
    {
        return A.d < B.d;
    }
};

vector< vector<edge> >v;
vector<c_edge>V;
vector< vi >dis;
vi h, used;
priority_queue<node, vector<node>, cmp>Q;
int n, m;

void relax(c_edge x)
{
    if(h[x.from] != INT_MAX)
        h[x.to] = min(h[x.to], h[x.from] + x.w);
}

bool Bellman_Ford()
{
    for(int i = 1 ; i <= n ; i ++)
        V.pb({n + 1, i, 0});
    
    for(int i = 1 ; i <= n ; i ++)
        h[i] = INT_MAX;
    
    h[n + 1] = 0;
    
    for(int i = 1 ; i <= n ; i ++)
        for(auto j : V)
            relax(j);
    
    for(auto j : V)
        if(h[j.to] > h[j.from] + j.w)
            return true;
    return false;
}

void init_Dijkstra(int vertex)
{
    while(!Q.empty())
        Q.pop();
    dis[vertex].resize(n + 1, INT_MAX);
}

void Dijkstra(int vertex)
{
    init_Dijkstra(vertex);
    
    dis[vertex][vertex] = 0;
    Q.push({0, vertex});
    
    while(!Q.empty())
    {
        node current = Q.top();
        Q.pop();
        
        for(auto i : v[current.vertex])
        {
            if(dis[vertex][i.to] > current.d + i.w)
            {
                dis[vertex][i.to] = current.d + i.w;
                Q.push({dis[vertex][i.to], i.to});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(false);
    
    cin >> n >> m;
    
    V.resize(m);
    h.resize(n + 2);
    dis.resize(n + 2);
    v.resize(n + 1);
    
    for(int i = 0 ; i < m ; i ++)
        cin >> V[i].from >> V[i].to >> V[i].w;
    
    if( Bellman_Ford() == true)
    {
        cout << "negative cycle" << endl;
        return 0;
    }
    
    for(auto i : V)
    {
        if(i.from == n + 1)
            continue;
        v[i.from].pb({i.to, i.w + h[i.from] - h[i.to]});
    }
    
    for(int i = 1 ; i <= n ; i ++)
        Dijkstra(i);
    
    for(int i = 1 ; i <= n ; i ++)
        for(int j = 1 ; j <= n ; j ++)
            dis[i][j] = dis[i][j] + h[j] - h[i];
    cout << endl;
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= n ; j ++)
            cout << dis[i][j] << " ";
        cout << endl;
    }
    ///cerr << "Elapsed time: " << 1.0 * clock() / CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}

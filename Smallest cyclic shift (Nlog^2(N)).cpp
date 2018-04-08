#include <bits/stdc++.h>

using namespace std;

#define Long long long
#define ld long double
#define pii pair<int, int>
#define pli pair<Long, int>

const int me = 100025;
const int mod = 1.e9 + 7;
const int MAX_LOG = 20;

struct node{
    int value;
    int extra;
    int pos;
    
    node() {}
    node(int value, int extra, int pos) : value(value), extra(extra), pos(pos) {}
    bool operator < (const node other) const{
        if(value != other.value)
            return value < other.value;
        return extra < other.extra;
    }
};

int n, N, step;
char s[me];
int p[MAX_LOG][me];
node v[me];

int lcp(int i, int j){
    int ans = 0;
    for(int k = (int)log2(n); k >= 0 && i < n && j < n; k --)
        if(p[k][i] == p[k][j]){
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    return ans;
}

int naive(){
    int S = 0;
    for(int i = 1; i < N; i ++){
        for(int j = 0; j < N; j ++){
            if(s[S + j] < s[i + j])
                break;
            if(s[S + j] > s[i + j]){
                S = i;
                break;
            }
        }
    }
    return S;
}
void gen(){
    srand(time(NULL));
    n = rand() % me;
    for(int i = 0; i < n; i ++)
        s[i] = (char)(rand() % 26 + 'a');
}

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    gets(s);
    //gen();
    N = strlen(s);
    for(int i = 0; i < N; i ++)
        s[i + N] = s[i];
    n = N << 1;
    for(int i = 0; i < n; i ++)
        p[0][i] = s[i] - 'a';
    for(int cnt = 1; cnt < n; cnt *= 2){
        ++ step;
        for(int i = 0; i < n; i ++){
            v[i].value = p[step - 1][i];
            v[i].extra = (i + cnt < n) ? p[step - 1][i + cnt] : -1;
            v[i].pos = i;
        }
        sort(v, v + n);
        for(int i = 0; i < n; i ++)
            p[step][ v[i].pos ] = (i > 0 && v[i].value == v[i - 1].value && v[i].extra == v[i - 1].extra) ? p[step][ v[i - 1].pos ] : i;
    }
    int S = 0;
    for(int i = 1; i < N; i ++){
        int c = lcp(S, i);
        if(c < N){
            if(s[S + c] > s[i + c])
                S = i;
        }
    }
    //cerr << S << endl;
    //cerr << naive() << endl;
    for(int i = S; i < S + N; i ++)
        putchar(s[i]);
    puts("");
    
    return 0;
}

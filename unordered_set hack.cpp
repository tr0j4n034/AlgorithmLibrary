#include <bits/stdc++.h>

/*
 Can be used to hack unordered_set/map solutions
 in Codeforces and other similar online judges.
 Implementation was taken from Codeforces.
 */

using namespace std;

const int me = 100025;

int ar[100] = {0};
unordered_set <int> S;

int main() {
    srand(31);
    
    int k, x, pos = 0, c = 0, l = 0, i = 1;
    int n = 1e5; /// make n larger as possible
    printf("%d\n", n);
    
    for (i = 1; i <= n; i++) {
        x = ((rand() << 15) ^ rand()) % 1000000007 + 1;
        int lol = S.bucket_count();
        if (lol >= 6){
            c = ++ar[pos];
            x = c * lol;
            if (x > 1000000000){
                ar[pos] = 1;
                c = ar[pos];
                x = c * lol;
            }
            
            while (S.count(x)) x += (rand() % 97);
        }
        while (S.count(x)) x += (rand() % 179371);
        
        if (x > 1000000000){
            i--;
            continue;
        }
        //printf("%d", x);
        //if(i > 1)
        //    putchar(' ');
        S.insert(x);
        k = S.bucket_count();
        if (k != l) pos++;
        l = k;
    }
    puts("");
    
    return 0;
}

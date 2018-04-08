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
#include <set>
#include <map>
//#include <unordered_map>
#include <utility>
#include <cassert>
#include <iomanip>
#include <ctime>

using namespace std;

const int me = 1000025;
const int sz = 21;

int t, n, m, k, ps;
int primes[me], lp[me], phi[me], depth[me], sum[sz][me];

int main(int argc, const char * argv[]) {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    
    for(int i = 2; i < me; i ++){
        if(!lp[i]){
            primes[++ps] = i;
            lp[i] = i;
        }
        for(int j = 1; j <= ps && primes[j] <= lp[i] && i * primes[j] < me; j ++)
            lp[i * primes[j]] = primes[j];
    }
    
    return 0;
}

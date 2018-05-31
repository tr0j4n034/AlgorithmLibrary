//
//  main.cpp
//  practice
//
//  Created by Mahmud on 5/31/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//


// refer to this problem
// http://codeforces.com/gym/101808/problem/B
// and tutorial
// http://codeforces.com/blog/entry/59696

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>

using namespace std;

const int MAX = 4005;
const int mods[] = {715225741, 1000000007};
const int bases[] = {555558019, 777781447};

int T, N;
int id[MAX], h[2][MAX];
pair<int, int> edges[MAX];
map<pair<int, int>, int> hashBlocks[MAX];

int power(int a, int b, int modulo) {
    if (b == 0) return 1 % modulo;
    if (b & 1) return 1LL * a * power(a, b - 1, modulo) % modulo;
    return power(1LL * a * a % modulo, b >> 1, modulo);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> T;
    while (T --) {
        cin >> N;
        for (int i = 1; i <= N; i ++) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            edges[i] = make_pair(u, v);
        }
        vector<pair<int, int>> values = vector<pair<int, int>>(edges + 1, edges + N + 1);
        sort(values.begin(), values.end());
        for (int i = 1; i <= N; i ++) {
            id[i] = (int)(lower_bound(values.begin(), values.end(), edges[i]) - values.begin()) + 1;
            h[0][i] = power(bases[0], id[i], mods[0]);
            h[1][i] = power(bases[1], id[i], mods[1]);
        }
        for (int i = 1; i <= N; i ++) {
            hashBlocks[i].clear();
        }
        for (int i = 1; i <= N; i ++) {
            pair<int, int> hashSum(0, 0);
            for (int j = i; j <= N; j ++) {
                hashSum.first = (hashSum.first + h[0][j]) % mods[0];
                hashSum.second = (hashSum.second + h[1][j]) % mods[1];
                hashBlocks[j - i + 1][hashSum] ++;
            }
        }
        int result = 0;
        for (int i = 1; i <= N; i ++) {
            for (auto j : hashBlocks[i]) {
                result += j.second * (j.second - 1) / 2;
            }
        }
        cout << result << endl;
    }
    
    return 0;
}

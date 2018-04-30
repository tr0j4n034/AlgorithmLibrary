//
//  main.cpp
//  practice
//
//  Created by Mahmud on 04/30/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

const int MAX = 100005;

typedef pair<int, pair<int, int>> edge;

int N, M;
vector<edge> edges;

int parent[MAX], size[MAX];

int Find(int x) {
    return x == parent[x] ? x : parent[x] = Find(parent[x]);
}
bool Union(int x, int y) {
    int root1 = Find(x);
    int root2 = Find(y);
    if (root1 == root2) return false;
    if (size[root1] > size[root2]) swap(root1, root2);
    if (size[root1] == size[root2]) size[root2] += size[root1];
    parent[root1] = root2;
    return true;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i ++) {
        int u, v, l;
        cin >> u >> v >> l;
        edges.push_back(make_pair(l, make_pair(u, v)));
    }
    sort(edges.begin(), edges.end());
    
    for (int i = 1; i <= N; i ++) {
        parent[i] = i;
        size[i] = 1;
    }
    int mst = 0;
    for (auto i : edges) {
        int x = i.second.first;
        int y = i.second.second;
        if (Union(x, y)) mst += i.first;
    }
    cout << mst << endl;
    
    return 0;
}

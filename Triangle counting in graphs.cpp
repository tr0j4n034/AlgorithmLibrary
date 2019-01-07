//
//  main.cpp
//  practice
//
//  Created by Mahmud on 01/07/19.
//  Copyright © 2018 Mahmud. All rights reserved.
//

/*
 Fast triangle counting for graphs
 O(M * sqrt(M)) compexity where M is the edge size of the graph
 Note that: The implementation removes multiple edges
    and do not consider same triples more than once.
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <utility>
#include <functional>
#include <numeric>

using namespace std;

const int MAX_SIZE = 1 << 17;

int N, M;
int degrees[MAX_SIZE];
vector<pair<int, int>> edgeList;
vector<vector<int>> graph;
bitset<MAX_SIZE> adj[MAX_SIZE];

int main(int argc, const char * argv[]) {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i ++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edgeList.push_back(make_pair(u, v));
    }
    sort(edgeList.begin(), edgeList.end());
    edgeList.erase(unique(edgeList.begin(), edgeList.end()), edgeList.end());
    graph.resize(N + 1);
    for (auto edge: edgeList) {
        int u = edge.first;
        int v = edge.second;
        graph[u].push_back(v);
        graph[v].push_back(u);
        adj[u][v] = 1;
        adj[v][u] = 1;
        degrees[u] ++;
        degrees[v] ++;
    }
    int threshold = (int)sqrt(1. * M);
    vector<int> heavyNodes;
    for (int i = 1; i <= N; i ++) {
        if (degrees[i] >= threshold) {
            heavyNodes.push_back(i);
        }
    }
    vector<int> isHeavy(N + 1, 0);
    for (int i: heavyNodes) {
        isHeavy[i] = 1;
    }
    vector<int> orders(N + 1);
    iota(orders.begin(), orders.end(), 1);
    sort(orders.begin(), orders.end(), [&](int u, int v) {
        if (degrees[u] != degrees[v]) {
            return degrees[u] < degrees[v];
        } else {
            return u < v;
        }
    });
    long long result = 0;
    for (int i = 0; i < (int)heavyNodes.size(); i ++) {
        for (int j = i + 1; j < (int)heavyNodes.size(); j ++) {
            for (int k = j + 1; k < (int)heavyNodes.size(); k ++) {
                int a = heavyNodes[i];
                int b = heavyNodes[j];
                int c = heavyNodes[k];
                if (adj[a][b] && adj[a][c] && adj[b][c]) {
                    result ++;
                }
            }
        }
    }
    for (auto edge: edgeList) {
        int u = edge.first;
        int v = edge.second;
        if (isHeavy[u] && isHeavy[v]) {
            continue;
        } if (orders[u] > orders[v]) {
            swap(u, v);
        }
        for (auto neighbor: graph[u]) {
            if (orders[neighbor] < orders[u]) {
                continue;
            } if (adj[v][neighbor]) {
                result ++;
            }
        }
    }
    cout << result << endl;
    
    return 0;
}


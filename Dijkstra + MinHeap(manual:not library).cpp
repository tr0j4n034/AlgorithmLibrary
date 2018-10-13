//
//  main.cpp
//  practice
//
//  Created by Mahmud on 10/11/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

const int MAX_NODE_COUNT = 1 << 17;
typedef vector<vector<pair<int, int>>> graph;


class item {
    int node;
    int d; // distance
    
public:
    item() {
        
    }
    item(int _n, int _d) {
        node = _n;
        d = _d;
    }
    int getNodeID() {
        return node;
    }
    int getDistance() {
        return d;
    }
    void setNodeID(int _n) {
        node = _n;
    }
    void setDistance(int _d) {
        d = _d;
    }
    bool operator < (const item other) const {
        if (d != other.d) {
            return d < other.d;
        } else {
            return node < other.node;
        }
    }
    bool operator < (const int key) const {
        return d < key;
    }
    bool operator == (const item other) const {
        return node == other.node && d == other.d;
    }
    bool operator <= (const item other) const {
        return make_pair(d, node) <= make_pair(other.d, other.node);
    }
    bool operator >= (const item other) const {
        return make_pair(d, node) >= make_pair(other.d, other.node);
    }
    bool operator > (const item other) const {
        if (d != other.d) {
            return d > other.d;
        } else {
            return node > other.node;
        }
    }
};

class MinHeap {
    const int MAX_HEAP_SIZE = 1 << 18;
    
    int heapSize;
    vector<item> data;
    
    int parent(int node) {
        return node >> 1;
    }
    int leftChild(int node) {
        return node << 1;
    }
    int rightChild(int node) {
        return node << 1 | 1;
    }
    void heapify(int node) {
        int position = node;
        if (leftChild(node) <= heapSize && data[leftChild(node)] < data[position]) {
            position = leftChild(node);
        } if (rightChild(node) <= heapSize && data[rightChild(node)] < data[position]) {
            position = rightChild(node);
        }
        if (position != node) {
            swap(data[position], data[node]);
            heapify(position);
        }
    }
    void siftUp(int node) {
        while (node > 1 && data[parent(node)] > data[node]) {
            swap(data[parent(node)], data[node]);
            node = parent(node);
        }
    }
    
public:
    MinHeap() {
        heapSize = 0;
        data.resize(MAX_HEAP_SIZE);
    }
    int getSize() {
        return heapSize;
    }
    item heapMin() {
        return data[1];
    }
    int heapMinValue() {
        return data[1].getDistance();
    }
    int heapMinID() {
        return data[1].getNodeID();
    }
    void buildHeap() {
        for (int i = (getSize() >> 1); i >= 1; i --) {
            heapify(i);
        }
    }
    void extractMin() {
        data[1] = data[heapSize --];
        heapify(1);
    }
    void heapIncreaseKey(int node, int key) {
        if (data[node].getDistance() >= key) {
            return;
        }
        data[node].setDistance(key);
        siftUp(node);
    }
    void heapInsert(int id, int key) {
        ++heapSize;
        data[heapSize].setNodeID(id);
        data[heapSize].setDistance(-(1 << 30));
        heapIncreaseKey(heapSize, key);
    }
};

//#include <set>
//#include <ctime>
//
//bool test() {
//    srand(unsigned(time(NULL)));
//    MinHeap h;
//    multiset<int> s;
//    for (int i = 0; i < 50000; i ++) {
//        int x = rand() * rand() % 123456;
//        s.insert(x);
//        h.heapInsert(x);
//    }
//    for (int i = 0; i < 10000; i ++) {
//        int type, a;
//        type = rand() % 3;
//        if (type == 0) {
//            a = rand() * rand() % 123456;
//            h.heapInsert(a);
//            s.insert(a);
//        } else if (type == 1) {
//            h.extractMin();
//            s.erase(s.begin());
//        } else {
//            int a = h.heapMin();
//            int b = *s.begin();
//            if (a != b) {
//                return false;
//            }
//        }
//    }
//    return true;
//}




int N, M;
int source, sink;
graph G;
vector<pair<int, int>> edgeList;

vector<int> bfs(int source, graph G) {
    int nodes = (int)G.size();
    vector<int> distances(nodes, nodes + 1);
    queue<int> Q;
    Q.push(source);
    distances[source] = 0;
    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();
        for (auto neighbor: G[current]) {
            if (distances[neighbor.first] > distances[current] + 1) {
                distances[neighbor.first] = distances[current] + 1;
                Q.push(neighbor.first);
            }
        }
    }
    return distances;
}

int main() {
    //    cout << test() << endl;
    
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    scanf("%d%d", &N, &M);
    scanf("%d%d", &source, &sink);
    
    G.resize(N);
    for (int i = 0; i < M; i ++) {
        int u, v, l;
        scanf("%d%d%d", &u, &v, &l);
        G[u].push_back(make_pair(v, l));
        // if undirected, add the the backward edge.
        //G[v].push_back(make_pair(u, l));
        
        // edgeList.push_back(make_pair(u, l));
    }
//    vector<int> minMoves = bfs(source, G);
//    G.clear();
//    G.resize(N);
//    for (auto edge: edgeList) {
//        int from = edge.first;
//        int to = edge.second;
//        if (minMoves[from] & 1) {
//            G[from].push_back(make_pair(to, 2));
//        } else {
//            G[from].push_back(make_pair(to, 1));
//        }
//    }
    vector<int> distances(N, 1 << 30);
    distances[source] = 0;
    MinHeap h;
    h.heapInsert(source, 0);
    while (h.getSize() > 0) {
        int top = h.heapMinID();
        int d = h.heapMinValue();
        h.extractMin();
        if (d > distances[top]) {
            continue;
        }
        for (auto neighbor: G[top]) {
            int to = neighbor.first;
            int weight = neighbor.second;
            if (distances[to] > distances[top] + weight) {
                distances[to] = distances[top] + weight;
                h.heapInsert(to, distances[to]);
            }
        }
    }
    printf("%d", distances[sink]);
    
    return 0;
}

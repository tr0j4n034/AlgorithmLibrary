//
//  main.cpp
//  practice
//
//  Created by Mahmud on 12/02/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

/*
 Quadtree implementation for 2D aggregate functions handling
 Wikipedia page for quadtrees: https://en.wikipedia.org/wiki/Quadtree
 The implementation below solves the following "Mineral Mining" problem:
    - You are given set of N points in 2D plane with fixed aggregate value
    - And you get Q queries in the following form:
        - each query consists of M rectangles with sides parallel to coordinate axes
        - you are required to find the total sum (aggregate function) of all the points
            lying in union of these rectangles
 
 Building the tree O(N * log(N))
 Complexity of answering a set of only one query: O(M * log^2(N)) on average
 Since we need to preserve the data structure for successive queries, a roll-back routine
    is required (O(M * log^2(N)))
 
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int MAX_SIZE = 1 << 19;

struct point{
    int x;
    int y;
    int value;
    point() {
        
    }
    point(int __x, int __y, int __value) {
        x = __x;
        y = __y;
        value = __value;
    }
};
struct rectangle{
    int xLow, yLow;
    int xHigh, yHigh;
    rectangle() {
        
    }
    rectangle(int x, int y, int X, int Y) {
        xLow = min(x, X);
        yLow = min(y, Y);
        xHigh = max(x, X);
        yHigh = max(y, Y);
    }
};
struct query{
    int n;
    vector<rectangle> qrecs;
    query() {
        
    }
    query(int __n, vector<rectangle> __qrecs) {
        n = __n;
        qrecs = __qrecs;
    }
};

int N, Q;
vector<point> bases;
vector<query> queries;

int xRange, yRange;
vector<int> xCoords;
vector<int> yCoords;

int stree[MAX_SIZE << 2], lazy[MAX_SIZE << 2];

void add(int I, int lowx, int highx, int lowy, int highy, int x, int y, int value) {
    if (lowx == highx && lowy == highy) {
        stree[I] += value;
        lazy[I] = stree[I];
        return;
    }
    int middlex = (lowx + highx) >> 1;
    int middley = (lowy + highy) >> 1;
    if (x <= middlex && y <= middley) {
        add(I * 4 - 2, lowx, middlex, lowy, middley, x, y, value);
    } else if (x <= middlex) {
        add(I * 4 - 1, lowx, middlex, middley + 1, highy, x, y, value);
    } else if (x > middlex && y <= middley) {
        add(I * 4, middlex + 1, highx, lowy, middley, x, y, value);
    } else {
        add(I * 4 + 1, middlex + 1, highx, middley + 1, highy, x, y, value);
    }
    stree[I] = stree[I * 4 - 2] + stree[I * 4 - 1] + stree[I * 4] + stree[I * 4 + 1];
    lazy[I] = stree[I];
}
int get(int I, int lowx, int highx, int lowy, int highy, int x, int X, int y, int Y) {
    if (lazy[I] == 0) {
        return 0;
    }
    if (lowx > X || highx < x) {
        return 0;
    } if (lowy > Y || highy < y) {
        return 0;
    } if (lowx >= x && highx <= X && lowy >= y && highy <= Y) {
        int v = lazy[I];
        lazy[I] = 0;
        return v;
    }
    int middlex = (lowx + highx) >> 1;
    int middley = (lowy + highy) >> 1;
    int sum = 0;
    sum += get(I * 4 - 2, lowx, middlex, lowy, middley, x, X, y, Y);
    sum += get(I * 4 - 1, lowx, middlex, middley + 1, highy, x, X, y, Y);
    sum += get(I * 4, middlex + 1, highx, lowy, middley, x, X, y, Y);
    sum += get(I * 4 + 1, middlex + 1, highx, middley + 1, highy, x, X, y, Y);
    lazy[I] = lazy[I * 4 - 2] + lazy[I * 4 - 1] + lazy[I * 4] + lazy[I * 4 + 1];
    return sum;
}
void rollBack(int I, int lowx, int highx, int lowy, int highy, int x, int X, int y, int Y) {
    if (lowx > X || highx < x) {
        return;
    } if (lowy > Y || highy < y) {
        return;
    } if (lowx >= x && highx <= X && lowy >= y && highy <= Y) {
        lazy[I] = stree[I];
        return;
    }
    int middlex = (lowx + highx) >> 1;
    int middley = (lowy + highy) >> 1;
    rollBack(I * 4 - 2, lowx, middlex, lowy, middley, x, X, y, Y);
    rollBack(I * 4 - 1, lowx, middlex, middley + 1, highy, x, X, y, Y);
    rollBack(I * 4, middlex + 1, highx, lowy, middley, x, X, y, Y);
    rollBack(I * 4 + 1, middlex + 1, highx, middley + 1, highy, x, X, y, Y);
    lazy[I] = lazy[I * 4 - 2] + lazy[I * 4 - 1] + lazy[I * 4] + lazy[I * 4 + 1];
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d", &N);
    for (int i = 0; i < N; i ++) {
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
        bases.push_back(point(x, y, v));
        xCoords.push_back(x);
        yCoords.push_back(y);
    }
    scanf("%d", &Q);
    while (Q --) {
        query q;
        scanf("%d", &q.n);
        for (int i = 0; i < q.n; i ++) {
            int x, y, X, Y;
            scanf("%d%d%d%d", &x, &y, &X, &Y);
            q.qrecs.push_back(rectangle(x, y, X, Y));
            xCoords.push_back(x);
            xCoords.push_back(X);
            yCoords.push_back(y);
            yCoords.push_back(Y);
        }
        queries.push_back(q);
    }
    sort(xCoords.begin(), xCoords.end());
    sort(yCoords.begin(), yCoords.end());
    xCoords.erase(unique(xCoords.begin(), xCoords.end()), xCoords.end());
    yCoords.erase(unique(yCoords.begin(), yCoords.end()), yCoords.end());
    
    xRange = (int)xCoords.size();
    yRange = (int)yCoords.size();
    //    xRange = 1024;
    //    yRange = 1024;
    for (auto &p: bases) {
        p.x = (int)(lower_bound(xCoords.begin(), xCoords.end(), p.x) - xCoords.begin()) + 1;
        p.y = (int)(lower_bound(yCoords.begin(), yCoords.end(), p.y) - yCoords.begin()) + 1;
    } for (auto &q: queries) {
        for (auto &qr: q.qrecs) {
            qr.xLow = (int)(lower_bound(xCoords.begin(), xCoords.end(), qr.xLow) - xCoords.begin()) + 1;
            qr.yLow = (int)(lower_bound(yCoords.begin(), yCoords.end(), qr.yLow) - yCoords.begin()) + 1;
            qr.xHigh = (int)(lower_bound(xCoords.begin(), xCoords.end(), qr.xHigh) - xCoords.begin()) + 1;
            qr.yHigh = (int)(lower_bound(yCoords.begin(), yCoords.end(), qr.yHigh) - yCoords.begin()) + 1;
        }
    }
    for (auto &p: bases) {
        add(1, 1, xRange, 1, yRange, p.x, p.y, p.value);
    }
    vector<int> results;
    for (auto &q: queries) {
        int sum = 0;
        for (auto &qr: q.qrecs) {
            sum += get(1, 1, xRange, 1, yRange, qr.xLow, qr.xHigh, qr.yLow, qr.yHigh);
        } for (auto &qr: q.qrecs) {
            rollBack(1, 1, xRange, 1, yRange, qr.xLow, qr.xHigh, qr.yLow, qr.yHigh);
        }
        results.push_back(sum);
    }
    for (int i = 0; i < (int)results.size(); i ++) {
        printf("%d", results[i]);
        if (i < (int)results.size() - 1) {
            printf("\n");
        }
    }
    
    return 0;
}

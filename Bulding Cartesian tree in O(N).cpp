//
//  main.cpp
//  practice
//
//  Created by Mahmud on 02/18/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>

using namespace std;

const int MAX = 100005;

int N;
int data[MAX];
int label[MAX], leftChild[MAX], rightChild[MAX], parent[MAX];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i ++) cin >> data[i];
    
    int root = 1;
    leftChild[1] = 0;
    rightChild[1] = 0;
    label[1] = data[1];
    
    for (int i = 2; i <= N; i ++) {
        int last = i - 1;
        label[i] = data[i];
        rightChild[i] = 0;
        while (label[last] > data[i] && last != root) {
            last = parent[last];
        }
        if (label[last] > data[i]) {
            parent[root] = i;
            leftChild[i] = root;
            root = i;
        }
        else if(rightChild[last] == 0) {
            rightChild[last] = i;
            parent[i] = last;
            leftChild[i] = 0;
        }
        else {
            parent[rightChild[last]] = i;
            leftChild[i] = rightChild[last];
            rightChild[last] = i;
            parent[i] = last;
        }
    }
    cout << "root = " << root << endl;
    for (int i = 1; i <= N; i ++) {
        cout << i << " " << label[i] << " " << leftChild[i] << " " << rightChild[i] << ", and parent = " << parent[i] << endl;
    }
    
    return 0;
}

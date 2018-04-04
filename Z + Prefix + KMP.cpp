//
//  main.cpp
//  practice
//
//  Created by Mahmud on 03/30/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

// from Mike Mirzayanov's lectures

#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX = 100005;

void calculate_ZFunction(int *z, string s) {
    int N = (int)s.size();
    int l = 0;
    int r = 0;
    for (int i = 0; i < N; i ++) z[i] = 0;
    for (int i = 1; i < N; i ++) {
        if (r >= i) z[i] = min(z[i - l], r - i + 1);
        while (z[i] + i < N && s[z[i]] == s[z[i] + i]) z[i] ++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}
void calculate_PrefixFunction(int *b, string s) {
    int N = (int)s.size();
    for (int i = 0; i < N; i ++) b[i] = 0;
    for (int i = 1; i < N; i ++) {
        int k = b[i - 1];
        while (k > 0 && s[k] != s[i]) k = b[k - 1];
        if (s[k] == s[i]) b[i] = k + 1;
    }
}
void KMP(string text, string pattern) {
    int N = (int)text.size();
    int M = (int)pattern.size();
    int b[MAX];
    calculate_PrefixFunction(b, pattern);
    
    int k = 0;
    for (int i = 0; i < N; i ++) {
        while (k > 0 && pattern[k] != text[i]) k = b[k - 1];
        if (pattern[k] == text[i]) {
            k ++;
            if (k == M) {
                cout << "occurrence ends in " << i << endl;
                k = b[k - 1];
            }
        }
    }
}

int z[MAX];

int main() {
    string s;
    cin >> s;
    int N = (int)s.size();
    calculate_ZFunction(z, s);
    for (int i = 0; i < N; i ++) cout << z[i] << ", "; cout << endl;
    
    
    return 0;
}

//
//  main.cpp
//  practice
//
//  Created by Mahmud on 6/04/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 10001;

string add(string a, string b) {
    string c = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int q = 0;
    while (i >= 0 || j >= 0) {
        int sum = q;
        if (i >= 0) sum += a[i] - '0';
        if (j >= 0) sum += b[j] - '0';
        if (sum > 9) {
            sum -= 10;
            q = 1;
        }
        else {
            q = 0;
        }
        i --;
        j --;
        c += (char)(sum + '0');
    }
    if (q > 0) {
        c += (char)('1');
    }
    reverse(c.begin(), c.end());
    return c;
}
string subtract(string a, string b) {
    string c = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int r = 0;
    while (i >= 0) {
        int difference = a[i] - '0' - r;
        if (j >= 0) {
            difference -= b[j] - '0';
        }
        if (difference < 0) {
            difference += 10;
            r = 1;
        }
        else {
            r = 0;
        }
        i --;
        j --;
        c += (char)(difference + '0');
    }
    while ((int)c.size() > 1 && c.back() == '0') {
        c.pop_back();
    }
    reverse(c.begin(), c.end());
    return c;
}
int compare(string a, string b) {
    int l1 = (int)a.size();
    int l2 = (int)b.size();
    if (l1 > l2) return 1;
    if (l1 < l2) return -1;
    for (int i = 0; i < l1; i ++) {
        if (a[i] > b[i]) return 1;
        if (a[i] < b[i]) return -1;
    }
    return 0;
}
string divide(string a, int b) {
    string c = "";
    int q = 0;
    for (int i = 0; i < (int)a.size(); i ++) {
        q = 10 * q + a[i] - '0';
        int r = q / b;
        q %= b;
        if (r > 0 || !c.empty()) {
            c += (char)(r + '0');
        }
    }
    if (c.empty()) c = "";
    return c;
}

int main() {
    
    return 0;
}

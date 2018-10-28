//
//  main.cpp
//  practice
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

/*
 Karatsuba multiplication in O(N^(log2(3))) ~ N^1.58
 Please, refer to https://en.wikipedia.org/wiki/Karatsuba_algorithm
  to see the inner mechanism in the algorithm.
 Some for loops and operations can be replaced with builtin functions for speedup.
 */

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef string number;

bool isZero(number &a) {
    for (auto ch: a) {
        if (ch != '0') {
            return false;
        }
    }
    return true;
}
number add(number a, number b) { // addition of two numbers in linear time
    string sum = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int r = 0;
    while (i >= 0 || j >= 0) {
        int state = r;
        if (i >= 0) state += a[i] - '0';
        if (j >= 0) state += b[j] - '0';
        if (state > 9) {
            state -= 10;
            r = 1;
        } else {
            r = 0;
        }
        i --;
        j --;
        sum += (char)(state + '0');
    }
    if (r > 0) {
        sum += (char)(r + '0');
    }
    while ((int)sum.size() > 1 && sum.back() == '0') {
        sum.pop_back();
    }
    reverse(sum.begin(), sum.end());
    return sum;
}
string subtract(number a, number b) { // assuming a >= b, subtraction in linear time
    string difference = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int r = 0;
    while (i >= 0) {
        int state = a[i] - '0' - r;
        if (j >= 0) {
            state -= b[j] - '0';
        }
        if (state < 0) {
            state += 10;
            r = 1;
        } else {
            r = 0;
        }
        i --;
        j --;
        difference += (char)(state + '0');
    }
    while ((int)difference.size() > 1 && difference.back() == '0') {
        difference.pop_back();
    }
    reverse(difference.begin(), difference.end());
    return difference;
}
void split(number &a, number &l, number &r) {
    int length = (int)a.size();
    int half = length >> 1;
    l = a.substr(0, half);
    r = a.substr(half);
}
void normalize(number &a, number &b) { // making the lengths equal to 2's power
    int la = (int)a.size();
    int lb = (int)b.size();
    int to = -1;
    for (int i = 0; ; i ++) {
        if ((1 << i) >= la && (1 << i) >= lb) {
            to = (1 << i);
            break;
        }
    }
    if (la < to) {
        reverse(a.begin(), a.end());
        while (la < to) {
            a += '0';
            la ++;
        }
        reverse(a.begin(), a.end());
    }
    if (lb < to) {
        reverse(b.begin(), b.end());
        while (lb < to) {
            b += '0';
            lb ++;
        }
        reverse(b.begin(), b.end());
    }
    
}
void insertTrailingZeros(number &a, int z) {
    for (int i = 0; i < z; i ++) {
        a += '0';
    }
}
string defaultMultiplier(number a, number b) {
    int aValue = stoi(a);
    int bValue = stoi(b);
    return to_string(aValue * bValue);
}
number karatsuba(number a, number b) {
    if ((int)a.size() < 3) { // if small string lengths achieved, use integer multiplication
        return defaultMultiplier(a, b);
    }
//    if (isZero(a) || isZero(b)) {
//        return "0";
//    }
    normalize(a, b);
    string leftA, rightA;
    string leftB, rightB;
    split(a, leftA, rightA);
    split(b, leftB, rightB);
    string p1 = karatsuba(leftA, leftB);
    string p2 = karatsuba(rightA, rightB);
    string aSum = add(leftA, rightA);
    string bSum = add(leftB, rightB);
    string p3 = karatsuba(aSum, bSum);
    string p4 = subtract(subtract(p3, p1), p2);
    insertTrailingZeros(p1, (int)a.size());
    insertTrailingZeros(p4, (int)a.size() >> 1);
    return add(p1, add(p2, p4));
}
number multiply(number a, number b) {
//    considering that this code assumes only positive numbers,
//    you can handle negative numbers as well (even big decimals).
    return karatsuba(a, b);
}

int main(int argc, const char * argv[]) {
    string a, b;
    cin >> a >> b;
    cout << multiply(a, b) << endl;
    while (1) {
        
    }
    return 0;
}

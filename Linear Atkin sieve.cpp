//
//  main.cpp
//  practice
//
//  Created by Mahmud on 12/24/17.
//  Copyright © 2017 Mahmud. All rights reserved.
//

/// Atkin's linear sieve algorithm
/// reference: https://en.wikipedia.org/wiki/Sieve_of_Atkin


#include <iostream>
#include <cmath>
#include <ctime>
#include <cassert>

using namespace std;

const int LIMIT = 1000000001;
const int SQUARE_COUNT = 40005;
const int WHEEL = 60;
const int WHEEL_SIZE = 16;

char prime[LIMIT];
int s[] = {1, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 49, 53, 59}; // generating wheel
int Modulos1[] = {1, 13, 17, 29, 37, 41, 49, 53};
int Modulos2[] = {7, 19, 31, 43};
int Modulos3[] = {11, 23, 47, 59};
int activeModulos1[WHEEL];
int activeModulos2[WHEEL];
int activeModulos3[WHEEL];
int squares[SQUARE_COUNT]; // may need

int main() {
    for (int i = 0; i < sizeof(Modulos1) / sizeof(int); i ++) activeModulos1[Modulos1[i]] = 1;
    for (int i = 0; i < sizeof(Modulos2) / sizeof(int); i ++) activeModulos2[Modulos2[i]] = 1;
    for (int i = 0; i < sizeof(Modulos2) / sizeof(int); i ++) activeModulos3[Modulos3[i]] = 1;
    
    //for (int i = 1; i < SQUARE_COUNT; i ++) squares[i] = i * i;
    //fill(prime, prime + LIMIT, 1);
    //    for (int w = 0, N; w * WHEEL < LIMIT; w ++) {
    //        for (int j = 0; j < WHEEL_SIZE && (N = w * WHEEL + s[j]) < LIMIT; j ++) {
    //            prime[w * WHEEL + s[j]] = 0;
    //        }
    //    }
    cerr << "done in: " << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    for (int x = 1, N, M = 4; M < LIMIT; x ++, M = 4 * x * x) {
        for (int y = 1; (N = M + y * y) < LIMIT; y += 2) {
            if (activeModulos1[N % WHEEL]) prime[N] ^= 1;
        }
    }
    cerr << "done in: " << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    for (int x = 1, N, M = 3; M < LIMIT; x += 2, M = 3 * x * x) {
        for (int y = 2; (N = M + y * y) < LIMIT; y += 2) {
            if (activeModulos2[N % WHEEL]) prime[N] ^= 1;
        }
    }
    cerr << "done in: " << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    for (int x = 2, N, M = 12; M - (x - 1) * (x - 1) < LIMIT; x ++, M = 3 * x * x) {
        for (int y = x - 1; y > 0 && (N = M - y * y) < LIMIT; y -= 2) {
            if (activeModulos3[N % WHEEL]) prime[N] ^= 1;
        }
    }
    cerr << "done in: " << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    for (int w = 0, N; (w * WHEEL) * (w * WHEEL) < LIMIT; w ++) {
        for (int x = 0; x < WHEEL_SIZE; x ++) {
            N = WHEEL * w + s[x];
            if (N < 7 || !prime[N]) continue;
            for (int c = N * N; c < LIMIT; c += N * N) prime[c] = 0;
        }
    }
    cerr << "done in: " << 1.0 * clock() / CLOCKS_PER_SEC << endl;
    return 0;
    int cnt = 3;
    cout << 2 << endl;
    cout << 3 << endl;
    cout << 5 << endl;
    for (int w = 0, N; w * WHEEL < LIMIT; w ++) {
        for (int j = 0; j < WHEEL_SIZE && (N = w * WHEEL + s[j]) < LIMIT; j ++) {
            if (prime[WHEEL * w + s[j]]) cnt ++;
        }
    }
    cout << "number of primes = " << cnt << endl;
    
    
    return 0;
}

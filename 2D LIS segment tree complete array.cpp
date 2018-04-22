//
//  main.cpp
//  practice
//
//  Created by Mahmud on 04/18/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#pragma GCC optimize("-0g")

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

const int MAX = 100005;

int values[MAX * 75] = {-1};
int leftChildID[MAX * 75];
int rightChildID[MAX * 75];
int offset = 0;

int N, Nx, Ny;
int x[MAX], y[MAX];
int roots[MAX];
int dp[MAX];

void update(int rootID, int low, int high, int position, int value) {
    if (values[low] == -1) return;
    if (low == high) {
        values[rootID] = value;
        return;
    }
    int middle = (low + high) >> 1;
    if (position <= middle) {
        if (leftChildID[rootID] == 0) {
            leftChildID[rootID] = ++offset;
            values[offset] = 0;
        }
        update(leftChildID[rootID], low, middle, position, value);
    }
    else {
        if (rightChildID[rootID] == 0) {
            rightChildID[rootID] = ++offset;
            values[offset] = 0;
        }
        update(rightChildID[rootID], middle + 1, high, position, value);
    }
    values[rootID] = max(values[leftChildID[rootID]], values[rightChildID[rootID]]);
}
int get(int rootID, int low, int high, int l, int r) {
    if (values[rootID] == -1) return 0;
    if (low > r || high < l) return 0;
    if (low >= l && high <= r) return values[rootID];
    int middle = (low + high) >> 1;
    int q1 = get(leftChildID[rootID], low, middle, l, r);
    int q2 = get(rightChildID[rootID], middle + 1, high, l, r);
    return q1 > q2 ? q1 : q2;
    //return max(get(pool[root.leftChildID], low, middle, l, r),
    //           get(pool[root.rightChildID], middle + 1, high, l, r));
}
void outerUpdate(int position, int innerPosition, int value) {
    for ( ; position <= Nx; position += (position & -position)) {
        if (values[roots[position]] == -1) {
            roots[position] = ++offset;
            values[roots[position]] = 0;
        }
        update(roots[position], 1, Ny, innerPosition, value);
    }
}
int outerGet(int position, int innerL, int innerR) {
    int s = 0;
    for ( ; position > 0; position -= (position & -position)) {
        int current = get(roots[position], 1, Ny, innerL, innerR);
        if (current > s) s = current;
    }
    return s;
}

template <class T>
void fastInput(T &N) {
    char ch;
    int sign = 1;
    N = 0;
    while ((ch = getchar_unlocked()) && ch == ' ') {};
    if (ch == '-') sign = -1;
    else if (isdigit(ch)) N = ch - '0';
    while ((ch = getchar_unlocked()) && isdigit(ch)) {
        N = (N << 1) + (N << 3) + ch - '0';
    }
    if (sign == -1) N = ~N + 1;
}
/**** FAST IO ****/
inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x );
inline void writeWord( const char *s );

/** Read */

static const int buf_size = 4096;

inline int getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}

inline int readChar() {
    int c = getChar();
    while (c <= 32)
        c = getChar();
    return c;
}

template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
    if (write_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}

template <class T>
inline void writeInt( T x, char end ) {
    if (x < 0)
        writeChar('-'), x = -x;
    
    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}

inline void writeWord( const char *s ) {
    while (*s)
        writeChar(*s++);
}

struct Flusher {
    ~Flusher() {
        if (write_pos)
            fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;

int main() {
    //scanf("%d", &N);
    N = readInt();
    //fastInput(N);
    //for (int i = 1; i <= N; i ++) scanf("%d%d", &x[i], &y[i]);
    for (int i = 1; i <= N; i ++) {
        //fastInput(x[i]);
        //fastInput(y[i]);
        x[i] = readInt();
        y[i] = readInt();
    }
    vector<int> values = vector<int> (x + 1, x + N + 1);
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for (int i = 1; i <= N; i ++) {
        x[i] = (int)(lower_bound(values.begin(), values.end(), x[i]) - values.begin()) + 1;
    }
    Nx = (int)values.size();
    values = vector<int> (y + 1, y + N + 1);
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    for (int i = 1; i <= N; i ++) {
        y[i] = (int)(lower_bound(values.begin(), values.end(), y[i]) - values.begin()) + 1;
    }
    Ny = (int)values.size();
    
    int result = 0;
    for (int i = 1; i <= N; i ++) {
        dp[i] = outerGet(x[i] - 1, 1, y[i] - 1) + 1;
        //cout << i << " --> " << x[i] << " " << y[i] << endl;
        //cout << i << " " << dp[i] << endl;
        if (dp[i] > result) result = dp[i];
        outerUpdate(x[i], y[i], dp[i]);
    }
    cout << result << endl;
    
    return 0;
}

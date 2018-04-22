#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define _INFINITY 1 << 30
#define M 1000001


/*
 Maximum Sum Subarray Problem
 O(N * log(N)) solution with divide & conquer
 */

using namespace std;

int n, i, j, k;
int a[M];
char ch;

int FindMaxCrossingSubarray(int A[M], int low, int mid, int high)
{
    int leftsum = -_INFINITY;
    int sum = 0;
    int maxleft, maxright;
    for(i = mid ; i >= low ; i --)
    {
        sum = sum + A[i];
        if(sum > leftsum)
        {
            leftsum = sum;
            maxleft = i;
        }
    }
    int rightsum = -_INFINITY;
    sum = 0;
    for(j = mid + 1 ; j <= high ; j ++)
    {
        sum = sum + A[j];
        if(sum > rightsum)
        {
            rightsum = sum;
            maxright = j;
        }
    }
    return (maxleft,maxright, leftsum + rightsum);
}
int FindMaximumSubarray(int A[M], int low, int high)
{
    if(high == low) {
        return (low, high, A[low]);
    }
    else {
        int mid = (low + high) / 2;
        int crosslow, crosshigh, crosssum;
        int leftlow, lefthigh, leftsum, rightsum, rightlow, righthigh;
        
        (leftlow, lefthigh, leftsum) = FindMaximumSubarray(A, low, mid);
        (rightlow, righthigh, rightsum) = FindMaximumSubarray(A, mid + 1, high);
        (crosslow, crosshigh, crosssum) = FindMaxCrossingSubarray(A, low, mid, high);
        
        if(leftsum >= rightsum && leftsum >= crosssum)
            return (leftlow, lefthigh, leftsum);
        else if(rightsum >= leftsum && rightsum >= crosssum)
            return (rightlow, righthigh, rightsum);
        else return (crosslow, crosshigh, crosssum);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    cout << FindMaximumSubarray(a, 1, n) << endl;
    
    return 0;
}

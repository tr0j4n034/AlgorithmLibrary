// Hacking quicksort solutions during competitions
// The code belongs to Halyavin (CF handle).

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>

std::vector<int> anti_sort(size_t n) {
  std::vector<int> res(2 * n + 1);
  std::iota(res.begin(), res.end(), 0);
  for (size_t i = n; i-- > 0;) {
    std::swap(res[2 * i + 1], res[i + n]);
  }
  return res;
}

void genB(std::ostream &out) {
  std::vector<int> gen = anti_sort(49999);
  int n = gen.size();
  out << n  << std::endl;
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      out << " ";
    }
    out << gen[i] + 1;
  }
  out << std::endl;
}

int main() {
  std::cin.sync_with_stdio(false);
  std::cin.tie(nullptr);
  genB(std::cout);
  return 0;
}



//// hacked solution:
#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b){
	return *(const long long int*)a - *(const long long int *)b;
}


int main(void){
	long long int n,i,j,sum,ans;
	long long int arr[100005];
	scanf("%lli",&n);
	for(i = 0; i < n; i++){
		scanf("%lli",&arr[i]);
	}
	qsort(arr,n,sizeof arr[0],cmpfunc);
	ans = 0;
	for(i = 1; i <= 35; i++){
		sum = 1LL << i;
		for(j = 0; j < n - 1; j++){
			if(arr[j] >= sum){
				break;
			}
			else{
				long long int start,middle,end,front,back;
				long long int target = sum - arr[j];
//				printf("%lli %lli %lli\n",sum,arr[j],target);
				start = j + 1;
				end = n - 1;
				if(arr[start] <= target && arr[end] >= target){
					if(arr[start] == target){
						front = start;
					}
					else{
						while(start < end - 1){
							middle = (start + end)/2;
							if(arr[middle] < target){
								start = middle;
							}
							else{
								end = middle;
							}
						}
						if(arr[start+1] == target){
							front = start + 1;
						}
					}
					if(arr[n-1] == target){
						back = n-1;
					}
					else{
						back = n-1;
						start = front;
						while(start < back - 1){
							middle = (start + back)/2;
							if(arr[middle] > target){
								back = middle;
							}
							else{
								start = middle;
							}
						}
						back--;
					}
					if(arr[front] == target){
						ans += back - front +1;
					}
//					printf("%lli %lli %lli %lli\n",target,j,front,back);
				}
			}
		}
	}
	printf("%lli\n",ans);
}

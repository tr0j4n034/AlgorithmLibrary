# Implementations for some most used algorithms
Codes have mostly been written in C++. Please, consider compiling the code using C++11 or higher to avoid any compilation issues or warnings.

The list of implemented algorithms:
1. 2D Fenwick tree implementation using static arrays.
    - Point updates or range queries are handled in O(log^2(N)).
    - ~5x faster than pointer implementation
2. Finding Articulation points and bridges of graphs
    - Linear time implementation
3. Binary trie using static arrays
    - Implementation can be modified for larger alphabets
    - ~4x faster than pointer implementation
4. Building Cartesian trees in linear time
5. Finding the closest points in a set of 2D points in O(N * log(N))
6. Decart tree with data references
    - Please, refer to the problem on the link in the file to understand what type of queries need to be handled
    - Expected O(log(N)) time approach to handle standard BST operations
    - Extra tree and dynamic array operations
7. Dijkstra with Min-Heap:
    - Manual implementation of the heap
8. Finding dynamic median:
    - Logarithmic solution to find median during series of update operations
9. Fast ternary search
    - O(log(2)(N)) performance instead of classic O(log(3/2)(N))
10. Fibonacci matrix
    - 2x2 matrix implementation to calculate N-th Fibonacci number in O(log(N))
11. Implicit segment tree implementation
    - It's pointer implementation, using the same approach in [1], static array implementation can be produced.
    - Update/Ask queries in O(log(RANGE))
12. Johnson's all pairs shortest path problem
    - O(V * E * log(V)) overall complexity
    - Bellman-Ford algorithm is used to detect negative cycle(if any).
13. Karatsuba multiplication in O(N^1.58)
    - multiplication of large integers (big integer in CP)
    - Although FFT is O(N * log(N)), Karatsuba is handy when you do not have prewritten FFT code.
14. Kruskal Minimal Spanning Tree Algorithm in O(E * log(V))
    - Union/Find data structure
15. Atkin's prime sieve in O(N)
    - Atkin's wheel ("WHEEL" variable in the code) can be adjusted
16. Linear prime sieve
17. MO's algorithm
    - Offline query handling
18. Finding farthest points based on Manhattan distance in 2D grid 
    - O(N * log2(N))
    - can be extended to larger dimensions O(N * 2^d * log2(N))
19. Miller-Rabin primality test
20. Ordered set - Decart tree
    - Just more powerful than a BST
21. Persistent segment tree implementation
    - static array implementation
    - finding Kth element in any sorted subarray of elements in O(log(N))
22. Hash table for comparing range of fixed objects
23. Rope - builtin decart tree
24. Basic String matching utilities
     - Z function
     - prefix function
     - KMP algorithm
25. Fast/ultrafast input & output for enermous input
    - getchar_unlocked() will probably produce some warnings (unsafe blabla...), you may replace it with getchar()
26. Multiplication bases and modulos for hash tables
27. A method to hack unordered_set solutions during competitions
    - The solution belongs to a coder who hacked my solution during one of Codeforces contests)
28. Quicksort hack by Halyavin
    - Some people still use qsort() function in C. The code produces adversary test cases.
29. Quadtree implementation for 2D aggregate queries

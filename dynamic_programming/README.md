# Dynamic Programming

Dynamic Programming (DP) is a problem-solving technique that solves complex problems by breaking them down into simpler subproblems and storing the results of subproblems to avoid redundant calculations. This approach optimizes recursive algorithms by eliminating overlapping subproblems.

## Algorithm Overview

Dynamic Programming is based on two key principles:

1. **Optimal Substructure**: The optimal solution to a problem contains optimal solutions to its subproblems
2. **Overlapping Subproblems**: The same subproblems are solved multiple times in a naive recursive approach

## DP Approaches

### 1. Memoization (Top-Down)
- Start with the original problem
- Break it down recursively  
- Store results in a cache/memo table
- Use cached results when the same subproblem reoccurs

### 2. Tabulation (Bottom-Up)
- Start with the smallest subproblems
- Build up solutions iteratively
- Store results in a table (usually an array)

## Implementation Examples

This directory contains three classic DP problems:

### 1. Climbing Stairs (Naive Recursion vs DP)

**Problem**: Count ways to reach the top of n stairs, taking 1 or 2 steps at a time.

```c
// Naive recursion - O(2^n) time
int climbing_stairs(int target) {
    if (target == 0) return 1;
    if (target == 1 || target == 2) return target;
    return climbing_stairs(target-1) + climbing_stairs(target-2);
}
```

This is equivalent to the Fibonacci sequence but with exponential time complexity due to repeated calculations.

### 2. Fibonacci (Optimized DP)

**Problem**: Calculate the nth Fibonacci number efficiently.

```c
// DP approach - O(n) time, O(1) space
int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    int res[2] = {0, 1};
    for (int i = 2; i <= n; i++) {
        int new = res[0] + res[1];
        res[1] = res[0];
        res[0] = new;
    }
    return res[0] + res[1];
}
```

### 3. Coin Change (Memoization)

**Problem**: Find minimum number of coins needed to make a target amount.

```c
// Memoized DP - O(target * num_coins) time
int coin_change(int target, int coins[], int num_coins, int cache[]) {
    if (target < 0) return -1;
    if (cache[target] != -1) return cache[target];  // Use cached result
    if (target == 0) {
        cache[target] = 0;
        return 0;
    }
    
    int result = INT_MAX;
    for (int i = 0; i < num_coins; i++) {
        int partial = coin_change(target-coins[i], coins, num_coins, cache);
        if (partial != -1) {
            result = min(result, 1 + partial);
        }
    }
    cache[target] = result;
    return result;
}
```

## Time Complexity Comparison

| Algorithm | Naive Recursion | DP Optimized |
|-----------|----------------|--------------|
| Fibonacci | O(2^n) | O(n) |
| Climbing Stairs | O(2^n) | O(n) |
| Coin Change | O(coins^target) | O(target × coins) |

## Space Complexity

| Approach | Space Complexity | Description |
|----------|------------------|-------------|
| Memoization | O(n) | Recursive call stack + cache |
| Tabulation | O(n) | DP table storage |
| Space Optimized | O(1) | Only store necessary previous results |

## Usage Examples

### Fibonacci Example

```c
#include "dp.h"
#include <stdio.h>

int main() {
    int n = 10;
    int result = fibonacci(n);
    printf("Fibonacci of %d: %d\n", n, result);
    return 0;
}
```

### Coin Change Example

```c
#include "dp.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int coins[] = {1, 3, 4};
    int num_coins = 3;
    int target = 6;
    
    // Initialize cache with -1
    int* cache = malloc((target + 1) * sizeof(int));
    for (int i = 0; i <= target; i++) {
        cache[i] = -1;
    }
    
    int result = coin_change(target, coins, num_coins, cache);
    printf("Minimum coins needed for %d: %d\n", target, result);
    
    free(cache);
    return 0;
}
```

## Building and Testing

Compile and run:
```bash
gcc -o dp dp.c
./dp
```

## Common DP Patterns

### 1. Linear DP
- **Examples**: Fibonacci, Climbing Stairs, House Robber
- **Pattern**: `dp[i] = f(dp[i-1], dp[i-2], ...)`

### 2. Grid DP  
- **Examples**: Unique Paths, Minimum Path Sum
- **Pattern**: `dp[i][j] = f(dp[i-1][j], dp[i][j-1])`

### 3. Interval DP
- **Examples**: Matrix Chain Multiplication, Palindrome Partitioning
- **Pattern**: `dp[i][j] = min/max over k (dp[i][k] + dp[k+1][j])`

### 4. Tree DP
- **Examples**: Maximum Path Sum, House Robber III
- **Pattern**: Process children before parent

## When to Use Dynamic Programming

Consider DP when you have:

1. **Overlapping Subproblems**: Same calculations repeated
2. **Optimal Substructure**: Optimal solution built from optimal subsolutions  
3. **Exponential Naive Solution**: Recursive solution with exponential time
4. **Decision Making**: Choosing optimal actions at each step

## Advantages

- **Efficiency**: Reduces exponential algorithms to polynomial time
- **Systematic**: Clear framework for solving optimization problems
- **Reusable**: Solutions to subproblems can be reused
- **Optimal**: Guarantees optimal solution when applicable

## Disadvantages

- **Memory**: Requires additional space for storing subproblem results
- **Complexity**: Can be difficult to identify DP structure
- **Overhead**: May be overkill for simple problems
- **Not Always Applicable**: Not all problems have optimal substructure

## Applications

Dynamic Programming is commonly used in:

- **Algorithm Optimization**: Converting recursive solutions
- **Computer Graphics**: Shortest path algorithms
- **Bioinformatics**: DNA sequence alignment
- **Economics**: Resource allocation problems
- **Game Theory**: Optimal strategy determination
- **Machine Learning**: Sequence modeling, reinforcement learning
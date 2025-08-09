#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int climbing_stairs(int target) {
    // THIS IS NOT DP. This is a sample of naive recursion to introduce DP.
    // Base cases: target = 0, target = 1, target = 2
    if (target == 0) {
        // We're done
        return 1;
    }
    if (target == 1 || target == 2) {
        // If target is 1, only 1 way to reach.
        // If target is 2, 2 ways (1+1 or 2 straight)
        return target;
    }
    // Else, we need to do some recursion.
    
    return climbing_stairs(target-1) + climbing_stairs(target-2);
}

// NOTE: See the return for climbing_stairs? It's fibonacci with naive recursion.
// Meaning, this function could be optimized by avoiding repeated work.
// That is what DP is about. See fibonacci(int n) below:

int fibonacci(int n) {
    // Gets the fibonacci sequence for n iterations.
    // e.g 1 is 1 (1), 2 is 1 (), 3 is 2, 4 is 5, so on.
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    // Avoid repeating work. Create array to store the values.
    int res[2];
    res[0] = 0;
    res[1] = 1;
    for (int i = 2; i <= n; i++) {
        int new = res[0] + res[1];
        // Update previous vals
        res[1] = res[0];
        res[0] = new;
    }
    // Fibonacci is always the sum of the previous two.
    return res[0] + res[1];
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int coin_change(int target, int coins[], int num_coins, int cache[]) {
    if (target < 0) {
        // Ignore, as you went overboard.
        return -1;
    }
    // Check if we have it in our cache
    // If it's there, don't bother with the rest.
    if (cache[target] != -1) {
        return cache[target];
    }
    // Base case for recursion.
    if (target == 0) {
        // Found solution.
        cache[target] = 0;
        return 0;
    }
    int result = INT_MAX;
    for (int i = 0; i < num_coins; i++) {
        int partial = coin_change(target-coins[i], coins, num_coins, cache);
        if (partial != -1) {
            result = min(result, 1+partial);
        }
    }
    cache[target] = result;
    return result;
}

int main() {

    for (int tgt = 0; tgt < 10; tgt++){
        int res = climbing_stairs(tgt);
        printf("Result for %d: %d\n", tgt, res);
    }
    
    return 0;
}
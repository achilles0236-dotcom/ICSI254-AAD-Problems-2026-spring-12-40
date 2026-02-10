#include <stdio.h>

#define MOD 998244353

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    long long palindrome_count[n + 1];
    
    for (int len = 1; len <= n; len++) {
        int free_positions = (len + 1) / 2;
        palindrome_count[len] = power(k, free_positions, MOD);
    }
    
    long long prefix_sum[n + 1];
    prefix_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = (prefix_sum[i - 1] + palindrome_count[i]) % MOD;
    }
    
    long long total = 0;
    
    for (int len = 1; len <= n; len++) {
        long long count = palindrome_count[len];
        
        long long concat_count = 0;
        for (int i = 1; i < len; i++) {
            long long pairs = (palindrome_count[i] * palindrome_count[len - i]) % MOD;
            concat_count = (concat_count + pairs) % MOD;
        }
        
        
        long long overcount = ((len - 1) * palindrome_count[len]) % MOD;
        concat_count = (concat_count - overcount + MOD) % MOD;
        
        count = (count + concat_count) % MOD;
        total = (total + count) % MOD;
    }
    
    printf("%lld\n", total);
    
    return 0;
}

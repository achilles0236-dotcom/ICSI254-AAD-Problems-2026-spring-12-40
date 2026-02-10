#include <stdio.h>

#define MOD 998244353

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;

    static long long g[100005];

    for (int i = 1; i <= n; i++) {
        g[i] = power(k, (i + 1) / 2);
    }

    
    for (int i = 1; i <= n; i++) {
        for (int j = 3 * i; j <= n; j += 2 * i) {
            g[j] = (g[j] - g[i] + MOD) % MOD;
        }
    }

    
    long long total_ans = 0;
    for (int d = 1; d <= n; d++) {
        long long contribution = (1LL * d * g[d]) % MOD;
        
        long long count = (n / d + 1) / 2;
        
        long long added_value = (contribution * (count % MOD)) % MOD;
        total_ans = (total_ans + added_value) % MOD;
    }

    printf("%lld\n", total_ans);

    return 0;
}

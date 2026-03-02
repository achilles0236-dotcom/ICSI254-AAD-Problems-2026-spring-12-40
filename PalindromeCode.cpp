#include <iostream>
#include <vector>
using namespace std;

static const long long MOD = 998244353LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    if (!(cin >> n >> k)) return 0;

    vector<int> mu(n + 1, 0), primes;
    vector<char> isComp(n + 1, 0);
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!isComp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > n) break;
            isComp[(int)v] = 1;
            if (i % p == 0) {
                mu[(int)v] = 0;
                break;
            }
            mu[(int)v] = -mu[i];
        }
    }

    vector<long long> pw(n + 2, 1);
    long long km = k % MOD;
    for (int i = 1; i <= n + 1; ++i) pw[i] = pw[i - 1] * km % MOD;

    const long long inv2 = (MOD + 1) / 2;

    vector<long long> A(n + 1, 0);
    for (int m = 1; m <= n; ++m) {
        if (m & 1) {
            A[m] = pw[(m + 1) / 2];
        } else {
            A[m] = pw[m / 2] * ((k + 1) % MOD) % MOD * inv2 % MOD;
        }
    }

    vector<long long> a(n + 1, 0);
    for (int d = 1; d <= n; ++d) {
        if (mu[d] == 0) continue;
        for (int t = 1; d * t <= n; ++t) {
            int m = d * t;
            if (mu[d] == 1) a[m] += A[t];
            else a[m] -= A[t];
            if (a[m] >= MOD) a[m] -= MOD;
            if (a[m] < 0) a[m] += MOD;
        }
    }

    vector<long long> D(n + 1, 0);
    for (int d = 1; d <= n; ++d) {
        long long add = (1LL * d * a[d]) % MOD;
        if (add == 0) continue;
        for (int m = d; m <= n; m += d) {
            D[m] += add;
            if (D[m] >= MOD) D[m] -= MOD;
        }
    }

    long long ans = 0;
    for (int L = 1; L <= n; ++L) {
        ans += D[L];
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << '\n';
    return 0;
}

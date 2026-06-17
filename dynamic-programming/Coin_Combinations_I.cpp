#include <iostream>
#include <vector>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;

ll coinCombinations(const vector<int>& coins, const int x) {
    vector<ll> dp(x + 1, 0);
    dp[0] = 1;

    for (int sum = 1; sum <= x; ++sum) {
        for (int coin : coins) {
            if (sum >= coin) dp[sum] = (dp[sum] + dp[sum - coin]) % MOD;
        }
    }

    return dp[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<int> coins;
    coins.reserve(n);
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        coins.push_back(temp);
    }

    cout << coinCombinations(coins, x);

    return 0;
}
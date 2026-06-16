#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int minimizeCoins(const vector<int>& coins, const int x) {
    vector<int> dp(x + 1, -1);
    int minCoin = *min_element(coins.begin(), coins.end());
    if (minCoin > x) return -1;

    for (int coin : coins) {
        if (coin == x) return 1; 
        dp[coin] = 1;
    }

    for (int sum = minCoin; sum <= x; ++sum) {
        if (dp[sum] == -1) continue;
        for (int coin : coins) {
            int newSum = sum + coin;
            if (newSum > x) continue;
            dp[newSum] = min(dp[newSum], dp[sum] + 1);
            if (dp[newSum] == -1) dp[newSum] = dp[sum] + 1;
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

    cout << minimizeCoins(coins, x);

    return 0;
}
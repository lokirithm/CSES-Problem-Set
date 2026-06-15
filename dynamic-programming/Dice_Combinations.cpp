#include <iostream>
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;

ll diceCombinations(int n) {
    ll ways[6] = {1, 1, 2, 4, 8, 16};
    ll prev = 32;

    for (int i = 6; i <= n; ++i) {
        ll temp = ways[(i + 6) % 6];
        ways[(i + 6) % 6] = prev;
        prev = (prev + ways[(i + 6) % 6] - temp + MOD) % MOD;
    }
    
    return ways[(n + 6) % 6];
}

int main() {
    int n;
    cin >> n;
    cout << diceCombinations(n) << "\n";
    return 0;
}
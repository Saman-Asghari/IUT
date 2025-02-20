#include <iostream>
#include<vector>
using namespace std;

const int MAX_N = 303;
const int MOD = 1000 * 1000 * 1000 + 7;

int dp[MAX_N][MAX_N];

int main()
{
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++)
        cin >> h[i];

    for (int i = 0; i < n; i++)
        dp[i][i] = 1;
    for (int i = 1; i < n; i++)
        dp[i - 1][i] = 1 + (h[i - 1] == h[i]);
    for (int d = 2; d < n; d++)
    {
        for (int i = 0; i < n - d; i++)
        {
            int j = i + d;
            if (h[i] != h[j])
                dp[i][j] = dp[i][j - 1];
            else
            {
                dp[i][j] = dp[i][j - 1] + 1;
                for (int k = i + 1; k < j; k++)
                    if (h[k] >= h[i])
                        dp[i][j] = (dp[i][j] + dp[k][j - 1]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = (ans + dp[i][n - 1]) % MOD;

    cout << ans << '\n';
    return 0;
}

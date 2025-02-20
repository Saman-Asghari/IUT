#include<iostream>
using namespace std;

const int MAXN = 101, MAXA = 2e5 + 1, MOD = 1e9 + 7;
int dp[2][MAXA], ps[2][MAXA];

int get(int i, int l, int r)
{
    if (l == 0)
        return ps[i][r];
    return (ps[i][r] - ps[i][l - 1]) % MOD;
}

int main()
{
    int n, d;
    cin >> n >> d;

    for (int i = 0; i <= d; i++)
        dp[0][i] = 1;

    ps[0][0] = dp[0][0];
    for (int j = 1; j < MAXA; j++)
        ps[0][j] = (ps[0][j - 1] + dp[0][j]) % MOD;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < MAXA; j++)
            dp[i & 1][j] = get((i - 1) & 1, max(j - d, 0), min(MAXA - 1, j + d));

        ps[i & 1][0] = dp[i & 1][0];
        for (int j = 1; j < MAXA; j++)
            ps[i & 1][j] = (ps[i & 1][j - 1] + dp[i & 1][j]) % MOD;
    }

    cout << (ps[(n - 1) & 1][MAXA - 1] + MOD) % MOD << endl;
    return 0;
}
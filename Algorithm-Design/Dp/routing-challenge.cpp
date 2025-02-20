#include<iostream>
using namespace std;

const long long INF = 1e18;
const int MAXN = 2000 + 1;

int n, m, a[MAXN][MAXN];
long long dp[MAXN][MAXN][2];

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    dp[0][0][0] = dp[0][0][1] = a[0][0];
    for (int i = 1; i < m; i++)
    {
        dp[0][i][1] = dp[0][i - 1][1] + a[0][i];
        dp[0][i][0] = INF;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (j == 0)
                dp[i][j][1] = a[i][j] + min(dp[i - 1][j][0], dp[i - 1][j][1]);
            else
                dp[i][j][1] = a[i][j] + min(min(dp[i - 1][j][0], dp[i - 1][j][1]), dp[i][j - 1][1]);

        for (int j = m - 1; j >= 0; j--)
            if (j == m - 1)
                dp[i][j][0] = a[i][j] + min(dp[i - 1][j][0], dp[i - 1][j][1]);
            else
                dp[i][j][0] = a[i][j] + min(min(dp[i - 1][j][0], dp[i - 1][j][1]), dp[i][j + 1][0]);
    }

    cout << dp[n - 1][m - 1][1] << endl;
    return 0;
}

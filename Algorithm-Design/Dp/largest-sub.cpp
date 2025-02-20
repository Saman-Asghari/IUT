#include <iostream>
using namespace std;

const int MAXN = 100 * 1000 + 10;

long long dp[MAXN];
int a[MAXN];
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        dp[i + 1] = max((long long)a[i], dp[i] + a[i]);

    long long ans = -1e18;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);

    cout << ans << endl;

    return 0;
}
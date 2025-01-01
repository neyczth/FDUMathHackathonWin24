#include <iostream>
#include <vector>
#include <cstdint>
#define MAXN 505
#define MOD 1000000007
using namespace std;

int64_t mat1[MAXN][MAXN] = {0}, mat2[MAXN][MAXN] = {0};
int64_t ans[MAXN][MAXN] = {0};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("K.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int n, p, m;
    cin >> n >> p >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            cin >> mat1[i][j];
    for (int i = 0; i < p; i++)
        for (int j = 0; j < m; j++)
            cin >> mat2[i][j];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < p; k++) {
                ans[i][j] += (mat1[i][k] % MOD) * (mat2[k][j] % MOD) % MOD;
                ans[i][j] = (ans[i][j] + MOD) % MOD;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << ans[i][j] << ' ';
        cout << endl;
    }

    return 0;
}
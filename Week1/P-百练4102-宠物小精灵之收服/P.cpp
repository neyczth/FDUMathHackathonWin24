#include <iostream>
#include <algorithm>
#define MAX_BALL 1005
#define MAX_HP 505
#define MAX_POKEMON 105
using namespace std;

int dp[MAX_BALL][MAX_HP][2] = {0};
int ball_num[MAX_POKEMON] = {0}, damage[MAX_POKEMON] = {0};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("P.in", "r", stdin);
    #endif

    // dp[n][m][k]: 用至多n个精灵球, 皮卡丘消耗体力m, 只考虑前k个精灵的最多收服数量
    // dp[n][m][k] = max(dp[n][m][k-1], dp[n-n[k]][m-m[k]][k-1]+1)
    int num_ball, num_hp, num_pokemon;
    cin >> num_ball >> num_hp >> num_pokemon;

    for (int k = 0; k < num_pokemon; k++)
        cin >> ball_num[k] >> damage[k];

    for (int i = 1; i <= num_ball; i++)
        for (int j = 1; j <= num_hp; j++)
            dp[i][j][0] = ((i >= ball_num[0]) && (j >= damage[0]));

    for (int k = 1; k < num_pokemon; k++)
        for (int i = 1; i <= num_ball; i++)
            for (int j = 1; j <= num_hp; j++) {
                int &&tmp = k&1;
                dp[i][j][tmp] = dp[i][j][tmp^1];
                if (i >= ball_num[k] && j >= damage[k])
                    dp[i][j][tmp] = max(dp[i][j][tmp], dp[i-ball_num[k]][j-damage[k]][tmp^1] + 1);
            }

    int &&tmp = (num_pokemon-1)&1;
    int max_pokemon = dp[num_ball][num_hp-1][tmp];
    int use_hp = num_hp-1;
    while (use_hp > 0 && dp[num_ball][use_hp-1][tmp] == max_pokemon) use_hp--;
    cout << max_pokemon << ' ' << num_hp - use_hp << endl;

    return 0;
 }
#include <iostream>
#include <cstring>
#define MAXN 105
#define INF 0x3f3f3f3f
using namespace std;

int dist[MAXN][MAXN] = {0};
int next_city_idx[MAXN][MAXN] = {0};
int city_tax[MAXN] = {0};
int num_city = 0;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("I.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    while (cin >> num_city) {
        if (!num_city) break;

        memset(next_city_idx, -1, sizeof(next_city_idx));
        for (int i = 1; i <= num_city; i++) {
            for (int j = 1; j <= num_city; j++) {
                cin >> dist[i][j];
                if (dist[i][j] == -1) dist[i][j] = INF;
                else next_city_idx[i][j] = j;
            }
        }

        for (int i = 1; i <= num_city; i++) cin >> city_tax[i];

        // Floyd
        for (int k = 1; k <= num_city; k++)
            for (int i = 1; i <= num_city; i++)
                for (int j = 1; j <= num_city; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j] + city_tax[k] ||
                        (dist[i][j] == dist[i][k] + dist[k][j] + city_tax[k] && next_city_idx[i][k] < next_city_idx[i][j])) {
                        dist[i][j] = dist[i][k] + dist[k][j] + city_tax[k];
                        next_city_idx[i][j] = next_city_idx[i][k];
                    }
                }
        
        int start_city = 0, end_city = 0;
        while (cin >> start_city >> end_city) {
            if (start_city == -1 && end_city == -1) break;

            cout << "From " << start_city << " to " << end_city << " :" << endl;
            cout << "Path: " << start_city;
            int cur_city = start_city;
            while (cur_city != end_city) {
                cur_city = next_city_idx[cur_city][end_city];
                cout << "-->" << cur_city;
            }
            cout << endl;
            cout << "Total cost : " << dist[start_city][end_city] << endl;
            cout << endl;
        }
    }

    return 0;
}
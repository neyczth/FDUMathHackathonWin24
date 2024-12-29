#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX_TREASURE 105
using namespace std;

class Treasure {
  public:
    int tot_weight = 0, tot_val = 0;
    double unit_val = 0.0f;

    Treasure(const int& _weight=0, const int& _val=0):
        tot_weight(_weight), tot_val(_val) {
        unit_val = (double)tot_val / tot_weight;
    }
};
vector<Treasure> treasure_list(MAX_TREASURE);

int main() {
    #ifndef ONLINE_JUDGE
        freopen("D.in", "r", stdin);
    #endif

    int num_test_case, num_treasure;
    int tot_weight, tot_val;
    double pack_volume, ans;
    scanf("%d", &num_test_case);
    while (num_test_case--) {
        ans = 0;

        scanf("%lf", &pack_volume);
        scanf("%d", &num_treasure);
        for (int i = 0; i < num_treasure; i++) {
            scanf("%d %d", &tot_weight, &tot_val);
            treasure_list[i] = Treasure(tot_weight, tot_val);
        }

        sort(treasure_list.begin(), treasure_list.begin() + num_treasure,
            [](const Treasure &t1, const Treasure &t2) {
                return t1.unit_val > t2.unit_val;
            });

        for (int i = 0; i < num_treasure && pack_volume > 0; i++) {
            Treasure &cur_treasure = treasure_list[i];
            if (pack_volume > cur_treasure.tot_weight) {
                ans += cur_treasure.tot_val;
                pack_volume -= cur_treasure.tot_weight;;
            }
            else {
                ans += cur_treasure.unit_val * pack_volume;
                pack_volume = 0;
            }
        }

        printf("%.2lf\n", ans);
    }

    return 0;
}
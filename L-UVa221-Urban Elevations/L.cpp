#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_BUILDING 105
using namespace std;

class Building {
  public:
    int x = 0, y = 0; // (x, y) is the coordinate of the southwest corner.
    int width = 0, height = 0;
    bool is_visible = false;
    int idx = 0;
};
vector<Building> building_list(MAX_BUILDING);
vector<int> x_coordinates(2*MAX_BUILDING);

bool cover(const Building& cur_b, const int &pos) {
    return cur_b.x <= pos && cur_b.x + cur_b.width >= pos;
}

bool is_blocked(const Building &a, const Building &b, const int &pos) {
    // Return: Is a blocked by b at pos?
    return cover(b, pos) && a.y > b.y && a.height <= b.height;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("L.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int test_cnt = 0, num_building;
    int depth;
    while (cin >> num_building) {
        test_cnt++;
        if (!num_building) break;
        for (auto &building : building_list) building.is_visible = false;
        
        for (int i = 0; i < num_building; i++) {
            Building &cur_b = building_list[i];
            cin >> cur_b.x >> cur_b.y >> cur_b.width >> depth >> cur_b.height;
            x_coordinates[2*i] = cur_b.x; x_coordinates[2*i+1] = cur_b.x + cur_b.width;
            cur_b.idx = i+1;
        }
        sort(x_coordinates.begin(), x_coordinates.begin() + 2*num_building);
        sort(building_list.begin(), building_list.begin() + num_building,
            [] (const Building& a, const Building &b) {
                return a.x < b.x || (a.x == b.x && a.y < b.y);
            });
        int num_unique_x = unique(x_coordinates.begin(), x_coordinates.begin() + 2*num_building) - x_coordinates.begin();
        for (int i = 0; i < num_unique_x-1; i++) {
            int &&mid_x = (x_coordinates[i] + x_coordinates[i+1]) / 2;
            for (int j = 0; j < num_building; j++) {
                if (building_list[j].is_visible == true) continue;
                if (!cover(building_list[j], mid_x)) continue;
                bool is_ok = true;
                for (int k = 0; k < num_building; k++) {
                    if (j != k && is_blocked(building_list[j], building_list[k], mid_x)) {
                        is_ok = false; break;
                    }
                }
                building_list[j].is_visible = is_ok;
            }
        }
        if (test_cnt > 1) cout << endl;
        cout << "For map #" << test_cnt << ", the visible buildings are numbered as follows:" << endl;
        bool first_output = true;
        for (int i = 0; i < num_building; i++) {
            if (building_list[i].is_visible) {
                if (!first_output) cout << ' ';
                first_output = false;
                cout << building_list[i].idx;
            }
        }
        cout << endl;
    }

    return 0;
}
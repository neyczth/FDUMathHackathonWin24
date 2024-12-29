#include <cstdio>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("B.in", "r", stdin);
    #endif

    double ans = 0;
    double x;
    for (int i = 0; i < 12; i++) {
        scanf("%lf", &x);
        ans += x;
    }
    ans /= 12;
    printf("$%.2f\n", ans);
    
    return 0;
}
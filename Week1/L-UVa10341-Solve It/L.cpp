#include <cstdio>
#include <cmath>
#define EPS 1e-10
using namespace std;

double cal_f(const double &x, const double &p, const double &q, const double &r, const double &s, const double &t, const double &u) {
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("L.in", "r", stdin);
    #endif

    double p, q, r, s, t, u;
    while (scanf("%lf %lf %lf %lf %lf %lf", &p, &q, &r, &s, &t, &u) != EOF) {
        auto f = [&](const double &x) { return cal_f(x, p, q, r, s, t, u); };
        double left = 0.0, right = 1.0;
        if (f(left) * f(right) > 0) { printf("No solution\n"); }
        else {
            while (right - left > EPS) {
                double &&mid = (left + right) / 2;
                if (f(mid) < 0.0) right = mid;
                else left = mid;
            }
            printf("%.4lf\n", (left + right) / 2);
        }
    }

    return 0;
}
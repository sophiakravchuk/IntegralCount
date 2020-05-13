#include <vector>
#include <cmath>

double function_x(double x1, double x2, int m, std::vector<int> a1, std::vector<int> a2, std::vector<int> c) {
//    int m = 5;
//    std::vector<int> a1 {1, 2, 1, 1, 5};
//    std::vector<int> a2 {4, 5, 1, 2, 4};
//    std::vector<int> c {2, 1, 4, 7, 2};

    double y;
    double result = 0;
    for (int i= 0; i <= m; i++) {
        double argument = (pow(x1 - a1[i], 2) + pow(x2 - a2[i], 2));
        double curr_result = c[i] * exp((-1)/M_PI * argument) * cos(M_PI * argument);
        result += curr_result;
    }
    y = - result;
    return y;
}
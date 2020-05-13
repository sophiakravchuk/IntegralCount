#include <iostream>
#include "integral_count.cpp"
#include "time_measurement.cpp"


double checkErr(int x1, int x2, int y1, int y2, double abs_err,
        double rel_err, int am_threads, int m, std::vector<int> a1,
        std::vector<int> a2, std::vector<int> c, int stop_signal) {
    int n = 300;
    double diff_abs = 5.0;
    double diff_rel = 1.0;

    auto start_time = get_current_time_fenced();

    double area1 = intg(x1, x2, y1, y2, n, am_threads, m, a1, a2, c);
    double area2 = 0.0;
    while (diff_abs > abs_err or diff_rel > rel_err) {
        if (stop_signal == 0) {
            break;
        }
        n *= 2;

        area2 = intg(x1, x2, y1, y2, n, am_threads, m, a1, a2, c);
        diff_abs = std::abs(area2 - area1);
        diff_rel = diff_abs/area2;
        area1 = area2;
        stop_signal -= 1;
    }
    std::cout << "Area: " << area1 << std::endl;

    auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;

    std::cout << "Total time: " << to_us(total_time) << std::endl;
    if (stop_signal == 0) {
        std::cout << "Too many iterations" << std::endl;
    }
    return area2;
}

#include "function.cpp"
#include <mutex>
#include <thread>

std::mutex mtx;
double integral_all(double x1, double x2, int y1, int y2, int ny, int nx,double& area,
       int m, std::vector<int> a1, std::vector<int> a2, std::vector<int> c) {

    double step_x = (double)(x2 - x1)/nx;//ny*am_of_threads;  // width of each small rectangle
    double step_y = (double)(y2 - y1) /ny;  // height of each small rectangle
    double local_area = 0.0;  // signed area

    for (int i = 0; i < nx; i ++) {
        for (int j = 0; j < ny; j ++) {
            local_area += function_x((x1 + (i + 0.5) * step_x), (y1 + (j + 0.5) * step_y), m, a1, a2, c) * step_x * step_y; // sum up each small rectangle
        }
    }

    mtx.lock();
    area += local_area;
    mtx.unlock();
    return area;
}

double intg(int x1, int x2, int y1, int y2, int n, int am_threads, int m,
        std::vector<int> a1, std::vector<int> a2, std::vector<int> c) {

    std::vector<std::thread> vector_of_threads;
    vector_of_threads.reserve(am_threads);
    double area = 0.0;
    double thr_div_x = (double)(x2-x1)/am_threads;

    int nx = n/am_threads;
    for(int i = 0; i < am_threads; i++) {
        vector_of_threads.emplace_back(std::thread(integral_all,
                x1+(thr_div_x*i), x1+thr_div_x*(i+1),
                y1, y2, n, nx, std::ref(area), m, a1, a2, c));
    }
    for(auto& t: vector_of_threads) {
        t.join();
    }
//    std::cout << "n " << n << " Area " << area << std::endl;
    return area;
}



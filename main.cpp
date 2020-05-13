#include <iostream>
#include <vector>
#include <iterator>
#include "check_err.cpp"
#include "parsing_error.cpp"
#include "file_wr.cpp"


std::vector<int> from_str_to_int(std::string str1) {
    std::vector<std::string> vec1;
    std::vector<int> result;

    std::istringstream ss(str1);
    std::copy(std::istream_iterator<std::string>(ss),
              std::istream_iterator<std::string>(),
              std::back_inserter(vec1));

    for (std::string i: vec1) {
        result.push_back(std::stoi(i));
    }
    return result;

}

int main(int am, char** arr) {
    std::vector<std::string> ret;
    std::vector<int> a1, a2, c, lim_x, lim_y;
    double abs_err, rel_err;
    int am_threads, m, stop_signal;

    try {
        std::string file_name = arr[1];
        ret = reading_from_file(file_name);
        int am_threadsPar = std::stoi(arr[2]);

    if (ret.size() < 10 ) {
        throw MyParsingError("Not enough arguments in the input file");
    }
    else if (ret.size() > 10 ) {
        throw MyParsingError("Too many arguments in the input file");
    }
        a1 = from_str_to_int(ret[6]);
        a2 = from_str_to_int(ret[7]);
        c = from_str_to_int(ret[8]);
        lim_x = from_str_to_int(ret[0]);
        lim_y = from_str_to_int(ret[1]);
        abs_err = std::stod(ret[2]);
        rel_err = std::stod(ret[3]);
        am_threads = std::stoi(ret[4]);
        m = std::stoi(ret[5]);
        stop_signal = std::stoi(ret[9]);

        am_threads = am_threadsPar;
    }
    catch (std::invalid_argument&) {
        throw MyParsingError("Arguments in the file are not numeric");
    }
    catch (std::logic_error&) {
        throw MyParsingError("Not enough arguments");
    }

    if (lim_x[0] > lim_x[1] or lim_y[0] > lim_y[1]) {
        throw MyParsingError("Lower limit of integration should be smaller than upper");
    }
    if (abs_err <= 0) {
        throw MyParsingError("Absolute error should be more than 0");
    }
    if (rel_err <= 0) {
        throw MyParsingError("Relative error should be more than 0");
    }
    if (am_threads < 1) {
        throw MyParsingError("Amount of threads should be positive");
    }
    if (stop_signal <= 0) {
        throw MyParsingError("Max number of iterations should be positive");
    }
    if (a1.size() != a2.size() || a1.size() != c.size() || a2.size() != c.size()) {
        throw MyParsingError("a1, a2, c must have the same amount of arguments");
    }

    checkErr(lim_x[0], lim_x[1], lim_y[0],lim_y[1],
            abs_err, rel_err, am_threads, m, a1, a2, c, stop_signal);

    std::cout << "Abs. error: " << std::stod(ret[2]) << std::endl;
    std::cout << "Rel. error: " << std::stod(ret[3]) << std::endl;

    return 0;
}


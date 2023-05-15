#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "alg.cpp"

int main() {
    const size_t repeats = 1;
    std::ofstream Intergal("integral.txt");
    Intergal << std::setprecision(6) << std::fixed << "rec\t\t\titer\n";

    long double sum_integral_recur{}, sum_integral_iter{};

    for (size_t iter = 10; iter <= 10; ++iter) {
        for (size_t i{}; i < repeats; ++i) {
            std::cout << "Точность знаков после запятой : " << iter << " из 10" << " | Кол-во прогонов : " << i
                      << " из " << repeats << "\r" << std::flush;
            // clock_t begin = clock();
            // myIntegral_recur((size_t)powl(10, iter), cosl, 0, 1);
            // clock_t end = clock();
            // sum_integral_recur += (long double)(end - begin) / CLOCKS_PER_SEC;
            
            clock_t begin = clock();
            myIntegral_iter((size_t)powl(10, iter), cosl, 0, 1);
            clock_t end = clock();
            sum_integral_iter += (long double)(end - begin) / CLOCKS_PER_SEC;
        }
        Intergal << 1000000 * sum_integral_recur / repeats << "\t"
                 << 1000000 * sum_integral_iter / repeats << '\n';
    }
    return 0;
}

#ifndef ALG_CPP
#define ALG_CPP

#define fi 1.618033988749894

#include <cmath>
#include <iostream>
#include <ostream>

long double myIntegral_iter(const size_t N, auto func, long double a,
                            long double b) {
    long double sum = 0, step = (b - a) / (long double)N;
    for (long double i = a; i < b + step / 2; i += step) {
        sum += func(i);
        
        // std::cout << i << "\r" << std::flush;
    }
    return sum * step;
}

long double myIntegral_recur(const size_t N, auto func, long double a,
                             long double b, long double sum = 0,
                             long double step = 0) {
    if (step == 0) {
        step = (b - a) / (long double)N;
    };
    if (a < b + step / 2) {
        sum += func(a);
        return myIntegral_recur(N, func, a + step, b, sum, step);
    } else {
        return sum * step;
    }
}

#endif

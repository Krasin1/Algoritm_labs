#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "alg.cpp"

void generate_str(char* str, size_t n) {
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < n; ++i) {
        str[i] = rand() % 5 + 65;
    }
    str[n] = '\0';
}

auto main() -> int {
    srand((unsigned)time(NULL));
    const size_t textMaxLen = 10000, strLen = 5, step = 1000, repeats = 100000;
    double sum_rabin{}, sum_boer{};
    char* text = new char[textMaxLen + 1]{};
    char str[strLen + 1]{};

    std::ofstream boer("_boer.txt");
    std::ofstream rabin("_rabin.txt");
    boer << std::setprecision(6) << std::fixed
         << "Время в микросекуднах | Размер строки\n";
    rabin << std::setprecision(6) << std::fixed
          << "Время в микросекуднах | Размер строки\n";
    for (size_t textLen = step; textLen <= textMaxLen; textLen += step) {
        generate_str(text, textLen);
        sum_rabin = 0;
        sum_boer = 0;
        for (size_t j{}; j < repeats; ++j) {
            generate_str(str, strLen);

            clock_t begin = clock();
            search(text, str);
            clock_t end = clock();
            sum_boer += (double)(end - begin) / CLOCKS_PER_SEC;

            begin = clock();
            rabinKarp(str, text);
            end = clock();
            sum_rabin += (double)(end - begin) / CLOCKS_PER_SEC;
            std::cout << "Шаг : " << textLen << " | Кол-во прогонов : " << j
                      << "       \r" << std::flush;
        }
        boer << 1000000 * sum_boer / repeats << " " << textLen << '\n';
        rabin << 1000000 * sum_rabin / repeats << " " << textLen << '\n';
    }
    delete[] text;
    return 0;
}

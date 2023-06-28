#include <ctime>
#include <random>
#include <fstream>
#include <iomanip>
#include "eulerMaze.hpp"
#include "deepMaze.hpp"

using matr = std::vector<std::vector<bool>>;

auto main() -> int {
    srand((unsigned)time(NULL));
    unsigned repeats = 1000;
    double sum_euler, sum_deep;

    std::ofstream euler("euler.txt");
    std::ofstream deep("deep.txt");
    Maze elr;
    deepMaze dp;

    for (unsigned i{5}; i <= 100; i += 5) {
        sum_euler = 0;
        sum_deep = 0;

        for (unsigned j{}; j < repeats; ++j) {
            dp.fillEmpty(i);
            clock_t begin = clock();
            dp.generate(i);
            clock_t end = clock();
            sum_deep = (double)(end - begin) / CLOCKS_PER_SEC;

            elr.fillEmpty(i);
            begin = clock();
            elr.generate(i);
            end = clock();
            sum_euler = (double)(end - begin) / CLOCKS_PER_SEC;

            std::cout << "Шаг : " << i << " | Кол-во прогонов : " << j
                      << "       \r";
        }
        deep<< i << " " << std::fixed << std::setprecision(6) << 1000000 * sum_deep / repeats << '\n';
        euler << i << " " << std::fixed << std::setprecision(6)  << 1000000 * sum_euler/ repeats << '\n';
    }
/*
    matr vert = {
        {0, 0, 0, 1},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 0, 0, 1},
    };
    matr horiz = {
        {1, 0, 1, 0},
        {0, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 1, 1, 1},
    };
    Maze maze(4, vert, horiz);
    // maze.printMaze();
    Maze kek;
    // kek.generate(14);
    // kek.printMaze();

    deepMaze lol;
    lol.generate(10);
    lol.printMaze();
*/  
    return 0;
}

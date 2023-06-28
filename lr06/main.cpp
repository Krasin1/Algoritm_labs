#include <ctime>
#include <random>
#include "eulerMaze.hpp"
#include "deepMaze.hpp"

using matr = std::vector<std::vector<bool>>;

auto main() -> int {
    srand((unsigned)time(NULL));
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


    
    return 0;
}

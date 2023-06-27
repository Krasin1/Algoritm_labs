#include <iostream>
#include <vector>
#include <ctime>
#include <random>

using matr = std::vector<std::vector<bool>>;

class Maze {
   public:
    Maze() {
        vert.reserve(4);
        vec.reserve(4);
        for (size_t i{}; i < 4; ++i) {
            vert[i].reserve(4);
            vec[i].reserve(4);
        }
    }

    Maze(size_t N) {
        vert.reserve(N);
        vec.reserve(N);
        for (size_t i{}; i < N; ++i) {
            vert[i].reserve(N);
            vec[i].reserve(N);
        }
    }

    Maze(matr& a, matr& b) : vert(a), horiz(b) {}

    void fillEmptyRow(size_t N) {
        counter = 0;

        for (size_t i{}; i < N; ++i) {
            vec[0][i] = 0;
        }
    }

    void assignUniqueSet(size_t N) {
        for (size_t j{}; j < N; ++j) {
            if (vec[0][j] == 0) {
                vec[0][j] = (int)counter;
            }
            counter++;
        }
    }

    void addingVerticalWalls(size_t row) {
        for(size_t i {}; i < vert.size(); ++i){
            bool choise = rand() % 2;
        }

    }

    void generate() {
        size_t N = vert.size();
        fillEmptyRow(N);
        for (size_t i{}; i < N; ++i) {
            assignUniqueSet(N);
            addingVerticalWalls(i);
        }
    }

    void printMaze() {
        size_t N = vert.size();

        std::cout << "+";
        for (size_t i{}; i < N; ++i) {
            std::cout << "---+";
        }
        std::cout << "\n";
        for (size_t i{}; i < N; ++i) {
            std::cout << "|";
            for (size_t j{}; j < N; ++j) {
                if (vert[i][j] || j == N - 1)
                    std::cout << "   |";
                else
                    std::cout << "    ";
            }
            std::cout << "\n+";
            for (size_t j{}; j < N; ++j) {
                if (horiz[i][j] || i == N - 1)
                    std::cout << "---+";
                else
                    std::cout << "   +";
            }
            std::cout << "\n";
        }
    }

   private:
    matr vert;
    matr horiz;
    std::vector<std::vector<int>> vec;
    size_t counter;
};

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
    Maze maze(vert, horiz);
    maze.printMaze();
    return 0;
}

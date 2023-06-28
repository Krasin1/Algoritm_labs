#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using matr = std::vector<std::vector<bool>>;

class Maze {
   public:
    Maze() : counter(1), size(3) { resizeAllVec(size); }

    Maze(size_t N) : counter(1), size(N) { resizeAllVec(size); }

    Maze(size_t size, matr& a, matr& b)
        : vert(a), horiz(b), counter(1), size(size) {}

    void resizeAllVec(size_t N) {
        vert.resize(N);
        vec.resize(N);
        horiz.resize(N);
        for (size_t i{}; i < N; ++i) {
            vert[i].resize(N);
            vec[i].resize(N);
            horiz[i].resize(N);
        }
    }

    void fillEmpty(size_t N) {
        counter = 1;
        size = N;
        resizeAllVec(N);
        for (size_t i{}; i < N; ++i) {
            for (size_t j{}; j < N; ++j) {
                vec[i][j] = 0;
                horiz[i][j] = false;
                vert[i][j] = false;
            }
        }
    }

    void assignUniqueSet(size_t N) {
        for (size_t j{}; j < size; ++j) {
            if (vec[N][j] == 0) {
                vec[N][j] = (int)counter;
                counter++;
            }
        }
    }

    void addingVerticalWalls(size_t row) {
        for (size_t i{}; i < size - 1; ++i) {
            bool choise = rand() % 2;
            if (choise || vec[row][i] == vec[row][i + 1]) {
                vert[row][i] = true;
            } else {
                for (size_t j{}; j < size; ++j) {
                    if (vec[row][j] == vec[row][i]) {
                        vec[row][j] = vec[row][i + 1];
                    }
                }
            }
        }
        vert[row][size - 1] = true;
    }

    size_t checkSet(int Set, size_t row) {
        size_t temp_cnt = 0;
        for (size_t i{}; i < size; ++i) {
            if (vec[row][i] == Set) {
                temp_cnt++;
            }
        }
        return temp_cnt;
    }

    void addingHoirzWalls(size_t row) {
        for (size_t i{}; i < size; ++i) {
            bool choise = rand() % 2;
            if (choise && checkSet(vec[row][i], row) != 1) {
                horiz[row][i] = true;
            }
        }
    }
    size_t calculateHorizontalWalls(int element, size_t row) {
        size_t countHorizontalWalls = 0;
        for (size_t i = 0; i < size; i++) {
            if (vec[row][i] == element && horiz[row][i] == false) {
                countHorizontalWalls++;
            }
        }
        return countHorizontalWalls;
    }

    void checkHorizWalls(size_t row) {
        for(size_t i{}; i < size; ++i) {
            if(calculateHorizontalWalls(vec[row][i], row) == 0) {
                horiz[row][i] = false;
            }
        }
    }

    void prepareNewLine(size_t row) {
        for (size_t i{}; i < size; ++i) {
            if (horiz[row][i] == true) {
                vec[row + 1][i] = 0;
            } else {
                vec[row + 1][i] = vec[row][i];
            }
        }
    }

    void checkEndLine() {
        size_t endl = size - 1;
        for (size_t i{}; i < size - 1; ++i) {
            if (/*vert[endl][i] && */vec[endl][i]  != vec[endl][i + 1]) {
                vert[endl][i] = false;
                // merge sets
                for (size_t j{}; j < size; ++j) {
                    if (vec[endl][j] == vec[endl][i]) {
                        vec[endl][j] = vec[endl][i + 1];
                    }
                }
                // i++;
            }
            horiz[endl][i] = true;
        }
        horiz[endl][endl] = true;
        std::cout << '\n';
    }
    void addEndLine() {
        assignUniqueSet(size - 1);
        addingVerticalWalls(size - 1);
        printMaze();
        checkEndLine();
    }

    void generate(size_t n) {
        fillEmpty(n);
        for (size_t i{}; i < size - 1; ++i) {
            assignUniqueSet(i);
            addingVerticalWalls(i);
            addingHoirzWalls(i);
            checkHorizWalls(i);
            prepareNewLine(i);
        }
        addEndLine();
    }

    void printMaze() {
        std::cout << "+";
        for (size_t i{}; i < size; ++i) {
            std::cout << "---+";
        }
        std::cout << "\n";
        for (size_t i{}; i < size; ++i) {
            std::cout << "|";
            for (size_t j{}; j < size; ++j) {
                if (vert[i][j] || j == size - 1)
                    std::cout << "   |";
                else
                    std::cout << "    ";
            }
            std::cout << "\n+";
            for (size_t j{}; j < size; ++j) {
                if (horiz[i][j] || i == size - 1)
                    std::cout << "---+";
                else
                    std::cout << "   +";
            }
            std::cout << "\n";
        }
        std::cout << " ";
        for (size_t i{}; i < size; ++i) {
            std::cout << vec[size - 1][i] << " ";
        }
        std::cout << '\n';
    }

   private:
    matr vert;
    matr horiz;
    std::vector<std::vector<int>> vec;
    size_t counter;
    size_t size;
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
    Maze maze(4, vert, horiz);
    // maze.printMaze();
    Maze kek;
    kek.generate(14);
    kek.printMaze();
    return 0;
}

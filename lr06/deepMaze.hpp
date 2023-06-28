#include <iostream>
#include <vector>
#include <utility>
#include <stack>

#include <unistd.h>
using matr = std::vector<std::vector<bool>>;

class deepMaze {
   public:
    deepMaze(): size(3) { resizeAllVec(size); }

    deepMaze(size_t N): size(N) { resizeAllVec(size); }

    deepMaze(size_t size, matr& a, matr& b)
        : vert(a), horiz(b), size(size) {}

    void resizeAllVec(size_t N) {
        vert.resize(N);
        visited.resize(N);
        horiz.resize(N);
        for (size_t i{}; i < N; ++i) {
            vert[i].resize(N);
            visited[i].resize(N);
            horiz[i].resize(N);
        }
    }

    void fillEmpty(size_t N) {
        size = N;
        resizeAllVec(N);
        for (size_t i{}; i < N; ++i) {
            for (size_t j{}; j < N; ++j) {
                visited[i][j] = false;
                horiz[i][j] = true;
                vert[i][j] = true;
            }
        }
    }
    bool checkCell(int x, int y) {
        if(x < 0 || x > (int)size - 1 || y < 0 || y > (int)size - 1) {
            return false;
        }
        return true;
    }

    std::pair<int, int> checkNeighbors(int x, int y) {
        std::vector<std::pair<int, int>> neighbors;
        bool top = checkCell(x, y - 1);
        bool right = checkCell(x + 1, y);
        bool bottom = checkCell(x, y + 1);
        bool left = checkCell(x - 1, y);

        if (top && !visited[y - 1][x]) {
            neighbors.push_back(std::make_pair(x, y - 1));
        }
        if (right && !visited[y][x + 1]) {
            neighbors.push_back(std::make_pair(x + 1, y));
        }
        if (bottom && !visited[y + 1][x]) {
            neighbors.push_back(std::make_pair(x, y + 1));
        } 
        if (left && !visited[y][x - 1]) {
            neighbors.push_back(std::make_pair(x - 1, y));
        }
        if (neighbors.size() != 0) {
            size_t ran = (size_t)rand() % neighbors.size();
            // std::cout<< ran << " " << neighbors[ran].first << " " << neighbors[ran].second << "\n";
            return neighbors[ran];
        } else {
            return std::make_pair(-1, -1);
        }
    }

    void removeWalls(int x1, int y1, int x2, int y2){
        int dx = x2 - x1;
        int dy = y2 - y1;
        if (dx == 1) {
            vert[(size_t)y1][(size_t)x1] = false;
        } else if (dx == -1) {
            vert[(size_t)y2][(size_t)x2] = false;
        }
        if (dy == 1) {
            horiz[(size_t)y1][(size_t)x1] = false;
        } else if (dy == -1) {
            horiz[(size_t)y2][(size_t)x2] = false;
        }
    }

    void generate(size_t N) {
        std::pair<int, int> currnet_cell = std::make_pair(0, 0);
        while(1) {
            // usleep(500000);
            visited[currnet_cell.second][currnet_cell.first] = true;
            std::pair<int, int> next_cell = checkNeighbors(currnet_cell.first, currnet_cell.second);
            // std::cout << currnet_cell.first << " " << currnet_cell.second << " | " << next_cell.first << " " << next_cell.second << " | " << stack.size() << '\n';
            if (next_cell.first != -1 || next_cell.second != -1) {
                visited[next_cell.second][next_cell.first] = true;
                stack.push(currnet_cell);
                removeWalls(currnet_cell.first, currnet_cell.second, next_cell.first, next_cell.second);
                currnet_cell = next_cell;
                // printMaze();
            } else if (!stack.empty()) {
                    currnet_cell = stack.top();
                    stack.pop();
            } 
            if (stack.empty()) {
                break;
            }
        }
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
        std::cout << '\n';
    }

   private:
    matr vert;
    matr horiz;
    std::vector<std::vector<bool>> visited;
    std::stack<std::pair<int, int>> stack;
    size_t size;
};

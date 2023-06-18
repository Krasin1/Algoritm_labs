#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void print_vec(std::vector<std::vector<int>> &arr) {
    const int INF = 10000000;
    std::cout << '\n'
              << std::setw(4) << ""
              << "|";
    for (size_t i{}; i < arr.size(); ++i) {
        std::cout << std::setw(4) << i + 1;
    }
    std::cout << "\n____";
    for (size_t i{}; i < arr.size(); ++i) {
        std::cout << "____";
    }
    std::cout << "_\n";
    for (size_t i{}; i < arr.size(); ++i) {
        std::cout << std::setw(4) << i + 1 << "|";
        for (size_t j{}; j < arr[i].size(); ++j) {
            if (arr[i][j] == 0 || arr[i][j] == INF)
                std::cout << std::setw(4) << "-";
            else
                std::cout << std::setw(4) << arr[i][j];
        }
        std::cout << '\n';
    }
}

void clear_graph(int n, std::vector<std::vector<int>> &graph) {
    const int INF = 10000000;
    graph.clear();
    graph.resize((unsigned)n);
    for (int i{}; i < n; ++i) {
        graph[(unsigned)i].assign((unsigned)n, INF);
    }
    for (unsigned i{}; i < (unsigned)n; ++i) {
        graph[i][i] = 0;
    }
}

bool nodeInGraph(std::vector<std::vector<int>> &graph, size_t node) {
    const int INF = 10000000;
    for (int i{}; i < (int)graph[node].size(); ++i) {
        if (graph[node].at((unsigned)i) != 0 &&
            graph[node].at((unsigned)i) != INF) {
            return true;
        }
    }
    return false;
}

void newGraph(int n, std::vector<std::vector<int>> &graph) {
    const int INF = 10000000;
    clear_graph(n, graph);

    int edges = ((n * (n - 1) / 2) - (n - 1)) / 10 * 3 + (n - 1);

    for (size_t i{}; i < (size_t)edges; ++i) {
        size_t start = (size_t)rand() % (unsigned)n;
        size_t end = (size_t)rand() % (unsigned)n;
        size_t wght = (size_t)rand() % 14 + 1;
        if (start != end && graph[end][start] == INF) {
            graph[end][start] = (int)wght;
            graph[start][end] = (int)wght;
        } else {
            i--;
            continue;
        }
    }
    for (int i{}; i < n; ++i) {
        if (!nodeInGraph(graph, (unsigned)i)) {
            size_t start, end, wght;
            do {
                start = (size_t)i;
                end = (size_t)rand() % (unsigned)n;
                wght = (size_t)rand() % 14 + 1;
            } while (start == end);

            graph[end][start] = (int)wght;
            graph[start][end] = (int)wght;
        }

        unsigned count = 0;
        size_t temp;
        for (int j{}; j < n; ++j) {
            if (graph[i][j] != 0 && graph[i][j] != INF) {
                count++;
                temp = j;
            }
        }
        if (count < 2) {
            size_t start, end, wght;
            do {
                start = (size_t)i;
                end = (size_t)rand() % (unsigned)n;
                wght = (size_t)rand() % 14 + 1;
            } while (start == end || end == temp);
            graph[end][start] = (int)wght;
            graph[start][end] = (int)wght;
        }
    }
}

void Deikstra(unsigned start, unsigned end,
              std::vector<std::vector<int>> &matr) {
    // print_vec(matr);
    const unsigned INF = 10000000;
    const unsigned N = (unsigned)matr.size();
    unsigned minIndex, minWeight, temp;
    std::vector<bool> visited(N, false);
    std::vector<unsigned> distances(N, INF);
    distances[start] = 0;

    do {
        minIndex = INF;
        minWeight = INF;
        for (unsigned i{}; i < N; ++i) {
            if (!visited[i] && distances[i] < minWeight) {
                minIndex = i;
                minWeight = distances[i];
            }
        }

        if (minIndex != INF) {
            for (unsigned i{}; i < N; ++i) {
                if (matr[minIndex][i] != INF && matr[minIndex][i] > 0) {
                    temp = minWeight + (unsigned)matr[minIndex][i];
                    if (temp < distances[i]) distances[i] = temp;
                }
            }
            visited[minIndex] = true;
        }
    } while (minIndex < INF);
    // Восстанавливаем путь
    unsigned weight = distances[end];
    std::string way = std::to_string(end + 1);
    while (end != start) {
        for (unsigned i{}; i < N; ++i) {
            if (matr[i][end] != 0 && matr[i][end] != INF) {
                temp = weight - (unsigned)matr[i][end];
                if (temp == distances[i]) {
                    end = i;
                    weight = temp;
                    way += "<-" + std::to_string(i + 1);
                }
            }
        }
    }
    // for(unsigned i {}; i < way.length(); ++i) {
    //     std::cout << way[i] << " ";
    // }
    // std::cout << '\n';
}

void make_best(std::vector<std::vector<int>> &matr,
               std::vector<std::vector<int>> &best) {
    const unsigned INF = 10000000;
    unsigned N = (unsigned)matr.size();
    best.resize(N);
    for (unsigned i{}; i < N; ++i) {
        best[i].resize(N);
    }
    for (unsigned i{}; i < best.size(); ++i) {
        for (unsigned j{}; j < best[i].size(); ++j) {
            best[i][j] = INF;
            if (matr[i][j] != 0 && matr[i][j] != INF) {
                best[i][j] = (int)j;
            }
            if (i == j) best[i][j] = (int)i;
        }
    }
}
void print_best(std::vector<std::vector<int>> &best) {
    std::cout << "\nМатрица маршрутов";
    const unsigned INF = 10000000;
    std::cout << '\n'
              << std::setw(4) << ""
              << "|";
    for (size_t i{}; i < best.size(); ++i) {
        std::cout << std::setw(4) << i + 1;
    }
    std::cout << "\n____";
    for (size_t i{}; i < best.size(); ++i) {
        std::cout << "____";
    }
    std::cout << "_\n";
    for (unsigned i{}; i < best.size(); ++i) {
        std::cout << std::setw(4) << i + 1 << "|";
        for (unsigned j{}; j < best[i].size(); ++j) {
            if (best[i][j] == INF)
                std::cout << std::setw(4) << "-";
            else
                std::cout << std::setw(4) << best[i][j] + 1;
        }
        std::cout << '\n';
    }
    std::cout << "\n";
}

void originalFloydWarshall(std::vector<std::vector<int>> &matrix,
                           std::vector<std::vector<int>> &best) {
    unsigned numberOfVert = (unsigned)matrix.size();
    for (unsigned k = 0; k < numberOfVert; k++) {
        for (unsigned i = 0; i < numberOfVert; i++) {
            for (unsigned j = 0; j < numberOfVert; j++) {
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    best[i][j] = best[i][k];
                }
            }
        }
    }
}
int main() {
    srand((unsigned)time(NULL));
    unsigned repeats = 10000;
    double sum_floyd, sum_deikstra;
    std::vector<std::vector<int>> matr, best;

    std::ofstream floyd("floyd.txt");
    std::ofstream deikstra("deikstra.txt");

    for (unsigned i{5}; i <= 100; i += 5) {
        sum_floyd = 0;
        sum_deikstra = 0;
        for (unsigned j{}; j < repeats; ++j) {
            newGraph((int)i, matr);

            clock_t begin = clock();
            Deikstra(0, i - 1, matr);
            clock_t end = clock();
            sum_deikstra = (double)(end - begin) / CLOCKS_PER_SEC;

            make_best(matr, best);
            begin = clock();
            originalFloydWarshall(matr, best);
            end = clock();
            sum_floyd = (double)(end - begin) / CLOCKS_PER_SEC;
            std::cout << "Шаг : " << i << " | Кол-во прогонов : " << j
                      << "       \r";
        }
        deikstra << i << " " << 1000000 * sum_deikstra / repeats << '\n';
        floyd << i << " " << 1000000 * sum_floyd / repeats << '\n';
    }

    return 0;
}

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

struct edge {
    size_t node_start;
    size_t node_end;
    size_t weight;
};

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
}

void matr_to_edges(std::vector<std::vector<int>> &arr,
                   std::vector<edge> &edges) {
    const int INF = 10000000;
    size_t N = arr.size();
    edges.clear();
    for (size_t i{}; i < N; ++i) {
        for (size_t j{i}; j < N; ++j) {
            if (i < j && arr[i][j] != 0) {
                edges.push_back(edge{i, j, (size_t)arr[i][j]});
            }
        }
    }
}

void edges_to_matr(int n, std::vector<edge> &edges,
                   std::vector<std::vector<int>> &arr) {
    clear_graph(n, arr);
    std::cout << '\n';
    for (auto &a : edges) {
        // std::cout << a.node_start << " " << a.node_end << '\n';
        arr.at(a.node_start).at(a.node_end) = (int)a.weight;
        arr.at(a.node_end).at(a.node_start) = (int)a.weight;
    }
}

bool nodeInGraph(std::vector<edge> &graph, size_t node) {
    for (int i{}; i < (int)graph.size(); ++i) {
        if (graph[(unsigned long)i].node_start == node ||
            graph[(unsigned long)i].node_end == node)
            return true;
    }
    return false;
}

bool nodeInGraph(std::vector<std::vector<int>> &graph, size_t node) {
    for (int i{}; i < (int)graph[node].size(); ++i) {
        if (graph[node].at((unsigned)i) != 0) {
            return true;
        }
    }
    return false;
}

bool edgeInGraph(std::vector<edge> &graph, edge e) {
    for (int i{}; i < (int)graph.size(); ++i) {
        if (graph[(unsigned long)i].node_start == e.node_start &&
            graph[(unsigned long)i].node_end == e.node_end)
            return true;
    }
    return false;
}


void newGraph(int n, std::vector<edge> &graph) {
    std::vector<bool> node_in_graph((unsigned)n, false);
    graph.clear();

    int edges = ((n * (n - 1) / 2) - (n - 1)) / 10 * 3 + (n - 1);
    graph.resize((unsigned)edges);

    for (size_t i{}; i < (size_t)edges; ++i) {
        size_t start = (size_t)rand() % (unsigned)n;
        size_t end = (size_t)rand() % (unsigned)n;
        size_t wght = (size_t)rand() % 14 + 1;
        if (start > end) std::swap(start, end);
        if (start != end && !edgeInGraph(graph, edge{start, end, wght})) {
            graph[i].node_start = start;
            graph[i].node_end = end;
            graph[i].weight = wght;
            node_in_graph[start] = true;
            node_in_graph[end] = true;
        } else {
            i--;
            continue;
        }
    }
    for (int i{}; i < n; ++i) {
        if (!node_in_graph[(unsigned)i]) {
            size_t start = (size_t)i;
            size_t end = (size_t)rand() % (unsigned)n;
            size_t wght = (size_t)rand() % 14 + 1;
            if (start == end) {
                i--;
                continue;
            }
            if (start > end) std::swap(start, end);
            graph.push_back(edge{start, end, wght});
        }
    }
}

void newGraph(int n, std::vector<std::vector<int>> &graph) {
    const int INF = 10000000;
    clear_graph(n, graph);

    int edges = ((n * (n - 1) / 2) - (n - 1)) / 10 * 3 + (n - 1);

    for (size_t i{}; i < (size_t)edges; ++i) {
        size_t start = (size_t)rand() % (unsigned)n;
        size_t end = (size_t)rand() % (unsigned)n;
        size_t wght = (size_t)rand() % 14 + 1;
        if (start > end) std::swap(start, end);
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
            size_t start = (size_t)i;
            size_t end = (size_t)rand() % (unsigned)n;
            size_t wght = (size_t)rand() % 14 + 1;
            if (start == end) {
                i--;
                continue;
            }
            if (start > end) std::swap(start, end);
            graph[end][start] = (int)wght;
            graph[start][end] = (int)wght;
        }
    }
}

void Prim(int N, std::vector<std::vector<int>> &graph,
          std::vector<std::vector<int>> &result) {
    const int INF = 10000000;
    std::vector<bool> used((unsigned long)N);
    std::vector<int> min_e((unsigned long)N, INF);
    std::vector<int> sel_e((unsigned long)N, -1);
    min_e[0] = 0;
    for (int i{}; i < N; ++i) {
        int v = -1;
        for (int j{}; j < N; ++j) {
            if (!used[(unsigned long)j] &&
                (v == -1 ||
                 min_e[(unsigned long)j] < min_e[(unsigned long)v])) {
                v = j;
            }
        }
        used[(unsigned long)v] = true;
        if (sel_e[(unsigned long)v] != -1) {
            result.at(v).at(sel_e.at(v)) = graph[v][sel_e[v]];
            result.at(sel_e.at(v)).at(v) = graph[sel_e[v]][v];
            std::cout << i << " " << v << "\n";
            print_vec(result);
        }
        for (int to{}; to < N; ++to) {
            if (graph[(unsigned long)v][(unsigned long)to] <
                min_e[(unsigned long)to]) {
                min_e[(unsigned long)to] =
                    graph[(unsigned long)v][(unsigned long)to];
                sel_e[(unsigned long)to] = v;
            }
        }
    }
}
bool compare(edge a, edge b) { return a.weight < b.weight; }

void Kruskal(std::vector<std::vector<int>> &arr,
             std::vector<std::vector<int>> &result) {
    const int INF = 10000000;
    std::vector<edge> edges;
    matr_to_edges(arr, edges);
    sort(edges.begin(), edges.end(), compare);
    size_t N = edges.size();
    std::vector<size_t> tree_id(N + 1);
    for (size_t i{}; i < N; ++i) tree_id[i] = i;
    for (size_t i{}; i < N; i++) {
        size_t start = edges[i].node_start;
        size_t end = edges[i].node_end;
        if (tree_id[start] != tree_id[end]) {
            result[start][end] = (int)edges[i].weight;
            result[end][start] = (int)edges[i].weight;
            // print_vec(result);
            size_t old_id = tree_id[end];
            size_t new_id = tree_id[start];
            for (size_t j{}; j < N; ++j) {
                if (tree_id[j] == old_id) tree_id[j] = new_id;
            }
        }
    }
}

void Kruskal(std::vector<edge> &arr, std::vector<edge> &result) {
    size_t N = arr.size();
    std::vector<size_t> tree_id(N + 1);
    for (size_t i{}; i < N; ++i) tree_id[i] = i;
    sort(arr.begin(), arr.end(), compare);

    for (size_t i{}; i < N; i++) {
        size_t start = arr[i].node_start;
        size_t end = arr[i].node_end;
        if (tree_id[start] != tree_id[end]) {
            result.push_back(edge{start, end, arr[i].weight});
            size_t old_id = tree_id[end];
            size_t new_id = tree_id[start];
            for (size_t j{}; j < N; ++j) {
                if (tree_id[j] == old_id) tree_id[j] = new_id;
            }
        }
    }
    for (size_t i{}; i < result.size(); i++) {
        if (result[i].node_start == 0 && result[i].node_end == 0) {
            result.erase(result.begin() + (long)i);
            i--;
        }
    }
}


int main() {
    srand((unsigned)time(NULL));
    const size_t repeats = 10000;
    double sum_kruskal{}, sum_prim{};
    std::vector<edge> arr(101);
    std::vector<edge> result;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> resh;
    

    const size_t nodes = 10;
    std::vector<edge> test{{0, 1, 7}, {0, 3, 2}, {0, 5, 4}, {1, 3, 2},
                           {3, 5, 1}, {1, 2, 1}, {4, 5, 8}, {2, 3, 2},
                           {3, 4, 6}, {2, 4, 3}};
    std::vector<std::vector<int>> matr;
    clear_graph(6, resh);
    edges_to_matr(6, test, matr);
    print_vec(matr);
    // Kruskal(matr, resh);
    // print_vec(resh);

    clear_graph(6, resh);
    Prim(6, matr, resh);
    print_vec(resh);

    // std::ofstream kruskal("kruskal.txt");
    // std::ofstream prim("prim.txt");
    //
    // for (size_t i{5}; i <= 100; i += 5) {
    //     sum_kruskal = 0;
    //     sum_prim = 0;
    //     for (size_t j{}; j < repeats; ++j) {
    //         clear_graph((int)i, resh);
    //         result.clear();
    //         newGraph((int)i, arr);
    //         clock_t begin = clock();
    //         Kruskal(arr, result);
    //         clock_t end = clock();
    //         sum_kruskal += (double)(end - begin) / CLOCKS_PER_SEC;
    //
    //         newGraph((int)i, graph);
    //         begin = clock();
    //         Prim((int)i, graph, resh);
    //         end = clock();
    //         sum_prim += (double)(end - begin) / CLOCKS_PER_SEC;
    //
    //         std::cout << "Шаг : " << i << " | Кол-во прогонов : " << j
    //                   << "       \r";
    //     }
    //     kruskal << 1000000 * sum_kruskal / repeats << " " << i << '\n';
    //     prim << 1000000 * sum_prim / repeats << " " << i << '\n';
    // }
}

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void clear_graph(int n, std::vector<std::vector<int>> &graph) {
    const int INF = 10000000;
    graph.clear();
    graph.resize((unsigned)n);
    for (int i{}; i < n; ++i) {
        graph[(unsigned)i].assign((unsigned)n, INF);
    }
}

bool nodeInGraph(std::vector<std::vector<int>> &graph, size_t node) {
    for (int i{}; i < (int)graph[node].size(); ++i) {
        if (graph[node].at((unsigned)i) != 0) {
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

void Deikstra(int start, int end, std::vector<std::vector<int>> &matr){
    const int INF = 10000000;
    const int N = matr.size();
    int minIndex, min, temp;
    std::vector<int> min_dist(N, INF);
    std::vector<int> visited(N + 1, 1);

    min_dist[start] = 0;
    do {
        minIndex = INF;
        min = INF;
        for(int i{}; i < N; ++i){
            if((visited[i] == 1) && (min_dist[i] < min)){
                min = min_dist[i];
                minIndex = i;
            }
            if(minIndex != INF) {
                for(int i{}; i < N; ++i) {
                    if(matr[minIndex][i] > 0) {
                        temp = min + matr[minIndex][i];
                        if (temp < min_dist[i]){
                            min_dist[i] = temp;
                        }
                    }
                }
            }
            visited[minIndex] = 0;
        }
    } while(minIndex < INF) ;
    

    // std::vector<int> ver(N);
    // ver[0] = end + 1;
    // int prev = 1;
    // int weight = min_dist[end];
    //
    // while(end != start){
    //     for(int i{}; i < N; ++i){
    //         if(matr[i][end] != 0) {
    //             int temp = weight - matr[i][end];
    //             if (temp == min_dist[i]){
    //                 weight = temp;
    //                 end = i;
    //                 ver[prev] = i + 1;
    //                 prev++;
    //             }
    //         }
    //     }
    // }
    //
    // for(int i{prev - 1}; i >= 0; --i){
    //     std::cout << std::setw(3) << ver[i];
    // }
}



int main() {
    std::vector<std::vector<int>> matr;
    newGraph(10, matr);
    Deikstra(0, 10, matr);
    return 0;
}

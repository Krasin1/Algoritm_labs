#include <ctime>
#include <fstream>  //для записи в файл
#include <iomanip>  //для setprecision
#include <iostream>

template <typename T>
void bubble_sort(T* a, size_t size) {
    T temp;
    for (size_t i{}; i < size - 1; ++i) {
        for (size_t j{}; j < size - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

template <typename T>
void hoarasort(T* a, size_t first_ind, size_t last_ind) {
    size_t i = first_ind, j = last_ind;
    T tmp, x = a[(first_ind + last_ind) / 2];

    do {
        while (a[i] < x) i++;
        while (a[j] > x) j--;

        if (i <= j) {
            if (i < j) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last_ind) hoarasort(a, i, last_ind);
    if (first_ind < j) hoarasort(a, first_ind, j);
}

template <typename T>
void generate_new_arr(T* arr, size_t elem) {
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < elem; ++i) {
        arr[i] = rand() % (int)elem;
    }
}

auto main() -> int {
    const size_t N = 1000, repeats = 10000, step = 30;
    int* arr_hoar = new int[N];
    int* arr_bubble = new int[N];
    double sum_hoar{}, sum_bubble{};

    std::ofstream hoar("hoarsort.txt");
    std::ofstream bubble("bubble.txt");
    hoar << std::setprecision(6) << std::fixed
         << "Время в микросекуднах | Размер массива \n";
    bubble << std::setprecision(6) << std::fixed
           << "Время в микросекуднах | Размер массива \n";

    for (size_t i{step}, cnt{1}; i < N; i += step, ++cnt) {
        generate_new_arr(arr_bubble, i);
        generate_new_arr(arr_hoar, i);
        sum_hoar = 0;
        sum_bubble = 0;

        for (size_t j{}; j < repeats; ++j) {
            clock_t begin = clock();
            hoarasort(arr_hoar, 0, i + 1);
            clock_t end = clock();
            sum_hoar += (double)(end - begin) / CLOCKS_PER_SEC;

            begin = clock();
            bubble_sort(arr_bubble, i);
            end = clock();
            sum_bubble += (double)(end - begin) / CLOCKS_PER_SEC;
            std::cout << "Шаг : " << i << " | Кол-во прогонов : " << j
                      << "       \r" << std::flush;
        }
        hoar << 1000000 * sum_hoar / repeats << " " << i << '\n';
        bubble << 1000000 * sum_bubble / repeats << " " << i << '\n';
    }

    delete[] arr_bubble;
    delete[] arr_hoar;
    return 0;
}

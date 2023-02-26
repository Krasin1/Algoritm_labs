#include <ctime>
#include <fstream>  //для записи в файл
#include <iomanip>  //для setprecision
#include <iostream>
#include <thread>

#define N 8500
#define repeats 100000

template <typename T>
class sort {
   public:
    sort() : arr(new T[N]), copy(new T[N]), time_array(new double[repeats]) {
        generate_new_arr();
        std::copy(arr, arr + N, copy);
    }

    void generate_new_arr() {
        srand((unsigned)time(NULL));
        for (size_t i = 0; i < N; ++i) {
            arr[i] = rand() % N;
        }
    }

    void generate_new_arr(T * arr) {
        srand((unsigned)time(NULL));
        for (size_t i = 0; i < N; ++i) {
            arr[i] = rand() % N;
        }
    }

    void time_to_file(const char* sort_name) {
        std::string name_dot_format(sort_name);
        std::ofstream file(name_dot_format.append(".txt"));
        file << std::setprecision(6) << std::fixed;
        file << "Размер массива : " << N << " | Кол-во прогонов: " << repeats
             << "\n";
        for (size_t i = 0; i < repeats; ++i) {
            file << time_array[i] << '\n';
        }
    }

    T* get_arr() { return arr; }
    T* get_time_array() { return time_array; }

    void measure_time(const char* (*func_sort)(T*, int, int)) {
        std::copy(copy, copy + N, arr);
        std::cout << "Размер массива : " << N
                  << " | Кол-во прогонов: " << repeats << "\n";
        double sum = 0;
        std::string func_name;
        for (size_t i = 0; i < repeats; ++i) {
            generate_new_arr();
            // std::copy(copy, copy + N, arr);

            clock_t begin = clock();
            func_name = func_sort(arr, 0, N - 1);
            clock_t end = clock();

            time_array[i] = (double)(end - begin) / CLOCKS_PER_SEC;
            sum += time_array[i];
            std::cout << std::setprecision(3) << std::fixed
                      << "Проценты : " << ((double)i / repeats) * 100
                      << "% | Кол-во прогонов : " << i << "        \r"
                      << std::flush;
        }
        std::cout << std::setprecision(6)
                  << "\rВремя сортировки за все прогоны : " << sum
                  << " сек. | Среднее время " << func_name << " : "
                  << sum / repeats << " сек.          \n";
        time_to_file(func_name.data());
    }

    void show_arr() {
        for (size_t i{}; i < N; ++i) {
            std::cout << arr[i] << '\n';
        }
    }

    ~sort() {
        delete[] arr;
        delete[] copy;
        delete[] time_array;
    }

   private:
    T* arr;
    T* copy;
    double* time_array;
};

template <typename T>
const char* bubble_sort(T* a, int, int size = N - 1) {
    T temp;
    for (int i{}; i < size - 1; ++i) {
        for (int j{}; j < size - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    return static_cast<const char*>(__FUNCTION__);
}

template <typename T>
const char* hoarasort(T* a, int first_ind = 0, int last_ind = N - 1) {
    int i = first_ind, j = last_ind;
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

    return static_cast<const char*>(__FUNCTION__);
}

auto main() -> int {
    sort<int> test;
    test.measure_time(bubble_sort);
    test.measure_time(hoarasort);
    // test.show_arr();
    return 0;
}

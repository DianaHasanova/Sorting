#include <stdio.h>
#include "libs/sortingAlgorithms/sortingAlgorithms.h"

void generateRandomArray(int *a, size_t n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] =/*INT_MIN/2*/+rand();
    }
}

void generateOrderedArray(int *a, size_t n) {
    for (int i = 0; i < n; i++)
        a[i] = i;
}

void generateOrderedBackwards(int *a, size_t n) {
    int element = n;
    for (int i = 0; i < n; i++)
        a[i] = element--;
}


void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {bubbleSort,    "bubbleSort"},
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {combSort,      "combSort"},
            {shellSort,     "shellSort"},
            {radixSort,     "radixSort"},
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("------------------------------\n ");
        printf(" Size: %d\n ", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}

int main() {
    timeExperiment();
    
    return 0;
}

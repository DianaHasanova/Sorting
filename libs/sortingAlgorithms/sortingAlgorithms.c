//
// Created by Дианочка on 09.03.2022.
//

#include "sortingAlgorithms.h"
#include <string.h>

//возвращает true, если массив отсортирован по неубыванию, иначе false
bool isOrdered(const int *a, size_t n) {
    for (int i = 1; i < n; ++i)
        if (a[i - 1] > a[i])
            return false;
    return true;
}

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf(" Run #%zu| ", runCounter++);
    printf(" Name: %s\n ", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  sortFunc(innerBuffer, size);
              }, time);

    // результаты замера
    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time: %.3f s.\n ", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv ", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n ", size, time);
        fclose(f);
    } else {
        printf("Wrong!\n");

        // вывод массива, который не смог быть отсортирован
        outputArray(innerBuffer, size);

        exit(1);
    }
}


void inputArray(int *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray(const int *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSort(int *a, size_t n) {
    int noSwap;
    for (size_t i = n - 1; i >= 0; i--) {
        noSwap = 1;
        for (size_t j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                noSwap = 0;
            }
        }
        if (noSwap == 1)
            break;
    }
}

void selectionSort(int *a, const size_t n) {
    for (int i = 0; i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
}

void insertionSort(int *a, const size_t n) {
    for (size_t i = 1; i < n; i++) {
        int t = a[i];
        int j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void combSort(int *a, const size_t n) {
    size_t step = n;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < n; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

void shellSort(int *a, const size_t n) {
    int i, j, step;
    int tmp;
    for (step = n / 2; step > 0; step /= 2)
        for (i = step; i < n; i++) {
            tmp = a[i];
            for (j = i; j >= step; j -= step) {
                if (tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
}

void getPrefixSum(int *a, int n) {
    int prev = a[0];
    *a = 0;
    for (int i = 1; i < n; i++) {
        int t = a[i];
        a[i] = prev + a[i - 1];
        prev = t;
    }
}

#define KEY 8
#define MASK 255

void radixSort(int *a, size_t n) {
    int buffer[n];
    for (int byte = 0; byte < sizeof(int); byte++) {
        int values[MASK + 1] = {0};
        for (int i = 0; i < n; i++) {
            int k;
            if (byte + 1 == sizeof(int))
                k = ((a[i] >> (byte * KEY)) + CHAR_MAX + 1) & MASK;
            else
                k = (a[i] >> (byte * KEY)) & MASK;
            values[k]++;
        }
        getPrefixSum(values, MASK + 1);
        for (size_t i = 0; i < n; i++) {
            int k;
            if (byte + 1 == sizeof(int))
                k = ((a[i] >> (byte * KEY)) + CHAR_MAX + 1) & MASK;
            else
                k = (a[i] >> (byte * KEY)) & MASK;
            buffer[values[k]++] = a[i];
        }
        memcpy(a, buffer, sizeof(int) * n);
    }
}



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
    int *innerBuffer = (int *) malloc(sizeof(int) * 10000000);
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
    free(innerBuffer);
}

void checkNComp(long long (*sortFunc)(int *, size_t), void (*generateFunc)(int *, size_t),
                size_t size, char *experimentName) {
    static size_t runCounter = 1;

    static int innerBuffer[1000000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    long long nComps = sortFunc(innerBuffer, size);

    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("Number of comparisons: %lld\n", nComps);

        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf(" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, nComps);
        fclose(f);
    } else {
        printf(" Wrong!\n");

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

long long getBubbleSortNComp(int *a, size_t n) {
    long long nComps = 0;
    int noSwap;
    for (size_t i = n - 1; ++nComps && i >= 0; i--) {
        noSwap = 1;
        for (size_t j = 0; ++nComps && j < i; j++) {
            if (++nComps && a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                noSwap = 0;
            }
        }
        if (++nComps && noSwap == 1)
            break;
    }
    return nComps;
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

long long getSelectionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        if (++nComps && i != minIndex)
            swap(&a[i], &a[minIndex]);
    }

    return nComps;
}

void insertionSort(int *a, size_t n) {
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

long long getInsertionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < n; i++) {
        int t = a[i];
        int j = i;
        while (++nComps && j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }

    return nComps;
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

long long getCombSortNComp(int *a, size_t n) {
    long long nComps = 0;
    size_t step = n;
    int swapped = 1;
    while (++nComps && step > 1 || swapped) {
        if (++nComps && step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < n; ++i, ++j)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }

    return nComps;
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

long long getShellSortNComp(int *a, size_t n) {
    long long nComps = 0;
    int i, j, step;
    int tmp;
    for (step = n / 2; ++nComps && step > 0; step /= 2)
        for (i = step; ++nComps && i < n; i++) {
            tmp = a[i];
            for (j = i; ++nComps && j >= step; j -= step) {
                if (++nComps && tmp < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }

    return nComps;
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
    int *buffer = (int *) malloc(sizeof(int) * n);
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
    free(buffer);
}

long long getRadixSortNComp(int *a, size_t n) {
    int *buffer = (int *) malloc(sizeof(int) * n);
    long long nComps = 0;
    for (int byte = 0; ++nComps && byte < sizeof(int); byte++) {
        int values[MASK + 1] = {0};
        for (int i = 0; ++nComps && i < n; i++) {
            int k;
            if (++nComps && byte + 1 == sizeof(int))
                k = ((a[i] >> (byte * KEY)) + CHAR_MAX + 1) & MASK;
            else
                k = (a[i] >> (byte * KEY)) & MASK;
            values[k]++;
        }
        getPrefixSum(values, MASK + 1);
        for (size_t i = 0; ++nComps && i < n; i++) {
            int k;
            if (++nComps && byte + 1 == sizeof(int))
                k = ((a[i] >> (byte * KEY)) + CHAR_MAX + 1) & MASK;
            else
                k = (a[i] >> (byte * KEY)) & MASK;
            buffer[values[k]++] = a[i];
        }
        memcpy(a, buffer, sizeof(int) * n);
    }
    free(buffer);

    return nComps;
}



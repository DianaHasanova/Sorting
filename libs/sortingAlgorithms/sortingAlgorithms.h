//
// Created by Дианочка on 09.03.2022.
//

#ifndef LABSORTING_SORTINGALGORITHMS_H
#define LABSORTING_SORTINGALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool isOrdered(const int *a, size_t n);

#define TIME_TEST(testCode, time) { \
clock_t start_time = clock();       \
testCode                            \
clock_t end_time = clock();         \
clock_t sort_time = end_time - start_time; \
time = (double)sort_time/CLOCKS_PER_SEC; \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

// функция сортировки
typedef struct SortFunc {
    void (*sort)(int *a, size_t n); // указатель на функцию сортировки
    char name[64]; // имя сортировки, используемое при выводе
} SortFunc;

// функция генерации
typedef struct GeneratingFunc {
    void (*generate)(int *a, size_t n); // указатель на функцию генерации последоват.
    char name[64]; // имя генератора, используемое при выводе
} GeneratingFunc;

typedef struct SortFuncNComp {
    long long (*sort)(int *a, size_t n); // указатель на функцию сортировки
    char name[64]; // имя сортировки, используемое при выводе
} SortFuncNComp;

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName);

void checkNComp(long long (*sortFunc)(int *, size_t),
                void (*generateFunc)(int *, size_t),
                size_t size, char *experimentName);


void inputArray(int *a, size_t n);

void outputArray(const int *a, size_t n);

void swap(int *a, int *b);

//пузырьковая сортировка
void bubbleSort(int *a, size_t n);

// сортировка выбором
void selectionSort(int *a, size_t n);

//сортировка вставками
void insertionSort(int *a, size_t n);

//сортировка расческой
void combSort(int *a, size_t n);

//сортировка Шелла
void shellSort(int *a, size_t n);

//цифровая сортировка
void radixSort(int *a, size_t n);

long long getSelectionSortNComp(int *a, size_t n);

long long getBubbleSortNComp(int *a, size_t n);

long long getInsertionSortNComp(int *a, size_t n);

long long getCombSortNComp(int *a, size_t n);

long long getShellSortNComp(int *a, size_t n);

long long getRadixSortNComp(int *a, size_t n);

#endif //LABSORTING_SORTINGALGORITHMS_H

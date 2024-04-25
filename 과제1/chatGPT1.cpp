#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NUM 100000

// �Ҽ� �Ǻ� �Լ�
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int n;
    int numbers[MAX_NUM];
    int sortedNumbers[MAX_NUM];
    int sortedCount = 0;
    int primes[MAX_NUM];
    int primeCount = 0;
    clock_t start, end;
    double cpu_time_used;

    // ����ڷκ��� �Է� �ޱ�
    printf("Input the number of numbers to process: ");
    scanf("%d", &n);

    while (n < 2 || n > 30) {
        printf("Invalid input. Input the number of numbers to process: ");
        scanf("%d", &n);
    }

    printf("Input the numbers to be processed: ");

    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    // �Է� ���� ���� �����ϱ�
    for (int i = 0; i < n; i++) {
        bool isDuplicate = false;
        for (int j = i + 1; j < n; j++) {
            if (numbers[i] == numbers[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            sortedNumbers[sortedCount++] = numbers[i];
        }
    }

    for (int i = 0; i < sortedCount; i++) {
        for (int j = i + 1; j < sortedCount; j++) {
            int start = sortedNumbers[i];
            int end = sortedNumbers[j];
            int primeNum = 0;

            for (int k = start; k <= end; k++) {
                if (isPrime(k)) {
                    primeNum++;
                }
            }

            primes[primeCount++] = primeNum;
            printf("Number of prime numbers between %d, %d: %d\n", start, end, primeNum);
        }
    }

    // ���� �ð� ����
    start = clock();

    // ������� ����� �Ϸ��� �������� ���α׷� ������ �����ϴ�.

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Total execution time using C is %lf seconds!\n", cpu_time_used);
    return 0;
}

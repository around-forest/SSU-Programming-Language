#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(void) {
	int n;
	
	do {
		printf(">> Input the number of numbers to process: ");
		scanf("%d", &n);

		if (n < 2 | n > 30) {
			printf("*Warnning* number of numbers should be between 2 to 30\n\n");
		}
	} while (n < 2 | n > 30);

	int array[n] = {0};

	printf(">> Input the numbers to be processed: \n");

	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d", &k);
		array[i] = k;
	}
	
	time_t start = clock();

// 정렬 
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (array[i] > array[j]) {
				int temp = array[j];
				array[j] = array[i];
				array[i] = temp;
			}
		}
	}

// 소수 개수 반환
	for(int i = 0; i < n-1; i++){
		int count = 0;
		
		while(array[i] == array[i+1]){
			i++;
		}
		
		for(int j = array[i]; j <= array[i+1]; j++){
			int temp = 0;
			for(int k = 2; k < j; k++){
				if((j%k) == 0){
					temp++;
				}
			}
			if(temp == 0){
				count++;
			}
		}
		
		printf("Number of prime numbers between %d, %d: %d\n", array[i], array[i+1], count);
	} 
	
	time_t end = clock();
	printf("\nTotal execution time using C is %lf seconds!", (double)(end - start) / CLOCKS_PER_SEC);
}


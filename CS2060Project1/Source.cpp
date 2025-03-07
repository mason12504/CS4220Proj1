#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(char a[]);

int main(void) {
	char str1[] = "12345";
	size_t mainsizeof1 = sizeof(str1);
	printf("Size of str1 in main: %zu\n", mainsizeof1);

	char str2[] = "1234567890123456789";
	size_t mainsizeof2 = sizeof(str2);
	printf("Size of str2 in main: %zu\n", mainsizeof2);

	char str3[] = "12";
	size_t mainsizeof3 = sizeof(str3);
	printf("Size of str2 in main: %zu\n", mainsizeof3);

	

	printf("\nsize of string 1 ");
	printArray(str1);

	printf("\nsize of string 2 ");
	printArray(str2);

	printf("\nsize of string 3 ");
	printArray(str3);

	int myint = 1000;

	printf("\n size of a pointer: %zu \n", sizeof(&myint));
}
void printArray(char a[]) {
	size_t sizevar = sizeof(a);
	printf("in printArray: %zu\n ", sizevar);
	for (size_t i = 0; i < sizevar; i++) {
		printf("%c", a[i]);
	}
}
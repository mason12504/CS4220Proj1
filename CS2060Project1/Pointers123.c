// Project 3 Implimentation
// Mason Andersen
// CS 2060
// 4-25-2024
// 
// ** WRITTEN USING WINDOWS 10 OPERATING SYSTEM **
//
// This program allows an admin to create services for multiple rideshare companies, and take rides from users
// An administrator enters cost parameters, and can see a daily summary of the rides and ratings
// Riders are able to select companies, view immediate ride details, and give ratings of the ride experience
// Each rideshare has its own parameters and surveys, and a unique summary printed to an output file

#include <stdio.h>   // input output
#include <stdlib.h>  // for rand
#include <time.h>    // for srand seed
#include <stdbool.h> // for boolean variable in input validation
#include <string.h>  // strcmp etc
#include <math.h>	// used in getAlphabeticalRank

int main() {
	int myarray[10][10] = {0};
	int value = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			myarray[i][j] = value;
			value = value + 1;
			
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int value = myarray[i][j];
			printf("ptr: %d \n ", &myarray[i][j]);
			printf("%d ", myarray[i][j]);
		}
	}
	return 0;
}
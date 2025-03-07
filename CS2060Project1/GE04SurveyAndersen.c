// This program gets and analyzes survey data for a rideshare company

#include <stdio.h>

// define constants for array size
#define SURVEY_CATEGORIES 3
#define RIDER_COUNT 7

// function prototypes
void getRatings(int mainArr[][SURVEY_CATEGORIES], const char* categoriesArr[], int min, int max, int* riderCount);
void printCategories(const char* categories[], size_t totalCategories);
void printSurveyResults(const int surveyArr[][SURVEY_CATEGORIES], const char* categoriesArr[], const int* riderCount);
void calculateCategoryAverages(const int surveyArr[][SURVEY_CATEGORIES], double averages[], const int* riderCount);
void printCategoryData(const double averages[], const char* categoriesArr[]);

int main(void){

	// define arrays for storing ratings and averages
	// initialize to 0 so it sets every value to 0 instead of junk
	int rideshareSurvey[RIDER_COUNT][SURVEY_CATEGORIES] = { 0 };
	double categoryAverages[SURVEY_CATEGORIES] = { 0 };

	// store the categories as strings 
	const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };

	// initialize ridercount to 0, pass its address 
	int riderCount = 0; 

	// run the main functions
	// riderCount given as address so functions can all use and edit the same variable
	getRatings(rideshareSurvey, surveyCategories, 5, 1, &riderCount);
	printSurveyResults(rideshareSurvey, surveyCategories, &riderCount);
	calculateCategoryAverages(rideshareSurvey, categoryAverages, &riderCount);
	puts("");
	printCategoryData(categoryAverages, surveyCategories);
	return 0;
}

// code given from ge04
void printCategories(const char* categories[], size_t totalCategories)
{
	//loop to display each category horizontally
	printf("%s", "Rating Categories:\t");
	for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
	{
		printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
	}
	puts(""); // start new line of output
}

// gets ratings for each category from user
// stops after getting input from 5 riders
// Parameters:
//	int mainArr[] the array that the user input is stored in
//  const char* categoriesArr[] the array with category names
//  int min and max the range of valid user input (currently unused)
//  int *riderCount the number of riders whose surveys have been processed
//
//  const used for categories as they should not change, mainArr not const since it must be changed by function
// No return value
// 
void getRatings(int mainArr[][SURVEY_CATEGORIES], const char* categoriesArr[], int min, int max, int *riderCount) {
	printf("We want to know how your experience was on your ride today. Using the rating system %d to %d enter your rating for each category:\n", min, max);

	printCategories(categoriesArr, SURVEY_CATEGORIES);

	// prompt for input until 5 riders reached
	for (int riders = 0; riders < 5; riders++) {
		*riderCount = *riderCount + 1;
		printf("Rider %d: ", riders+1);

		// for every rider get their input for each category
		for (int category = 0; category < SURVEY_CATEGORIES; category++) {
			printf("\nEnter the rating for \n %d %s:", category+1, categoriesArr[category]);
			scanf("%d", &mainArr[riders][category]);
		}
		
	}
	
}

// outputs the survey results array with useful formatting for the user
// Parameters
//  const int surveyArr[] the array from which to read results for output
//  const char* categoriesArr[] the array storing category strings
//  const int* riderCount the number of riders (how far in the array to output)
//  all address params constant since they are read-only
// No returns
void printSurveyResults(const int surveyArr[][SURVEY_CATEGORIES], const char* categoriesArr[], const int* riderCount) {
	
	printCategories(categoriesArr, SURVEY_CATEGORIES);

	// for each rider (row in array) print the survey number
	for (int riders = 0; riders < *riderCount; riders++) {
		printf("Survey %d: \t\t", riders + 1);

		// for each category (column in array) print the user input stored
		for (int category = 0; category < SURVEY_CATEGORIES; category++) {
			printf("\t%d\t\t", surveyArr[riders][category]);	// \t is tabs for format allignment
		}

		// add a newline for formatting
		puts("");
	}
}

// finds the average of all rider responses in each category
// Parameters
//  surveyArr[] the array to read rider responses from
//  averages[] the array to store calculated averages
//  riderCount the number of riders processed 
// No return value
void calculateCategoryAverages(const int surveyArr[][SURVEY_CATEGORIES], double averages[], const int* riderCount) {

	// initialize a temporary total to calculate each average value
	int tempTotal = 0;

	// for each category find the average value
	for (int category = 0; category < SURVEY_CATEGORIES; category++) {
		tempTotal = 0;		// reset total for each category

		// get the sum of values in a given category
		for (int result = 0; result < *riderCount; result++) {
			tempTotal = tempTotal + surveyArr[result][category];
		}
		// calculate and store average value, cast to double for decimal precision
		averages[category] = (double) tempTotal / *riderCount;
	}
	
}

// outputs calculated category averages 
// Parameters
//  averages[] the array averages are stored in
//  categoriesArr[] the array category strings are stored in
// No return value
void printCategoryData(const double averages[], const char* categoriesArr[]) {
	printCategories(categoriesArr, SURVEY_CATEGORIES);
	printf("Rating Averages: \t");

	for (int category = 0; category < SURVEY_CATEGORIES; category++) {
		printf("\t%0.1lf\t\t", averages[category]);		// \t tabs for format alignment, 0.1lf for 1 decimal precision on a double
	}
		
}
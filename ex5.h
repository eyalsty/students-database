/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 01
* Exercise name: ex5
************************/

#define NUMBER_OF_STUDENTS 50
#define SIZE_NAME_AND_LNAME 42
#define SIZE_NAME 21
#define NUMBER_OF_COURSE 5
#define END_OF_LINE_SIZE 1
#define SIZE_OF_LINE 202
#define EMPTY -1
#define ERROR -1
#define SUCSSES 1
#include<string.h>

//insert new student to the database with his courses and grade, or update an existing student.
int InsertStudent(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS], int grades[][NUMBER_OF_COURSE],
	char nameOfCourse[][NUMBER_OF_STUDENTS][SIZE_NAME], int* numOfStudP);

//for operation 2: recieve name and last name from user to delete, and remove all his information from the database
int DeleteStudent(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS], int grades[][NUMBER_OF_COURSE],
	char nameOfCourse[][NUMBER_OF_STUDENTS][SIZE_NAME], int *numOfStudP);

/*for operation 3 or 4: print new aggregation menu for the user and print the fitting students and values
according to the selected aggregation*/
int PrintByAggregation(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS], int grades[][NUMBER_OF_COURSE], int* numOfStudP, int operation);
//print the menu
void PrintMainMenu();
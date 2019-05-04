/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 01
* Exercise name: ex5
************************/

#include<stdio.h>
#include "ex5.h"

int main()
{
	char names[NUMBER_OF_STUDENTS][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE] = { 0 };
	int indexs[NUMBER_OF_STUDENTS];
	int grades[NUMBER_OF_STUDENTS][NUMBER_OF_COURSE];
	char nameOfCourse[NUMBER_OF_COURSE][NUMBER_OF_STUDENTS][SIZE_NAME] = { 0 };
	int operation = EMPTY;
	char dummy;
	int i, j;
	int numOfStud = 0;
	//initialize the indexs array to be empty (-1)
	for (i = 0;i < NUMBER_OF_STUDENTS;i++) {
		indexs[i] = EMPTY;
		//initialize the grades array to be empty (-1)
		for (j = 0;j < NUMBER_OF_COURSE;j++)
		grades[i][j] = EMPTY;
	}
	//print the main menu
	PrintMainMenu();
	do
	{
		scanf("%d%c", &operation, &dummy);
		switch (operation)
		{
		case 0:
		{
			break;
		}
		//if case 1
		case 1:
		{
			//check for free space to add new student, if number of students is full (50) print error
			if (numOfStud > NUMBER_OF_STUDENTS - 1)
			{
				printf("Error: there is no more space.\n");
			}
			//if there is room go to function "InsertStudent", if error was returned print invalid name or grade
			else if (InsertStudent(names, indexs, grades, nameOfCourse, &numOfStud) == ERROR)
			{
				printf("Error: invalid name or grade.\n");
			}
			printf("Select the next operation (insert 5 for complete menu).\n");
			break;
		}
		//if operation is 2
		case 2:
		{
			DeleteStudent(names, indexs, grades, nameOfCourse, &numOfStud);
			printf("Select the next operation (insert 5 for complete menu).\n");
			break;
		}
		case 3:
			//if operation is 3 or 4
		case 4:
		{
			//if no students in the database print error
			if (numOfStud == 0)
			{
				printf("Error: there are no students.\n");
			}
			//if there are students run the function "PrintByAggregation"
			else {
				PrintByAggregation(names, indexs, grades, &numOfStud, operation);
			}
			printf("Select the next operation (insert 5 for complete menu).\n");
			break;
		}
		case 5:
		{
			//print the main menu
			PrintMainMenu();
			break;
		}
		default:
		{
			//if different integer was input print error
			printf("Error: unrecognized operation.\n");
			printf("Select the next operation (insert 5 for complete menu).\n");
			break;
		}
		}
		//continue as long as operation is not equal 0, if its 0 - stop.
	} while (operation != 0);
	return 0;
} 








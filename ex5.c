/************************
* Student name: Eyal Styskin
* Student: 206264749
* Course Exercise Group: 01
* Exercise name: ex5
************************/

#include<stdio.h>
#include "ex5.h"

/*******************************************************************************************************************
* Function Name: insertCourse
* Input: char studentCourses[][], int index, char courseBuffer[],int gradesBuffer[] .
* Output: int
* Function Operation: The function gets the input entered between the symbol ':' or ';' To the mark ';' from the
					  function "insertStudent" .
					  In this range, a course name and the grade of the course have to appear, so the function
					  checks the following conditions:    The length of the course name is no greater than
					  20 letters and consists only of letters and spaces.
					  There is a comma (,) which separates the course name from the grade.
					  The grade is between 0 and 100 and consists only of numbers.
					  After the function makes sure that there is a course and a grade, and it is correct,
					  it returns 1 (success), otherwise it returns 0 (error).
********************************************************************************************************************/

int InsertCourse(char studentCourses[][SIZE_NAME], int index, char courseBuffer[SIZE_OF_LINE],
	int gradesBuffer[NUMBER_OF_COURSE])
{
	int i = 0, writeIndex = 0, flag = 0, nameSize = 0, grade = 0, thereIsGrade = 0;
	//a while loop to check every char until it reaches comma(,)
	while (courseBuffer[i] != ',')
	{
		//ignore spaces before the course name
		if (courseBuffer[i] != ' ' || flag == 1)
		{
			//if a not-space char appeares it means that its the courses name, and the flag int changes to 1.
			if (flag == 0) {
				flag++;
			}
			//condition to check if the input consists only of uppercase/lowercase letters and spaces.
			if (courseBuffer[i] > 'z' || (courseBuffer[i] < 'A' && courseBuffer[i] != ' ') ||
				(courseBuffer[i] > 'Z'&&courseBuffer[i] < 'a')) {
				return ERROR;
			}
			//copy the input course to a new temporary courses array.
			studentCourses[index][writeIndex] = courseBuffer[i];
			//the next writing index
			writeIndex++;
			//increase the size of the new name if the char inserted
			nameSize++;
		}
		//check the course name to be less then 20 chars
		if (nameSize > SIZE_NAME - 1) {
			return ERROR;
		}
		//next reading index
		i++;
	}
	//put a \0 at the end of the courses name
	studentCourses[index][writeIndex] = 0;
	//if no course name was entered return error
	if (writeIndex == 0) {
		return ERROR;
	}
	i++;
	//continue reading after the comma until the ';' sign.
	while (courseBuffer[i] != ';') {
		//spaces after the grade are not illegal, ERROR being returned
		if ((courseBuffer[i] == ' ') && (thereIsGrade == 1)) {
			return ERROR;
		}
		//if a not-space char appeared means there is a grade
		if (courseBuffer[i] != ' ') {
			thereIsGrade = 1;
			//check if this char is a number between 0 and 9.
			if ((courseBuffer[i] < '0') || (courseBuffer[i] > '9'))
			{
				return ERROR;
			}
			//change the grade from char to an int
			grade *= 10;
			grade += courseBuffer[i] - '0';
		}
		i++;
	}
	//insert the grade integer to an temporary array of grades
	gradesBuffer[index] = grade;
	//check that the insert grade is legal (between 0 and 100)
	if (grade > 100 || thereIsGrade == 0) {
		return ERROR;
	}
	return SUCSSES;
}

/*******************************************************************************************************************
* Function Name:DecreaseIndex
* Input: int i, char names[][], int indexs[)
* Output: -
* Function Operation: The function recieves the index in the array where space needed to be made and moves all the
						names one place forward.
						She starts from the last student in the array, advances him one forward and then continues
						to the other students one after the other until it reaches the needed index.
						Then it stops when the index is available.
********************************************************************************************************************/

void DecreaseIndex(int i, char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE], int indexs[NUMBER_OF_STUDENTS])
{
	//set j to one place after the index
	int j = i + 1;
	//loop to find the last student in the array
	while (j < NUMBER_OF_STUDENTS && names[j] != 0)
	{
		j++;
	}
	//as long as it didnt reach the needed-space index, it decreases all of the students by one index.
	for (;j > i;j--) {
		strcpy(names[j], names[j - 1]);
		indexs[j] = indexs[j - 1];
	}
}

/*******************************************************************************************************************
* Function Name:AddNames
* Input: char nameAndLname[], char names[][], int indexs[]
* Output: int (index or ERROR(-1))
* Function Operation: The function receives a valid name and last name (after check) from the function "insertStudent".
					   The function searches for a free spot in the student's general naming array and sorts it out
					   at the same time.  In case that an old name is already in the place where the new one should
					   enter, the function gives it room by summoning another auxiliary function that takes the
					   whole array one place down from the desired location.
********************************************************************************************************************/

int AddNames(char nameAndLname[SIZE_NAME_AND_LNAME],
	char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS])
{
	int i;
	//loop for all the students in the array
	for (i = 0;i < NUMBER_OF_STUDENTS;i++) {
		//if the spot is empty copy the name to that place and set indexs to that place to be empty
		if (names[i][0] == 0) {
			strcpy(names[i], nameAndLname);
			indexs[i] = EMPTY;
			//return the the index of the name in the names array.
			return i;
		}
		//compare the input name to the names in the array
		int compare = strcmp(names[i], nameAndLname);
		//
		if (compare == 1) {
			DecreaseIndex(i, names, indexs);
			strcpy(names[i], nameAndLname);
			indexs[i] = EMPTY;
			//return the the index of the name in the names array.
			return i;
		}
		else if (compare == 0) {
			//return the the index of the name in the names array.
			return i;
		}
	}
}

/*******************************************************************************************************************
* Function Name:ExistStudCourse
* Input: char nameOfCourse[][][], int gradesBuffer[],char studentCourses[][], int grades[][], int index
* Output: int
* Function Operation: The function is an auxiliary function of "AddCourse" and indicates that the student has
					  already entered the system and and update is needed.
					  If the inserted course already exists, the function update its grade.
                      If a new course has been added, it will search for a free place on the student's list of 
					  courses and put the course and the grade there.
					  There is a limit to 5 courses, therefore, The function will return an error when attempting
					  to insert the sixth course and no update or new addition of the course has been made.
********************************************************************************************************************/

int ExistStudCourse(char nameOfCourse[][NUMBER_OF_STUDENTS][SIZE_NAME], int gradesBuffer[NUMBER_OF_COURSE],
	char studentCourses[][SIZE_NAME], int grades[][NUMBER_OF_COURSE], int index)
{
	int i = 0, courseIndex = 0;;
	//a boolian integer to indicate if any change has been made(course added or update)
	int existCourse = 0;
	//i is the number of course recieved from input
	while (i < NUMBER_OF_COURSE)
	{
		//corseIndex is the number of course and grade that the student has in his arrays
		while (courseIndex < 5)
		{
			//compare exist course with new inputed course
			int compare = strcmp(nameOfCourse[courseIndex][index], studentCourses[i]);
			//if the comparison equal, update the grade and change the boolian to exist
			if (compare == 0)
			{
				grades[index][courseIndex] = gradesBuffer[i];
				existCourse = 1;
				break;
			}
			//if the courses differ, the check database courses array, if its empty, insert the new course.
			else {
				if (nameOfCourse[courseIndex][index][0] == 0)
				{
					//copy the course name and his grade.
					strcpy(nameOfCourse[courseIndex][index], studentCourses[i]);
					grades[index][courseIndex] = gradesBuffer[i];
					//change boolian to exist
					existCourse = 1;
					break;
				}
			}
			//check next course index
			courseIndex++;
		}
		//after all course indexes were checked. reset it and increase i.
		courseIndex = 0;
		i++;
	}
	//return the boolian int (SUCCESS(1) OR ERROR (-1))
	return existCourse;
}

/*******************************************************************************************************************
* Function Name:AddCourse
* Input: char nameOfCourse[][][], int gradesBuffer[],char studentCourses[][], int grades[][], int index
* Output: -
* Function Operation: The function adding the student's new courses and grades to the general courses and grades
		   arrays (in the same index).
		   If the student is already in the system the function send his courses and grades to another function
		   that updates his data.
********************************************************************************************************************/

int AddCourse(char nameOfCourse[][NUMBER_OF_STUDENTS][SIZE_NAME], int gradesBuffer[NUMBER_OF_COURSE],
	char studentCourses[][SIZE_NAME], int grades[][NUMBER_OF_COURSE], int index)
{
	int i, j;
	int existCourse = 0;
	/*index is the the value in the indexs array at the student's name place. so it equals to the index of this 
	student's courses and grades in the courses names and grades arrays. if empty = new student  */
	if (index == EMPTY)
	{
		//a loop to go through all the students
		for (i = 0; (i < NUMBER_OF_STUDENTS && existCourse == 0); i++)
		{
			//condition to find an empty spot for the new student
			if (nameOfCourse[0][i][0] == 0)
			{
				//a loop to copy all the new courses and grades to the array in the appropriate place
				for (j = 0; j < NUMBER_OF_COURSE; j++)
				{
					strcpy(nameOfCourse[j][i], studentCourses[j]);
					grades[i][j] = gradesBuffer[j];
					//stop the loop and return the index when it finishes copy the courses
					if (gradesBuffer[j] == EMPTY)
						return i;
				}
			}
		}
		return i;
	}
	//if index is not empty, it means that this student was already in the database and needs an update.
	else {
		//function to update the student's courses and grades, if no new courses exist or no updates, it returns ERROR
		if (ExistStudCourse(nameOfCourse, gradesBuffer, studentCourses, grades, index) == 0)
			return ERROR;
		return index;
	}
}

/*******************************************************************************************************************
* Function Name:checkFullName
* Input: char nameBuffer[],char nameOfCourse[].
* Output: int 
* Function Operation: The function receives a name and last name as inputed from the function "insertStudent"
					 and checks the following requirements: None of the names are longer than 20 characters.
					 The name is composed only of smaller/ upper letters and spaces.
					 Must be entered both first and last name.
					 Ignoring unnecessary spaces that appear before the name or last name.
					 If all is correct, the name is transferred to a one-dimensional array and returns the index
					 of the input reading. If not, the function returns an error (-1).
********************************************************************************************************************/

int CheckFullName(char nameBuffer[SIZE_OF_LINE], char nameAndLname[SIZE_NAME_AND_LNAME])
{
	int nameSize = 0, writeIndex = 0, i = 0, beforeFnameOrAfter = 0;
	//read the name buffer until the \0
	while (nameBuffer[i] != 0)
	{
		//condition to check if the input consists only of uppercase/lowercase letters and spaces.
		if ((nameBuffer[i] == ' ') || (nameBuffer[i] >= 'A' && nameBuffer[i] <= 'Z') ||
			(nameBuffer[i] >= 'a' && nameBuffer[i] <= 'z'))
		{
			//if the char is a not space, we start reading
			if (nameBuffer[i] != ' ' || beforeFnameOrAfter == 2)
			{
				//beforeFnameOrAfter changes to 1, indicates we read first name
				if (beforeFnameOrAfter == 0)
				{
					beforeFnameOrAfter = 1;
				}
				//beforeFnameOrAfter changes to 2, indicates we read last name
				if (beforeFnameOrAfter == -1)
				{
					beforeFnameOrAfter = 2;
				}
				//increase the length size of the name
				nameSize++;
				//copy the name to a new temporary name and last name array
				nameAndLname[writeIndex] = nameBuffer[i];
				writeIndex++;
				//if the name is longer then 20 chars
				if (nameSize > SIZE_NAME -1) {
					return ERROR;
				}i++;
			}
			//if a space char read read
			else
			{
				// first name already been read and now there s a space
				if (beforeFnameOrAfter == 1) {
					beforeFnameOrAfter = -1;
					//reset the name size to 0
					nameSize = 0;
					//put a space between the first and the last name
					nameAndLname[writeIndex] = ' ';
					//increase the writing and the reading index
					writeIndex++;
					i++;
				}
				else {
					//increase reading index
					i++;
				}
			}
		}
		else {
			return ERROR;
		}
	}
	//put \0 on the end of the name and last name array
	nameAndLname[writeIndex] = 0;
	//if no last name was entered
	if (beforeFnameOrAfter != 2)
	{
		return ERROR;
	}
	//return the reading index
	return i;
}

/*******************************************************************************************************************
* Function Name:insertStudent
* Input: char names[][],int indexs[],int grades[][],char nameOfCourse[][][], int* numOfStudP.
* Output: int (1,-1)
* Function Operation: The function gets input from the user containing the student's name, his courses, and the grades.
*					 afterwards the input being sent to auxiliary functions, who check his correctness.
*					 If it is valid and meets all the conditions, I put the student in the database and print a message
*					 that the student was added.
*					 If the student already exists and I just updated the grades then the message that the 
*					 student has been updated will be printed.
********************************************************************************************************************/

int InsertStudent(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS], int grades[][NUMBER_OF_COURSE],
	char nameOfCourse[][NUMBER_OF_STUDENTS][SIZE_NAME], int* numOfStudP)
{
	int addCourseVal = 0;
	int studIndex,index, indexVal;
	char buffer[SIZE_OF_LINE] = { 0 };
	char nameBuffer[SIZE_OF_LINE];
	char nameAndLname[SIZE_NAME_AND_LNAME];
	int gradesBuffer[NUMBER_OF_COURSE];
	char studentCourses[NUMBER_OF_COURSE][SIZE_NAME] = { 0 };
	char courseBuffer[SIZE_OF_LINE];
	int numberOfCourse = 0;
	int writeIndex = 0, i = 0, k = 0, j = 0;
	//initialize the array to -1
	for (k = 0;k < NUMBER_OF_COURSE;k++) {
		gradesBuffer[k] = EMPTY;
	}
	//recieve input from user in max line of 202 (200 + \0 + \n)
	fgets(buffer, SIZE_OF_LINE, stdin);
	//a loop to copy the input (name and last name) until ':' or \n to an array 
	while (buffer[j] != ':' && buffer[j] != '\0')
	{
		nameBuffer[j] = buffer[j];
		j++;
	}
	// put a \0 in the last index of the array.
	nameBuffer[j] = 0;
	//the function "CheckFullName" returns the reading index of the input or ERROR
	i = CheckFullName(nameBuffer,nameAndLname);
	if (i == ERROR)
	{
		return ERROR;
	}
	//add +1 to i in order to continue the reading after the ':' sign.
	i++;
	writeIndex = 0;
	//a loop to copy the continue into new temporary array, until it reaches the end of the line.
	while (buffer[i] != '\n'&&buffer[i] != 0 && numberOfCourse < 5) {
		courseBuffer[writeIndex] = buffer[i];
		writeIndex++;
		//if it reached the sign ';' it means that a course and a grade inputed.
		if (buffer[i] == ';') {
			//end the reading array
			courseBuffer[writeIndex + 1] = 0;
			//restart the reading index
			writeIndex = 0;
			//send the course and the grade to a function that checks its correction and copies it to new 2-d array
			addCourseVal = InsertCourse(studentCourses, numberOfCourse, courseBuffer, gradesBuffer);
			//if the function returns ERROR
			if (addCourseVal == ERROR) {
				return ERROR;
			}
			//counter to the number of courses
			numberOfCourse++;
		}
		//next reading index
		i++;
	}
	//if writeIndex wasnt reset. it means the input did not end with ';'
	if (writeIndex != 0)
	{
		return ERROR;
	}
	//add the names to the all of the students names array
	studIndex = AddNames(nameAndLname, names, indexs);
	// set index to be the value indexs[studIndex] contains (the index of its grade and course)
	index = indexs[studIndex];
	//indexVal equals the returned value (ERROR or the course's index)
	indexVal = AddCourse(nameOfCourse, gradesBuffer, studentCourses, grades, index);
	if (indexVal == ERROR)
		return ERROR;
	//i set the new index of the courses and grades to be the value in the array indexs(at the student's index)
	else
	{
		indexs[studIndex] = indexVal;
	}
	//if the value is -1 , it means the student is new
	if (index == EMPTY)
	{
		printf("Student \"%s\" added.\n", nameAndLname);
		*numOfStudP += 1;
	}
	//if the value isnt -1 it means its already been set and was updated.
	else {
		printf("Student \"%s\" updated.\n", nameAndLname);
	}
	return SUCSSES;
}

/*******************************************************************************************************************
* Function Name:DeleteStudent
* Input: char names[][], int indexs[], int grades[][], char nameOfCourse[][][], int *numOfStudP
* Output: 0
* Function Operation: The function of task 2. recieve from the user a name that needs to be deleted.
					  If the entered name is invalid, the function will return an error message.
					  If the entered name is valid, the function will search for it in the names array. if it is
					  found, it will delete the student from the database. If the inserted name does not exist in
					  names array, an error "student does not exist" message will be printed.
********************************************************************************************************************/

int DeleteStudent(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS], int grades[][NUMBER_OF_COURSE],
	char nameOfCourse[][NUMBER_OF_STUDENTS][SIZE_NAME], int *numOfStudP)
{
	char buffer[SIZE_NAME];
	char nameBuffer[SIZE_NAME];
	char nameAndLname[SIZE_NAME_AND_LNAME];
	int compare, j,k, i = 0;
	//recieve from the user the name to delete
	fgets(buffer, SIZE_NAME_AND_LNAME, stdin);
	//copy the input to a temporary name array 
	while (buffer[i] != '\n')
	{
		nameBuffer[i] = buffer[i];
		i++;
	}
	//put a \0 in the end of the array
	nameBuffer[i] = 0;
	//send the inputed name to a function to check its correction. if ilegal, (ERROR (-1)) is returned
	if (CheckFullName(nameBuffer, nameAndLname) == ERROR)
	{
		printf("Error: invalid name.\n");
		return 0;
	}
	//a loop to go through all the students in the names array
	for (i = 0; i < NUMBER_OF_STUDENTS; i++)
	{
		//compare the input name to each student in the database
		compare = strcmp(names[i], nameAndLname);
		//if 0, found a comparison and the student exists in the array
		if (compare == 0)
		{
			/*this loop increases the index of all the students by 1, from one place after the exist
			student. in this way, he will be ran over and the next student will take his place*/
			for (j = i; j < *numOfStudP + 1; j++)
			{
				strcpy(names[j], names[j + 1]);
				indexs[j] = indexs[j + 1];
			}
			//after deleteing the student from the names array, i delete all of his grades
			grades[indexs[j]][0] = EMPTY;
			//a loop to go through all of this student'ss courses and to delete all of them.
			for (k = 0; k < NUMBER_OF_COURSE; k++)
			{
				nameOfCourse[k][indexs[j]][0] = 0;
			}
			//after all the data of this student was deleted, a message is printed
			printf("Student \"%s\" deleted.\n", nameAndLname);
			//decrease 1 from the student's counter
			*numOfStudP -= 1;
			return 0;
		}
	}
	//if not even one comparison was found, "student does not exist" message is printed
	if (compare != 0)
	{
		printf("Error: student name does not exist.\n");
		return 0;
	}
}

/*******************************************************************************************************************
* Function Name:AvgCalc
* Input: int allGrades[]
* Output: average grade ( 0-100)
* Function Operation: recieve one student's grades array with max of 5 grades.
					  the function calculates the average grade, and returns it.
********************************************************************************************************************/

int AvgCalc(int allGrades[])
{
	int sum = 0, avg = 0;
	int k = 0;
	int gradesCount = 0;
	//k is the number of the course (max 5 courses)
	while (k < NUMBER_OF_COURSE)
	{
		//if the checked index in the array is not empty (not -1), it being added to the sum
		if (allGrades[k] != EMPTY)
		{
			sum += allGrades[k];
			//counts the number of the calculated grades
			gradesCount++;
		}
		//check the next grade
		k++;
	}
	//the sum of the grade, divided by the number of grades, gives us the average grade.
	avg = sum / gradesCount;
	return avg;
}

/*******************************************************************************************************************
* Function Name:FindMaxGrade
* Input: int allGrades[]
* Output: maxGrade ( 0-100)
* Function Operation: recieve one student's grades array with max of 5 grades.
					  the function is looking for the highest grade in the array and returns it.
********************************************************************************************************************/

int FindMaxGrade(int allGrades[])
{
	//set highest grade to be -1, so the first grade will always be higher
	int highestGrade = EMPTY;
	int k = 0;
	//k is the number of the course (max 5 courses)
	while (k < NUMBER_OF_COURSE)
	{
		//condition to check if the checked grade is the highest.
		if (allGrades[k] > highestGrade)
		{
			highestGrade = allGrades[k];
		}
		//check next grade
		k++;
	}
	return highestGrade;
}
/*******************************************************************************************************************
* Function Name:FindMinGrade
* Input: int allGrades[]
* Output: lowest grade ( 0-100)
* Function Operation:recieve one student's grades array with max of 5 grades.
					  the function checks for the lowest grade in the array and returns it.
********************************************************************************************************************/

int FindMinGrade(int allGrades[])
{
	//set lowest grade to be 101, so the first grade will definately be lower
	int lowestGrade = 101;
	int k = 0;
	//k is the number of the course (max 5 courses)
	while (k < NUMBER_OF_COURSE)
	{
		//if the checked grade is the lowest, and the grade index is not empty (not -1 as set)
		if ((allGrades[k] < lowestGrade) && allGrades[k] != EMPTY)
		{
			lowestGrade = allGrades[k];
		}
		k++;
	}
	return lowestGrade;
}
/*******************************************************************************************************************
* Function Name:SumGrade
* Input: int allGrades[]
* Output: sum all of grades ( 0-500)
* Function Operation: recieve one student's grades array with max of 5 grades.
					  the function sums all the student's grades toegether and returns it.
********************************************************************************************************************/

int SumGrade(int allGrades[])
{
	int k = 0;
	int sum = 0;
	//k is the number of the course (max 5 courses)
	while (k < NUMBER_OF_COURSE)
	{
		//if the checked grade index is not empty (not -1) its being added to the total grades sum
		if (allGrades[k] != EMPTY)
		{
			sum += allGrades[k];
		}
		//check next grade
		k++;
	}
	return sum;
}
/*******************************************************************************************************************
* Function Name:CountGrades
* Input: int allGrades[]
* Output: number ofs grade (1-5)
* Function Operation: recieve one student's grades array with max of 5 grades.
					  the function counts how many grades does the student have and returns it.
********************************************************************************************************************/

int CountGrades(int allGrades[])
{
	int k = 0;
	//sets the grades counter to 0
	int counter = 0;
	while (k < NUMBER_OF_COURSE)
	{
		//if the grade index is not empty (not -1) it counts it as one grade
		if (allGrades[k] != EMPTY)
		{
			counter++;
		}
		//check next grade
		k++;
	}
	return counter;
}

/*******************************************************************************************************************
* Function Name:CheckMaxGrade
* Input: char names[][], int indexs[], int grades[][], int* numOfStudP, int(*func)(int*)
* Output: -
* Function Operation: An auxiliary function for task 3. the function receives the desired aggregation method
					  from the function PrintByAggregation. The function calculates the desired aggregation
					  for each student in the names array and then finds the highest value among all the students.
					  after it found, the name of the student 
********************************************************************************************************************/

void CheckMaxGrade(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE], int indexs[NUMBER_OF_STUDENTS],
	int grades[][NUMBER_OF_COURSE], int* numOfStudP, int(*func)(int*))
{
	int i;
	//set maxVal value to be -1, so the first value that will enter, definately will be higher.
	int maxVal = EMPTY;
	int current, studIndex;
	//loop to check the value returns from each student that exists in the database
	for (i = 0; i < *numOfStudP; i++)
	{
		//set current to be the value returned from the student
		current = func(grades[indexs[i]]);
		//if current is higher then the highest value, set the maxVal to be equal to current
		if (current > maxVal)
		{
			maxVal = current;
			//keep the index of the student with the highest value in an integer, to remember it
			studIndex = i;
		}	
	}
	//print the name of the student with the highest value, and its value
	printf("%s, %d\n", names[studIndex], maxVal);
}

/*******************************************************************************************************************
* Function Name:PrintAll
* Input: char names[][], int indexs[], int grades[][], int* numOfStudP, int(*func)(int*)
* Output: -
* Function Operation: An auxiliary function for task 4. the function receives the desired aggregation method
					  from the function PrintByAggregation. The function calculates the desired aggregation
					  for each student in the names array and then prints all of the students names and their 
					  aggregation value Sorted by lexicographic order from lowest to the highest.
********************************************************************************************************************/

void PrintAll(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE], int indexs[NUMBER_OF_STUDENTS],
	int grades[][NUMBER_OF_COURSE], int* numOfStudP, int(*func)(int*))
{
	int i, current;
	//loop to go through all the students that exist in the database
	for (i = 0; i < *numOfStudP; i++)
	{
		//current is the aggregation value that returned from the function
		current = func(grades[indexs[i]]);
		//print the name of the student and the value from the calculation function
		printf("%s, %d\n", names[i], current);
	}
}

/*******************************************************************************************************************
* Function Name:PrintByAggregation
* Input: char names[][], int indexs[], int grades[][], int* numOfStudP, int operation
* Output: int 0
* Function Operation: Function received after selecting operations 3 or 4.
					  The function prints a new menu to the user and receives the desired aggregation.
					  The aggregation is then sent to the appropriate functions (according to the selected opperation)
					  and those functions print the names of the students with the values ​​obtained after the
					  required calculation.
********************************************************************************************************************/

int PrintByAggregation(char names[][SIZE_NAME_AND_LNAME + END_OF_LINE_SIZE],
	int indexs[NUMBER_OF_STUDENTS], int grades[][NUMBER_OF_COURSE], int* numOfStudP, int operation)
{
	char aggregation;
	printf("Please select the aggregation method:\n");
	printf("\ta. Average grade.\n");
	printf("\tb. Maximal grade.\n");
	printf("\tc. Minimal grade.\n");
	printf("\td. Sum.\n");
	printf("\te. Count.\n");
	printf("\t0. Return the main menu.\n");
	scanf("%c", &aggregation);
	//if operation 3 chosen, we enter this condition and send the selected aggregation to function "CheckMaxGrade".
	if (operation == 3)
	{
		switch (aggregation)
		{
		case 'a':
		{
			//calculate highest avarage
			CheckMaxGrade(names, indexs, grades, numOfStudP, AvgCalc);
			break;
		}
		case 'b':
		{
			//calculate highest grade
			CheckMaxGrade(names, indexs, grades, numOfStudP, FindMaxGrade);
			break;
		}
		case 'c':
		{
			//calculate highest minimal grade
			CheckMaxGrade(names, indexs, grades, numOfStudP, FindMinGrade);
			break;
		}
		case 'd':
		{
			//calculate highest sum of grades
			CheckMaxGrade(names, indexs, grades, numOfStudP, SumGrade);
			break;
		}
		case 'e':
		{
			//calculate highest number of grades
			CheckMaxGrade(names, indexs, grades, numOfStudP, CountGrades);
			break;
		}
		default:
			//if 0 is entered , return to main function
			break;
		}
	}
	//if operation 4 chosen, we enter this condition and send the selected aggregation to function "PrintAll".
	if (operation == 4)
	{
		switch (aggregation)
		{
		case 'a':
		{
			//print all the students names sorted and their avarage grade
			PrintAll(names, indexs, grades, numOfStudP, AvgCalc);
			break;
		}
		case 'b':
		{
			//print all the students names sorted and their max grade
			PrintAll(names, indexs, grades, numOfStudP, FindMaxGrade);
			break;
		}
		case 'c':
		{
			//print all the students names sorted and their minimal grade
			PrintAll(names, indexs, grades, numOfStudP, FindMinGrade);
			break;
		}
		case 'd':
		{
			//print all the students names sorted and their sum of grades
			PrintAll(names, indexs, grades, numOfStudP, SumGrade);
			break;
		}
		case 'e':
		{
			//print all the students names sorted and their number of grades
			PrintAll(names, indexs, grades, numOfStudP, CountGrades);
			break;
		}
		default:
			//if 0 chosen, return to main function
			break;
		}
	}
	return 0;
}

void PrintMainMenu()
{
	printf("Please select the operation:\n");
	printf("\t0. Exit.\n");
	printf("\t1. Insert or update student grades.\n");
	printf("\t2. Delete student information.\n");
	printf("\t3. Print the student with maximal computed grade.\n");
	printf("\t4. Print all the students with their computed grades.\n");
	printf("\t5. Print the menu.\n");
}

	

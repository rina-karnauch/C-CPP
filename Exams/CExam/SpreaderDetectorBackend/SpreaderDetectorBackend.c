//
// Created by Rina Karnauch on 01/08/2020.
//

#include "SpreaderDetectorParams.h"

// LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// MACROS
#define ONE 1
#define FLOAT_ONE 1.0000000000f
#define EPSILON 0.00000000001
#define ZERO 0
#define FLOAT_ZERO 0.000f
#define MAIN_INFECTOR -1
#define MINUS_ONE -1
#define TWO 2
#define ARGS_AMOUNT 3
#define DECIMAL 10
#define ALLOC_SIZE 10

#define SPACE " "
#define MAX_LINE_LEN 1024
#define READ_ONLY "r"
#define WRITE "w"

// MSGS
#define ARGS_ERROR "Usage: ./SpreaderDetectorBackend <Path to People.in> <Path to Meetings.in>\n"
#define INPUT_ERROR "Error in input files.\n"
#define OUTPUT_ERROR "Error in output file.\n"


// STRUCTS
/**
 * a struct of a person.
 */
typedef struct Person
{
	int ID;
	int order;
	float age;
	float crnaRate;
	char *name;

} Person;

/**
 * a struct of line in the meeting file
 */
typedef struct meetLines
{
	int infectorID; // left value
	int infectedID; // right value
	float dist; // in meters
	float time; // in minutes
} meetLines;

// ENUMS
/**
 * enum for person's line indexes
 */
enum peopleLine
{
	name = 0,
	ID = 1,
	age = 2,
};

/**
 * enum for a meeting line indexes
 */
enum meetingLine
{
	infector = 0,
	infected = 1,
	dist = 2,
	time = 3,
};

// FUNCTIONS
/**
 * library error message
 */
void libraryError()
{
	fprintf(stderr, STANDARD_LIB_ERR_MSG);
	exit(EXIT_FAILURE);
}

/**
 * input file error message
 */
void inputError()
{
	fprintf(stderr, INPUT_ERROR);
	exit(EXIT_FAILURE);
}

/**
 * output file error message
 */
void outputError()
{
	fprintf(stderr, OUTPUT_ERROR);
	exit(EXIT_FAILURE);
}

/**
 * one of files error message
 */
void argsError()
{
	fprintf(stderr, ARGS_ERROR);
	exit(EXIT_FAILURE);
}

/**
 * a function to compare two person structs by their
 * probability to corona virus shit is getting real
 * @param p1: person p1
 * @param p2: perosn p2
 * @return: p1 if prob1 is bigger, p2 if prob2 is bigger, if they are the same
 * we shall return their order by their ID.
 */
int cmpProb(const void *p1, const void *p2);

/**
 * corona rate determination function
 * @param dist: dist between 2 people
 * @param time: time of distance
 * @return the probabilty of corona
 */
float crna(float dist, float time);

/**
 * a function to read a line
 * @param line: the line
 * @param p: the person we will initialize
 */
bool readPeopleLine(char *line, Person *p);

/**
 * a function to read a line of a meeting in the meetings file
 * @param line: the line
 * @param meet: the meeting
 * @return: true for success, false for failure
 */
bool readMeetingLine(char *line, meetLines *meet);

/**
 * a function to handle the people file
 * @param fPeople: a pointer to the opened file.
 * @param pArray: a pointer to an array of PERSON struct.
 * @return: true if read fine, false otherwise for failure.
 */
Person *personFileHandeling(FILE *fPeople, int *len);

/**
 * a function to read the meetings files
 * @param fMeetings: the pointer to meetings file
 * @param crnaMan: id of corona man.
 * @param len: length of mArray will be updated
 * @return: pointer to the array of meetLines
 */
meetLines *meetingsFileHandeling(FILE *fMeetings, int *len, int *crnaMan);


/**
 * a function to sort out the probabilities table
 * @param pArray: the people array
 * @param mArray: the meetings array
 * @param crnaMan: the C O R O N A - M A N
 */
void crnaRateTableModification(Person *pArray, meetLines *mArray, int crnaMan, int pArrayLen,
							   int mArrayLen);

/**
 * a function to output the final results
 * @param output: pointer to file
 * @param pArray: array of people
 * @param pArrayLen: len of array of people
 */
void fileOutput(FILE *output, Person **pArray, int pArrayLen);

/**
 * a function to compare two struccts by their ID, they are person structs
 * @param m1: first struct
 * @param m2: second struct
 * @return: -1 when first is before the second 1 otherwise, we know they are different
 */
int cmpID(const void *m1, const void *m2);

/**
 * binary search function
 * @param pArray: the array of person
 * @param start: the start index
 * @param end: end index
 * @param ID: ID we looking for
 * @return: pointer to the person struct we look for
 */
Person *binarySearch(Person *pArray, int start, int end, int ID);

/**
 * a function to sort the array of person by the prob's
 * @param pArray: person Array
 * @param pArrayLen: the length of the array
 * @return: false for failure with fail and true for success
 */
bool sortByProb(Person *pArray, int pArrayLen);

/**
 * a function to free and exit according to the method we need
 * @param func: function of exit
 * @param pArray: array of people.
 * @param meetingsArray: array of meetings.
 */
void freeAndExit(void (*func)(), Person **pArray, meetLines **meetingsArray, int pArrayLen);

/**
 * a function to finally free all memory after wokr
 * @param pArray: people's array
 * @param pArrayLen: array's len
 * @param mArray: meetings array
 */
void finalFree(Person **pArray, int pArrayLen, meetLines **mArray);

// ALLOCATION HANDELING

/**
 * a function to free and exit according to the method we need
 * @param func: function of exit
 * @param pArray: array of people.
 * @param meetingsArray: array of meetings.
 */
void freeAndExit(void (*func)(), Person **pArray, meetLines **meetingsArray,
				 const int pArrayLen)
{
	for (int i = 0; i < pArrayLen; i++)
	{
		char *p = (*pArray)[i].name;
		free(p);
		p = NULL;
	}

	if(pArray != NULL)
	{
		free(*pArray);
		pArray = NULL;
	}

	if(meetingsArray != NULL)
	{
		free(*meetingsArray);
		meetingsArray = NULL;
	}

	func();
}

/**
 * a function to finally free all memory after wokr
 * @param pArray: people's array
 * @param pArrayLen: array's len
 * @param mArray: meetings array
 */
void finalFree(Person **pArray, const int pArrayLen, meetLines **mArray)
{
	for (int i = 0; i < pArrayLen; i++)
	{
		char *p = (*pArray)[i].name;
		free(p);
		p = NULL;
	}

	free(*pArray);
	pArray = NULL;
	free(*mArray);
	mArray = NULL;
}

// IMPLEMENTATIONS
/**
 * a function to compare two person structs by their
 * probability to corona virus shit is getting real
 * @param p1: person p1
 * @param p2: perosn p2
 * @return: p1 if prob1 is bigger, p2 if prob2 is bigger, if they are the same
 * we shall return their order by their ID.
 */
int cmpProb(const void *p1, const void *p2)
{
	Person *pf = (Person *) p1;
	Person *ps = (Person *) p2;

	float crnaRatep1 = pf->crnaRate;
	float crnaRatep2 = ps->crnaRate;

	float comp = crnaRatep1 - crnaRatep1;

	if (crnaRatep1 > crnaRatep2)
	{
		return MINUS_ONE;
	}
	else if (crnaRatep1 < crnaRatep2)
	{
		return ONE;
	}
	if (comp < EPSILON && comp > (MINUS_ONE) * (EPSILON))
		// THEY ARE EQUAL
	{
		if (pf->order < ps->order)
		{
			return MINUS_ONE;
		}
		else
		{
			return ONE;
		}
	}

	return ZERO;
}

/**
 * corona rate determination function
 * @param dist: dist between 2 people
 * @param time: time of distance
 * @return the probabilty of corona
 */
float crna(const float dist, const float time)
{
	float denom = ((float) time) * ((float) MIN_DISTANCE);
	float nomen = ((float) dist) * ((float) MAX_TIME);

	return (float) (denom / nomen);
}

/**
 * a function to read a line
 * @param line: the line
 * @param p: the person we will initialize
 */
bool readPeopleLine(char *line, Person *p)
{
	char *newString = strtok(line, SPACE);

	char *endPtr = "\0";
	int j = 0;

	while (newString != NULL)
	{
		if (j == name)
		{
			p->name = (char *) malloc(sizeof(char) * (strlen(newString) + ONE));
			if (p->name == NULL)
			{
				return false; // ALLOC PROBELM
			}
			strcpy(p->name, newString);
		}
		else if (j == ID)
		{
			p->ID = (int) strtol(newString, &endPtr, DECIMAL);
		}
		else if (j == age)
		{
			p->age = (float) strtof(newString, &endPtr);
		}
		j = j + 1;
		newString = strtok(NULL, SPACE);
	}

	p->crnaRate = EPSILON;
	return true;
}

/**
 * a function to read a line of a meeting in the meetings file
 * @param line: the line
 * @param meet: the meeting
 * @return: true for success, false for failure
 */
bool readMeetingLine(char *line, meetLines *meet)
{
	char *newString = strtok(line, SPACE);

	char *endPtr = "\0";
	int j = 0;

	while (newString != NULL)
	{
		if (j == infector)
		{
			meet->infectorID = (int) strtol(newString, &endPtr, DECIMAL);
		}
		else if (j == infected)
		{
			meet->infectedID = (int) strtol(newString, &endPtr, DECIMAL);
		}
		else if (j == dist)
		{
			meet->dist = (float) strtof(newString, &endPtr);
		}
		else if (j == time)
		{
			meet->time = (float) strtof(newString, &endPtr);
		}

		j = j + 1;
		newString = strtok(NULL, SPACE);
	}

	return true;
}

/**
 * a function to handle the people file
 * @param fPeople: a pointer to the opened file.
 * @param pArray: a pointer to an array of PERSON struct.
 * @return: true if read fine, false otherwise for failure.
 */
Person *personFileHandeling(FILE *fPeople, int *len)
{
	int capacity = ALLOC_SIZE;
	char line[MAX_LINE_LEN + ONE];

	Person *pArray = (Person *) malloc(sizeof(Person) * ALLOC_SIZE);

	if (pArray == NULL)
	{
		/* fclose(fPeople);
		freeAndExit(libraryError, pArray, NULL); */
		return NULL;
	}

	int i = 0;
	while (fgets(line, MAX_LINE_LEN, fPeople) != NULL)
	{
		bool check = readPeopleLine(line, (&(pArray[i])));
		if (check == false)
		{
			return NULL;
		}

		pArray[i].order = i;
		i++;

		if (i == capacity)
		{
			capacity = capacity + ALLOC_SIZE;
			pArray = (Person *) realloc(pArray, sizeof(Person) * capacity);
		}

		if (pArray == NULL)
			// memory alloc problem
		{
			return NULL;
		}
	}

	*len = i;
	return pArray;
}

/**
 * a function to read the meetings files
 * @param fMeetings: the pointer to meetings file
 * @return: pointer to the array of meetLines
 */
meetLines *meetingsFileHandeling(FILE *fMeetings, int *len, int *crnaMan)
{
	int capacity = ALLOC_SIZE;
	char line[MAX_LINE_LEN + ONE];

	meetLines *mArray = (meetLines *) malloc(sizeof(meetLines) * ALLOC_SIZE);

	if (mArray == NULL)
	{
		return NULL;
	}

	int i = MAIN_INFECTOR;
	while (fgets(line, MAX_LINE_LEN, fMeetings) != NULL)
	{
		if (i == MAIN_INFECTOR)
		{
			char *endptr = "\0";
			char *newString = strtok(line, endptr);
			*crnaMan = (int) strtol(newString, &endptr, DECIMAL);
			i++;
			continue;
		}

		bool check = readMeetingLine(line, (&(mArray[i])));
		if (check == false)
		{
			return NULL;
		}

		i++;

		if (i == capacity)
		{
			capacity = capacity + ALLOC_SIZE;
			mArray = (meetLines *) realloc(mArray, sizeof(meetLines) * capacity);
		}

		if (mArray == NULL) // memory alloc problem
		{
			return NULL;
		}
	}

	*len = i;
	return mArray;
}

/**
 * a function to compare two struccts by their ID, they are person structs
 * @param m1: first struct
 * @param m2: second struct
 * @return: -1 when first is before the second 1 otherwise, we know they are different
 */
int cmpID(const void *m1, const void *m2)
{
	Person *p1 = (Person *) m1;
	Person *p2 = (Person *) m2;

	int id1 = p1->ID;
	int id2 = p2->ID;

	return (id2 - id1);
}

/**
 * binary search function
 * @param pArray: the array of person
 * @param start: the start index
 * @param end: end index
 * @param ID: ID we looking for
 * @return: pointer to the person struct we look for
 */
Person *binarySearch(Person *pArray, int start, int end, const int ID)
{
	if (end >= start)
	{
		int mid = start + (end - start) / TWO;

		if (pArray[mid].ID == ID)
		{
			return &pArray[mid];
		}
		if (pArray[mid].ID < ID)
		{
			return binarySearch(pArray, start, mid - ONE, ID);
		}
		return binarySearch(pArray, mid + ONE, end, ID);
	}
	return NULL;
}

/**
 * a function to sort out the probabilities table
 * @param pArray: the people array
 * @param mArray: the meetings array
 * @param crnaMan: the C O R O N A - M A N
 */
void crnaRateTableModification(Person *pArray, meetLines *mArray, const int crnaMan,
							   const int pArrayLen, const int mArrayLen)
{
	if (pArrayLen == ONE)
	{
		Person *coronaP = binarySearch(pArray, ZERO, pArrayLen, crnaMan);

		coronaP->crnaRate = FLOAT_ONE; // infector!
	}

	else if (pArrayLen < ONE || mArrayLen < ONE)
	{
		return;
	}

	Person *coronaP = binarySearch(pArray, ZERO, pArrayLen, crnaMan);

	coronaP->crnaRate = FLOAT_ONE; // infector!

	for (int i = 0; i < mArrayLen; i++)
	{
		int idInfected = mArray[i].infectedID;
		int idInfector = mArray[i].infectorID;

		Person *currentInfected = binarySearch(pArray, ZERO, pArrayLen, idInfected);
		Person *currentInfector = binarySearch(pArray, ZERO, pArrayLen, idInfector);

		float time = mArray[i].time;
		float dist = mArray[i].dist;

		float crnaRate = crna(dist, time);
		float prevCoronaRate = currentInfector->crnaRate;

		currentInfected->crnaRate = (float) (crnaRate * prevCoronaRate);
	}
}

/**
 * a function to output the final results
 * @param output: pointer to file
 * @param pArray: array of people
 * @param pArrayLen: len of array of people
 */
void fileOutput(FILE *output, Person **pArray, const int pArrayLen)
{
	Person *pArr = *pArray;
	for (int i = 0; i < pArrayLen; i++)
	{
		float crnaRate = pArr[i].crnaRate;
		char *name = pArr[i].name;

		unsigned long id = (unsigned long) pArr[i].ID;

		if (crnaRate >= MEDICAL_SUPERVISION_THRESHOLD)
		{
			fprintf(output, MEDICAL_SUPERVISION_THRESHOLD_MSG, name, id);
		}
		else if (crnaRate >= REGULAR_QUARANTINE_THRESHOLD)
		{
			fprintf(output, REGULAR_QUARANTINE_MSG, name, id);
		}
		else if (crnaRate >= FLOAT_ZERO)
		{
			fprintf(output, CLEAN_MSG, name, id);
		}

	}

	fclose(output);
}

/**
 * a function to sort the array of person by the prob's
 * @param pArray: person Array
 * @param pArrayLen: the length of the array
 * @return: false for failure with fail and true for success
 */
bool sortByProb(Person *pArray, const int pArrayLen)
{

	qsort(pArray, pArrayLen, sizeof(Person), cmpProb);

	FILE *output = fopen(OUTPUT_FILE, WRITE);

	if (output == NULL)
	{
		fclose(output);
		return false;
	}

	fileOutput(output, &pArray, pArrayLen);

	return true;
}

int main(int argc, char *argv[])
{
	if (argc != ARGS_AMOUNT)
	{
		argsError();
		// we got exit inside.
		return ONE;
	}

	// its two becuase people file given second
	FILE *fPeople = fopen(argv[ONE], READ_ONLY);
	if (fPeople == NULL)
	{
		fclose(fPeople);
		inputError();
		// we got exit inside
		return ONE;
	}

	int pArrayLen = 0;
	Person *pArray = personFileHandeling(fPeople, &pArrayLen);

	if (pArray == NULL)
	{
		fclose(fPeople);
		fPeople = NULL;

		// WE GOT AN ALLOC PROBELM IN personFileHandeling
		freeAndExit(libraryError, &pArray, NULL, pArrayLen); // exit inside.
		return EXIT_FAILURE;
	}

	qsort(pArray, pArrayLen, sizeof(Person), cmpID);

	fclose(fPeople);

	// its one becuase meetings file given first
	FILE *fMeetings = fopen(argv[TWO], READ_ONLY);
	if (fMeetings == NULL)
	{
		fclose(fMeetings);
		freeAndExit(inputError, &pArray, NULL, pArrayLen); // exit inside.
		return EXIT_FAILURE;
	}

	int mArrayLen = 0;
	int crnaMan = 0;
	meetLines *mArray = meetingsFileHandeling(fMeetings, &mArrayLen, &crnaMan);

	if (mArray == NULL)
	{
		fclose(fPeople);
		fPeople = NULL;

		// WE GOT AN ALLOC PROBELM IN personFileHandeling
		freeAndExit(libraryError, &pArray, &mArray, pArrayLen); // exit inside.
		return EXIT_FAILURE;
	}

	fclose(fMeetings);

	crnaRateTableModification(pArray, mArray, crnaMan, pArrayLen, mArrayLen);
	bool checkOutput = sortByProb(pArray, pArrayLen);

	if (!checkOutput)
	{
		freeAndExit(outputError, &pArray, &mArray, pArrayLen);
		return EXIT_FAILURE;
	}

	finalFree(&pArray, pArrayLen, &mArray);
	return EXIT_SUCCESS;
}
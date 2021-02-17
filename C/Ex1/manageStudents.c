#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ARR 43
#define INPUT_LEN 61
#define MIN_AGE 18
#define MAX_AGE 120
#define MIN_GRADE 0
#define MAX_GRADE 100
#define MIN_ID_LEN 1000000000
#define MAX_ID_LEN 9999999999
#define DIVIDOR 1000000000
#define MAX_CLASS 5500
#define EXIT_SUCCESS 1
#define EXIT_FAILURE 0

/**
* this is a student struct.
* here we have a student object, with all
* the parameters specializing each student
**/
struct gStudent
{

	long idNum;
	char name[ARR], city[ARR], country[ARR];
	int grade, age;
	float avg;

};

typedef struct gStudent gStudent;

gStudent gClass[MAX_CLASS];
gStudent gSorted[MAX_CLASS];

void merge(int low, int mid, int high);

void mergeSort(int low, int high);

void printSort(gStudent *toPrint, int stdCounter);

void quickSort(gStudent *A, int low, int high);

int quickPart(gStudent *A, int low, int high);

int checkItems(int items, int ind_row)
{
	/**
	 * @param items: items from fgets
	 * @pararm ind_row: number of row we point on
	 * a function which checks the amount of items we received.
	**/
	if (items != 6)
	{
		printf("ERROR: info must match specified format\n");
		printf("in line %d\n", ind_row);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int checkInfo(int ind, long idNum, char *name, int grade, int age, char *country, char *city)
{
	/**
	 * @param ind: index of row
	 * @param idNum, *name, grade, age, *country *city: student information
	 * a function that checks the input we received
	 **/
	if ((idNum < MIN_ID_LEN) || (idNum > MAX_ID_LEN))
		/**
		* id number not in range
		*/
	{
		printf("ERROR: id must be a 10 digits number that does not start with 0\n");
		printf("in line %d\n", ind);
		return EXIT_FAILURE;
	}
	else if (idNum / DIVIDOR == 0)
		/**
		* id number too short or too long
		*/
	{
		printf("ERROR: id must be a 10 digits number that does not start with 0\n");
		printf("in line %d\n", ind);
		return EXIT_FAILURE;
	}

	int lenName = (int) strlen(name);
	char hyp = '-';

	for (int i = 0; i < lenName; i++)
	{
		if (!isalpha(name[i]))
		{
			if (name[i] != hyp)
			{
				if (!isspace(name[i]))
				{
					printf("ERROR: name can only contain alphabetic characters, whitespaces or '-'\n");
					printf("in line %d\n", ind);
					return EXIT_FAILURE;
				}
			}
		}
	}

	if ((grade < MIN_GRADE) || (grade > MAX_GRADE))
		/**
		* grade not in range
		*/
	{
		printf("ERROR: grade must be an integer between 0 and 100\n");
		printf("in line %d\n", ind);
		return EXIT_FAILURE;
	}
	else if ((age < MIN_AGE) || (age > MAX_AGE))
		/***
		 * age not in range
		 */
	{
		printf("ERROR: age must be an integer between 18 and 120\n");
		printf("in line %d\n", ind);
		return EXIT_FAILURE;
	}
	int lenCount = (int) strlen(country);
	int lenCity = (int) strlen(city);
	/**
	 *   in the next two loops we check if the city and the country
	 *   only contain alphabetic chars or an hypen.
	 * */
	for (int i = 0; i < lenCount; i++)
	{
		if (!isalpha(country[i]))
		{
			if (country[i] != hyp)
			{
				printf("ERROR: country can only contain alphabetic characters or '-'\n");
				printf("in line %d\n", ind);
				return EXIT_FAILURE;
			}
		}
	}
	for (int j = 0; j < lenCity; j++)
	{
		if (!isalpha(city[j]))
		{
			if (city[j] != hyp)
			{
				printf("ERROR: city can only contain alphabetic characters or '-'\n");
				printf("in line %d\n", ind);
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}


int functions(int reminder)
{
	/***
	* this is a functions function.
	* @param reminder: tells us which one of the options we are doing
	* 1 - best student. 2-merge sort. 3-quick sort.
	* output - 0 when we are done.
	***/
	gStudent saver;
	int stdCounter = 0;
	float maxAvg = -1;
	char inp[INPUT_LEN];
	char q[] = "q\n";
	int indRow = 0;
	int check2 = 0;
	printf("Enter student info. To exit press q, then enter\n");

	char* fCheck = fgets(inp, INPUT_LEN, stdin);
	if (fCheck == NULL)
	{
		printf("ERROR: fgets failed.\n");
		printf("in line %d\n", indRow);
		return EXIT_SUCCESS;
	}

	int comp = strcmp(q, inp);

	while (comp)
	{
		int items;
		long id_num;
		int grade;
		int age;
		char name[ARR], city[ARR], country[ARR];
		items = sscanf(inp, "%ld,%[^,],%d,%d,%[^,],%s", &id_num, name, &grade, &age, country, city);

		int check1 = checkItems(items, indRow);

		if (check1)
		{
			/**
			 * if we have enough items, we can go on to our next check
			 * inside checkInfo we check every aspect about the input of the student.
			 * **/
			check2 = checkInfo(indRow, id_num, name, grade, age, country, city);
		}

		if (check2 && check1)
		{
			/***
			 * now we have passed all tests about the aspects of the input.
			 * we are now applying the information inside the student.
			 * and follow accordingly to the request of the manger.
			 */
			gStudent s1;
			s1.idNum = id_num;
			s1.age = age;
			s1.grade = grade;
			strcpy(s1.name, name);
			strcpy(s1.city, city);
			strcpy(s1.country, country);
			float g = (float) grade;
			float a = (float) age;
			s1.avg = g / a;

			if (reminder != 1)
			{
				gClass[stdCounter] = s1;
				gSorted[stdCounter] = s1;

			}

			stdCounter = stdCounter + 1;

			if (s1.avg > maxAvg)
			{
				saver = s1;
				maxAvg = s1.avg;
			}

		}

		printf("Enter student info. To exit press q, then enter\n");
		fCheck = fgets(inp, INPUT_LEN, stdin);

		if (fCheck == NULL)
		{
			printf("ERROR:fgets failed.\n");
			printf("in line %d\n", indRow + 1);
			return EXIT_SUCCESS;
		}

		comp = strcmp(q, inp);
		indRow++;

		if ((!comp) && (stdCounter == 0))
		{
			return EXIT_FAILURE;
		}

		if (!comp)
		{
			/**
			 * the consumer asked to finish up, now we need to deal with the request
			 * 1- find best student.
			 * 2- merge sort by average of grades.
			 * 3- quick sort by alphabet.
			 * **/
			if (reminder == 1)
			{
				/**
				 * here we find the best student of them all.
				 * **/

				printf("best student info is: %ld,%s,%d,%d,%s,%s\n", saver.idNum, saver.name,
					   saver.grade, saver.age, saver.country, saver.city);
			}

			else if (reminder == 2)
			{
				/**
				 * here we need to do merge sort by averages.
				 * **/
				int low = 0;
				int high = stdCounter - 1;
				mergeSort(low, high);
				printSort(gSorted, stdCounter);

			}

			else if (reminder == 3)
			{
				/**
				 * here we need to do quick sort by alphabetic order of the names.
				 **/
				int low = 0;
				int high = stdCounter - 1;
				quickSort(gClass, low, high);
				printSort(gClass, stdCounter);

			}
		}


	}

	return EXIT_FAILURE;
}

void mergeSort(int low, int high)
{
	/**
	 * mergeSort main function, here we divide into little sub-arrays and call
	 * to sort and merge them.
	 * @param low: lower index we point on
	 * @param high: higher index we point on
	 * **/

	int mid;

	if (low < high)
	{
		mid = (low + high) / 2;
		mergeSort(low, mid);
		mergeSort(mid + 1, high);
		merge(low, mid, high);
	}
	else
	{
		return;
	}
}

void merge(int low, int mid, int high)
{
	/**
	 * merge sort, part 2, here we sort it out.
	 * @param low: lower index we point on
	 * @param mid: middle index we point on
	 * @param high: higher index we point on
	 * **/

	int p1, p2, i;

	for (p1 = low, p2 = mid + 1, i = low; ((p1 <= mid) && (p2 <= high)); i++)
	{
		if (gClass[p1].avg <= gClass[p2].avg)
		{
			gSorted[i] = gClass[p1];
			p1 = p1 + 1;
		}
		else
		{
			gSorted[i] = gClass[p2];
			p2 = p2 + 1;
		}
	}

	while (p1 <= mid)
	{
		gSorted[i] = gClass[p1];
		i = i + 1;
		p1 = p1 + 1;
	}

	while (p2 <= high)
	{
		gSorted[i] = gClass[p2];
		i = i + 1;
		p2 = p2 + 1;
	}

	for (i = low; i <= high; i++)
	{
		gClass[i] = gSorted[i];
	}

}

void printSort(gStudent *toPrint, int stdCounter)
{
	/**
	 * a function to print the given array after sort.
	 * @param *toPrint: array to print
	 * @param stdCounter: number of students to print
	 * **/

	for (int i = 0; i < stdCounter; i++)
	{
		printf("%ld,%s,%d,%d,%s,%s\n", toPrint[i].idNum, toPrint[i].name, toPrint[i].grade,
			   toPrint[i].age,
			   toPrint[i].country, toPrint[i].city);
	}
}

void quickSort(gStudent *A, int low, int high)
{
	/**
	 * recursive sort named quick sort.
	 * part 1 out of 3 in quick sort.
	 * @param *A: the array to sort
	 * @param low: lower index
	 * @param high: higher index
	 * **/
	if (low < high)
	{
		int pi = quickPart(A, low, high);
		quickSort(A, low, pi - 1);
		quickSort(A, pi + 1, high);
	}
}

void swap(gStudent *a, gStudent *b)
{
	/**
	 * swapping array content. part 3 of quick sort.
	 * @param *a: first array content
	 * @param *b: second array content to be switched with
	 * **/
	gStudent temp = *a;
	*a = *b;
	*b = temp;
}

int quickPart(gStudent *A, int low, int high)
{
	/**
	 * partitioning the array, part 2 of quick sort.
	 * @param: *A: the array to sort
	 * @param low: lower index
	 * @param high: higher index
	 * **/

	char pivot[ARR];
	strcpy(pivot, A[high].name);

	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		int check_asci = strcmp(A[j].name, pivot);
		if (check_asci < 0)
		{
			i = i + 1;
			swap(&A[i], &A[j]);

		}
	}

	swap(&A[i + 1], &A[high]);
	return (i + 1);
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("USAGE: CLI arguments format is wrong.\n");
		return EXIT_SUCCESS;
	}

	else
	{
		/**
		 * we check the arguments which were given to the CLI, and follow accordingly.
		 * instructions are:
		 * best - find best student out of given students.
		 * merge - merge sort to the list of students(numeric by averages).
		 * quick - quick sort to the list of students(alphabetic).
		 * **/
		int reminder = 0;
		char arg[ARR];
		strcpy(arg, argv[1]);

		int comp1 = strcmp("best", arg);
		int comp2 = strcmp("merge", arg);
		int comp3 = strcmp("quick", arg);

		if (!comp1)
		{
			reminder = 1;
		}
		else if (!comp2)
		{
			reminder = 2;
		}
		else if (!comp3)
		{
			reminder = 3;
		}
		else
		{
			printf("USAGE: arguments given is invalid");
			return EXIT_SUCCESS;
		}

		int ret = functions(reminder);
		if (ret)
		{
			return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}

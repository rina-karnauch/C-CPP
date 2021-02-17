#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAX INT_MAX
#define TOTAL_LOSS -1
#define MAX_LINE 1025
#define FEATURES 4

/**
 * this is a struct of InfoLines.
 * each object is a line, with the features we want for them to have.
 */
typedef struct InfoLine
{
	char first;
	char last;
	int amount, price;
} InfoLine;

int argManagement(int argc);

int checkInt(char string[]);

int possibleRails(char *rails, char row[]);

int hypChecker(char row[]);

int checkChar(char given, const char *rails, int posConnects);

int insertInfo(char *rails, char *row, int posConnects, InfoLine *object);

int minimalPrice(const int *prices, int rowC);

void changePrices(int *prices, int rowC, int into);

void argError();

int findIndex(const char *rails, int posConnects, char wanted);

void lineError(int line);

int minChoosen(int **arr, int posConnects, int len);

void zeroFirstLine(int **arr, int posConnects);

void outputSuccess(int choosen);

void priceReturn(int rowC, int j, int i, int posConnects, InfoLine *objLines, char *rails,
				 int *prices, int **arr);

void arrayBuilding(int **arr, InfoLine *objLines, char *rails, int rowC,
				   int posConnects,
				   int len,
				   int *prices);

void nullPointers(int **arr, InfoLine *objLines, char *rails, int *prices, int len);

void changePrices(int *prices, int rowC, int into)
{
	/**
	 * a function which changes the array of prices
	 * @param prices: the array of prices.
	 * @param rowC: the amount of prices.
	 * @param into: the value we change to.
	 * **/
	for (int k = 0; k < rowC; k++)
	{
		prices[k] = into;
	}
}

int argManagement(int argc)
{
	/**
	 * a function which checks the amount of arguments from the CLI.
	 * @param argc: the amount
	 * @return SUCCESS for correct, FAILURE for another amount.
	 * **/
	if (argc != 1)
	{
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int checkInt(char string[])
{
	/**
	* a function which checks the integer in the string.
	* @param string: the string
	* @return: TOTAL_LOSS (-1) for failure, the int for success.
	 * **/
	char *pEnd = NULL;
	int checkN = (int) strtol(string, &pEnd, 10);
	if (*pEnd != '\0')
	{
		return TOTAL_LOSS;
	}
	return checkN;
}

int hypens(char row[])
{
	/**
	 *
	 **/
	int i = 0;
	int counter = 0;
	while (row[i] != '\0')
	{
		if (row[i] == ',')
		{
			counter = counter + 1;
		}
		i = i + 1;
	}

	return counter;

}

int possibleRails(char *rails, char row[])
{
	/**
	 * a function which checks if the row contains only possible chars.
	 * @param rails: the array of possible chars.
	 * @return: FAILURE for not valid SUCCESS for valid.
	 * **/
	char rowcpy[MAX_LINE];
	strcpy(rowcpy, row);

	char hyp[] = ",";
	char *token;
	token = strtok(rowcpy, hyp);
	char i = 0;
	int c = 0;
	int hyps = 0;

	while (token != NULL)
	{
		char len = (char) strlen(token);

		if (len > EXIT_FAILURE)
		{
			return EXIT_FAILURE;
		}

		strncpy(rails + i, token, 1);
		i = i + 1;
		c = c + 1;
		token = strtok(NULL, hyp);
	}

	hyps = hypens(row);

	if (hyps != c - 1)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int hypChecker(char row[])
{
	/**
	 * a function to check amount of hyps ('-') in line
	 * @param row: the text in the row
	 * @return SUCCESS for 3, FAILURE for more or less.
	 * **/
	int i = 0;
	char hyp[] = ",";

	char cpy[MAX_LINE];
	strcpy(cpy, row);

	char *token = strtok(cpy, hyp);
	while (token)
	{
		i = i + 1;
		token = strtok(NULL, hyp);
	}

	if (i != FEATURES)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int checkChar(char given, const char *rails, int posConnects)
{
	/**
	 * a function to check if the given char is in the rails array.
	 * @param given: given char to check.
	 * @param rails: array of possible chars.
	 * @param posConnects: amount of possible chars.
	 * @return SUCCESS or FAILURE.
	 * **/
	for (int j = 0; j < posConnects; j++)
	{

		if (given == rails[j])
		{
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

int insertInfo(char *rails, char *row, int posConnects, InfoLine *object)
{
	/**
	 * a function which inserts Info inside the object.
	 * @param rails: the possible rails array.
	 * @param row: the text in the row.
	 * @param posConnects: the amount of possible railways.
	 * @param object: the object we insert into.
	 * @return: SUCCESS for SUCCESS inserting, FAILURE for problem while trying.
	 * **/
	char hyp[] = ",";
	char cpy[MAX_LINE];
	strcpy(cpy, row);

	char *pEnd = NULL;
	char *token;
	token = strtok(cpy, hyp);
	int k = 0;
	int checkC;
	int len;

	while ((token != NULL) && (k < 4))
	{
		if (k == 0)
		{
			len = (int) strlen(token);
			if (len > EXIT_FAILURE)
			{
				return EXIT_FAILURE;
			}

			checkC = checkChar(*token, rails, posConnects);
			if (checkC)
			{
				return EXIT_FAILURE;
			}
			object->first = *token;
		}
		else if (k == 1)
		{
			len = (int) strlen(token);
			if (len < EXIT_FAILURE)
			{
				return EXIT_FAILURE;
			}

			checkC = checkChar(*token, rails, posConnects);
			if (checkC)
			{
				return EXIT_FAILURE;
			}
			object->last = *token;
		}
		else if (k == 2)
		{
			len = (int) strlen(token);
			if (len < EXIT_FAILURE)
			{
				return EXIT_FAILURE;
			}
			checkC = (int) strtol(token, &pEnd, 10);

			if (*token != '0' && checkC == 0)
			{
				return EXIT_FAILURE;
			}
			if (*pEnd == '\n')
			{
				return EXIT_FAILURE;
			}

			if (checkC == 0)
			{
				return EXIT_FAILURE;
			}

			object->amount = checkC;
		}
		else if (k == 3)
		{
			int j = 0;
			pEnd = NULL;
			while (token[j] != '\0')
			{

				if (!isdigit(token[j]))
				{
					return EXIT_FAILURE;
				}
				j = j + 1;
			}
			checkC = (int) strtol(token, &pEnd, 10);

			if (*token == '0' && checkC == 0)
			{
				return EXIT_FAILURE;
			}
			if (*pEnd == '\n')
			{
				return EXIT_FAILURE;
			}

			if (checkC < 0)
			{
				return EXIT_FAILURE;
			}

			object->price = checkC;
		}

		token = strtok(NULL, hyp);
		k = k + 1;
	}

	token = NULL;
	return EXIT_SUCCESS;
}

int findIndex(const char *rails, int pos, char wanted)
{
	/**
	 * a function to find the Index of the wanted char.
	 * @param rails: array of rails.
	 * @param pos: possible connections.
	 * @param wanted: wanted char.
	 * @return number of index or -1 if not found.
	 * **/
	for (int k = 0; k < pos; k++)
	{
		if (rails[k] == wanted)
		{
			return k;
		}
	}
	return TOTAL_LOSS;
}

int minimalPrice(const int *prices, int rowC)
{
	/**
	 * a function to find minimal price out of prices.
	 * @param prices: the array of prices.
	 * @param rowC: number of rows we have, amount of prices.
	 * @return: the minimal price.
	 * **/
	int minPrice = MAX;

	for (int t = 0; t < rowC; t++)
	{
		if (prices[t] < minPrice)
		{
			minPrice = prices[t];
		}
	}

	return minPrice;
}

void argError()
{
	/**
	 * a function to output argument Error into file.
	 * **/

	FILE *pFile = NULL;
	pFile = fopen("railway_planner_output.txt", "w");
	fprintf(pFile, "Usage: RailWayPlanner <InputFile>");
	fclose(pFile);
}

void lineError(int line)
{
	/**
	 * a function to output line of Error.
	 * **/

	FILE *pFile = NULL;
	pFile = fopen("railway_planner_output.txt", "w");
	fprintf(pFile, "Invalid input in line: %d.", line);
	fclose(pFile);
}

int minChoosen(int **arr, int pos, int len)
{
	/**
	 * a function to find the minimal price
	 * @param arr : the array
	 * @param pos : the amount of possible rails, number of options we choose from.
	 * @param len : the length of the rail.
	 * @return: the minimal amount or for none, -1.
	 * **/
	int choosen = MAX;
	for (int i = 0; i < pos; i++)
	{
		if (arr[len - 1][i] < choosen)
		{
			choosen = arr[len - 1][i];
		}
	}
	if (choosen == MAX)
	{
		return TOTAL_LOSS;
	}
	return choosen;
}

void outputSuccess(int choosen)
{
	/**
	 * a function to output the success value.
	 * **/
	FILE *pFile = NULL;
	pFile = fopen("railway_planner_output.txt", "w");
	fprintf(pFile, "The minimal price is: %d", choosen);
	fclose(pFile);
}

void zeroFirstLine(int **arr, int pos)
{
	/**
	 * a function to zero out the content of the first row.
	* @param arr: the array we fill up.
	 * **/
	for (int j = 0; j < pos; j++)
	{ //  colms
		arr[0][j] = 0;
	}
}

void priceReturn(int rowC, int j, int i, int posConnects, InfoLine *objLines, char *rails,
				 int *prices, int **arr)
/**
 * a function to return the needed element inside the array
 * **/
{
	for (int k = 0; k < rowC; k++)
	{
		int length = objLines[k].amount;
		int rest = i - length;

		char end = rails[j];

		if (objLines[k].last != rails[j])
		{
			prices[k] = MAX;
		}

		else if (rest == 0 && (end == objLines[k].last))
		{
			int price = objLines[k].price;
			prices[k] = price;
		}
		else if (rest > 0)
		{
			char start = objLines[k].first;
			int boxIndex = findIndex(rails, posConnects, start);
			// ^ the index of the colm of the start char.
			if (boxIndex == TOTAL_LOSS || arr[rest][boxIndex] == MAX)
				// if there is no char ending in this char.
			{
				prices[k] = MAX;
			}
			else
			{
				if (objLines[k].price + arr[rest][boxIndex] < 0)
				{
					prices[k] = MAX;
				}
				else
				{
					prices[k] = objLines[k].price + arr[rest][boxIndex];
				}

			}
		}
		else if (rest < 0)
		{
			prices[k] = MAX;
		}

		arr[i][j] = prices[k];
	}

	int minPrice = minimalPrice(prices, rowC);
	arr[i][j] = minPrice;

	changePrices(prices, rowC, MAX);
}


void arrayBuilding(int **arr, InfoLine *objLines, char *rails, int rowC, int posConnects,
				   int len,
				   int *prices)
{
	/**
	 * a function that changes the table we are building for the railways.
	 * @param arr: the array, the table.
	 * @param objLines: array of objects, our lines.
	 * @param rails: array of possible rails signs.
	 * @param rowC: number of lines.
	 * @param posConnects: numer of connections.
	 * @param len: length of wanted railway.
	 * @param prices: array of prices.
	 * **/
	int i, j;

	for (i = 1; i < len; i++)
	{ // rows- length of current road- i.
		for (j = 0; j < posConnects; j++)
		{ // colms- the end of last part
			priceReturn(rowC, j, i, posConnects, objLines, rails, prices, arr);
		}
	}
}


void nullPointers(int **arr, InfoLine *objLines, char *rails, int *prices, int len)
{
	/**
	 * a function to set all pointers to NULL
	 * @param arr: array pointer.
	 * @param objLines: objLines pointer.
	 * @param rails: rails pointer.
	 * @param prices: prices pointer.
	 * **/
	for (int i = 0; i < len; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
	free(objLines);
	free(rails);
	free(prices);
	arr = NULL;
	objLines = NULL;
	rails = NULL;
	prices = NULL;
}

void outEmpty()
{
	/**
	 * a function to output an empty File.
	 */
	FILE *pFile = NULL;
	pFile = fopen("railway_planner_output.txt", "w");
	fprintf(pFile, "File is empty.");
	fclose(pFile);
}

int main(int argc, char *argv[])
{
	/**
	 * the main function.
	 * @param argc: amount of args from CLI
	 * @param argv: the arguments
	 * @return: FAILURE for fail, SUCCESS for success.
	 * **/
	FILE *pFile = NULL;
	int **arr = NULL;
	InfoLine *objLines = NULL;
	char *rails = NULL;
	int *prices = NULL;

	if (argManagement(argc))
	{
		argError();
		return EXIT_FAILURE;
	}

	pFile = fopen(argv[1], "r");

	fseek(pFile, SEEK_SET, SEEK_END);
	int size = (int) ftell(pFile);
	if (size == 0)
	{
		fclose(pFile);
		outEmpty();
		return EXIT_FAILURE;
	}

	fseek(pFile, SEEK_SET, SEEK_SET);

	int railwayLength = 0;
	int posConnects = 0;
	int check;
	int counter = 1;

	char row[MAX_LINE];
	int rowC = 0;

	while (fgets(row, MAX_LINE, pFile) != NULL)
	{
		int lastInd = (int) strlen(row) - 1;
		if (row[lastInd] == '\n')
		{
			row[lastInd] = '\0';
		}
		if (counter == 1)
		{
			check = checkInt(row);
			if (check == TOTAL_LOSS)
			{
				fclose(pFile);
				lineError(counter);
				return EXIT_FAILURE;
			}
			railwayLength = check;
		}
		else if (counter == 2)
		{
			check = checkInt(row);
			if (check == TOTAL_LOSS)
			{
				fclose(pFile);
				lineError(counter);
				return EXIT_FAILURE;
			}
			if (check == 0)
			{
				fclose(pFile);
				lineError(counter);
				return EXIT_FAILURE;
			}
			posConnects = check;
		}
		else if (counter == 3)
		{
			int cons = posConnects;
			rails = (char *) malloc(sizeof(char) * (cons));
			if (rails == NULL)
			{
				nullPointers(arr, objLines, rails, prices, 0);
				return TOTAL_LOSS;
			}

			check = possibleRails(rails, row);
			if (check)
			{
				fclose(pFile);
				nullPointers(arr, objLines, rails, prices, 0);
				lineError(counter);
				return EXIT_FAILURE;
			}

		}
		else if (counter >= 4)
		{
			int hypCheck = hypChecker(row);
			if (hypCheck)
			{
				fclose(pFile);
				nullPointers(arr, objLines, rails, prices, 0);
				lineError(counter);
			}

			if (objLines == NULL)
			{
				objLines = (InfoLine *) malloc(sizeof(InfoLine));
				if (objLines == NULL)
				{
					nullPointers(arr, objLines, rails, prices, 0);
					return EXIT_FAILURE;
				}

				check = insertInfo(rails, row, posConnects, &objLines[rowC]);
			}
			else
			{
				objLines = (InfoLine *) realloc(objLines, (sizeof(InfoLine) * (counter + 1)));
				if (objLines == NULL)
				{
					nullPointers(arr, objLines, rails, prices, 0);
					return EXIT_FAILURE;
				}
				check = insertInfo(rails, row, posConnects, &objLines[rowC]);
			}
			if (check)
			{
				nullPointers(arr, objLines, rails, prices, 0);
				fclose(pFile);
				lineError(counter);
				return EXIT_FAILURE;
			}
			rowC = rowC + 1;
		}
		counter = counter + 1;
	}
	fclose(pFile);

	int len = railwayLength + 1; // catalog of length of railways
	arr = (int **) malloc(len * (sizeof(int *))); // rows
	if (NULL == arr)
	{
		nullPointers(arr, objLines, rails, prices, len);
		return EXIT_FAILURE;
	}

	for (int i = 0; i < len; i++)
	{
		arr[i] = (int *) malloc(posConnects * (sizeof(int))); // colms
		if (arr[i] == NULL)
		{
			nullPointers(arr, objLines, rails, prices, 0);
			return EXIT_FAILURE;
		}
	}

	zeroFirstLine(arr, posConnects);


	prices = (int *) malloc(sizeof(int) * rowC);
	if (prices == NULL)
	{
		nullPointers(arr, objLines, rails, prices, len);
		return EXIT_FAILURE;
	}

	changePrices(prices, rowC, MAX);
	arrayBuilding(arr, objLines, rails, rowC, posConnects, len, prices);


	int choosen = minChoosen(arr, posConnects, len);
	outputSuccess(choosen);
	nullPointers(arr, objLines, rails, prices, len);

	return EXIT_SUCCESS;
}

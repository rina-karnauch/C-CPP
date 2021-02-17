//
// Created by Rina Karnauch on 01/08/2020.
//

#include "SpreaderDetectorBackend.c"

#define MEETING_1 "1_meeting.in"
#define MEETING_2 "2_meeting.in"
#define MEETING_3 "3_meeting.in"
#define MEETING_4 "4_meeting.in"

#define PEOPLE_1 "1_sol.in"
#define PEOPLE_2 "2_sol.in"
#define PEOPLE_3 "3_sol.in"
#define PEOPLE_4 "4_sol.in"

#define SOL_1 "1_sol.in"
#define SOL_2 "2_sol.in"
#define SOL_3 "3_sol.in"
#define SOL_4 "4_sol.in"

#define WRONG_MEETING "heil.in"
#define WRONG_PEOPLE "bibi.in"

static char **amount = (char **) 3;
static char **wrongSmallA = (char **) 1;
static char **wrongBigA = (char **) 5;

static char *meetingsArray = {PEOPLE_1, PEOPLE_2, PEOPLE_3, PEOPLE_4};
static char *peopleArray = {MEETING_1, MEETING_2, MEETING_3, MEETING_4};
static char *solArray = {SOL_1, SOL_2, SOL_3, SOL_4};


int test()
{
	int i;


	for (i = 0; i < 4; i++)
	{
		char args = {meetingsArray[i], peopleArray[i]};
		main(args, amount);
	}

	if (i != 3)
	{
		printf("something went wrong, iteration with file # %d failed", i + 1, stderr);
	}

	char wrongArgs = {'3'};
	main(wrongArgs, amount);
	printf("Error: argc was invalid, you should check your code", stderr);

	main(peopleArray[0], wrongSmallA);
	printf("Error: argv was invalid, the value given is smaller than 3", stderr);


	main(peopleArray[0], wrongBigA);
	printf("Error: argv was invalid, the value given is bigger than 3", stderr);

	return 0;
}


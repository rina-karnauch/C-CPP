//
// Created by Rina Karnauch on 28/06/2020.
//

#define GOOD_FILE_PATH_USER "ranks_small.txt"
#define GOOD_FILE_PATH_MOVIE  "movies_small.txt"
#define GOOD_MOVIE_NAME "ArabianNights"
#define GOOD_USER_NAME "Christopher"

// LIBS
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include "RecommenderSystem.h"

// MACROS
const std::string BAD_USER = "RANDOM_NAME";
const std::string BAD_FILE_PATH_USER =  "BAD_FILE_PATH_USER.asd";
const std::string BAD_FILE_PATH_MOVIE = "BAD_FILE_PATH_MOVIE.asd";
#define BAD_MOVIE_NAME "RANDOM_MOVIE"
#define NOTFOUND -1
#define ZERO 0
#define ONE 1
#define SUCCESS_READING 0
#define FAILURE_READING -1
#define k 2

// MSGS:
#define USER_ERROR "USER NOT FOUND"
#define FILE_PATH_ERROR "Unable to open file "

int main()
{
	std::stringstream buffer;
	std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());
	RecommenderSystem rec;
	int SUCCESS = rec.loadData(GOOD_FILE_PATH_MOVIE, BAD_FILE_PATH_USER);
	std::string text = buffer.str();
	if (text != "Unable to open file " + (string)GOOD_FILE_PATH_MOVIE + "\n")
	{
		std::cerr << "wrong file error message when received a bad user file";
		exit(1);
	}
	if (SUCCESS != NOTFOUND)
	{
		std::cerr << "didnt return -1 upon bad file path" << std::endl;
		exit(1);
	}
	rec = RecommenderSystem();
	buffer = std::stringstream();
	SUCCESS = rec.loadData(BAD_FILE_PATH_MOVIE, GOOD_FILE_PATH_USER);
	text = buffer.str();
	if (text != "Unable to open file " + BAD_FILE_PATH_MOVIE + "\n")
	{
		std::cerr << "wrong file error message when received a bad movie file";
		exit(1);
	}
	if (SUCCESS != NOTFOUND)
	{
		std::cerr << "didnt return -1 upon bad file path" << std::endl;
		exit(1);
	}
	rec = RecommenderSystem();
	buffer = std::stringstream();
	SUCCESS = rec.loadData(GOOD_FILE_PATH_MOVIE, GOOD_FILE_PATH_USER);
	if (SUCCESS != 0)
	{
		std::cerr << "didnt return 0 upon good file path" << std::endl;
		exit(1);
	}
	text = rec.recommendByContent(BAD_USER);
	if (text != "USER NOT FOUND")
	{
		std::cout << "did not return the right string in recommendByContent for a bad user name" << std::endl;
		exit(1);
	}
	SUCCESS = rec.predictMovieScoreForUser(BAD_USER, GOOD_MOVIE_NAME, 1);
	if (SUCCESS != NOTFOUND)
	{
		std::cout << "did not return -1 upon bad user name in predictMovieScoreForUser" << std::endl;
		exit(1);
	}
	SUCCESS = rec.predictMovieScoreForUser(GOOD_USER_NAME, BAD_USER, 1);
	if (SUCCESS != NOTFOUND)
	{
		std::cout << "did not return -1 upon bad movie name in predictMovieScoreForUser" << std::endl;
		exit(1);
	}
	text = rec.recommendByCF(BAD_USER, 1);
	if (text != "USER NOT FOUND")
	{
		std::cout << "did not return USER NOT FOUND upon bad user name in recommendByCF" << std::endl;
	}
	std::cerr.rdbuf(old);


	exit(0);
}

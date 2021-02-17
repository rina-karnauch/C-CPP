//
// Created by Rina Karnauch on 20/06/2020.
//
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
#define NOTFOUND -1
#define ZERO 0
#define ONE 1
#define SUCCESS_READING 0
#define FAILURE_READING -1

// MSGS:
#define USER_ERROR "USER NOT FOUND"
#define FILE_PATH_ERROR "Unable to open file "

//USINGS


using std::endl;
using std::cout;
using std::cerr;
using std::cin;

using std::stod;
using std::sort;

using std::unordered_map;
using std::string;
using std::pair;

using std::istream_iterator;
using std::istringstream;

using std::begin;
using std::end;


// PRIVATE:
/**
 * a function to build a pair of - (movie:ratings vector)
 * @param line: the line we got from the file
 * @return: the pair
 */
pair<string, vector<double>> RecommenderSystem::_movieVectorBuilder(const string &line)
{
	istringstream iss(line);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		 istream_iterator<string>(),
		 back_inserter(tokens));

	vector<double> currentVec;
	string currentStr = tokens[0];

	int size = tokens.size();
	for (int i = 1; i < size; i++)
	{
		double rate = stod(tokens[i]);
		currentVec.push_back(rate);
	}
	return pair(currentStr, currentVec);
}

/**
* a function to read the line of movie names
* @param line
*/
void RecommenderSystem::_movieNamesLine(const string &line)
{
	istringstream iss(line);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		 istream_iterator<string>(),
		 back_inserter(tokens));
	for (const auto &token : tokens)
	{
		_moviesByOrder.push_back(token);
	}
}

/**
 * a function to build a pair of name and vector of personal ratings
 * @param line: the line from the file
 * @return: a pair of: (name, vector(double))
 */
pair<string, unordered_map<string, double>> RecommenderSystem::_userInfoBuilder(string &line)
{
	istringstream iss(line);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		 istream_iterator<string>(),
		 back_inserter(tokens));
	string name = tokens[0];
	unordered_map<string, double> movieRatings;
	int sizeI = tokens.size();
	int sizeJ = _moviesByOrder.size();
	for (int i = 1, j = 0; i < sizeI && j < sizeJ; i++, j++)
	{
		string movie = _moviesByOrder[j];
		if (tokens[i] == "NA")
		{
			movieRatings[movie] = ZERO;
		}
		else
		{
			double rate = stod(tokens[i]);
			movieRatings[movie] = rate;
		}
	}
	return pair(name, movieRatings);
}


/**
 * a function to return the _resemblance between two vectors
 * @param faves: vector of
 * @param rates
 * @return
 */
double RecommenderSystem::_resemblance(const vector<double> &faves, const string &movieName)
{
	double mulVal = _mulVectors(_movieFeatures[movieName], faves);
	double normVal = (_movieNorms[movieName]) * (_normVec(faves));
	return mulVal / normVal;
}

/**
 * a function to return the scalar multipication of 2 vectors
 * @param name: the name fo the movie we look for its vector
 * @param faves: the faves vector as we calculated it
 * @return: the double scallar multipication
 */
double RecommenderSystem::_mulVectors(const vector<double> &rates, const vector<double> &faves)
{
	double mul = 0;
	int size = rates.size();
	for (int i = 0; i < size; i++)
	{
		mul = mul + rates[i] * faves[i];
	}
	return mul;
}

/**
 * a function to calculate the norm of the vector
 * @param vec: the vector
 * @return: the norm
 */
double RecommenderSystem::_normVec(const vector<double> &vec)
{
	double sum = 0;
	for (double i : vec)
	{
		double power = pow(i, 2);
		sum = sum + power;
	}
	return sqrt(sum);
}

/**
 * a function of comparison for the sort algorithem
 * @param p1: 1st pair
 * @param p2: 2nd pair
 * @return: true for p1 is greater, false otherwise.
 */
bool _compare(const pair<string, double> &p1, const pair<string, double> &p2)
{
	return p1.second > p2.second;
}

/**
* a funcion to change the prediction vector and mul it.
* @param predicts: the vector of pairs of string and double - predicts accorations.
* @param ranks: the ranks the person gave for each movie
* @param k: the value int choosen to predict by
*/
void RecommenderSystem::_mulPredicts(vector<pair<string, double>> &predicts,
									 const unordered_map<string, double> &ranks, int k)
{
	int size = predicts.size();
	for (int i = 0; i < k && i < size; i++)
	{
		double value = ranks.at(predicts[i].first);
		predicts[i].second = value * (predicts[i].second);
	}
}

/**
 * a function to sum two pairs
 * @param p
 * @return
 */
double RecommenderSystem::_sumPairs(const vector<pair<string, double>> &p, int k)
{
	double sum = 0;
	for (int i = 0; i < k; i++)
	{
		sum = sum + p[i].second;
	}
	return sum;
}

vector<double> RecommenderSystem::_createVector(const unordered_map<string, double> &userRanks)
{
	vector<double> userRatings;
	int size = _moviesByOrder.size();
	for (int i = 0; i < size; i++)
	{
		string movie = _moviesByOrder[i];
		double rate = userRanks.at(movie);
		userRatings.push_back(rate);
	}
	return userRatings;
}

/**
* a function to handle the _resemblance of each movie to all the other movies someone has saw
* @param unrankedMovie
* @param k: int of how many we will choose and predict by it
* @return
*/
double RecommenderSystem::_perdictMbyM(const string &unrankedMovie,
									   const unordered_map<string, double> &userRanks, int k)
{
	vector<double> feats = _movieFeatures[unrankedMovie];
	vector<pair<string, double>> predicts;

	for (auto &it:userRanks)
	{
		if (it.second > ZERO) // ranked movies
		{
			double res = _resemblance(feats, it.first);
			predicts.emplace_back(pair(it.first, res));
		}
	}

	sort(predicts.begin(), predicts.end(), _compare);

	double SumPredicts = _sumPairs(predicts, k);
	_mulPredicts(predicts, userRanks, k);
	double sumMultiPredicts = _sumPairs(predicts, k);

	double value = sumMultiPredicts / SumPredicts;
	return value;
}

// PUBLIC:

/**
 * a function load the data in the files
 * @param feats: string of path to the movieAttrributesFilePath
 * @param ranks: string of path to the userRantsFilePath
 * @return: 0 for success, -1 for failure
 */
int RecommenderSystem::loadData(const string &feats, const string &ranks)
{
	std::ifstream in;
	in.open(feats);
	if (!in)
	{
		cerr << FILE_PATH_ERROR << feats << endl;
		in.close();
		return FAILURE_READING;
	}

	string line;
	unordered_map<string, vector<double>> MovieTable;
	while (getline(in, line, '\n'))
	{
		pair p = _movieVectorBuilder(line);
		MovieTable.insert({p.first, p.second});
	}

	in.close();

	in.open(ranks);
	if (!in)
	{
		cerr << FILE_PATH_ERROR << feats << endl;
		in.close();
		return FAILURE_READING;
	}

	_movieFeatures = MovieTable;
	unordered_map<string, unordered_map<string, double>> userTable;

	int i = ONE;
	while (getline(in, line, '\n'))
	{
		if (i == ONE)
		{
			this->_movieNamesLine(line);
			i++;
		}
		else
		{
			pair<string, unordered_map<string, double>> currentUser = _userInfoBuilder(line);
			userTable[currentUser.first] = currentUser.second;
		}
	}

	_userRanks = userTable;
	int size = (_movieFeatures[_moviesByOrder[ZERO]].size());
	_featuresAmount = size;

	// we save the movie norms
	_movieNorms.reserve(size);

	for (auto &it: _movieFeatures)
	{
		double norm = _normVec(it.second);
		_movieNorms[it.first] = norm;
	}

	in.close();
	return SUCCESS_READING;
}

/**
 * a function to sup up values in the personRank map and avg them
 * @param rankings: the map of the personRank struct
 * @return: avg- double
 */
double RecommenderSystem::_avgValues(const unordered_map<string, double> &rankings)
{
	double sum = 0.0;
	int counter = 0;

	for (auto &it: rankings)
	{
		if (it.second != 0)
		{
			counter++;
		}
		sum = sum + it.second;
	}
	return sum / counter;
}

/**
 * a function to change the norm of the person's rating vector
 * @param personRates
 */
void RecommenderSystem::_normMap(unordered_map<string, double> &personRates, double avg)
{
	for (auto &it: personRates)
	{
		if (it.second != ZERO)
		{
			it.second = it.second - avg;
		}
	}
}

/**
 * a function to sum the avg'ed vectors
 * @param faves
 */
void
RecommenderSystem::_sumVectors(vector<double> &faves, unordered_map<string, double> &personRates)
{
	for (auto &i: _movieFeatures) // each one is a movie, with ratings
	{
		string name = i.first;
		double mul = personRates[name];
		vector<double> rates = i.second;

		int size = faves.size();
		for (int j = 0; j < size; j++)
		{
			faves[j] = mul * rates[j] + faves[j];
		}
	}
}


/**
* a function to recommend by content to the username
* @param userName: string of username
* @return: string of recommended movie
*/
string RecommenderSystem::recommendByContent(const string &userName)
{
	if (_userRanks.count(userName) <= ZERO)
	{
		return USER_ERROR;
	}

	unordered_map<string, double> personalRanking = _userRanks[userName];
	unordered_map<string, double> saveCopy = _userRanks[userName];

	double avg = _avgValues(personalRanking);

	_normMap(personalRanking, avg);

	unordered_map<string, double> results;
	int size = _featuresAmount;
	vector<double> faves(size);
	vector<double> rates;

	_sumVectors(faves, personalRanking);

	for (auto &it: saveCopy)
	{
		if (it.second == ZERO)
		{
			double img = _resemblance(faves, it.first);
			results[it.first] = img;
		}
	}

	string name;
	double max = -1;
	for (auto &it: results)
	{
		if (it.second > max)
		{
			name = it.first;
			max = it.second;
		}
	}
	return name;
}

/**
 * a function to predict movie score for user
 * @param movieName: the movie name
 * @param userName: the user name
 * @param k: integer k, amount of movies
 * @return
 */
double RecommenderSystem::predictMovieScoreForUser(const string &movieName, const string &userName,
												   const
												   int k)
{
	if (_userRanks.count(userName) <= ZERO || _movieFeatures.count(movieName) <= ZERO)
	{
		return NOTFOUND;
	}

	unordered_map<string, double> personalUserRanks = _userRanks[userName];

	double mul = _perdictMbyM(movieName, personalUserRanks, k);
	return mul;
}

/**
* a function to get the Max Movie Ranked
* @param finalRanks: the rank table
* @return: the string of the max recommended movie
*/
string RecommenderSystem::_getMaxMovieRanked(vector<pair<string, double>> &finalRanks)
{
	double max = -1;
	string s;
	for (auto &it:finalRanks)
	{
		if (it.second > max)
		{
			max = it.second;
			s = it.first;
		}
		else if (it.second == max)
		{
			s = _findFirst(it.first, s);
		}
	}
	return s;
}

/**
* a function to get the first out of two string movies in the _movieFeatures content
* @param s1: string 1
* @param s2: string 2
* @return: the first one which appears
*/
string RecommenderSystem::_findFirst(string &s1, string &s2)
{
	string s;
	for (auto &it:_moviesByOrder)
	{
		if (it == s1 || it == s2)
		{
			s = it;
			return s;
		}
	}
	return "none";
}

/**
* a function to recommend a movie to the user by picking the most predicted one
* @param userName: string of userName
* @param k: int k for the function predictMovieScoreForUser
* @return: a string of a movie
*/
string RecommenderSystem::recommendByCF(const string &userName, const int k)
{
	if (_userRanks.count(userName) <= ZERO)
	{
		return USER_ERROR;
	}

	unordered_map<string, double> personRanking; // the persons rankings
	vector<pair<string, double>> finalRanks; // what we will create

	personRanking = _userRanks[userName];

	for (auto &it: personRanking)
	{
		string movieName = it.first;
		if (it.second == ZERO)
		{
			double value = predictMovieScoreForUser(movieName, userName, k);
			finalRanks.emplace_back(pair(movieName, value));
		}
	}
	string s = _getMaxMovieRanked(finalRanks);
	return s;
}


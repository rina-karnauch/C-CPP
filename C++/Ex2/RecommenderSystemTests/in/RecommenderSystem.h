//
// Created by Rina Karnauch on 20/06/2020.
//

#ifndef EX2REWRITTEN_RECOMMENDERSYSTEM_H
#define EX2REWRITTEN_RECOMMENDERSYSTEM_H

#endif //EX2REWRITTEN_RECOMMENDERSYSTEM_H

// LIBS
#include <iostream>
#include <utility>
#include <iterator>
#include <unordered_map>
#include <vector>

// MACROS ETC'
#define NOTFOUND -1
#define ZERO 0
#define ONE 1
#ifndef EX2_RECOMMENDERSYSTEM_H
#define EX2_RECOMMENDERSYSTEM_H

#endif //EX2_RECOMMENDERSYSTEM_H

// USINGS:
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

/**
 * a class of the recommender system we made
 */
class RecommenderSystem
{
private:
	unordered_map<string, vector<double>> _movieFeatures; //map of :(movie name, (vector of
	// ratings))
	unordered_map<string, unordered_map<string, double>> _userRanks; //map of: (user name, (vector of
	// (movie:personal rating))
	vector<string> _moviesByOrder; //movies by order
	unordered_map<string, double> _movieNorms; //map of movieNorms
	int _featuresAmount;

	/**
	 * a function to build a pair of - (movie:ratings vector)
	 * @param line: the line we got from the file
	 * @return: the pair
	 */
	static pair<string, vector<double>> _movieVectorBuilder(const string &line);

	/**
	 * a function to read the line of movie names
	 * @param line
	 */
	void _movieNamesLine(const string &line);

	/**
	 * a function to build a pair of name and vector of personal ratings
	 * @param line: the line from the file
	 * @return: a pair of: (name, vector(double))
	 */
	pair<string, unordered_map<string, double>> _userInfoBuilder(
			string &line
																);

	/**
	 * a function to return the _resemblance between two vectors
	 * @param faves: vector of users ratings
	 * @return: the resemblance value
	 */
	double _resemblance(const vector<double> &faves, const string &movieName);

	/**
	 * a function to return the scalar multipication of 2 vectors
	 * @param rates: the vector rating features of the movie
	 * @param faves: the faves vector as we calculated it
	 * @return: the double scallar multipication
	 */
	static double _mulVectors(const vector<double> &rates, const vector<double> &faves);

	/**
	 * a function to calculate the norm of the vector
	 * @param vec: the vector
	 * @return: the norm
	 */
	static double _normVec(const vector<double> &vec);

	/**
	 * a function of comparison for the sort algorithem
	 * @param p1: 1st pair
	 * @param p2: 2nd pair
	 * @return: true for p1 is greater, false otherwise.
	 */
	friend bool _compare(const pair<string, double> &p1, const pair<string, double> &p2);

	/**
	 * a funcion to change the prediction vector and mul it.
	 * @param predicts: the vector of pairs of string and double - predicts accorations.
	 * @param ranks: the ranks the person gave for each movie
	 * @param k: the value int choosen to predict by
	 */
	static void
	_mulPredicts(vector<pair<string, double>> &predicts, const unordered_map<string, double> &ranks,
				 int k);

	/**
	* a function to sum two pairs
	* @param p1: pair 1
	* @param p2: pair 2
	* @return: their sum
	*/
	static double _sumPairs(const vector<pair<string, double>> &p, int k);


	/**
	 * a function to sum up values in the personRank map.
	 * @param rankings: the map of the personRank struct
	 * @return: sum- int.
	 */
	static double _avgValues(const unordered_map<string, double> &rankings);

	/**
	 * a function to change the norm of the person's rating vector
	 * @param personRates
	 */
	static void _normMap(unordered_map<string, double> &personRates, double avg);

	/**
	* a function to sum the avg'ed vectors
	* @param faves
	*/
	void _sumVectors(vector<double> &faves, unordered_map<string, double> &personRates);

	vector<double> _createVector(const unordered_map<string, double>
								 &userRanks);

	/**
	 * a function to handle the _resemblance of each movie to all the other movies someone has saw
	 * @param unrankedMovie
	 * @param k: int of how many we will choose and predict by it
	 * @return
	 */
	double _perdictMbyM(const string &unrankedMovie, const unordered_map<string, double> &userRanks,
						int k);

	/**
	 * a function to get the Max Movie Ranked
	 * @param finalRanks: the rank table
	 * @return: the string of the max recommended movie
	 */
	string _getMaxMovieRanked(vector<pair<string, double>> &finalRanks);


	/**
	 * a function to get the first out of two string movies in the _movieFeatures content
	 * @param s1: string 1
	 * @param s2: string 2
	 * @return: the first one which appears
	 */
	string _findFirst(string &s1, string &s2);

public:
	// C'TORS:
	/**
	 * constructor
	 */
	RecommenderSystem()
			: _movieFeatures(), _userRanks(), _moviesByOrder(), _movieNorms(),
			  _featuresAmount(ZERO)
	{};

	/**
	 * a function load the data in the files
	 * @param feats: string of path to the movieAttrributesFilePath
	 * @param ranks: string of path to the userRantsFilePath
	 * @return: 0 for success, -1 for failure
	 */
	int loadData(const string &feats, const string &ranks);


	/**
	 * a function to recommend by content to the username
	 * @param userName: string of username
	 * @return: string of recommended movie
	 */
	string recommendByContent(const string &userName);

	/**
	 * a function to predict movie score for user
	 * @param movieName: the movie name
	 * @param userName: the user name
	 * @param k: integer k, amount of movies
	 * @return
	 */
	double predictMovieScoreForUser(const string &movieName, const string &userName, int k);

	/**
	 * a function to recommend a movie to the user by picking the most predicted one
	 * @param userName: string of userName
	 * @param k: int k for the function predictMovieScoreForUser
	 * @return: a string of a movie
	 */
	string recommendByCF(const string &userName, int k);
};
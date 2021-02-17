//
// Created by Rina Karnauch on 06/08/2020.
//

#include <iostream>
#include <chrono>
#include <string>
#include "VLVector.hpp"
#include <algorithm>

using std::string;
using std::sort;

#include <ios>
#include <iostream>

using std::string;

// region The student class implementation

/**
 * \brief Describes a student.
 */
class Student
{
public:
	/**
	 * Default constructor (used with std::cin).
	 */
	Student() : _name(""), _average(0.0)
	{};

	/**
	 * Initializes a new student object.
	 * @param name The student full name.
	 * @param average The student grades average.
	 */
	Student(std::string const &name, double average) : _name(name), _average(average)
	{};

	/**
	 * Gets the student name.
	 * @return The student name.
	 */
	std::string getName() const
	{ return _name; }

	/**
	 * Gets the student grades average.
	 * @return The student average.
	 */
	double getAverage() const
	{ return _average; }


	bool operator==(const Student &other) const
	{
		return ((_average == other._average) && (_name == other._name));
	}

	bool operator!=(const Student &other) const
	{
		return ((_average != other._average) && (_name != other._name));
	}

	bool operator<(const Student &other) const
	{
		return ((_average < other._average));
	}

	Student &operator=(const Student &other)
	{
		if (&other != this)
		{
			_name = other._name;
			_average = other._average;
		}

		return *this;
	}


	friend std::istream &operator>>(std::istream &is, Student &s);

	friend std::ostream &operator<<(std::ostream &os, Student const &s);

private:
	/** \brief The student full name. */
	std::string _name;

	/** \brief The student grades average. */
	double _average;
};

/**
 * Reads a student object from the given stream.
 * @param is The stream object.
 * @param s The output student instance.
 * @return The modified input stream.
 */
std::istream &operator>>(std::istream &is, Student &s)
{
	std::string name;
	double average;

	is >> name >> average;

	s = Student(name, average);
	return is;
}

/**
 * Fills the given output stream with the information about the given student.
 * @param os The output stream.
 * @param s The student to write.
 * @return The modified output stream.
 */
std::ostream &operator<<(std::ostream &os, Student const &s)
{
	return os << s.getName() << " (average: " << s.getAverage() << ")";
}

// endregion
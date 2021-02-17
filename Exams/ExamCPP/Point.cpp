//
// Created by Rina Karnauch on 06/08/2020.
//

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;


class Point
{
private:
	int _x;
	int _y;

public:
	Point() : _x(0), _y(0)
	{};

	Point(int x, int y)
	{
		_x = x;
		_y = y;
	}

	int getX() const
	{ return _x; }

	int getY() const
	{ return _y; }

	/* Operator defined as member function is called on instance of the class. */
	bool operator==(const Point &rhs) const
	{

		return ((_x == rhs._x) && (_y == rhs._y));
		/* Your implementation goes here... */
	}

	// addition of another Point
	Point &operator+=(const Point &rhs)
	{
		// will allow שרשור
		_x += rhs._x;
		_y += rhs._y;
		return *this;
		/* Your implementation goes here... */
	}

	// addition of int
	Point &operator+=(const int val)
	{
		_x += val;
		_y += val;
		return *this;
		/* Your implementation goes here... */
	}

	// return -Point
	Point &operator-()
	{
		_x *= -1;
		_y *= -1;
		return *this;
		/* Your implementation goes here... */
	}


	// pre increment
	Point &operator++()
	{
		_x++;
		_y++;
		return *this;
		/* Your implementation goes here... */
	}

	// post increment
	Point operator++(int)
	{
		Point tmp = *this;

		_x++;
		_y++;

		return tmp;
		/* Your implementation goes here... */
	}


	/* const access version
	   Acceptable indices 0,1. Others can result in run-time error */
	// non-nonst access

	const int &operator[](const unsigned short coord) const
	{
		// check if coord!= 0,1
		if (coord == 0)
		{
			return _x;
		}
		else if (coord == 1)
		{
			return _y;
		}
		else
		{
			throw std::exception();
		}
		/* Your implementation goes here... */
	}

	int &operator[](const unsigned short coord)
	{
		// check if coord!= 0,1
		if (coord == 0)
		{
			return _x;
		}
		else if (coord == 1)
		{
			return _y;
		}
		else
		{
			throw std::exception();
		}
		/* Your implementation goes here... */
	}

	/* Friends */

	// Returns a Point that is the result of addition of two Points.
	friend Point operator+(const Point &p1, const Point &p2)
	{
		return Point(p1._x + p2._x, p1._y + p2._y);
		/* Your implementation goes here... */
	}

	//ככ Outputs coordinates delimited by single space.
	friend ostream &operator<<(ostream &s, const Point &p)
	{
		cout << "(" << p._x << "," << p._y << ")";
		return s;
		/* Your implementation goes here... */
	}

	// Inputs coordinates delimited by single space.
	friend Point &operator>>(istream &s, Point &p)
	{
		int x, y;
		cin >> x >> y;
		p._x = x;
		p._x = y;
		return p;
		/* Your implementation goes here... */
	}

/* Operator defined outside as non-member function */
	bool operator<(const Point &p2) const
	{
		cout << _x;
		int x1powed = (_x * _x);
		int y1powed = (_y * _y);
		int x2powed = (p2.getX()) * (p2.getX());
		int y2powed = (p2.getY()) * (p2.getY());

		if (x2powed + y2powed >= y1powed + x1powed)
		{
			return true;
		}
		return false;
		/* Your implementation goes here... */
	}

	bool operator<=(const Point &p2) const
	{
		int x1powed = (_x) * (_x);
		int y1powed = (_y) * (_y);
		int x2powed = (p2.getX()) * (p2.getX());
		int y2powed = (p2.getY()) * (p2.getY());

		if (x1powed + y1powed <= x2powed + y2powed)
		{
			return true;
		}
		return false;
	}

	bool operator>(const Point &p2) const
	{
		int x1powed = (_x) * (_x);
		int y1powed = (_y) * (_y);
		int x2powed = (p2.getX()) * (p2.getX());
		int y2powed = (p2.getY()) * (p2.getY());

		if (x1powed + y1powed > x2powed + y2powed)
		{
			return true;
		}
		return false;
	}

	bool operator>=(const Point &p2) const
	{
		int x1powed = (_x) * (_x);
		int y1powed = (_y) * (_y);
		int x2powed = (p2.getX()) * (p2.getX());
		int y2powed = (p2.getY()) * (p2.getY());

		if (x1powed + y1powed >= x2powed + y2powed)
		{
			return true;
		}
		return false;
	}


};






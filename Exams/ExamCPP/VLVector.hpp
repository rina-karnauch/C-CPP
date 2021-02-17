//
// Created by Rina Karnauch on 04/08/2020.
//

#ifndef VLVECTOR_VLVECTOR_HPP
#define VLVECTOR_VLVECTOR_HPP

// LIBS
#include <iostream>
#include <utility>
#include <iterator>
#include <exception>
#include <cmath>

// MACROS
#define ZERO 0
#define ONE 1
#define THREE 3
#define TWO 2

// USINGS:
using std::nothrow;
using std::exception;

using std::endl;
using std::copy;
using std::cout;
using std::cin;
using std::cerr;
using std::distance;

using std::begin;
using std::end;
using std::ostream;
using std::out_of_range;
using std::bad_alloc;
using std::iterator;

/**
 * a class of Virtual Length Vector we will implement
 */
template<typename T, int STATIC_CAPACITY = 16>
class VLVector
{
public:
	typedef T *iterator;
	typedef const T *const_iterator;
private:
	T _staticBlock[STATIC_CAPACITY]; // static block
	T *_dynamicBlock = nullptr; // dynamic block
	int _dynamicSize;
	int _staticSize;
	int _allSize;
	int _currentCap;


	/**
	 * a function to copy all values of v to VLVector
	 * @param v: the VLVector we copy from
	 */
	void _copyValues(const VLVector<T, STATIC_CAPACITY> &v)
	{
		if (v._allSize > STATIC_CAPACITY)
		{
			_dynamicBlock = new(nothrow) T[v._allSize];
			if (_dynamicBlock == nullptr)
			{
				throw bad_alloc();
			}

			for (int i = ZERO; i < v._allSize; i++)
			{
				_dynamicBlock[i] = v._dynamicBlock[i];
			}
		}
		else
		{
			for (int i = ZERO; i < v._allSize; i++)
			{
				_staticBlock[i] = v._staticBlock[i];
			}
		}
	}

	/**
	 * a function to calculate current CapC
	 * @tparam T: the type of elements in VLV
	 * @tparam StaticCapacity: max static Capacity
	 * @return: int of capC
	 */
	int _calcuCapC()
	{
		return (int) floor(THREE * (_allSize + ONE) / TWO);
	}

	/**
	 * a function to calculate current CapC
	 * @tparam T: the type of elements in VLV
	 * @tparam StaticCapacity: max static Capacity
	 * @return: int of capC
	 */
	int _calcuCapC(int newS)
	{
		return (int) floor(THREE * (newS / TWO));
	}

	/**
	 * a function to change the capacity
	 */
	void _changeCapC()
	{
		if (_allSize <= STATIC_CAPACITY)
		{
			_currentCap = STATIC_CAPACITY;
		}
		int capC = _calcuCapC();
		_currentCap = capC;
	}

	/**
	 * realloc helper functions- from static to dynamic
	 */
	void _moveToDynamic()
	{
		int newCap = _calcuCapC(); // we had 16, so we don't add one to _allSize, becuase now
		// have 16 values, and the formula is 3(16+1)/2 for just beyond 16.
		_dynamicBlock = new(nothrow) T[newCap];

		if (_dynamicBlock == nullptr)
		{ throw bad_alloc(); }

		for (int i = ZERO; i < STATIC_CAPACITY; i++)
		{
			_dynamicBlock[i] = _staticBlock[i];
			_staticBlock[i] = T();
		}

		_dynamicSize = STATIC_CAPACITY;
		_staticSize = ZERO;
		_changeCapC();
	}

	/**
	 * realloc helper functions- from dynamic to bigger dynamic
	 * @param newSize: the new amount of elements in the array - still no updated.
	 */
	void _reDynamic(const int &newSize)
	{
		int newCap = _calcuCapC(newSize);

		T *newDynamic = new(nothrow) T[newCap];

		if (_dynamicBlock == nullptr)
		{ throw bad_alloc(); }

		for (int i = ZERO; i < _allSize; i++)
		{
			newDynamic[i] = _dynamicBlock[i];
		}

		_dynamicBlock = newDynamic;
		// we haven't added elements yet so we dont update _dynamicSize
		// cap will be updated outside
	}

	/**
	 *  helper function to reallocate memory according to the needed size
	 * @param newSize: the new next size of the array
	 */
	void _realloc(const int &newSize)
	{
		// WE HAVEN'T ADDED ALLSIZE + 1 YET
		// we shall add it only outside of _realloc

		if (newSize - ONE == STATIC_CAPACITY) // from static to dynamic, first step
			// _allSize is the added value with the new element, before we could fit now we can't.
		{
			_moveToDynamic();
			return;
		}
		else if (newSize > _currentCap) // need to change the capacity, and accordingly to
			// reallocate, becuase _allSize new isthe new size we need to have and it's not enought.
		{
			_reDynamic(newSize);
			_changeCapC();
			return;
		}
		else if (newSize < STATIC_CAPACITY) // still static
		{
			return;
		}
	}


	template<class InputIterator>
	iterator _severalDynmHelper(int counter, int newSize, iterator t, InputIterator first)
	{

		int indexT = t - this->begin();
		InputIterator val = first;
		T *DynamicNew = new(nothrow) T[newSize];
		iterator begin = this->begin();
		iterator end = this->end();
		int index = ZERO;

		for (iterator i = begin; i < t; i++)
		{
			DynamicNew[index] = *i;
			index = index + ONE;
		}
		for (int k = ZERO; k < counter; k++)
		{
			DynamicNew[index] = *val;
			val = val + ONE;
			index = index + ONE;
		}
		for (iterator i = t; i < end; i++)
		{
			DynamicNew[index] = *i;
			index = index + ONE;
		}

		_dynamicBlock = DynamicNew;
		_dynamicSize = _dynamicSize + counter;
		_currentCap = newSize;
		_allSize = _dynamicSize;

		return (&(_dynamicBlock[indexT]));

	}

	template<class InputIterator>
	iterator _severalStaticToDynmHelper(int counter, int newSize, iterator t, InputIterator first)
	{
		_staticSize = ZERO;
		return _severalDynmHelper(counter, newSize, t, first);
	}


	template<class InputIterator>
	iterator _severalStaticHelper(int counter, int newSize, iterator t, InputIterator first)
	{
		int indexT = t - this->begin();
		int e = this->end() - this->begin();
		InputIterator val = first;
		for (int i = indexT + counter; i < e; i++)
		{
			_staticBlock[i] = _staticBlock[i - counter];
		}
		for (int i = indexT; i < indexT + counter; i++)
		{
			_staticBlock[i] = *val;
			val = val + ONE;
		}

		_allSize = _allSize + counter;
		_staticSize = _allSize;

		return (&(_staticBlock[indexT]));
	}

	/**
	 * insert2 helper
	 * @param newSize: new size of array after insertion
	 * @param t: the iterator
	 * @return: iterator to new place
	 */
	template<class InputIterator>
	iterator _reallocAfterSeverals(int counter, int newSize, iterator t, InputIterator first)
	{

		if (_allSize <= STATIC_CAPACITY && newSize > STATIC_CAPACITY)
		{
			return _severalStaticToDynmHelper(counter, newSize, t, first);
		}
		else if (_allSize <= STATIC_CAPACITY && newSize <= STATIC_CAPACITY)
		{
			return _severalStaticHelper(counter, newSize, t, first);
		}
		else // (_allSize > STATIC_CAPACITY && newSize > STATIC_CAPACITY)
		{
			return _severalDynmHelper(counter, newSize, t, first);
		}
	}

	/**
	 * insert2 helper
	 * @param newSize: new size of array after insertion
	 * @param t: the iterator
	 * @return: iterator to new place
	 */
	template<class InputIterator>
	const_iterator _reallocAfterSeverals(int counter, int newSize, const_iterator t,
										 InputIterator first)
	{

		if (_allSize <= STATIC_CAPACITY && newSize > STATIC_CAPACITY)
		{
			return _severalStaticToDynmHelper(counter, newSize, t, first);
		}
		else if (_allSize <= STATIC_CAPACITY && newSize <= STATIC_CAPACITY)
		{
			return _severalStaticHelper(counter, newSize, t, first);
		}
		else if (_allSize > STATIC_CAPACITY && newSize > STATIC_CAPACITY)
		{
			return _severalDynmHelper(counter, newSize, t, first);
		}
	}

	/**
	 * insert a value into a static array
	 * @param t: iterator to the position
	 * @param val: the value
	 * @return position of value after
	 */
	iterator _insert1IntoStatic(iterator t, T val)
	{
		// we have enough space to insert one another
		iterator i;
		iterator e = this->end();
		for (i = e; i > t; i--) // just moving the end
		{
			*i = *(i - ONE);
		}

		*t = val;
		_allSize += ONE;
		_staticSize += ONE;
		return t;
	}

	/**
	 * insert a value into a static array
	 * @param t: iterator to the position
	 * @param val: the value
	 * @return position of value after
	 */
	const_iterator _insert1IntoStatic(const_iterator t, T val)
	{
		// we have enough space to insert one another
		int indexT = t - this->begin();
		int e = this->end() - this->begin();
		for (int i = e; i > indexT; i--) // we just need to move the end
		{
			_staticBlock[i] = _staticBlock[i - ONE];
		}
		_staticBlock[indexT] = val;
		_staticSize += ONE;

		_allSize += ONE;
		return (const_iterator)(t);
	}

	/**
	 * insert a value from static to dynamic
	 * @param t: iterator to the position
	 * @param val: the value
	 * @return position of value after
	 */
	iterator _insert1FromDynmToStatic(iterator t, T val)
	{
		// adding one element will make the array dynamic
		int newCap = _calcuCapC();
		_dynamicBlock = new(nothrow) T[newCap];

		if (_dynamicBlock == nullptr)
		{
			throw bad_alloc();
		}

		int indexT = t - this->begin();
		int e = this->end() - this->begin();

		for (int i = ZERO; i < indexT; i++) // before the T value
		{
			_dynamicBlock[i] = _staticBlock[i];
			_staticBlock[i] = T();
		}

		_dynamicBlock[indexT] = val;

		for (int i = e; i >= indexT + ONE; i--) // after the value
		{
			_dynamicBlock[i] = _staticBlock[i - ONE];
		}

		_allSize += ONE;
		_dynamicSize = STATIC_CAPACITY + ONE;
		_staticSize = ZERO;
		_currentCap = newCap;

		return (&(_dynamicBlock[indexT]));
	}

	/**
	 * insert a value from static to dynamic
	 * @param t: iterator to the position
	 * @param val: the value
	 * @return position of value after
	 */
	const_iterator _insert1FromDynmToStatic(const_iterator t, T val)
	{
		// adding one element will make the array dynamic
		int newCap = _calcuCapC();
		_dynamicBlock = new(nothrow) T[newCap];

		int indexT = t - this->begin();
		int e = this->end() - this->begin();

		for (int i = ZERO; i < indexT; i++)
		{
			_dynamicBlock[i] = _staticBlock[i];
			_staticBlock[i] = T();
		}

		_dynamicBlock[indexT] = val;

		for (int i = e; i > indexT; i--)
		{
			_dynamicBlock[i] = _staticBlock[i - ONE];
		}

		_allSize += ONE;
		_dynamicSize = STATIC_CAPACITY + ONE;
		_staticSize = ZERO;
		_currentCap = newCap;

		return (&(_dynamicBlock[indexT]));
	}


	/**
	 * helper function to change cap and move the elements
	 * @param t: iterator to where we put it
	 * @param val: the value we put
	 * @return
	 */
	iterator _insert1CapDynm(iterator t, T val, const int newCap)
	{
		// we move everything to a dynamic array
		T *DynamicNew = new(nothrow) T[newCap];
		if (DynamicNew == nullptr)
		{
			throw bad_alloc();
		}

		int e = this->end() - this->begin();
		int indexT = t - this->begin();

		for (int i = ZERO; i < indexT; i++) //from begin to t
		{
			DynamicNew[i] = _dynamicBlock[i];
		}

		DynamicNew[indexT] = val;

		for (int i = e; i > indexT; i--) // from end to t
		{
			DynamicNew[i] = _dynamicBlock[i - ONE];
		}

		for (int i = ZERO; i < e + ONE; i++)
		{
			_dynamicBlock[i] = DynamicNew[i];
		}

		_currentCap = newCap;
		_allSize += ONE;
		_dynamicSize += ONE;
		return (&(_dynamicBlock[indexT]));
	}

	/**
	 * helper function to change cap and move the elements
	 * @param t: iterator to where we put it
	 * @param val: the value we put
	 * @return
	 */
	const_iterator _insert1CapDynm(const_iterator t, T val, const int newCap)
	{
		// we move everything to a dynamic array
		T *DynamicNew = new(nothrow) T[newCap];
		if (DynamicNew == nullptr)
		{
			throw bad_alloc();
		}

		int e = this->end() - this->begin();
		int indexT = t - this->begin();

		for (int i = ZERO; i < indexT; i++) //from begin to t
		{
			DynamicNew[i] = _dynamicBlock[i];
		}

		DynamicNew[indexT] = val;

		for (int i = e; i > indexT; i--) // from end to t
		{
			DynamicNew[i] = _dynamicBlock[i - ONE];
		}

		for (int i = ZERO; i < e + ONE; i++)
		{
			_dynamicBlock[i] = DynamicNew[i];
		}

		_currentCap = newCap;
		_allSize += ONE;
		_dynamicSize += ONE;
		return (&(_dynamicBlock[indexT]));
	}

	/**
	 * a helper function to move the elements in the dynamic array
	 * @param t: iterator to where we put it
	 * @param val: the value we put
	 * @return
	 */
	iterator _insert1NoCapDynm(iterator t, T val)
	{
		// we insert with no need to modify
		int e = this->end() - this->begin();
		int indexT = t - this->begin();

		for (int i = e; i > indexT; i--) // JUST CHANGE FROM END
		{
			_dynamicBlock[i] = _dynamicBlock[i - ONE];
		}

		_dynamicBlock[indexT] = val; // needed value in place t

		_allSize += ONE;
		_dynamicSize += ONE;
		return (&(_dynamicBlock[indexT]));
	}

	/**
	 * a helper function to move the elements in the dynamic array
	 * @param t: iterator to where we put it
	 * @param val: the value we put
	 * @return
	 */
	const_iterator _insert1NoCapDynm(const_iterator t, T val)
	{
		int e = this->end() - this->begin();
		int indexT = t - this->begin();

		for (int i = e; i > indexT; i--) // JUST CHANGE FROM END
		{
			_dynamicBlock[i] = _dynamicBlock[i - ONE];
		}

		_dynamicBlock[indexT] = val; // needed value in place t

		_allSize += ONE;
		_dynamicSize += ONE;
		return (&(_dynamicBlock[indexT]));
	}

	/**
	 * insert a value from dynamic to dynamic
	 * @param t: iterator to the position
	 * @param val: the value
	 * @return position of value after
	 */
	iterator _insert1IntoDynamic(iterator t, T val)
	{
		// the array is dynamic, we might need to make it bigger
		if (_allSize + ONE > _currentCap)
		{
			int newCap = _calcuCapC(_allSize + ONE);
			return _insert1CapDynm(t, val, newCap);
		}
		else
		{
			return _insert1NoCapDynm(t, val);
		}
	}

	/**
	 * insert a value from dynamic to dynamic
	 * @param t: iterator to the position
	 * @param val: the value
	 * @return position of value after
	 */
	const_iterator _insert1IntoDynamic(const_iterator t, T val)
	{

		// the array is dynamic, we might need to make it bigger
		int newCap = _calcuCapC(_allSize + ONE);
		if (_currentCap < newCap || _allSize + ONE < _currentCap)
		{
			return _insert1CapDynm(t, val, newCap);
		}
		else
		{
			return _insert1NoCapDynm(t, val);
		}

	}

	/**
	 * pop_back helper, which moves the dynamic array to static
	 */
	void _dynmToStaticReallocAndPop()
	{
		for (int i = ZERO; i < STATIC_CAPACITY; i++)
		{
			_staticBlock[i] = _dynamicBlock[i];
			_dynamicBlock[i] = T();
		}

		delete (_dynamicBlock);
		_allSize = _allSize - ONE;
		_staticSize = _allSize;
		_dynamicSize = ZERO;
		_changeCapC();
	}

	/**
	 * erase helper function from dynamic to Static case
	 * @param t: iterator to erase
	 * @return: iterator to t's new place
	 */
	iterator _erase2MoveToStatic(iterator t)
	{
		int indexT = t - this->begin();
		for (int i = ZERO; i < indexT; i++)
		{
			_staticBlock[i] = _dynamicBlock[i];
		}
		for (int i = indexT; i < STATIC_CAPACITY; i++)
		{
			_staticBlock[i] = _dynamicBlock[i + ONE]; // we need to delete the index T
		}

		_dynamicSize = ZERO;
		_staticSize = _allSize - ONE;
		_allSize = _allSize - ONE;
		_currentCap = STATIC_CAPACITY;

		return (&(_staticBlock[indexT]));
	}

	/**
	 * erase helper function from dynamic to Static case
	 * @param t: iterator to erase
	 * @return: iterator to t's new place
	 */
	const_iterator _erase2MoveToStatic(const_iterator t)
	{
		int indexT = t - this->begin();
		for (int i = ZERO; i < indexT; i++)
		{
			_staticBlock[i] = _dynamicBlock[i];
		}
		for (int i = indexT; i < STATIC_CAPACITY; i++)
		{
			_staticBlock[i] = _dynamicBlock[i + ONE]; // we need to delete the index T
		}

		delete[] _dynamicBlock;
		_dynamicSize = ZERO;
		_staticSize = _allSize - ONE;
		_allSize = _allSize - ONE;
		_currentCap = STATIC_CAPACITY;

		return (&(_staticBlock[indexT]));
	}

	/**
	 * erase helper function to move values to the left index near them
	 * @param t: value to start from we delete
	 * @return: iterator to t's new
	 */
	iterator _eraseHelper(iterator t)
	{
		int indexT = t - this->begin();
		int e = this->end() - this->begin();
		if (_allSize > STATIC_CAPACITY)
		{
			for (int k = indexT; k < e - ONE; k++)
			{
				_dynamicBlock[k] = _dynamicBlock[k + ONE];
			}
			_dynamicBlock[e - ONE] = T();
		}
		else
		{
			for (int i = indexT; i < e - ONE; i++)
			{
				_staticBlock[i] = _staticBlock[i + ONE];
			}
			_staticBlock[e - ONE] = T();
		}

		*(this->end()) = T();
		if (_allSize > STATIC_CAPACITY)
		{
			return &(_dynamicBlock[indexT]);
		}
		return (&_staticBlock[indexT]);
	}

	/**
	 * const erase helper function to move values to the left index near them
	 * @param t: value to start from we delete
	 * @return: iterator to t's new
	 */
	const_iterator _eraseHelper(const_iterator t)
	{
		int indexT = t - this->begin();
		int e = this->end() - this->begin();
		if (_allSize > STATIC_CAPACITY)
		{
			for (int k = indexT; k < e - ONE; k++)
			{
				_dynamicBlock[k] = _dynamicBlock[k + ONE];
			}
			_dynamicBlock[e - ONE] = T();
		}
		else
		{
			for (int i = indexT; i < e - ONE; i++)
			{
				_staticBlock[i] = _staticBlock[i + ONE];
			}
			_staticBlock[e - ONE] = T();
		}

		*(this->end()) = T();
		if (_allSize > STATIC_CAPACITY)
		{
			return &(_dynamicBlock[indexT]);
		}
		return (&_staticBlock[indexT]);
	}

public:
	/**
	 * constructor
	 */
	// CTORS:
	VLVector() : _staticBlock(), _dynamicBlock(nullptr), _dynamicSize(ZERO),
				 _staticSize(ZERO),
				 _allSize(ZERO), _currentCap(STATIC_CAPACITY)
	{};

	/**
	 * destructor
	 */
	~VLVector()
	{
		// delete[] _staticBlock;
		if (_dynamicSize > ZERO)
		{
			delete[] _dynamicBlock;
		}
		_allSize = ZERO;
		_dynamicSize = ZERO;
		_staticSize = ZERO;
	}

	/**
	 * copy constructor
	 * @param v: previous vector we are copying
	 */
	VLVector(const VLVector<T, STATIC_CAPACITY> &v)
	{
		_allSize = v._allSize;
		_dynamicSize = v._dynamicSize;
		_staticSize = v._staticSize;
		_currentCap = v._currentCap;
		_copyValues(v);
	}

	/**
	 * a constructor out of a range
	 * @param first: first iterator for T element
	 * @param last: last iterator for T element
	 */
	template<class InputIterator>
	VLVector(InputIterator first, InputIterator last)
	{
		InputIterator myIter;
		_dynamicBlock = nullptr;
		_allSize = ZERO;
		_dynamicSize = ZERO;
		_staticSize = ZERO;
		_currentCap = STATIC_CAPACITY;
		for (myIter = first; myIter < last; myIter++)
		{
			T newValue = T(*myIter);
			push_back(newValue); // values updated inside
		}
	}

	/**
	 * a function to create an iterator for the start of our class object
	 * @return begin iterator
	 */
	iterator begin()
	{
		if (_allSize <= STATIC_CAPACITY) // we don't have enough to send _dynamicBlock
		{
			return &(_staticBlock[ZERO]);
		}
		return &(_dynamicBlock[ZERO]);
	}

	/**
	 * cbegin functions
	 * @return
	 */
	const_iterator cbegin() const
	{
		if (_allSize <= STATIC_CAPACITY) // we don't have enough to send _dynamicBlock
		{
			return &(_staticBlock[ZERO]);
		}
		return &(_dynamicBlock[ZERO]);
	}

	/**
	 * a function to create a const iterator for the start of our class object
	 * @return const begin iterator
	 */
	const_iterator begin() const
	{
		if (_allSize <= STATIC_CAPACITY) // we don't have enough to send _dynamicBlock
		{
			return &(_staticBlock[ZERO]);
		}
		return &(_dynamicBlock[ZERO]);
	}

	/**
	 * a function to create an iterator for the end of our class object
	 * @return end iterator
	 */
	iterator end()
	{
		if (_allSize <= STATIC_CAPACITY) // we don't have enough to send _dynamicBlock
		{
			return &(_staticBlock[_allSize]);
		}
		return &(_dynamicBlock[_allSize]);
	}

	/**
	 * a function to create an iterator which is const for the end of our class object
	 * @return: const end iterator
	 */
	const_iterator end() const
	{
		if (_allSize <= STATIC_CAPACITY) // we don't have enough to send _dynamicBlock
		{
			return &(_staticBlock[_allSize]);
		}
		return &(_dynamicBlock[_allSize]);
	}

	const_iterator cend() const
	{
		if (_allSize <= STATIC_CAPACITY) // we don't have enough to send _dynamicBlock
		{
			return &(_staticBlock[_allSize]);
		}
		return &(_dynamicBlock[_allSize]);
	}

	//functions:
	/**
	 * a function to get the vector overall size
	 * @return: size_t size value
	 */
	size_t size()
	{
		return _allSize;
	}


	/**
	 * a function to calculate the capacity of the current vector
	 * @return
	 */
	size_t capacity()
	{
		return _currentCap;
	}

	/**
	 * empty checher
	 * @return: true for empty, false for none empty
	 */
	bool empty()
	{
		if (_allSize == ZERO)
		{
			return true;
		}
		return false;
	}

	/**
	 * function to know what is in the VLV in index i
	 * @param index: index of place we want
	 * @return: exception when index is out of range, otherwise T object.
	 */
	T &at(const size_t index)
	{
		if ((int) index >= _allSize || index < ZERO)
		{
			throw out_of_range("Out Of Bounds Error");
		}

		if (_allSize > STATIC_CAPACITY)
		{
			return _dynamicBlock[(int) index];
		}
		return _staticBlock[(int) index];
	}

	/**
	 * a function to add an element at the end of the array
	 * @param t: the T value we are adding at the end
	 */
	void push_back(T value)
	{
		_realloc(_allSize + ONE);
		if ( _allSize >= STATIC_CAPACITY)
		{
			_dynamicBlock[_allSize] = value;
			_dynamicSize = _dynamicSize + ONE;
		}
		else // _allSize < STATIC_CAPACITY // we don't have enough to send _dynamicBlock
		{
			_staticBlock[_allSize] = value;
			_staticSize = _staticSize + ONE;
		}

		_allSize = _allSize + ONE;
	}

	/**
	 * a function to insert val where t is
	 * @param t: position
	 * @param val: value to insert
	 * @return: the current position of val
	 */
	iterator insert(iterator t, T val)
	{
		if (_allSize + ONE <= STATIC_CAPACITY)
		{
			return _insert1IntoStatic(t, val); // insert inside a static, we have more space
		}
		else if (_allSize == STATIC_CAPACITY) // need to realloc to dynamic
		{
			return _insert1FromDynmToStatic(t, val);
		}
		else
		{
			return _insert1IntoDynamic(t, val);
		}
	}

	/**
	 * a function to insert val where t is
	 * @param t: position
	 * @param val: value to insert
	 * @return: the current position of val
	 */
	const_iterator insert(const_iterator t, T val)
	{
		if (_allSize + ONE <= STATIC_CAPACITY)
		{
			return _insert1IntoStatic(t, val); // insert inside a static
		}
		else if (_allSize == STATIC_CAPACITY)
		{
			return _insert1FromDynmToStatic(t, val);
		}
		else
		{
			return _insert1IntoDynamic(t, val);
		}
	}

	/**
	 * a function to insert several values inside our bunch of values
	 * @tparam InputIterator: input iterator to the value we insert
	 * @param p: our place we put it before position
	 * @param first: the first of input iterator
	 * @param last: the last of input iterator
	 * @return: iterator to the new value last added
	 */
	template<class InputIterator>
	iterator insert(iterator p, InputIterator first, InputIterator last)
	{
		int prevSize = _allSize;
		int counter = 0;
		InputIterator i = first;
		while (i < last)
		{
			counter = counter + ONE;
			i = i + ONE;
		}

		int newCap = _calcuCapC(prevSize + counter);
		return _reallocAfterSeverals(counter, newCap, p, first);
	}

	/**
	 * a function to insert several values inside our bunch of values
	 * @tparam InputIterator: input iterator to the value we insert
	 * @param p: our place we put it before position
	 * @param first: the first of input iterator
	 * @param last: the last of input iterator
	 * @return: iterator to the new value last added
	 */
	template<class InputIterator>
	const_iterator insert(const_iterator p, InputIterator first, InputIterator last)
	{

		int prevSize = _allSize;
		int counter = 0;
		InputIterator i = first;
		while (i < last)
		{
			counter++;
			i++;
		}

		int newCap = _calcuCapC(prevSize + counter);
		return _reallocAfterSeverals(counter, newCap, p, first);
	}

	void pop_back()
	{
		if (_allSize == ZERO)
		{
			return;
		}
		else if (_allSize - ONE == STATIC_CAPACITY) // making it smaller needs to be reallocated to
			// the
			// static memory
		{
			_dynmToStaticReallocAndPop();
		}
			// elseway we don't change the CAPC VALUE
		else if (_allSize - ONE < STATIC_CAPACITY)
		{
			_staticBlock[_allSize - ONE] = T();
			_allSize = _allSize - ONE;
			_staticSize = _staticSize - ONE;

		}
		else if ( _allSize - ONE > STATIC_CAPACITY) // no cap evaluation
		{
			_dynamicBlock[_allSize - ONE] = T();
			_dynamicSize = _dynamicSize - ONE;
			_allSize = _allSize - ONE;
		}
		else if (_allSize == ZERO)
		{
			return;
		}
	}

	/**
	 * a function to erase the value we point on
	 * @param t: the iterator
	 * @return: iterator to the new value inside t
	 */
	iterator erase(iterator t)
	{
		if (_allSize - ONE == STATIC_CAPACITY) // re move it to the static part
		{
			return _erase2MoveToStatic(t);
		}
		else
		{
			iterator back = _eraseHelper(t);
			if (_allSize - ONE < STATIC_CAPACITY)
			{
				_allSize = _allSize - ONE;
				_staticSize = _staticSize - ONE;
			}
			else if (_allSize - ONE > STATIC_CAPACITY)
			{
				_allSize = _allSize - ONE;
				_dynamicSize = _dynamicSize - ONE;
			}
			return back;
		}
	}

	/**
	 * a function to erase the value we point on
	 * @param t: the iterator
	 * @return: iterator to the new value inside t
	 */
	const_iterator erase(const_iterator t)
	{
		if (_allSize - ONE == STATIC_CAPACITY) // re move it to the static part
		{
			return _erase2MoveToStatic(t);
		}
		else
		{
			const_iterator back = _eraseHelper(t);
			if (_allSize - ONE < STATIC_CAPACITY)
			{
				_allSize = _allSize - ONE;
				_staticSize = _staticSize - ONE;
			}
			else if (_allSize - ONE > STATIC_CAPACITY)
			{
				_allSize = _allSize - ONE;
				_dynamicSize = _dynamicSize - ONE;
			}
			return back;
		}
	}

	/**
	 * erase from first to last without last
	 * @param firt: first to erase
	 * @param last: last to erase
	 * @return: lasts new place
	 */
	iterator erase(iterator first, iterator last)
	{
		int indexB = first - this->begin();
		iterator i = first;
		iterator k = first;
		while (i < last)
		{
			k = erase(k);
			i = i + ONE;
		}

		if (_allSize > STATIC_CAPACITY)
		{
			return &(_dynamicBlock[indexB]);
		}
		return &(_staticBlock[indexB]);
	}

	/**
	 * erase from first to last without last- const
	 * @param firt: first to erase
	 * @param last: last to erase
	 * @return: lasts new place
	 */
	const iterator erase(const_iterator first, const_iterator last)
	{
		int indexB = first - this->begin();
		const_iterator i = first;
		const_iterator k = first;
		while (i < last)
		{
			k = erase(k);
			i = i + ONE;
		}

		if (_allSize > STATIC_CAPACITY)
		{
			return &(_dynamicBlock[indexB]);
		}
		return &(_staticBlock[indexB]);
	}


	/**
	 * a function to clear all the vector elements
	 */
	void clear()
	{
		int k = _allSize;
		for (int i = ZERO; i < k; i++)
		{
			pop_back();
		}
	}

	/**
	 * a function which returns the data type we are holding
	 * @return: pointer to T data type
	 */
	T *data()
	{
		if (_allSize > STATIC_CAPACITY)
		{
			return _dynamicBlock;
		}
		return _staticBlock;
	}

	/**
	 * a function to get a subscript out of the array in index i
	 * @param i: index
	 * @return: the element inside
	 */
	T &operator[](const int i)
	{
		if (_allSize > STATIC_CAPACITY)
		{
			return _dynamicBlock[i];
		}
		return _staticBlock[i];
	}

	/**
	 * a const function to get a subscript out of the array in index i
	 * @param i: index
	 * @return: the element inside
	 */
	const T &operator[](const int i) const
	{
		if (_allSize > STATIC_CAPACITY)
		{
			return _dynamicBlock[i];
		}
		return _staticBlock[i];
	}

	/**
	 * opertator == for two VLV's
	 * @param rhs: right side VLV
	 * @return true upon same false otherwise
	 */
	bool operator==(const VLVector &rhs)
	{
		if (_allSize != rhs._allSize)
		{
			return false;
		}
		else if (_allSize > STATIC_CAPACITY)
		{
			for (int i = ZERO; i < _allSize; i++)
			{
				if (!(rhs[i] == _dynamicBlock[i]))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			for (int i = ZERO; i < _allSize; i++)
			{
				if (!(rhs[i] == _staticBlock[i]))
				{
					return false;
				}
			}
			return true;
		}
	}

	/**
	 * operator != to make sure if two VLVS are different
	 * @param rhs: right hand VLV
	 * @return
	 */
	bool operator!=(const VLVector &rhs)
	{
		return (!(*(this) == rhs));
	}

};

#endif //VLVECTOR_VLVECTOR_HPP

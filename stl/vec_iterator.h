#ifndef VEC_ITERATOR_H
#define VEC_ITERATOR_H

#include "my_iterator.h"
#include <algorithm>

namespace mystl {

template <typename T>
class VecIterator: public iterator<random_access_iterator_tag,
										T,
										ptrdiff_t,
										T*,
										T&>
{
public:
	VecIterator(T* ptr = nullptr): m_ptr(ptr) { }
	VecIterator(const VecIterator<T>& rhs) = default;
	~VecIterator() { }

	operator bool() const
	{
		if (m_ptr)
			return true;
		else
			return false;
	}
	
	const T* getConstPtr() const
	{
		return m_ptr;
	}
	
	VecIterator<T>& operator+=(const ptrdiff_t& i)
	{
		m_ptr += i;
		return *this;
	}
	VecIterator<T>& operator-=(const ptrdiff_t& i)
	{
		m_ptr -= i;
		return *this;
	}
	
	VecIterator<T>& operator++()
	{
		++m_ptr;
		return *this;
	}
	VecIterator<T> operator++(int)
	{
		auto tmp(*this);
		++m_ptr;
		return tmp;
	}
	VecIterator<T>& operator--()
	{
		--m_ptr;
		return *this;
	}
	VecIterator<T> operator--(int)
	{
		auto tmp(*this);
		--m_ptr;
		return tmp;
	}
	
	T& operator[](size_t pos)
	{
		return *(*this + pos);
	}
	
	T& operator*()
	{
		return *m_ptr;
	}
	const T& operator*() const
	{
		return *m_ptr;
	}
	T* operator->()
	{
		return m_ptr;
	}
private:
	T* m_ptr;
};

template <typename T>
VecIterator<T> operator+(const VecIterator<T>& lhs,
							const ptrdiff_t& i)
{
	return (lhs + i);
}

template <typename T>
VecIterator<T> operator+(const ptrdiff_t& i,
                            const VecIterator<T>& rhs)
{
	return (rhs + i);
}

template <typename T>
VecIterator<T> operator-(const VecIterator<T>& lhs,
							const ptrdiff_t& i)
{
	return (lhs - i);
}

template <typename T>
ptrdiff_t operator-(const VecIterator<T>& lhs,
                    const VecIterator<T>& rhs)
{
	return std::distance(rhs.getConstPtr(), lhs.getConstPtr());
}

template <typename T>
bool operator==(const VecIterator<T>& lhs,
                const VecIterator<T>& rhs)
{
	return lhs.getConstPtr() == rhs.getConstPtr();
}

template <typename T>
bool operator!=(const VecIterator<T>& lhs,
                const VecIterator<T>& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
bool operator<(const VecIterator<T>& lhs,
               const VecIterator<T>& rhs)
{
	return rhs - lhs > 0;
}

template <typename T>
bool operator>(const VecIterator<T>& lhs,
               const VecIterator<T>& rhs)
{
	return rhs < lhs;
}

template <typename T>
bool operator<=(const VecIterator<T>& lhs,
                const VecIterator<T>& rhs)
{
	return !(lhs > rhs);
}

template <typename T>
bool operator>=(const VecIterator<T>& lhs,
                const VecIterator<T>& rhs)
{
	return !(lhs < rhs);
}

}

#endif
